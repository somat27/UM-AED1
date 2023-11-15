#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> 
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TAMANHOSTR 50
#define MAXFRIENDS 50

//Estruturas

struct user {
	int numeroConta,dia,mes,ano,numeroTelemovel,amigos,tipoConta;
	char fName[50];
	char lName[50];
	char email[50];
	char username[50];
	char password[50];
	char desc[50];
};

struct publicacao {
	int tipoPub,numeroConta,idPub;
	char frase[150];
	char data[20];
	char fname[50];
	char lname[50];
};

struct amigos {
	int numeroConta,idSeguido;
	char fName[50];
	char lName[50];
	char fNameS[50];
	char lNameS[50];
};

//Estruturas

//Funções

void interface();
int paginaInicial();
void loginConta();
void friendster();
void eliminarConta();
void paginaPublicacoes();
void eliminarPub();
void paginaPerfil();
int verificarAmigo();
int contarAmigos();
void fazerAmigo();
void menuPub();
void listaFriends();
void desfazerFriend();
void editarPub();
int contarPub();
void procurarConta();
void mostrarPubs();
void tipoContaUser();
void criarPub();
void editarConta();
void registarConta();
void registroFirstName();
void registroLastName();
void registroEmail();
void registroNascimento();
void registroTelemovel();
void registroUsername();
void registroPassword();
int verificarIdConta();
void mostrarEstatistica();
int sairPrograma();

//Funções

int main(){
	setlocale(LC_ALL, "Portuguese"); //Mudar lingua para portugues devido aos acentos
	system("CLS");
	interface();
	int op = paginaInicial();
	if(op){
		if(op==1)
			loginConta();
		else if(op==2)
			registarConta();
		else if(op==3)
			paginaPublicacoes(0,0);
		else if(op==4)
			mostrarEstatistica();
		else if(op==5)
			sairPrograma();
	}else{
		return 0;
	}
	
	return 0;
}

//Interface

void interface(){
	printf("\n");
	printf("\n ¦¦¦¦¦¦¦ ¦¦¦¦¦¦  ¦¦ ¦¦¦¦¦¦¦ ¦¦¦    ¦¦ ¦¦¦¦¦¦  ¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦¦ ¦¦¦¦¦¦ ");
	printf("\n ¦¦      ¦¦   ¦¦ ¦¦ ¦¦      ¦¦¦¦   ¦¦ ¦¦   ¦¦ ¦¦         ¦¦    ¦¦      ¦¦   ¦¦");
	printf("\n ¦¦¦¦¦   ¦¦¦¦¦¦  ¦¦ ¦¦¦¦¦   ¦¦ ¦¦  ¦¦ ¦¦   ¦¦ ¦¦¦¦¦¦¦    ¦¦    ¦¦¦¦¦   ¦¦¦¦¦¦ ");
	printf("\n ¦¦      ¦¦   ¦¦ ¦¦ ¦¦      ¦¦  ¦¦ ¦¦ ¦¦   ¦¦      ¦¦    ¦¦    ¦¦      ¦¦   ¦¦");
	printf("\n ¦¦      ¦¦¦  ¦¦ ¦¦ ¦¦¦¦¦¦¦ ¦¦   ¦¦¦¦ ¦¦¦¦¦¦  ¦¦¦¦¦¦¦    ¦¦    ¦¦¦¦¦¦¦ ¦¦   ¦¦");
	printf("\n");
}

//Interface

//Pagina Inicial

int paginaInicial(){
	int op;
	printf("\n Bem vindo ao Friendster, a melhor rede social feita inteiramente em C. \n");
	printf("\n 1) Acessar Conta  2) Criar Conta  3) Modo Anônimo*  4) Estatistica  5) Sair");
	printf("\n *Apenas poderá ver conteúdo marcado como público.");
	printf("\n Opção: ");
	scanf("%d",&op);
	switch(op){
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			return op;
			break;
		default:
			printf("\n Opção invalida");
			printf("\n Press any key to continue......");
			getch();
			system("CLS");
			main();
			break;
	}
}

//Pagina Inicial

//Login Conta

void loginConta(){
	system("CLS");
	FILE *log;
	log = fopen("bd1","rb");
	if (log == NULL){
		printf("1 ERROR: File not open");
		fclose(log);
		log = fopen("bd1","ab");
		fclose(log);
		printf("\nTry Again ....");
		getch();
		loginConta();
	}
	FILE *lastlog;
	lastlog = fopen("lastlog","wb");
	struct user user;
	char username[200] = {}; //Password esta com {} para corrigir o erro de quando se erra a pass ele guardar enters e bugar a pass seguinte
	int i=0,numConta;
	interface();
	printf("\n Sistema de LOGIN\n");
	printf(" Username: ");scanf("%s",username);
	printf(" Password: ");
	char ch,password[200] = {};
	int cPos = 0;
	while(1){
		ch = getch();
		if(ch==13){ // Enter
			break;
		}else if(ch==8){ // BackSpace
			if(cPos>0){
				cPos--;
				password[cPos] = '\0';
				printf("\b \b");
			}
		}else if(ch==32||ch==9){ //Espaço ou Tab
			continue;
		}else{
			password[cPos] = ch;
			cPos++;
			printf("*");
		}
	}
	int fuser=0,fpass=0;
	while(fread(&user,sizeof(user),1,log)){
		if(strcmp(username,user.username) == 0){
			fuser = 1;
			if(strcmp(password, user.password) == 0){
				fpass = 1;
				numConta = user.numeroConta;
				fwrite(&user,sizeof(user),1,lastlog);
				break;
			}
		}
	}
	fclose(log);
	fclose(lastlog);
	if(fuser == 0){
		printf("\n");
		printf("\n Username invalido!");
		printf("\n Tenta novamente...");
		getch();
		loginConta();
	}else if(fpass == 0){
		printf("\n");
		printf("\n Password para o username: %s é invalida!",username);	
		printf("\n Tenta novamente...");
		getch();
		loginConta();
	}else{
		friendster(numConta);
	}
}

//Login Conta

//Friendster

