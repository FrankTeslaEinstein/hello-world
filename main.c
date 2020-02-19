#include <stdio.h>
#include <string.h>
#include "udp.h"
#define LF 10
UDP canal;
void leer(char msg[]);

int main(void){
	// comentario para git...
	create_UDP (&canal, "192.168.43.94", 8080, "192.168.43.122", 1112);
	//create_UDP (&canal, "192.168.100.4", 8080, "192.168.100.90", 1112);
	// inicializando canal UDP
	canal.capacity=100;				// Tamaño del buffer 1024 bytes 
	printf("Hasta aqui bien todo\n");
	char encender[]={'E','N','C','E','N','D','E','R',13,10,0};
	char apagar[]={'A','P','A','G','A','R',13,10,0};
	char color[]={'C','O','L','O','R',' ','R','G','B',':',128,30,255,13,10,0};
	char *sec[3];
	sec[0] = encender;
	sec[1] = apagar;
	sec[2] = color;
	char msg[100];
	int i=0;
	while(1){
		if(i==3)
			i=0;
		printf("Esperando:\n");	
		recv_UDP (&canal);
		if (canal.received_bytes < 0)
	      printf("ERROR in recvfrom\n");

		printf(" %d Bytes Rx: %s \n",canal.received_bytes,canal.buffer);	
		printf("Responder: ");
		
		scanf("%d",&i);

		sprintf(canal.buffer,"%s",sec[i]);
		canal.bytes_to_send = strlen(sec[i]);
		send_UDP (&canal);
		printf("Bytes Tx: %s \n",canal.buffer);
	}
	
	print_UDP (&canal);
	return 0;
}

void leer(char msg[]){
	
	int i=0;
	msg[i] = getchar();
	while(msg[i] != LF){
		i++;
		msg[i] = getchar();
	}
	msg[i] ='\0';	// caracter de termincaion de una cadena
}

