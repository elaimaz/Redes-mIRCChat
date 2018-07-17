#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h> //Para usar sockets
#include<netinet/in.h> //Para usar sockaddr_in
#include<arpa/inet.h> //Para usar htons.
#include<sys/types.h> //Para usar connect e listen

int main(int argc, char **argv)
{
	struct sockaddr_in servidor, cliente;
	int meuSocket, novoSocket;
	int aux;
	char buffer[100];
	int infiniteLoop = 1;

	//Criando socket
	meuSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPv4. SOCK_STREAM = TCP.

	if(meuSocket < 0){
		printf("Erro ao criar Socket!\n");
		return 1;
	}else{
		printf("Socket criado com sucesso.\n");
	}

	//Preparando a estrutura sockaddr_in
	servidor.sin_family = AF_INET;
	servidor.sin_addr.s_addr = INADDR_ANY;
	servidor.sin_port = htons(8888);


	//bind - ligando uma conexão socket a uma porta
	if (bind(meuSocket,(struct sockaddr *)&servidor,sizeof(servidor)) < 0)
	{
		puts ("Erro no bind");
		return 1;
	}else{
		printf("Bind realizado com sucesso.\n");
	}

	//Listen - Ouvindo conexões
	listen(meuSocket,2); //2 Indica que o socket terá 2 conexões. COMO FAZER PARA SER INDEFINIDO???
	

	while(infiniteLoop == 1){
		printf("Aguardando conexoes...\n");

		aux = sizeof(cliente);
		novoSocket = accept(meuSocket, (struct sockaddr *)&cliente, &aux);

		if(novoSocket < 0){
			printf("Erro no accept!\n");
			exit (1);
		}

		printf("Conexão aceita com o cliente %d.\n",novoSocket);

		strcpy(buffer,"Mensagem enviada pelo servidor.\n");
		aux = send(novoSocket, buffer, strlen(buffer), 0);

		if(aux < 0){
			printf("Erro ao enviar mensagem!\n");
			exit (1);
		}
	
	}
	printf("SAIU AQUI\n");
	return 0;
}