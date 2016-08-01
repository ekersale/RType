/***********************************************************************
 * Module:  AUnix.cpp
 * Author:  urvoy_p
 * Modified: Monday, October 20, 2014 4:23:13 PM
 * Purpose: Implementation of the class AUnix
 ***********************************************************************/

#include        <ScopedLock.hh>
#include		<string.h>
#include        <iostream>
#include		"Network.hh"

bool			Network::createSocket(std::string proto, int &type)
{
  struct protoent       *pe;
  ClientInfo		*current;

  if (_connected.find(0) != _connected.end())
    return (false);
  if (!(current = (new ClientInfo(_len))))
    return (false);
  if (!(pe = getprotobyname(proto.c_str())))
    return (false);
  if ((current->get_socket() = socket(_family, type, pe->p_proto)) == -1)
    {
      delete current;
      return (false);
    }
  _connected[++_id] = current; //stockage de la socket
  return (true);
}

void			Network::sflush(void)
{
  ScopedLock    lock(_safe);
  int			id = -1;

  while (++id < (int)_connected.size())
    closeSocket(id);
}

void			Network::closeSocket(int id)
{
  if (!is_connected(id))
    return ;
  if (id != 0)
    {
      closesocket(_connected[id]->get_socket());
      delete _connected[id];
      _connected.erase(id);
      _change = true;
    }
}

ClientInfo *		Network::maxSocket(void)
{
  std::map<int, ClientInfo *>::iterator it;
  static ClientInfo *	max = get_connected(0);

  if (_connected.size() == 1)
    return (get_connected(0));
  if (_change == true)
    {
      max = get_connected(0);
      for (it = _connected.begin(); it != _connected.end(); it++)
	if (max->get_socket() < it->second->get_socket())
	  max = it->second;
      _change = false;
    }
  return (max);
}

bool			Network::bindSocket(std::string port)
{
  get_connected(0)->setAddr(_family, port.c_str(), ""); //set addr SERVER, NULL car serveur
  if (bind(get_connected(0)->get_socket(), (saddr *)(&(get_connected(0)->get_info())), sizeof(saddrin)) < 0)
    return (false);
  return (true);
}

char *&			Network::get_buffer(int id)
{
  return (get_connected(id)->get_buffer());
}

int&			Network::get_filled(int id)
{
  return (get_connected(id)->get_filled());
}

ClientInfo *		Network::get_connected(int id)
{
  ScopedLock        lock(_safe);

  if (_connected.find(id) == _connected.end())
    return (NULL);
  return (_connected[id]);
}

void		Network::new_connected(int id, ClientInfo *client)
{
  ScopedLock        lock(_safe);

  _connected[id] = client;
}

bool        Network::is_connected(int id)
{
  ScopedLock        lock(_safe);

  if (_connected.find(id) == _connected.end())
    return (false);
  return true;
}

unsigned long        Network::connectedSize()
{
  ScopedLock        lock(_safe);

  return (_connected.size());
}

/* * * */
/* TCP */
/* * * */
bool			Network::listenSocket(int number)
{
  if (listen(get_connected(0)->get_socket(), number) < 0)
    return (false);
  return (true);
}

int			Network::acceptSocket(void)
{
  int		socklen;
  ClientInfo		*stranger = new ClientInfo(_len);

  if (!stranger)
    return (0);
  socklen = sizeof(saddrin);
  if ((stranger->get_socket() = accept(get_connected(0)->get_socket(), (saddr *)&(stranger->get_info()), &socklen)) < 0)
  {
    delete stranger;
    return (0);
  }
  new_connected(++_id, stranger);
  _change = true;
  return (_id);
}

