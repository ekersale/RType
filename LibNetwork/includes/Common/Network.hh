/***********************************************************************
 * Module:  Network.h
 * Author:  urvoy_p
 * Modified: Monday, October 20, 2014 4:23:13 PM
 * Purpose: Declaration of the class Network
 **********************************************************************
*/

#if !defined(__Network_hh)
#define __Network_hh

#include    "Mutex.hh"
#include	"INetwork.hh"
#ifdef		_WIN32
#include	"WClientInfo.hh"
#else
#include	"UClientInfo.hh"
#endif
#include	<map>
#include	<vector>

class Network : public INetwork
{
public:
  bool		    bindSocket(std::string);
  void		    closeSocket(int);
  bool		    createSocket(std::string, int &);
  char *&	    get_buffer(int id = 0);
  int &		    get_filled(int id = 0);
  ClientInfo *	get_connected(int id = 0);
  void          new_connected(int id, ClientInfo *);
  bool          is_connected(int id);
  unsigned long connectedSize();
  ClientInfo *	maxSocket(void);
  void		    sflush(void);
  //tronc commun
  
  bool		listenSocket(int);
  int		acceptSocket(void);
  int		connectSocket(std::string, std::string);
  bool		recvSocket(int);
  bool		sendSocket(int , void *, size_t);
  //tcp
  
  int		connectToSocket(std::string, std::string);
  bool		sendToSocket(int, void *, size_t);
  int		recvFromSocket(void);
  int		UDPDuplicate(ClientInfo *, int &);
  //udp
  
  Network(int, int, std::string, size_t = 512);
  Network(const Network& oldNetwork);
  ~Network();

private:
  int		_family;//tronc commun
  size_t	_len;
  int		_id;
  bool		_change;
  Mutex     *_safe;
  std::map<int, ClientInfo *> _connected; //<id, fd> //tcp
};

#endif