void friendster(int idAutor){
	int op;
	system("CLS");
	interface();
	printf("\n 1) Pagina Inicial 2) Perfil 3) Eliminar Conta 4) Terminar Sessão 5) Sair");
	printf("\n Opção: ");
	scanf("%d",&op);
	switch(op){
		case 1:
			paginaPublicacoes(1,idAutor);
			break;
		case 2:
			paginaPerfil(idAutor,0,0);
			break;
		case 3:
			eliminarConta(idAutor);
			break;
		case 4:
			main();
			break;
		case 5:
			sairPrograma();
			break;
		default:
			printf("\n Opção invalida");
			printf("\n Press any key to continue......");
			getch();
			system("CLS");
			friendster(idAutor);
			break;
	}
}

void eliminarConta(int idAutor){
	char op[25];
	system("CLS");
	printf("\n =======AVISO=======");
    printf("\n Esta ação é irreversível.\n\n");
	printf("\n Deseja Continuar? (sim ou nao)\n ");
	scanf("%s",op);
	if(!strcmp(op,"nao")||!strcmp(op,"Nao")){
		friendster(idAutor);
	}
	
    FILE *log;
    log = fopen("bd1","rb");
    if(log == NULL){
    	printf("1 ERROR: File not open");
    	fclose(log);
    	log = fopen("bd1","ab");
    	fclose(log);
		getch();
		eliminarConta(idAutor);
	}
	FILE *auxfile;
	auxfile = fopen("auxfile","wb");
	
	struct user user;
	int aux, i=0, apagar = 0;
	char ch,password[200] = {};
	int cPos = 0;
	while(fread(&user,sizeof(user),1,log)){
		if(user.numeroConta==idAutor){
			printf("\n Para verificar a autenticidade da conta, introduza a palavra passe! \n Pass: ");
			while(1){
				ch = getch();
				if(ch==13){ // Enter
					break;
				}else if(ch==8){ // BackSpace
					if(cPos>0){
						cPos--;
						password[cPos] = '\0';
						printf("\b \b");
					}
				}else if(ch==32||ch==9){ //Espaço ou Tab
					continue;
				}else{
					password[cPos] = ch;
					cPos++;
					printf("*");
				}
			}
			if(strcmp(user.password,password)==0){
				apagar = 1;
			}else{
				system("CLS");
				printf("\n Password Incorreta, por favor tente novamente mais tarde!");
				printf("\n Pressiona qualquer tecla para continuar...");
				getch();
				remove("auxfile");
				friendster(idAutor);
			}
		}else{
			fwrite(&user,sizeof(user),1, auxfile);
		}
	}
	fclose(log);
	fclose(auxfile);
	printf("\n\n Conta eliminada com sucesso.\n");
	printf("\n Pressiona qualquer tecla para continuar...");
	getch();
	if(apagar == 1){
		remove("bd1");
		rename("auxfile","bd1");
	}
	main();
}

void paginaPublicacoes(int tipoUser, int idAutor){
	int op;
	system("CLS");
	interface();
	printf("\n Lista de Publicações: \n");
	if(tipoUser == 0){
		mostrarPubs(1,0,0,0);
		printf("\n 1) Procurar Conta 2) Voltar");
		printf("\n Opção: ");
		scanf("%d", &op);
		switch(op){
			case 1:
				procurarConta(idAutor,tipoUser);
				break;
			case 2:
				main();
				break;
			default:
				printf("\n Opção invalida");
				printf("\n Press any key to continue......");
				getch();
				system("CLS");
				paginaPublicacoes(tipoUser, idAutor);
				break;
		}
	}if(tipoUser == 1){
		FILE *log;
		log = fopen("bd1","rb");
		printf("%s",log);
		if (log == NULL){
			printf("3 ERROR: File not open");
			fclose(log);
			log = fopen("bd1","ab");
			fclose(log);
			printf("\nTry Again ....");
			getch();
			paginaPublicacoes(tipoUser, idAutor);
		}
		struct user user;
		while(fread(&user,sizeof(user),1,log)){
			if(user.numeroConta == idAutor){
				mostrarPubs(1,1,0,0);
				printf("\n 1) Procurar Conta 2) Criar Publicação 3) Voltar");
				printf("\n Opção: ");
				scanf("%d", &op);
				fclose(log);
				switch(op){
					case 1:
						procurarConta(idAutor,tipoUser);
						break;
					case 2:
						criarPub(user.fName, user.lName, idAutor);
						break;
					case 3:
						friendster(idAutor);
						break;
					default:
						printf("\n Opção invalida");
						printf("\n Press any key to continue......");
						getch();
						system("CLS");
						paginaPublicacoes(tipoUser, idAutor);
						break;
				}
				break;
			}
		}
		//Modo User
		
		//Ver as publicações com o tipo: 1/2 (Publica/Restrita) e a 3 (Privada) mas apenas das pessoas que segue
	}
}

void procurarConta(int idAutor, int tipoVoltar){
	system("CLS");
	interface();
	char nome[50];
	printf("\n Nome da conta que deseja procurar: ");
	scanf("%s",nome);
	
	FILE *log;
	log = fopen("bd1","rb");
	printf("%s",log);
	if (log == NULL){
		printf("3 ERROR: File not open");
		fclose(log);
		log = fopen("bd1","ab");
		fclose(log);
		printf("\nTry Again ....");
		getch();
		procurarConta(idAutor,tipoVoltar);
	}
	
	struct user user;
	int i=1,op,continuar=0;
	char op2[5];
	while(fread(&user,sizeof(user),1,log)){
		if(strcmp(nome,user.fName)==0){
			printf("\n %s %s [@%s] é a conta que procura? (sim ou nao)",user.fName,user.lName,user.username);
			printf("\n Opção: ");
			scanf("%s",op2);
			if(!strcmp(op2,"sim")||!strcmp(op2,"Sim")){
				continuar = 1;
				fclose(log);
				paginaPerfil(idAutor, 1, user.numeroConta);
				break;
			}
		}
	}
	if(continuar == 0){
		printf("\n 1) Procurar Novamente 2) Voltar");
		printf("\n Opção: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				procurarConta(idAutor,tipoVoltar);
				break;
			case 2:
				paginaPublicacoes(tipoVoltar, idAutor);
				break;
			default:
				printf("\n Opção invalida");
				printf("\n Press any key to continue......");
				getch();
				procurarConta(idAutor,tipoVoltar);
				break;
		}
	}
}

