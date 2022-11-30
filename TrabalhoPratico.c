#include <stdio.h>
#include <time.h>

/*
	Registro de Utilizador
	Acesso autenticado pelo Utilizador
	Acesso a rede social em modo anonimo
	Acesso a informação estatistica
	Um User so pode ter ate X (defenido no codigo) de amigos
	Qualquer pessoa pode se tornar amigo de outro user registado na app
	Registro:
		Nome
		Email
		Data de Nascimento
		Numero de telemovel
	So pode fazer publicaçoes depois de login
	Publicação:
		Apenas texto(ate 150 caracteres)
		Data de publicação
		Identificação do criador
	Tipo de Publicação:
		Publica (Visivel por qualquer pessoa, inclusive para quem nao esta registado na app)
		Reservada (Apanas visivel para quem esta registrado na app)
		Privada (Apenas visivel para quem segue o criador)
	User:
		Pode mudar informações mas nao username
		Consultar a lista de amigos
		Criar publicações
		Ver as publicações dos amigos sendo eleas publicas, reservadas ou privadas
	Todos os dados teram de ser armazenados em ficheiros
	As publicações podem ser editadas ou ate removidas
	As amizades podem ser eliminadas
	Estatisticas da App:
		Utilizador com mais publicações
		Ultimo utilizador logado
		Numero Total de utilizadores
		Numero Total de Publicações
		Utilizador com mais amigos
		
	Sugestoes para valorizar o trabalho (aka tirar 20):
		Criar um user admin (sysadm)
			Consegue ver os dados de todos os utilizadores
			Consegue ver todas as publicações
			Consegue ver todas as amizades
		Ter uma sugestao de amizades conforme os seus amigos
		Ter uma opção de perfil privado,ou seja, so podem seguir se ele tiver o perfil publico	
*/

int main()
{
	time_t horario; //time_t é um tipo de varial para horario
	struct tm * timeinfo; //broken-down calendar time type: year, month, day, hour, minute, second
	time(&horario); //Da return ao horario do sistema na variavel horario
	timeinfo = localtime(&horario); //O valor do horario é dividido na estrutura tm e expresso no fuso horario local
	printf("%02d:%02d:%02d", timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec); //horas,minutos e segundos
	
	return 0;
}
