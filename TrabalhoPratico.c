#include <stdio.h>
#include <time.h>
#include <locale.h> 

struct login //Estrutura de login
{
    char fname[30];
    char lname[30];
    char username[30];
    char password[20];
};

void interface();
int loginRegister();
void loginConta();
void registerConta();

int main(){
	setlocale(LC_ALL, "Portuguese"); //Mudar lingua para portugues devido aos acentos
	interface(); //Desenhar Logo
	int op = loginRegister(); //User quer dar login ou register
	if(op){
		if(op==1)
			loginConta();
		else
			registerConta();
	}else{
		return -1;
	}
	
	system("CLS"); // server para limpar a tela
	
	time_t horario; //time_t é um tipo de varial para horario
	struct tm * timeinfo; //broken-down calendar time type: year, month, day, hour, minute, second
	time(&horario); //Da return ao horario do sistema na variavel horario
	timeinfo = localtime(&horario); //O valor do horario é dividido na estrutura tm e expresso no fuso horario local
	printf("%02d:%02d:%02d", timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec); //horas,minutos e segundos
	
	return 0;
}

void interface(){
	//Desenhar Logo
	puts("");
    puts("¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦¦      ¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦¦");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦¦¦     ¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦       ¦¦¦");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦¦¦¦    ¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦       ¦¦¦");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦ ¦¦¦   ¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦       ¦¦¦");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦  ¦¦¦  ¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦¦");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦   ¦¦¦ ¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦    ¦¦¦   ");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦    ¦¦¦¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦     ¦¦¦  ");
    puts("     ¦¦¦              ¦¦¦         ¦¦¦     ¦¦¦¦¦    ¦¦¦       ¦¦¦    ¦¦¦              ¦¦¦      ¦¦¦ ");
    puts("     ¦¦¦         ¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦      ¦¦¦¦    ¦¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦¦¦¦¦¦¦    ¦¦¦       ¦¦¦");
    puts("");
}

int loginRegister(){
	int op;
	puts("1) Acessar Conta \t 2) Criar Conta");
	printf("Opção: ");
	scanf("%d",&op);
	if(op==1||op==2){
		return op;
	}else{
		printf("Opção invalida");
		return 0;
	}
}

void loginConta(){
	char username[30],password[20];
    FILE *log;

    log = fopen("login.txt","r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        fopen("login.txt", "wb");
    }

    struct login l;

    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:  ");
    fgets(username, 30, stdin);
    printf("\nPassword: ");
    printf("\n");
    fgets(password, 20, stdin);

    while(fread(&l,sizeof(l),1,log))
        {
        if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)

            {   
                printf("\nSuccessful Login\n");
            }
        else 
            {
                printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
            }
        }

    fclose(log);

    return;
}

void registerConta(){
	char firstname[15];
    FILE *log;

    log=fopen("login.txt","w");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        fopen("login.txt", "wb");
    }


    struct login l;

    printf("\nWelcome to your online course provider. We need to enter some details for registration.\n\n");
    printf("\nEnter First Name:\n");
    scanf("%c",l.fname);
    printf("\nEnter Surname:\n");
    scanf("%s",l.lname);

    printf("Thank you.\nNow please choose a username and password as credentials for system login.\nEnsure the username is no more than 30 characters long.\nEnsure your password is at least 8 characters long and contains lowercase, uppercase, numerical and special character values.\n"); 

    printf("\nEnter Username:\n");
    scanf("%s",l.username);
    printf("\nEnter Password:\n");
    scanf("%s",l.password);


    fwrite(&l,sizeof(l),1,log);
    fclose(log);

    printf("\nConfirming details...\n...\nWelcome, %s!\n\n",firstname);
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");
        getchar();
    system("CLS");
    login();
}
