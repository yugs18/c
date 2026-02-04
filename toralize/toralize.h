/* toralize.h - Header file for toralize project */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOCALHOST_IP    "127.0.0.1"
#define TORALIZE_PORT   9050

typedef unsigned char int8;
typedef unsigned short int16;
typedef unsigned int int32;

/*

	            	+----+----+----+----+----+----+----+----+----+----+....+----+
		            | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
		            +----+----+----+----+----+----+----+----+----+----+....+----+
 # of bytes:	       1    1      2              4           variable       1

*/