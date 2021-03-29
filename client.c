#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#define DEFAULT_BUFLEN 512

#define server "www.yahoo.com"
int FunctieClient()
{ 
	
	FILE *fisierscriere;
	fisierscriere=fopen("index.html","w");
	int am; //socket
	int info;
	struct addrinfo hints, *res;
        struct addrinfo *serverinfo; 
	int addrlen;

        memset(&hints, 0, sizeof (hints));
	hints.ai_family=AF_INET6;  //pt. ipv6
	hints.ai_socktype=SOCK_STREAM; //pt. TCP
        //incarcare structura adresa
	if((info=getaddrinfo("www.yahoo.com","80",&hints,&res))!=0) //80 e numarul portului HTTP
		//se preia adresele de la site  si incercam sa ne conectam la una dintre ele si in  res ramane adresa
	{
		printf("Nu se face legatura\n");
		return 0;
	}

	am=socket(AF_INET6,SOCK_STREAM,0);
	if(am==-1)
	{	 printf("\nEroare la creare socket.\n");
		return 0;
	}
	else printf("Socket creeat cu succes\n");
	int con; 
	con=connect(am,res->ai_addr,res->ai_addrlen);
	if(con==-1)  //verificam conexiune
	
           {
	   printf("Eroare conexiune\n");
	   return 0;
	   }
	else {
	printf("\nConectat\n");
	}


	char *msg="GET / HTTP/1.0\r\n\r\n"; //msg=pointer/mesaj
	int lenbuff, octeti_tr; //lenbuff=lungimea bufferului
	lenbuff=strlen(msg);  
	octeti_tr=send(am,msg,lenbuff,0);//apel send returneaza nr de bytes trimisi //prin primitiva prin care se trimit date prin conexiunea stabilita anterior
	if(octeti_tr==-1)
	{
		printf("\nEroare trimitere  mesaj\n");
		return 0;
	}
	else
	printf("\nMesaj trimis\n");
	

	
    char recv_buff[DEFAULT_BUFLEN]; //lungimea in care se citeste informatia
  
   // int recve;
    do
{
	octeti_tr=recv(am,recv_buff,DEFAULT_BUFLEN,0);//apel recve; primitiva prin care se receptioneaza date de la conexiunea stabilita anterior
	
    if(octeti_tr>0)
	   
	   
    { 
    //printf("\nMesaj receptionat: %d",octeti_tr);
   for(int i=0;i<octeti_tr;i++)  
   fprintf(fisierscriere,"%c", recv_buff[i]);
  
    
    }

    else if (octeti_tr==0)
	    printf("\nConexiune inchisa\n");
    else 
    {
	    printf("\nEroare la primire\n");
	    return 0;
    }
//if(octeti_tr==-1)
//	printf("\n Eroar!");
//else
//	break;
	


}while(octeti_tr>0);

fclose(fisierscriere);

return 0;

}


	
