#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h> //Criar sockets
#include<netinet/in.h> //Para usar sockaddr_in
#include<arpa/inet.h> //Para usar htons.
#include<sys/types.h> //Para usar connect
#include<string.h> //Para usar funções envolvendo Strings


int main(int argc, char  **argv)
{
	struct sockaddr_in servidor;
	int meuSocket;
	int tam; //Recebe o tamanho da mensagem do servidor.
	int booleano = 0; //0-False, 1-True
	char buffer[100];
	char entradaTexto[150],comando[5],apelido[25], mensagens[140]; //String para comandos e mensagens.
	char *token; //Para usar strtoken


	meuSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPv4 protocol. SOCK_STREAM = TCP.

	if(meuSocket == -1){
		printf("Erro ao criar socket!\n");
	}else{
		printf("Socket criado com sucesso: %d\n", meuSocket);
	}

	//Preparando a estrutura sockaddr_in
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(8888);
	servidor.sin_addr.s_addr = INADDR_ANY;

	
	//Esse laço pega o comando e o nome do usuário.
	while(booleano != 1){
		printf("\nDe o comando JOIN e em seguida o apelido sem espacos\n ex: JOIN Odin\n");
		scanf("%[^\n]s", entradaTexto);
		setbuf(stdin, NULL);
		//puts(entradaTexto);
		
		if(strlen(entradaTexto) < 6){
			printf("\n999 - Comando ou apelido invalidos, digite-os novamente");
		}else{

			token = strtok(entradaTexto, " ");
			strcpy (comando, token);
			//printf("\n%s\n", comando);

			token = strtok(NULL, "\n");
			puts(token);
			strcpy (apelido, token);
			
			if(apelido[0] == ' '){
				printf("\n201 - Apelido invalido, por favor digite novamente");
			}else{
				//printf("%s\n", apelido);
			
				if((strcmp(comando,"Join") == 0) || (strcmp(comando, "JOIN") == 0) || (strcmp(comando, "join") == 0)){
					booleano = 1;
				}else{
					printf("\n999 - Comando invalido, por favor digite novamente");
				}

			}
			//printf("\n");
			//puts(comando);
			//puts(apelido);
		}
		
	}


	if (connect (meuSocket, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
	{
		puts ("Erro ao conectar!");
	}else{
		puts ("Conectado");
	}

	//Recebendo mensagem do servidor
	tam = recv(meuSocket, buffer, sizeof(buffer),0);

	if(tam < 0){
		printf("Erro ao receber dados!\n");
		exit (1);
	}

	buffer[tam] = '\0';
	printf("===============================================================\n");
	printf("Servidor diz >> %s\n",buffer);

	return 0;
}