/*
* Project : R-Type
* Part : Server
* Author : giraud_d
 */

#ifndef         PROTOSERVER_H
#define         PROTOSERVER_H

#define         PING    'a' //1
#define         PONG    'b' //2
#define         PORT    "2000"
#define         FULL    0

struct          stdPacket {
    char        val;
};

struct          roomPortPacket {
    int         port;
};

struct          roomNamePacket {
    char        name[32];
};

#endif