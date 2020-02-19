


/*
  Libreria desarrollada por : Luis M. Rojas Cardenas
  2005.

*/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define CLIENTE     0
#define SERVIDOR    1

/******************************************************************/
/* create_UPD: crea un socket UDP.

   serv: contiene informacion relacionada con el servidor.
   addr; direccion del servidor; valida solo cuando type = 1
   port: numero de puerto a asociar con el socket creado.
   type: 0 = cliente, 1 = servidor.

   regresa: el descriptor del socket.

*/

typedef struct udp {
  int sockfd;
  struct sockaddr_in foreign;
  struct sockaddr_in local;
  int capacity;
  int received_bytes;
  int bytes_to_send;
  int sent_bytes;
  char *buffer[1024];
} UDP;

void create_UDP (UDP *udp, char *laddr, unsigned short lport, char *faddr, unsigned short fport);
void send_UDP (UDP *udp);
void recv_UDP (UDP *udp);
void close_UDP (UDP *udp);
void print_UDP (UDP *udp);