void mostrarPubs(int op1,int op2,int op3,int idAutor){ //Publica, Reservada, Privada, Id Conta
	FILE *pubs;
	pubs = fopen("pubs","rb");
	if (pubs == NULL){
		printf("2 ERROR: File not open");
		fclose(pubs);
		pubs = fopen("pubs","ab");
		fclose(pubs);
		printf("\nTry Again ....");
		getch();
		mostrarPubs(op1,op2,op3,idAutor);
	}
	
	struct publicacao publicacao;
	while(fread(&publicacao,sizeof(publicacao),1,pubs)){
		if(idAutor != 0){
			if(publicacao.numeroConta == idAutor){
				if(publicacao.tipoPub == 1 && op1){
					printf("\n %s %s -- %s [Publica]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);	
				}
				if(publicacao.tipoPub == 2 && op2){
					printf("\n %s %s -- %s [Reservada]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);					
				}
				if(publicacao.tipoPub == 3 && op3){
					printf("\n %s %s -- %s [Privada]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);				
				}
			}	
		}else{
			if(publicacao.tipoPub == 1 && op1){
				printf("\n %s %s -- %s [Publica]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);	
			}
			if(publicacao.tipoPub == 2 && op2){
				printf("\n %s %s -- %s [Reservada]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);					
			}
			if(publicacao.tipoPub == 3 && op3){
				printf("\n %s %s -- %s [Privada]\n ID %d -> %s\n",publicacao.fname,publicacao.lname,publicacao.data,publicacao.idPub,publicacao.frase);				
			}
		}
	}
	fclose(pubs);
}

void paginaPerfil(int idAutor, int verCriador, int idConta){
	system("CLS");
	if(verCriador == 0){
		FILE *log;
		log = fopen("bd1","rb");
		printf("%s",log);
		if (log == NULL){
			printf("3 ERROR: File not open");
			fclose(log);
			log = fopen("bd1","ab");
			fclose(log);
			printf("\nTry Again ....");
			getch();
			paginaPerfil(idAutor,verCriador, 0);
		}
		int op;
		struct user user;
		while(fread(&user,sizeof(user),1,log)){
			if(idAutor == user.numeroConta){
				int pubs = contarPub(user.numeroConta,0);
				int amigos = contarAmigos(user.numeroConta);
				char tipoConta[50];
				tipoContaUser(user.numeroConta, tipoConta);
				printf("\n %s %s [@%s]\t Conta %d: %s\n",user.fName, user.lName,user.username,user.numeroConta,tipoConta); 
				printf("\n Publicações: %d \t Amigos: %d\n",pubs,amigos);
				printf("\n Descrição: %s", user.desc);
				printf("\n\n\n Publicações: \n");
				mostrarPubs(1,1,1,idAutor);
				printf("\n 1) Menu Publicação 2) Editar Conta 3) Lista de Amigos 4) Voltar");
				printf("\n Opção: ");
				scanf("%d", &op);
				fclose(log);
				switch(op){
					case 1:
						menuPub(user.fName, user.lName, idAutor);
						break;
					case 2:
						editarConta(idAutor);
						break;
					case 3:
						listaFriends(idAutor);
						break;
					case 4:
						friendster(idAutor);
						break;
					default:
						printf("\n Opção invalida");
						printf("\n Press any key to continue......");
						getch();
						system("CLS");
						paginaPerfil(idAutor,verCriador,0);
						break;
				}
			}
		}
	}else if(verCriador == 1){
		FILE *log;
		log = fopen("bd1","rb");
		printf("%s",log);
		if (log == NULL){
			printf("3 ERROR: File not open");
			fclose(log);
			log = fopen("bd1","ab");
			fclose(log);
			printf("\nTry Again ....");
			getch();
			paginaPerfil(idAutor,verCriador,0);
		}
		int op;
		struct user user;
		while(fread(&user,sizeof(user),1,log)){
			if(idConta == user.numeroConta){
				int pubs = contarPub(user.numeroConta,0);
				int amigos = contarAmigos(user.numeroConta);
				int eAmigo = verificarAmigo(idAutor,user.numeroConta);
				char tipoConta[50];
				tipoContaUser(user.numeroConta, tipoConta);
				if(eAmigo == 1){
					printf("\n %s %s [@%s]\t Conta %d: %s\n",user.fName, user.lName,user.username,user.numeroConta,tipoConta); 
					printf("\n Publicações: %d \t Amigos: %d\n",pubs,amigos);
					printf("\n Descrição: %s", user.desc);
					printf("\n\n SÃO AMIGOS!\n\n Publicações: \n");
				}else{
					printf("\n %s %s [@%s]\t Conta %d: %s\n",user.fName, user.lName,user.username,user.numeroConta,tipoConta); 
					printf("\n Publicações: %d \t Amigos: %d\n",pubs,amigos);
					printf("\n Descrição: %s", user.desc);
					printf("\n\n\n Publicações: \n");
				}
				if(idAutor == 0){
					mostrarPubs(1,0,0,user.numeroConta);
					printf("\n 1) Voltar");
					printf("\n Opção: ");
					scanf("%d", &op);
					fclose(log);
					switch(op){
						case 1:
							paginaPublicacoes(0,0);
							break;
						default:
							printf("\n Opção invalida");
							printf("\n Press any key to continue......");
							getch();
							system("CLS");
							paginaPerfil(idAutor,verCriador,idConta);
							break;
					}
				}else{	
					if(eAmigo == 1){
						mostrarPubs(1,1,1,user.numeroConta);
					}else{
						mostrarPubs(1,1,0,user.numeroConta);
					}
					if(strcmp(tipoConta,"Privada")==0||eAmigo==1||idAutor==user.numeroConta){//Privada
						printf("\n 1) Voltar");
						printf("\n Opção: ");
						scanf("%d", &op);
						fclose(log);
						switch(op){
							case 1:
								friendster(idAutor);
								break;
							default:
								printf("\n Opção invalida");
								printf("\n Press any key to continue......");
								getch();
								system("CLS");
								paginaPerfil(idAutor,verCriador,idConta);
								break;
						}
					}else{//Publica
						printf("\n 1) Fazer Amizade 2) Voltar");
						printf("\n Opção: ");
						scanf("%d", &op);
						fclose(log);
						switch(op){
							case 1:
								fazerAmigo(idAutor,idConta);
								break;
							case 2:
								friendster(idAutor);
								break;
							default:
								printf("\n Opção invalida");
								printf("\n Press any key to continue......");
								getch();
								system("CLS");
								paginaPerfil(idAutor,verCriador,idConta);
								break;
						}
					}
				}
			}
		}
	}
}

int verificarAmigo(int idAutor, int numeroConta){
	FILE *amgs;
	amgs = fopen("ListaAmigos","rb");
	if(amgs == NULL){
		fclose(amgs);
		amgs = fopen("ListaAmigos","ab");
		fclose(amgs);
		listaFriends(idAutor);
	}
	struct amigos amigos;
	while(fread(&amigos,sizeof(amigos),1,amgs)){
		if(amigos.numeroConta==idAutor && amigos.idSeguido==numeroConta||amigos.numeroConta==numeroConta && amigos.idSeguido==idAutor){
			return 1;
		}
	}
	fclose(amgs);
	return 0;
}

int contarAmigos(int idAutor){
	int totalAmigos=0;
	FILE *amgs;
	amgs = fopen("ListaAmigos","rb");
	if(amgs == NULL){
		fclose(amgs);
		amgs = fopen("ListaAmigos","ab");
		fclose(amgs);
		listaFriends(idAutor);
	}
	struct amigos amigos;
	while(fread(&amigos,sizeof(amigos),1,amgs)){
		if(amigos.numeroConta==idAutor||amigos.idSeguido==idAutor){
			totalAmigos++;
		}
	}
	fclose(amgs);
	return totalAmigos;
}

void fazerAmigo(int idAutor, int idConta){
	system("CLS");
	interface();
	int totalAmigos = contarAmigos(idAutor);
	if(totalAmigos<=50){
		struct amigos amigos;
		FILE *amgs;
		amgs = fopen("ListaAmigos","ab");
		FILE *log;
		log = fopen("bd1","rb");
		struct user user;
		while(fread(&user,sizeof(user),1,log)){
			if(user.numeroConta == idConta){
				strcpy(amigos.fName,user.fName);
				strcpy(amigos.lName,user.lName);
			}
			if(user.numeroConta == idAutor){
				strcpy(amigos.fNameS,user.fName);
				strcpy(amigos.lNameS,user.lName);
			}
		}
		amigos.numeroConta = idAutor;
		amigos.idSeguido = idConta;
		fwrite(&amigos,sizeof(amigos),1,amgs);
		fclose(amgs);
		fclose(log);
		printf("\n %s %s, fizeste amizado com %s %s!",amigos.fNameS,amigos.lNameS,amigos.fName,amigos.lName);
		getch();
		paginaPerfil(idAutor,1,idConta);
	}else{
		printf("\n Nao podes fazer mais amigos!");
		printf("\n Pressiona uma tecla para voltar ...");
		getch();
		paginaPerfil(idAutor,1,idConta);
	}
}

void menuPub(char* fName, char* lName, int idAutor){
	int op;
	system("CLS");
	mostrarPubs(1,1,1,idAutor);
	printf("\n 1) Criar Publicacao 2) Editar Publicacao 3) Excluir Publicacao");
	printf("\n Opção: ");
	scanf("%d",&op);
	switch(op){
		case 1:
			criarPub(fName, lName, idAutor);
			break;
		case 2:
			editarPub(idAutor);
			break;
		case 3:
			eliminarPub(idAutor);
			break;
		default:
			printf("\n Opção invalida");
			printf("\n Press any key to continue......");
			getch();
			system("CLS");
			menuPub(fName,lName,idAutor);
			break;
	}
}

void listaFriends(int idAutor){
	system("CLS");
	interface();
	int totalAmigos = contarAmigos(idAutor);
	if(totalAmigos>0){
		printf("\n Lista de Amigos: \n");
		FILE *amgs;
		amgs = fopen("ListaAmigos","rb");
		if(amgs == NULL){
			fclose(amgs);
			amgs = fopen("ListaAmigos","ab");
			fclose(amgs);
			listaFriends(idAutor);
		}
		struct amigos amigos;
		while(fread(&amigos,sizeof(amigos),1,amgs)){
			if(amigos.numeroConta == idAutor){
				printf("\n 1: %d -> %s %s",amigos.idSeguido,amigos.fName,amigos.lName);
			}else if(amigos.idSeguido == idAutor){
				printf("\n 2: %d -> %s %s",amigos.numeroConta,amigos.fNameS,amigos.lNameS);
			}
		}
		int op;
		printf("\n\n 1) Desfazer Amizada 2) Voltar");
		printf("\n Opção: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				fclose(amgs);
				desfazerFriend(idAutor);
				break;
			case 2:
				fclose(amgs);
				friendster(idAutor);
				break;
			default:
				fclose(amgs);
				printf("\n Opção invalida, tente novamente mais tarde!");
				printf("\n Press any key to continue......");
				getch();
				listaFriends(idAutor);
				break;
		}
	}else{
		printf("\n Ainda nao tens amigos! \n");
		int op;
		printf("\n\n 1) Voltar");
		printf("\n Opção: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				friendster(idAutor);
				break;
			default:
				printf("\n Opção invalida, tente novamente mais tarde!");
				printf("\n Press any key to continue......");
				getch();
				listaFriends(idAutor);
				break;
		}
	}
}

void desfazerFriend(int idAutor){
	system("CLS");
	interface();
	FILE *amgs;
	amgs = fopen("ListaAmigos","rb");
	FILE *aux;
	aux = fopen("aux","wb");
	struct amigos amigos;
	printf("\n Qual o id que quer desfazer amizade? ");
	printf("\n ID: ");
	int id,removido=0;
	scanf("%d",&id);
	
	while(fread(&amigos,sizeof(amigos),1,amgs)){
		if(amigos.idSeguido == id && amigos.numeroConta == idAutor){
			removido = 1;
		}else{
			fwrite(&amigos,sizeof(amigos),1,aux);
		}
	}
	
	fclose(aux);
	fclose(amgs);
	printf("\n\n Amigo removido com sucesso.\n");
	printf("\n Pressiona qualquer tecla para continuar...");
	getch();
	if(removido == 1){
		remove("ListaAmigos");
		rename("aux","ListaAmigos");
	}
	listaFriends(idAutor);
}

void editarPub(int idAutor){
	system("CLS");
	FILE *pubs;
    pubs = fopen("pubs","rb");
    if(pubs == NULL){
    	printf("1 ERROR: File not open");
    	fclose(pubs);
    	pubs = fopen("pubs","ab");
    	fclose(pubs);
		getch();
		eliminarPub(idAutor);
	}
	FILE *auxfile;
	auxfile = fopen("auxfile","wb");
	
	struct publicacao publicacao;
	int aux, i=0, editar = 0,idPub,op;
	char password[50]={},texto[150];
	
	printf("\n Qual o id da publicacao que quer editar? \n ID: ");
	scanf("%d",&idPub);
	while(fread(&publicacao,sizeof(publicacao),1,pubs)){
		if((publicacao.numeroConta==idAutor)&&(publicacao.idPub==idPub)){
			printf("\n Texto: ");
			fflush(stdin);
			gets(texto);
			if(strlen(texto)>sizeof(texto)){
				printf("\n Uma publicação so pode ter ate 150 caracteres, por favor tente outra vez\n");
				printf("\n Press any key to continue......");
				getch();
				editarPub(idAutor);
			} 
			strcpy(publicacao.frase, texto);
			printf("\n Tipo de Publicacao? (1-Publica, 2-Reservada, 3-Privada)");
			printf("\n Opcao: ");
			scanf("%d",&op);
			switch(op){
				case 1:
					publicacao.tipoPub = 1;
					break;
				case 2:
					publicacao.tipoPub = 2;
					break;
				case 3:
					publicacao.tipoPub = 3;
					break;
				default:
					printf("\n Tipo invalido, tente novamente mais tarde!");
					printf("\n Press any key to continue......");
					getch();
					editarPub(idAutor);
					break;
			}
			fwrite(&publicacao,sizeof(publicacao),1, auxfile);
			editar = 1;
		}else{
			fwrite(&publicacao,sizeof(publicacao),1, auxfile);
		}
	}
	if(editar == 0){
		system("CLS");
		printf("\n Id da publicacao nao econtrado, por favor tente novamente mais tarde!");
		printf("\n Pressiona qualquer tecla para continuar...");
		getch();
		remove("auxfile");
		paginaPerfil(idAutor,0,0);
	}
	fclose(pubs);
	fclose(auxfile);
	printf("\n\n Publicacao editada com sucesso.\n");
	printf("\n Pressiona qualquer tecla para continuar...");
	getch();
	if(editar == 1){
		remove("pubs");
		rename("auxfile","pubs");
	}
	paginaPerfil(idAutor,0,0);
}

void eliminarPub(int idAutor){
	char op[25];
	system("CLS");
	printf("\n =======AVISO=======");
    printf("\n Esta ação é irreversível.\n\n");
	printf("\n Deseja Continuar? (sim ou nao)\n ");
	scanf("%s",op);
	if(!strcmp(op,"nao")||!strcmp(op,"Nao")){
		paginaPerfil(idAutor,0,0);
	}
	
    FILE *pubs;
    pubs = fopen("pubs","rb");
    if(pubs == NULL){
    	printf("1 ERROR: File not open");
    	fclose(pubs);
    	pubs = fopen("pubs","ab");
    	fclose(pubs);
		getch();
		eliminarPub(idAutor);
	}
	FILE *auxfile;
	auxfile = fopen("auxfile","wb");
	
	struct publicacao publicacao;
	int aux, i=0, apagar = 0,idPub;
	char password[50]={};
	printf("\n Qual o id da publicacao que quer eliminar? \n ID: ");
	scanf("%d",&idPub);
	while(fread(&publicacao,sizeof(publicacao),1,pubs)){
		if((publicacao.numeroConta==idAutor)&&(publicacao.idPub==idPub)){
			apagar = 1;
		}else{
			fwrite(&publicacao,sizeof(publicacao),1, auxfile);
		}
	}
	if(apagar == 0){
		system("CLS");
		printf("\n Id da publicacao nao econtrado, por favor tente novamente mais tarde!");
		printf("\n Pressiona qualquer tecla para continuar...");
		getch();
		remove("auxfile");
		paginaPerfil(idAutor,0,0);
	}
	fclose(pubs);
	fclose(auxfile);
	printf("\n\n Publicacao eliminada com sucesso.\n");
	printf("\n Pressiona qualquer tecla para continuar...");
	getch();
	if(apagar == 1){
		remove("pubs");
		rename("auxfile","pubs");
	}
	paginaPerfil(idAutor,0,0);
}

int contarPub(int idAutor, int tipoContador){
	if (tipoContador == 0){
		//contar quantas publicações o autor tem
		int contadorpubs = 0;
		FILE *pub;
		pub = fopen("pubs","rb");
		struct publicacao publicacao;
		if (pub == NULL){
			printf("4 ERROR: File not open");
			fclose(pub);
			pub = fopen("pubs","ab");
			fclose(pub);
			printf("\nTry Again ....");
			getch();
			contarPub(idAutor,tipoContador);
		}
		while(fread(&publicacao,sizeof(publicacao),1,pub)){
			if(publicacao.numeroConta == idAutor){
				contadorpubs = contadorpubs + 1;
			}
		}
		fclose(pub);
		return contadorpubs;
	}else if(tipoContador == 1){
		//contar quantas publicações o autor tem
		int contadorpubs = 0;
		FILE *pub;
		pub = fopen("pubs","rb");
		struct publicacao publicacao;
		if (pub == NULL){
			printf("4 ERROR: File not open");
			fclose(pub);
			pub = fopen("pubs","ab");
			fclose(pub);
			printf("\nTry Again ....");
			getch();
			contarPub(idAutor, tipoContador);
		}
		while(fread(&publicacao,sizeof(publicacao),1,pub)){
			contadorpubs = contadorpubs + 1;
		}
		fclose(pub);
		return contadorpubs;
	}
}

void tipoContaUser(int idAutor, char* tipoConta){
	char tContaUser[TAMANHOSTR];
	FILE *log;
	log = fopen("bd1","rb");
	struct user user;
	if (log == NULL){
		printf("5 ERROR: File not open");
		fclose(log);
		log = fopen("bd1","ab");
		fclose(log);
		printf("\nTry Again ....");
		getch();
		tipoContaUser(idAutor, tipoConta);
	}
	while(fread(&user,sizeof(user),1,log)){
		if(user.numeroConta == idAutor){
			if(user.tipoConta == 1){
				strcpy(tContaUser, "Privada");
			}else if(user.tipoConta == 0){
				strcpy(tContaUser, "Publica");
			}
		}
	}
	fclose(log);
	strcpy(tipoConta, tContaUser);
}

void criarPub(char* fName,char* lName, int idAutor){
	system("CLS");
	FILE *pubs;
	pubs = fopen("pubs","ab");
	struct publicacao publicacao;
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char rData[50];
	strcpy(rData,asctime(timeinfo));
	char frase[150];
	printf("\n Criar Publicação (lembrando)");
	printf("\n O que quer escrever? ");
	fflush(stdin);
	gets(frase);
	if(strlen(frase)>sizeof(frase)){
		printf("Uma publicação so pode ter ate 150 caracteres, por favor tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		criarPub(fName,lName,idAutor);
	} 
	
	int numPubs = contarPub(idAutor,1);
	
	printf("\n Que tipo de publicação quer?\n 1) Publica 2) Reservada 3) Privada");
	printf("\n Opção: ");
	int op;
	fflush(stdin);scanf("%d",&op);
	switch(op){
		case 1:
			publicacao.tipoPub = 1;
			break;
		case 2:
			publicacao.tipoPub = 2;
			break;
		case 3:
			publicacao.tipoPub = 3;
			break;
		default:
			printf("\n Tipo invalido, tente novamente mais tarde!");
			printf("\n Press any key to continue......");
			getch();
			criarPub(fName,lName,idAutor);
			break;
	}
	
	strcpy(publicacao.frase, frase);
	strcpy(publicacao.data, rData);
	publicacao.numeroConta = idAutor;
	strcpy(publicacao.fname, fName);
	strcpy(publicacao.lname, lName);
	publicacao.idPub = numPubs;
	fwrite(&publicacao,sizeof(publicacao),1,pubs);
	fclose(pubs);
	paginaPerfil(idAutor, 0,0);
	
}

void editarConta(int idAutor){
	system("CLS");
	interface();
	
	FILE *bd1;	
	bd1 = fopen("bd1","rb");
	
	FILE *auxfile;
	auxfile = fopen("auxfile","wb");
	
	struct user user;
	char resposta[50];
	int editar = 0;
	int i=1;
	while(fread(&user,sizeof(user),1,bd1)){
		if(idAutor == user.numeroConta){
			printf("\n Quer editar o nome [ %s %s ]? (sim ou nao)",user.fName,user.lName);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				printf("\n Primeiro Nome: ");
				scanf("%s",user.fName);
				printf(" Apelido: ");
				scanf("%s",user.lName);
				if(strlen(user.fName)>sizeof(user.fName)||strlen(user.lName)>sizeof(user.lName)){
					printf("Nome muito grande, tente novamente mais tarde!");
					printf("\nPress any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
			}
			system("CLS");
			interface();
			printf("\n Quer editar o email [ %s ]? (sim ou nao)",user.email);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				printf("\n Email: ");
				scanf("%s",user.email);
				if(strlen(user.email)>sizeof(user.email)){
					printf("Email muito grande, tente novamente mais tarde!");
					printf("\nPress any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
			}
			system("CLS");
			interface();
			printf("\n Quer editar a data de nascimento [ %d/%d/%d ]? (sim ou nao)",user.dia,user.mes,user.ano);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				int rdia,rmes,rano,erro=0;
				printf("\n Data de nascimento (DD/MM/AAAA): ");
				scanf("%d/%d/%d",&rdia,&rmes,&rano);
				if(rdia>=1&&rdia<=31){
					if(rmes>=1&&rmes<=12){
						if(rano>=1900&&rano<=2022){
							switch(rmes){
								case 1:
								case 3:
								case 5:
								case 7:
								case 8:
								case 10:
								case 12:
									user.dia = rdia;
									user.mes = rmes;
									user.ano = rano;
									break;
								case 2:
									if(rano%4==0){
										if(rdia<30){
											user.dia = rdia;
											user.mes = rmes;
											user.ano = rano;
										}else{
											erro = 1;
										}
									}else{
										if(rdia<29){
											user.dia = rdia;
											user.mes = rmes;
											user.ano = rano;
										}else{
											erro = 1;	
										}
									}
									break;
								case 4:
								case 6:
								case 9:
								case 11:
									if(rdia<31){
										user.dia = rdia;
										user.mes = rmes;
										user.ano = rano;
									}else{
										erro = 1;
									}
									break;	
								default: 
									erro = 1;
									break;
							}					
							
						}else{
						
							erro = 1;
						}
					}else{
					
						erro = 1;
					}
				}else{
					
					erro = 1;
				}
				if(erro == 1){
					printf("Data de nascimento incorreto, tente novamente mais tarde!");
					printf("\nPress any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
				
			}
			system("CLS");
			interface();
			printf("\n Quer editar o numero de telemovel [ %d ]? (sim ou nao)",user.numeroTelemovel);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				printf("\n Numero de Telemovel: ");
				scanf("%s",user.numeroTelemovel);
				if(user.numeroTelemovel>999999999||user.numeroTelemovel<900000000){
					printf("Numero de Telemovel incorreto, tente novamente mais tarde!");
					printf("\nPress any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
			}
			system("CLS");
			interface();
			printf("\n Quer editar a password? (sim ou nao)",user.password);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				int i = 0;
				char password[50],ch;
				int cPos=0;

				printf(" Password (Minimo 6 caracteres):");
				while(1){
					ch = getch();
					if(ch==13){ // Enter
						break;
					}else if(ch==8){ // BackSpace
						if(cPos>0){
							cPos--;
							password[cPos] = '\0';
							printf("\b \b");
						}
					}else if(ch==32||ch==9){ //Espaço ou Tab
						continue;
					}else{
						password[cPos] = ch;
						cPos++;
						printf("*");
					}
				}
				if(strlen(password)>sizeof(password)){
					printf("\n Password muito grande, tente novamente mais tarde!");
					printf("\n Press any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
				strcpy(user.password, password);
			}
			system("CLS");
			interface();
			printf("\n Quer editar a descriçao da sua conta? (sim ou nao)",user.desc);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				char desc[50];
				printf("\n Descrição: ");
				fflush(stdin);
				gets(desc);
				if(strlen(desc)>sizeof(desc)){
					printf("Uma descrição so pode ter ate 50 caracteres, tente novamente mais tarde!");
					printf("\nPress any key to continue......");
					getch();
					paginaPerfil(idAutor,0,0);
				}
				strcpy(user.desc,desc);
			}
			system("CLS");
			interface();
			printf("\n Quer editar o estado da sua conta? (sim ou nao)",user.desc);
			printf("\n Opção: ");
			scanf("%s",resposta);
			if(!strcmp(resposta,"sim")||!strcmp(resposta,"Sim")){
				int op;
				printf("\n Estado de Conta [1) Publica 2) Privada]: ");
				scanf("%d",&op);
				switch(op){
					case 1:
						user.tipoConta = 0;
						break;
					case 2:
						user.tipoConta = 1;
						break;
					default:
						printf("Tipo de conta invalido, tente novamente mais tarde!");
						printf("\nPress any key to continue......");
						getch();
						paginaPerfil(idAutor,0,0);
						break;
				}
			}
			editar = 1;
			fwrite(&user,sizeof(user),1,auxfile);
		}else{
			fwrite(&user,sizeof(user),1,auxfile);
		}
	}
	fclose(bd1);
	fclose(auxfile);
	printf("\n\n Conta editada com sucesso.\n");
	printf("\n Pressiona qualquer tecla para continuar...");
	if(editar == 1){
		remove("bd1");
		getch();
		rename("auxfile","bd1");
	}
	paginaPerfil(idAutor,0,0);
}

//Friendster

//Registar Conta

void registarConta(){
	system("CLS");
	
	int idConta = verificarIdConta();
	
	FILE *reg;
	reg = fopen("bd1","ab"); //Modo escrever

	struct user user;
	
	char firstname[50],lastname[50],email[50],username[50],password[50];
	int dia,mes,ano;
	int telemovel;
	
	if(idConta<=200){
		//Registro Primeiro Nome
		registroFirstName(firstname);
		strcpy(user.fName, firstname);
		//Registro Ultimo Nome
		registroLastName(lastname);
		strcpy(user.lName, lastname);
		//Registro Email
		registroEmail(email);
		strcpy(user.email, email);
		//registro Numero Telemovel
		registroTelemovel(&telemovel);
		user.numeroTelemovel = telemovel;
		//registro Data Nascimento
		registroNascimento(&dia,&mes,&ano);
		user.dia = dia;
		user.mes = mes;
		user.ano = ano;
		
		//registro Username
		registroUsername(username);
		strcpy(user.username, username);
		//Registro Password
		registroPassword(password);
		strcpy(user.password, password);
		//Infos default para todos os users criados
		user.numeroConta = idConta;
		user.amigos = 0;
		user.tipoConta = 0;
		strcpy(user.desc, "Ainda sem Descrição!");
		/* DEBUG:
		printf("\n Conta Numero: %d", user.numeroConta); 
	    printf("\n Nome: %s %s", user.fName, user.lName); 
	    printf("\n Email: %s", user.email);
	    printf("\n Telemovel: %ld", user.numeroTelemovel); 
	    printf("\n Username: %s", user.username);   
	    printf("\n Password: %s", user.password);   
	    printf("\n Descrição: %s", user.desc);   
	    printf("\n Amigos: %d", user.amigos);
	    printf("\n Tipo de Conta: %d", user.tipoConta);
	    printf("\n Data de Nascimento: %d/%d/%d", user.dia,user.mes,user.ano);
		*/
		//Escrever Registro no File "reg"
		fwrite(&user,sizeof(user),1,reg);
		fclose(reg);
		
		printf("\n Registado com sucesso!\nAgora deve logar com a sua conta nova.");
		printf("\n Press any key to continue......");
		getch();
		system("CLS");
		loginConta();
	}else{
		printf("\n Infelizmente já temos 200 contas registadas na aplicação.\n O que impossibilita a criação de mais contas.");
		printf("\n Press any key to continue......");
		getch();
		main();
	}
}

int verificarIdConta(){
	FILE *reg;
	reg = fopen("bd1","rb");
	if (reg == NULL){
		printf("7 ERROR: File not open");
		fclose(reg);
		reg = fopen("bd1","ab");
		fclose(reg);
		getch();
		registarConta();
	}
	struct user user;
	int ultimoId;
	while(fread(&user,sizeof(user),1,reg)){
		ultimoId = user.numeroConta;
	}
	if (ultimoId>200||ultimoId<0)
		ultimoId = 0;
	fclose(reg);
	return ultimoId+1;
}

void registroFirstName(char* firstname){
	char fnome[TAMANHOSTR];
	system("CLS");
	interface();
	printf("\n Primeiro Nome: ");
	scanf("%s",fnome);
	if(strlen(fnome)>sizeof(fnome)){
		printf("Nome muito grande tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		registroFirstName(firstname);
	}else
		strcpy(firstname, fnome);
}

void registroLastName(char* lastname){
	char lnome[TAMANHOSTR];
	system("CLS");
	interface();
	printf("\n Ultimo Nome: ");
	scanf("%s",lnome);
	if(strlen(lnome)>sizeof(lnome)){
		printf("Nome muito grande tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		registroLastName(lastname);
	}else
		strcpy(lastname, lnome);
}

void registroEmail(char* email){
	char mail[TAMANHOSTR];
	int i, j=0;
	system("CLS");
	interface();
	printf("\n Email: ");
	scanf("%s",mail);
	//Verificar se é um email valido, ou seja, se tem @ no email
	for(i=0;i<=strlen(mail);i++){
		if(mail[i]=='@')
			j = 1;
	}
	if(strlen(mail)>sizeof(mail)){
		printf("Email muito grande, tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		registroEmail(email);
	}else if(strlen(mail)<10){
		printf("Email muito pequeno, tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		registroEmail(email);
	}else if(j==0){
		printf("Email invalido\n");
		printf("\nPress any key to continue......");
		getch();
		registroEmail(email);
	}else
		strcpy(email, mail);
}

void registroNascimento(int* dia, int* mes,int* ano){
	system("CLS");
	interface();
	int rdia,rmes,rano,erro=0;
	printf("\n Data de Nascimento (DD/MM/AAAA): ");
	scanf("%d/%d/%d",&rdia,&rmes,&rano);
	if(rdia>=1&&rdia<=31){
		if(rmes>=1&&rmes<=12){
			if(rano>=1900&&rano<=2022){
				switch(rmes){
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:
						*dia = rdia;
						*mes = rmes;
						*ano = rano;
						break;
					case 2:
						if(rano%4==0){
							if(rdia<30){
								*dia = rdia;
								*mes = rmes;
								*ano = rano;
							}else{
								erro = 1;
							}
						}else{
							if(rdia<29){
								*dia = rdia;
								*mes = rmes;
								*ano = rano;
							}else{
								erro = 1;	
							}
						}
						break;
					case 4:
					case 6:
					case 9:
					case 11:
						if(rdia<31){
							*dia = rdia;
							*mes = rmes;
							*ano = rano;
						}else{
							erro = 1;
						}
						break;	
					default: 
						erro = 1;
						break;
				}					
				
			}else{
			
				erro = 1;
			}
		}else{
		
			erro = 1;
		}
	}else{
		
		erro = 1;
	}
	if(erro == 1){
		printf("Data de nascimento incorreto!");
		printf("\nPress any key to continue......");
		getch();
		registroNascimento(dia,mes,ano);
	}
}


void registroTelemovel(int* telemovel){
	int tele;
	system("CLS");
	interface();
	printf("\n Numero de telemovel: ");
	scanf("%ld",&tele);
	if(tele<900000000||tele>999999999){
		printf("Numero de telemovel incorreto!");
		printf("\nPress any key to continue......");
		getch();
		registroTelemovel(telemovel);
	}else
		*telemovel = tele;
}

void registroUsername(char* username){
	char nome[50];
	system("CLS");
	interface();
	printf("\n Username: ");
	scanf("%s",nome);
	if(strlen(nome)>sizeof(nome)){
		printf("Username muito grande tente outra vez\n");
		printf("\nPress any key to continue......");
		getch();
		registroUsername(username);
	}else
		strcpy(username, nome);
}

void registroPassword(char* password){
	char pass[50] = {},pass2[50] = {},ch;
	int cPos=0;
	system("CLS");
	interface();
	printf("\n Password (Minimo 6 caracteres):");
	while(1){
		ch = getch();
		if(ch==13){ // Enter
			break;
		}else if(ch==8){ // BackSpace
			if(cPos>0){
				cPos--;
				pass[cPos] = '\0';
				printf("\b \b");
			}
		}else if(ch==32||ch==9){ //Espaço ou Tab
			continue;
		}else{
			pass[cPos] = ch;
			cPos++;
			printf("*");
		}
	}
	cPos = 0;
	printf("\n Confirm Password:");
	while(1){
		ch = getch();
		if(ch==13){ // Enter
			break;
		}else if(ch==8){ // BackSpace
			if(cPos>0){
				cPos--;
				pass2[cPos] = '\0';
				printf("\b \b");
			}
		}else if(ch==32||ch==9){ //Espaço ou Tab
			continue;
		}else{
			pass2[cPos] = ch;
			cPos++;
			printf("*");
		}
	}
	int valor = strcmp(pass,pass2);
	if(strlen(pass)>sizeof(pass)){
		printf("\n Password muito grande, tente outra vez\n");
		printf("\n Press any key to continue......");
		getch();
		registroPassword(password);
	}else if(strlen(pass)<6){
		printf("\n Password muito curta, tente outra vez\n");
		printf("\n Press any key to continue......");
		getch();
		registroPassword(password);
	}else if(valor!=0){
		printf("\n Passwords não coincidem!\n");
		printf("\n Press any key to continue......");
		getch();
		registroPassword(password);
	}else
		strcpy(password, pass);
}

//Registar Conta

//Estatistica Friendster

void mostrarEstatistica(){
	system("CLS");
	interface();
	//Ultimo user logado (Gravar em base de dados)
	FILE *lastlog;
	lastlog = fopen("lastlog","rb");
	if (lastlog == NULL){
		printf("1 ERROR: File not open");
		fclose(lastlog);
		lastlog = fopen("lastlog","ab");
		fclose(lastlog);
		printf("\nTry Again ....");
		getch();
		mostrarEstatistica();
	}
	struct user user;
	while(fread(&user,sizeof(user),1,lastlog)){
		printf("\n Ultima conta logada: %s %s - ID: %d",user.fName,user.lName,user.numeroConta);
	}
	fclose(lastlog);
	FILE *pubs;
	pubs = fopen("pubs","rb");
	if (pubs == NULL){
		printf("1 ERROR: File not open");
		fclose(pubs);
		pubs = fopen("pubs","ab");
		fclose(pubs);
		printf("\nTry Again ....");
		getch();
		mostrarEstatistica();
	}
	struct publicacao publicacao;
	int maxUsers = verificarIdConta();
	int i,totalPub=0,maxPub=0;
	char lN[50],fN[50],maxF[50],maxL[50];
	while(fread(&publicacao,sizeof(publicacao),1,pubs)){
		for(i=1;i<maxUsers;i++){
			if(i==publicacao.numeroConta){
				totalPub ++;
				strcpy(fN,publicacao.fname);
				strcpy(lN,publicacao.lname);
			}
		}
		if(totalPub>maxPub){
			maxPub = totalPub;
			strcpy(maxF,fN);
			strcpy(maxL,lN);
		}
	}
	fclose(pubs);
	FILE *log;
	log = fopen("bd1","rb");
	if (pubs == NULL){
		printf("1 ERROR: File not open");
		fclose(log);
		log = fopen("bd1","ab");
		fclose(log);
		printf("\nTry Again ....");
		getch();
		mostrarEstatistica();
	}
	int maxAmg=0,maxUti=0;
	while(fread(&user,sizeof(user),1,log)){
		maxUti++;
		if(user.amigos>maxAmg){
			maxAmg = user.amigos;
			strcpy(fN,user.fName);
			strcpy(lN,user.lName);
		}
	}
	fclose(log);
	pubs = fopen("pubs","rb");
	int maxPubs=0;
	while(fread(&publicacao,sizeof(publicacao),1,pubs)){
		maxPubs++;
	}
	fclose(pubs);
	//Utilizador com mais publicações
	printf("\n %s %s tem %d publicações!",maxF,maxL,maxPub);
	//Utilizador com mais amigos
	printf("\n %s %s tem %d amigos!",fN,lN,maxAmg);
	//Numero Total de Utilizadores	
	printf("\n Existem %d utilizadores criados!",maxUti);
	//Numero Total de Publicações
	printf("\n Existem %d publicações criadas!",maxPubs);
	int op;
	printf("\n\n 1) Voltar");
	printf("\n Opção: ");
	scanf("%d",&op);
	switch(op){
		case 1:
			main();
			break;
		default:
			printf("\n Opção invalida, tente novamente!");
			printf("\n Press any key to continue......");
			getch();
			mostrarEstatistica();
			break;
	}
}

//Estatistica Friendster

//Sair Programa

int sairPrograma(){
	exit(0);
}

//Sair Programa