int			Network::connectSocket(std::string host, std::string port)
{
  struct protoent       *pe;
  ClientInfo		*stranger = new ClientInfo(_len);

  if (!stranger)
    return (0);
  if (!(pe = getprotobyname("TCP")))
    return (0);
  stranger->setAddr(_family, port.c_str(), host.c_str()); //prépare la connexion tcp vers un serveur
  if ((stranger->get_socket() = socket(_family, SOCK_STREAM, pe->p_proto)) == -1)
    return (0);
  if (connect(stranger->get_socket(), (saddr *)(&stranger->get_info()), sizeof(saddrin)) < 0)
  {
    closesocket(stranger->get_socket());
    delete stranger;
    return (0);
  }
  new_connected(++_id, stranger);
  _change = true;
  return (_id);
}

bool			Network::recvSocket(int id)
{
  int			len;

  if (!is_connected(id))
    return (false);
  len = recv(get_connected(id)->get_socket(), get_connected(0)->get_buffer(), get_connected(0)->get_len(), 0);
  if (len < 1)
    {
      closeSocket(id);
      get_connected(0)->get_buffer()[0] = 0;
      return (false);
    }
  get_connected(0)->get_filled() = len;
  return (true);
}

bool			Network::sendSocket(int id, void *buff, size_t len)
{
  if (!is_connected(id))
    return (false);
  if (send(_connected[id]->get_socket(), reinterpret_cast<char *>(buff), len, 0) < 0)
    {
      closeSocket(id);
      get_connected(0)->get_buffer()[0] = 0;
      return (false);
    }
  return (true);
}

/* * * */
/* UDP */
/* * * */
int			Network::connectToSocket(std::string host, std::string port)
{
  ClientInfo		*stranger = new ClientInfo(_len);

  if (!stranger)
    return (false);
  stranger->setAddr(AF_INET, port.c_str(), host.c_str()); //prépare la connexion udp vers un serveur
  new_connected(++_id, stranger);
  return (_id);
}

bool			Network::sendToSocket(int id, void *buff, size_t len)
{
  if (!is_connected(id))
    return (false);
  if (sendto(get_connected(0)->get_socket(), reinterpret_cast<char *>(buff), len, 0, (saddr *)(&(get_connected(id)->get_info())), (int)sizeof(saddrin)) < 0) //envoie
    {
      closeSocket(id);
      get_connected(0)->get_buffer()[0] = 0;
      return (false);
    }
  return (true);
}

int			Network::UDPDuplicate(ClientInfo *stranger, int &id)
{
  id = -1;

  while (++id < (int)connectedSize())
    if (memcmp(&get_connected(id)->get_info(), &stranger->get_info(), sizeof(saddrin)) == 0)
      return (true);
  return (false);
}

int			Network::recvFromSocket(void)
{
  int			len;
  int			id;
  int			socklen;
  static ClientInfo	stranger(1);
  ClientInfo		*nstranger;

  socklen = sizeof(saddrin); //bullshit
  len = recvfrom(get_connected(0)->get_socket(), get_connected(0)->get_buffer(),
		 get_connected(0)->get_len(), 0, (saddr *)&stranger.get_info(), &socklen);
  if (len < 1)
    {
      get_connected(0)->get_buffer()[0] = 0;
      return (false);
    }
  get_connected(0)->get_filled() = len;
  if (UDPDuplicate(&stranger, id)) // verificationd des duplicats
    return (id);
  if (!(nstranger = new ClientInfo(_len)))
    return (false);
  nstranger->get_info() = stranger.get_info();
  new_connected(++_id, nstranger); // en udp c'est le rcv qui dit qui vient de se connecter, on stocke ca
  return (_id);
}

Network::Network(int family, int type, std::string proto, size_t len)
{
  WSADATA		wsaData;

  _family = family;
  _id = -1;
  _len = len;
  _change = true;
  _safe = new Mutex();
  WSAStartup(MAKEWORD(2, 2), &wsaData);
  createSocket(proto, type);
}

Network::Network(const Network& oldNetwork)
{
  (void)oldNetwork;
}

Network::~Network()
{
  sflush();
  WSACleanup();
}
