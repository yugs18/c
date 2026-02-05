/* toralize.h - Header file for toralize project */
// https://www.openssh.org/txt/socks4.protocol

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define LOCALHOST_IP    "127.0.0.1" //
#define TORALIZE_PORT   9050
#define USERNAME		"toralize_user"
#define request_size    sizeof(struct toralize_request)
#define response_size   sizeof(struct toralize_response) 

// typedef unsigned char int8;
// typedef unsigned short int16;
// typedef unsigned int int32;

/*

	            	+----+----+----+----+----+----+----+----+----+----+....+----+
		            | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		            +----+----+----+----+----+----+----+----+----+----+....+----+
 # of bytes:	       1    1      2              4           variable       1

*/

struct toralize_request {
	uint8_t vn;
	uint8_t cd;
	uint16_t dstport;
	uint32_t dstip;
	unsigned char userid[16];
};

typedef struct toralize_request Req;

/*

				+----+----+----+----+----+----+----+----+
				| VN | CD | DSTPORT |      DSTIP        |
				+----+----+----+----+----+----+----+----+
 # of bytes:	   1    1      2              4


 */

 struct toralize_response {
	uint8_t vn;
	uint8_t cd;
	uint16_t unused_port;
	uint32_t unused_ip;
};

typedef struct toralize_response Res;

Req *create_request(const char *, int);
int main(int, char **);