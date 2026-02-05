/* toralize.h - Header file for toralize project */
// https://www.openssh.org/txt/socks4.protocol

#include <stdio.h>      // standard I/O (printf, perror)
#include <stdlib.h>     // malloc, free, exit
#include <string.h>     // memset, memcpy, strlen
#include <unistd.h>     // close, read, write
#include <sys/socket.h> // socket(), connect(), sockaddr
#include <arpa/inet.h>  // htons(), inet_addr()
#include <netinet/in.h> // sockaddr_in structure
#include <dlfcn.h>      // dynamic linking (dlsym, RTLD_NEXT)

/*
Why dlfcn.h is important
This is critical for toralize.
You override connect() using LD_PRELOAD, and dlsym() lets you call the real connect() after interception.
*/

#define LOCALHOST_IP    "127.0.0.1" // Tor SOCKS proxy runs locally
#define TORALIZE_PORT   9050 // Default Tor SOCKS4 port
#define USERNAME		"toralize_user" // SOCKS4 requires a USERID field (can be anything)

/*
Avoid hardcoding sizes
Make code safer if structs change
*/
#define request_size    sizeof(struct toralize_request)
#define response_size   sizeof(struct toralize_response) 

// typedef unsigned char int8;
// typedef unsigned short int16;
// typedef unsigned int int32;

/*
SOCKS4 request format (protocol note)

	            	+----+----+----+----+----+----+----+----+----+----+....+----+
		            | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		            +----+----+----+----+----+----+----+----+----+----+....+----+
 # of bytes:	       1    1      2              4           variable       1

*/

struct toralize_request {
    uint8_t  vn;        // SOCKS version number (must be 0x04)
    uint8_t  cd;        // Command code (0x01 = CONNECT)
    uint16_t dstport;   // Destination port (network byte order)
    uint32_t dstip;     // Destination IP address (network byte order)
    unsigned char userid[16]; // SOCKS4 USERID (null-terminated)
};


typedef struct toralize_request Req; // Alias for convenience

/*
SOCKS4 response format (protocol note)

				+----+----+----+----+----+----+----+----+
				| VN | CD | DSTPORT |      DSTIP        |
				+----+----+----+----+----+----+----+----+
 # of bytes:	   1    1      2              4


 */

 struct toralize_response {
    uint8_t  vn;           // Response version (usually 0x00)
    uint8_t  cd;           // Status code (90 = request granted)
    uint16_t unused_port;  // Not used by SOCKS4
    uint32_t unused_ip;    // Not used by SOCKS4
};


typedef struct toralize_response Res; // Alias for convenience

// Function prototypes
Req *create_request(struct sockaddr_in *); // Create a SOCKS4 request based on the target address
int connect(int, const struct sockaddr *, socklen_t); // Override connect() to route through Tor