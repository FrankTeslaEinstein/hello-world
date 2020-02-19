

/* 
  Libreria desarrollada por : Luis M. Rojas Cardenas
  2005. 

*/


#include "udp.h" 

void print_UDP (UDP *udp)
{
  printf ("foreing address : %s\n", inet_ntoa (udp->foreign.sin_addr));
  printf ("foreing port    : %d\n", ntohs (udp->foreign.sin_port));
  printf ("local   address : %s\n", inet_ntoa (udp->local.sin_addr));
  printf ("local   port    : %d\n", ntohs (udp->local.sin_port));
  printf ("buffer capacity : %d\n", udp->capacity);
}

void create_UDP (UDP *udp, char *laddr, unsigned short lport, char *faddr, unsigned short fport)
{
  bzero ((void *)udp, sizeof (UDP));

  if ((udp->sockfd = socket (PF_INET, SOCK_DGRAM, 0)) < 0) {
     puts ("Problemas al abrir el socket");
     exit (1);
  }
  printf ("socket() OK\n");

  bzero ((void *)&(udp->foreign), sizeof (struct sockaddr_in)); 
  bzero ((void *)&(udp->local), sizeof (struct sockaddr_in)); 

  printf ("bzero () OK\n");

  udp->foreign.sin_family = udp->local.sin_family = AF_INET;

  udp->foreign.sin_addr.s_addr = inet_addr (faddr);
  udp->foreign.sin_port = htons (fport);

  if (laddr == NULL) {
    printf ("local address 'laddr' is NULL, I can not continue \n");
    exit (1);
  }

  udp->local.sin_addr.s_addr = inet_addr (laddr);
  udp->local.sin_port = htons (lport);

  if (bind (udp->sockfd, (struct sockaddr *)&(udp->local), sizeof (struct sockaddr_in)) < 0) {
    printf ("problems with 'bind'\n");
    exit (1);
  };
  printf ("bind () OK\n");
}



/******************************************************************/

void send_UDP (UDP *udp)
{
  udp->sent_bytes = sendto (udp->sockfd, (void *)udp->buffer, udp->bytes_to_send, 0, (struct sockaddr *)&(udp->foreign), (socklen_t) sizeof (struct sockaddr_in));

  if (udp->sent_bytes < 0) {
    puts ("Error with 'sendto'");
    exit (1);
  }
}


/******************************************************************/
/* recv_UPD: Recibe datos en una asociacion UDP */

void recv_UDP (UDP *udp)
{
  int fromlen;

  fromlen = sizeof (struct sockaddr_in);

  udp->received_bytes = recvfrom (udp->sockfd, (void *)udp->buffer, udp->capacity, 0, (struct sockaddr *) &(udp->foreign),(socklen_t *)&fromlen);

}

void close_UDP (UDP *udp)
{
  close (udp->sockfd);
}



