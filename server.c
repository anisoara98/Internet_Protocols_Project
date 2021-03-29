#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "client.c"
int main()
{
	FunctieClient();
	FILE *fisiercitire;

	int am4, newsock, port=22211;
	socklen_t cli; //genereaza marimea spatiului de stocare al structurii
	char buff_am[512];
	char *msg="Comanda neimplementata";
	int lenght=strlen(msg);
	int recve,send_am;
	struct sockaddr_in serv_addr, cli_addr;
	am4=socket(AF_INET, SOCK_STREAM,0); //ipv4  
	//creeaza un nou punct terminal de comunicare
	if(am4<0) {printf("Nu se poate deschide socket!\n");}

	serv_addr.sin_family=AF_INET; //ipv4
	serv_addr.sin_port=htons(port); //port 
	serv_addr.sin_addr.s_addr=INADDR_ANY; //se conecteaza la adresa ip a statiei

	if(bind(am4,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0) 
		{printf("Eroare in functia bind\n");
		return 0; }
	listen(am4,7); 
	while(1)
	{
		cli=sizeof(cli_addr); //dimensiunea structurii
		newsock=accept(am4,(struct sockaddr *)&cli_addr,&cli); //accepta conex. de la client
		//accept blocheaza asteptarea pana cand o noua cerere de conexiune soseste.
		if(newsock<0) {
			printf("Eroare la acceptare!\n");
			return 0;
		              }
			else { printf("Conexiune acceptata!\n");

		do
		{
			recve=recv(newsock,buff_am,sizeof(buff_am),0);
			//recv primitiva pt socket stream prin care se receptioneaza date de la conexiunea stabilita anterior
			if(recve>0) {
					if(strcmp(buff_am,"01#")==0)
					{ fisiercitire=fopen("index.html","r");
				       	char s[255];
					while(!feof(fisiercitire))
					{
						fgets(s,255,fisiercitire);
						send(newsock,s,strlen(s),0);
						memset(s,0,sizeof s);
					}//end while
					fclose(fisiercitire);
					}//end if
					else 
					{
						 send_am=send(newsock,msg,lenght,0);
                                                 memset(buff_am,0,sizeof(buff_am)); //elibereaza memoria	
					}//end else

				} 
			
	if(recve==0){
		printf("Conexiune inchisa!\n");
		close(newsock);
		break;
		}
		}while(recve>0); //end do-while
			}


	}//end while(1)
	return 0;
}
