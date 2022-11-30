#include <stdio.h>
#include <time.h>
#include <locale.h> 

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
	
}

void registerConta(){
	
}
