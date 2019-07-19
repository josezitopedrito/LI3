
#include "date.h"
#include "interface.h"
#include "estruturas.h"
#include "common.h"
#include <gmodule.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que armazena as informações essenciais duma pergunta */
struct question{
	/* Id da questão */
	long id;
	/* Data de criação da questão */
	long creationdate;
	/* ID do user que fez a questão */
	long owneruserid;
	/* Tags associadas a essa questão */
	char**tags;
	/* Número de tags */
	int numtag;
	/* Título da questão */
	char* title;
	/* Contagem do número de respostas associadas à questão */
	int answercount;
	/* IDs das respostas associadas à questão */
	GArray* answer;
};

/* Estrutura que armazena as informações essenciais duma resposta */
struct answer{
	/* ID da resposta */
	long id;
	/* Data de criação da resposta */
	long creationdate;
	/* ID da pergunta onde foi feita a resposta */
	long parentid;
	/* Score da resposta */
	int score;
	/* ID do user que fez esta resposta */
	long owneruserid;
	/* Número de comentários feitos na resposta */
	int commentcount;
};

//_____________________________________________________________________________________________________________

/* Estrutura que armazena as informações essenciais dum user */
struct auser{
	/* Nome do user */
	char* name;
	/* Bio do user */
	char* aboutme;
	/* Reputação do user */
	long reputation;
	/* ID do user */
	long id;
	/* Número de perguntas feitas pelo user */
	int numquestion;
	/* Apontadores das perguntas feitas pelo user */
	GPtrArray *questions;
	/* Número de respostas feitas pelo user */
	int numanswer;
	/* Apontadores das respostas feitas pelo user */
	GPtrArray *answer;
};

//_____________________________________________________________________________________________________________

/*
Transforma os vários longs dedicados a cada parâmetro duma data num único long 

param day Dia 
param month Mês
param year Ano
param hour Hora
param min Minuto
param sec Segundo
param msec Milissegundo

return (long) Data transformada em long
*/


long createData(long day, long month, long year, long hour, long min, long sec, long msec) {
    long aux=msec + sec*1000 + min*100000 + hour*10000000 + day*1000000000 + month*100000000000 + year*10000000000000;
    return aux;
}



//______________________________________________________________________________________________________________

/*
Getter que nos fornece o Id do User que escreveu a Answer fornecida como parâmetro

param Apontador para um tipo Answer

return Id do User que escreveu a Answer (long)
*/
long get_owidA(AAnswer a){
	return a->owneruserid;
}

//______________________________________________________________________________________________________________

/*
Função que é passada a um "foreach" que insere um par de longs (número de posts e id de um user) num array bidimensional organizado por ordem decrescente de número de posts.  

param idp Id do user.
param ap Apontador para o user a testar.
param arr Array bidimensional de longs ordenado por número de posts.
*/
void inserePar(gpointer idp, gpointer ap, gpointer arr){
	long *newid= idp;
	if(arr==NULL){
		printf("O array era nulo \n");
		return;
	}
	long (*arrp)[2] = arr;
	AUser a= (AUser) ap;
	int i, j;
	long N= arrp[0][0];

	if(((long)a->numquestion+a->numanswer)<=arrp[N][0])
		return;

	for(i=1;i<=N;i++){
		if(((long)a->numquestion+a->numanswer)>=arrp[i][0]) {
			for(j=N;j>i;j--){
				arrp[j][1]=arrp[j-1][1];
				arrp[j][0]=arrp[j-1][0];
			}
			arrp[i][0]=(a->numquestion+a->numanswer);
			arrp[i][1]=(long) newid;
			return;
		}
	}
	return;
}

//______________________________________________________________________________________________________________________
/*
Getter que fornece o score da Answer fornecida como parâmetro

param Apontador para um tipo Answer

return O score da Answer (long)
*/
int get_score (AAnswer a){
	return a->score;
}

/*
Getter que fornece o número de comentários da Answer fornecida como parâmetro

param Apontador para um tipo Answer

return Número de comentários da Answer (int)
*/
int get_numcomments(AAnswer a){
	return a->commentcount;
}

/*
Getter que fornece o nome do User fornecido como parâmetro

param Apontador para um tipo User

return O nome do User (char*)
*/
char* get_name(AUser a){
	return a->name;
}

/*
Getter que fornece o título da Question fornecida como parâmetro

param Apontador para um tipo Question

return O título da Question (char*)
*/
char* get_title(AQuestion a){
	return a->title;
}

/*
Getter que fornece o Id do User fornecido como parâmetro

param Apontador para um tipo User

return O Id do User (long)
*/
long get_id(AUser a){
	return a->id;
}

/*
Getter que fornece o score da Answer fornecida como parâmetro

param Apontador para um tipo Question

return O Id da Question (long)
*/
long get_qid(AQuestion a){
	return a->id;
}

/*
Getter que fornece o Id do User que escreveu a Question fornecida como parâmetro

param Apontador para um tipo Question

return O Id do User que escreveu a Question (long)
*/
long get_owid(AQuestion a){
	return a->owneruserid;
}

/*
Getter que fornece o Id da Question a qual a Answer fornecida como parâmetro responde

param Apontador para um tipo Answer

return O Id da Question a qual a Answer responde (long) 
*/
long get_pid(AAnswer a){
	return a->parentid;
}

/*
Getter que fornece as tags da Question fornecida como parâmetro

param Apontador para um tipo Question

return Array de tags da Question (char**)
*/
char** get_tags(AQuestion a){
	return a->tags;
}

/*
Getter que fornece o número de tags de uma Question fornecida como parâmetro

param Apontador para um tipo Question

return O número de tags que a Question tem (int)
*/
int get_numtag(AQuestion a){
	return a->numtag;
}

/*
Getter que fornece a data de criação da Question fornecida como parâmetro

param Apontador para um tipo Question

return A data de criação da Question (long)
*/
long get_creationdate (AQuestion a){
	return a->creationdate;
}

/*
Getter que fornece a reputação do User fornecido como parâmetro

param Apontador para um tipo User

return A reputação do User (long)
*/
long get_reputation(AUser a){
	return a->reputation;
}

/*
Getter que fornece o número de Questions do User fornecido como parâmetro

param Apontador para um tipo User

return O número de Questions do User (int)
*/
int get_numquestion(AUser a){
	return a->numquestion;
}

/*
Getter que fornece o número de Answers do User fornecido como parâmetro

param Apontador para um tipo User

return O número de Answers do User (int)
*/
int get_numanswer(AUser a){
	return a->numanswer;
}

/*
Função que incrementa em 1 o número de Questions do User fornecido como parâmetro 

param Apontador para um tipo user
*/
void inc_numquestion(AUser a){
	a->numquestion++;
}

/*
Função que incrementa em 1 o número de Answers do User fornecido como parâmetro 

param Apontador para um tipo user
*/
void inc_numanswer(AUser a){
	a->numanswer++;
}

/*
Getter que dá o pointer array de Answers do User fornecido como parâmetro

param Apontador para um tipo User

return Um apontador para o pointer array de Answers do User (GPtrArray*)
*/
GPtrArray* getAnsU(AUser a){
	return a->answer;
}

/*
Getter que dá o array de Answers da Question fornecida como parâmetro

param Apontador para um tipo Question

return Um apontador para o array de Answers da Question (GArray*)
*/
GArray* getAnsQ(AQuestion q){
	return q->answer;
}

/*
Getter que dá o pointer array de Questions do User fornecido como parâmetro

param Apontador para um tipo User

return Um apontador para o pointer array de Questions do User (GPtrArray*)
*/
GPtrArray* getQuesU(AUser a){
	return a->questions;
}
//_____________________________________________________________________________________________________________

/*
Função que cria um User, retornando um apontador para ele, e dando como parâmetros o seu nome, a sua reputação, a sua bio e o seu Id

param Uma string passará a ser o nome do User, um long que passará a ser a reputação do User, uma string que passará a ser a o bio do User e um long que passará a ser o Id do User

return Um apontador para um tipo User
*/
AUser createUser (char* nm,long rep,char* abt,long nid){
	AUser new;
	new = (AUser) malloc(sizeof(struct auser));
	if(strlen(nm)>0){
	new->name=(char*)malloc((strlen(nm)+1)*sizeof(char));
	strcpy(new->name,nm);
	}
	new->reputation=rep;
	if(strlen(abt)>0){
	new->aboutme=(char*)malloc((strlen(abt)+1)*sizeof(char));
	strcpy(new->aboutme,abt);
	}
	new->id=nid;
	new->numquestion=0;
	new->numanswer=0;
	new->questions= g_ptr_array_new();
	new->answer= g_ptr_array_new();
	return new;
}

/* 
Função que cria uma Answer, retornando um apontador para ela, e dando como parâmetros o seu Id, a sua data de criação, o Id da Question a qual responde, o score da Answer, o Id do User que escreveu e o número de comentários que a Answer tem

param Um long que passará a ser o Id da Answer, um long que passará a ser a data de criaçao da Answer, um long que passará a ser o Id da Question a qual a Answer em Question responde, um int que passará a ser o score da Answer,um long que passará a ser o Id do User que escreveu a Answer e um int que passará a ser numero de comentarios que Answers obteu 

return Um apontador para um tipo Answer
*/
AAnswer createAnswer (long id,long creationdate,long parentid,int scr,long owneruserid,int commentcount){
	AAnswer ans = (AAnswer) malloc(sizeof(struct answer));
	ans->id=id;
	ans->creationdate=creationdate;
	ans->parentid=parentid;
	ans->score=scr;
	ans->owneruserid=owneruserid;
	ans->commentcount=commentcount;
	return ans;
}

/*
Função que retira para um array de strings cada tag encontrada numa string. 

param str A string a dividir
param ntags Apontador para um int que corresponde ao número de tags encontradas.

return char** Array de strings, em que cada string é uma tag.
*/

char** gtags (char* str,int *ntags) {
   	
   	char meme[strlen(str)];
   	strcpy(meme, str);
   	const char s[3] = "<>";
   	char* token;
   	int c=0,i=0;
   	for(i=0;i<strlen(str);i++)
   		if(str[i]=='<')
   			c++;
   	if (c==0){
   		(*ntags)=0;
   		return NULL;
	}
   	char* ptags[c];
   
   	token = strtok(meme, s);
    
    i=0;
   	while( token != NULL ) {
     	ptags[i++]=mystrdup(token);
        token = strtok(NULL, s);
   	}

   	char** ret= malloc((i+1)*sizeof(long));
   	for(i=0;i<c;i++)
   		ret[i]=ptags[i];
   	ptags[i]=NULL;

   	(*ntags)=c;
	return ret;
}

/*
Função que cria uma Question, retornando um apontador para a Question, e dando como parametros o seu Id, a sua data de criaçao, o Id do User que criou a Question, o conjunto das tags da Question, o titulo da Question e o numero de Answers

param Um long que passará a ser o Id da Question, um long que passará a ser a data de criação da Question, um long que passará a ser o Id do User que escreveu a Question, uma string que passará a ser o concat das tags da Question, uma string que passará a ser o título da Question e o um int que passará a ser o número de Answers que a Question tem

return Um apontador para um tipo Question
*/
AQuestion createQuestion (long id,long creationdate,long owneruserid,char* strtags,char* title,int answercount){
	AQuestion ques = (AQuestion) malloc(sizeof(struct question));
	ques->id=id;
	ques->creationdate=creationdate;
	ques->owneruserid=owneruserid;
	ques->tags= gtags(strtags, &(ques->numtag));
	ques->title= mystrdup(title);
	//ques->title=(char*)malloc((strlen(title)+1)*sizeof(char));
	//strcpy(ques->title,title);
	ques->answercount=answercount;
	ques->answer= g_array_new (FALSE, FALSE, sizeof (long));
	return ques;
}


/*
Função que compara dois constpointers que depois sao casted para apontadores de questões (AQuestion), esta função retorna um int que depende do resultado da comparação de datas de criação

param Dois gconstpointers

return Um int que varia consoante a comparação
*/
int comp(gconstpointer a,gconstpointer b){
	AQuestion q1 = (AQuestion) a;
	AQuestion q2 = (AQuestion) b;
	if((q1->creationdate)>(q2->creationdate))
		return -1;
	if((q1->creationdate)<(q2->creationdate))
		return 1;
	else
		return 0;
}
//_________________________________________________________________________________________
//QUERY 3

/*
Função que fornece permissão para obter um long que aumenta conforme a idade e o quão recente é a data

param Uma data do tipo definido pelos docentes

return A data alterada para o benefício do trabalho (long)
*/
long convert(Date a){
	long year=(long)get_year(a);
	long month=(long)get_month(a);
	long day=(long)get_day(a);
	return (1000000000*day + 100000000000*month + 10000000000000*year);
}

/*
Função de comparação que verifica se a data de uma Question se encontra entre duas outras datas

param Três gpointers
*/
void faux1(gpointer a,gpointer b, gpointer c){
	AQuestion new = (AQuestion) b;
	long (*array) = c;
	if((array[0]<=new->creationdate)&&(new->creationdate<=array[1]))
		array[2]++;
}

/*
Função de comparaçao que verifica se a data de uma Answer se encontra entre duas outras datas

param Tres gpointers
*/
void faux2(gpointer a,gpointer b, gpointer c){
	AAnswer new = (AAnswer) b;
	long (*array) = c;
	if((array[0]<=new->creationdate)&&(new->creationdate<=array[1]))
		array[2]++;
}


//_________________________________________________________________________________________
//QUERY 4

/*
Função que procura num array de strings a string dada.

param big Array de strings.
param small String a procurar.

return int 1 se encontrar a string, 0 caso contrário.
*/


int searchT(char** big,char* small, int numtag){
	if(big==NULL || small == NULL || numtag==0)
		return 0;
	int i, j;
	for(i=0;i<numtag;i++){
		for(j=0;(big[i][j]==small[j]);j++)
			if(big[i][j]=='\0')
				return 1;
	}
	return 0;
}


//_________________________________________________________________________________________

// query 5
/*
Getter que dá a bio do User fornecido como parâmetro

param Apontador para um tipo User

return A bio de um User (char*)
*/
char* get_thisbio(AUser a){
	return a->aboutme;
}

/*
Função que organiza as questões dadas por datas

param ap AQuestion dado 
param arr matriz de 2 dimensões onde será inserido
*/

void insereParDateQ(gpointer ap, gpointer arr){
	if(arr==NULL){
		printf("O array era nulo \n");
		return;
	}
	long (*arrp)[2] = arr;
	AQuestion a= (AQuestion) ap;
	int i, j;
	if(get_owid(a)!= (arrp[1][0]))
		return;
	long data = a->creationdate;
	long N= arrp[0][0];
	if(data<=arrp[N][0])
		return;
	for(i=2;i<=N+1;i++){
		if(data>=arrp[i][0]) {
			for(j=N+1;j>i;j--){
				arrp[j][1]=arrp[j-1][1];
				arrp[j][0]=arrp[j-1][0];
			}
			arrp[i][0]=data;
			arrp[i][1]=a->id;
			return;
		}
	}
	return;
}

/*
Função que organiza as respostas dadas por datas

param ap AAnswer dado 
param arr matriz de 2 dimensões onde será inserido
*/

void insereParDateA(gpointer ap, gpointer arr){
	if(arr==NULL){
		printf("O array era nulo \n");
		return;
	}
	long (*arrp)[2] = arr;
	AAnswer a= (AAnswer) ap;
	int i, j;
	if(get_owidA(a)!= (arrp[1][0]))
		return;
	long data = a->creationdate;
	long N= arrp[0][0];
	if(data<=arrp[N][0])
		return;
	for(i=2;i<=N+1;i++){
		if(data>=arrp[i][0]) {
			for(j=N+1;j>i;j--){
				arrp[j][1]=arrp[j-1][1];
				arrp[j][0]=arrp[j-1][0];
			}
			arrp[i][0]=data;
			arrp[i][1]=a->id;
			return;
		}
	}
	return;
}




//_______________________________________________________________________________________
//QUERY 6
/*
Função que pega em dois constpointers que depois são casted para apontadores de Answer (AAnswer) e organizam as duas Answers conforme o seu score

param Dois gconstpointers

return Um int que depende do resultado da comparaçao de score
*/
int compVotes(gconstpointer a,gconstpointer b){
	AAnswer q1 = (AAnswer) a;
	AAnswer q2 = (AAnswer) b;
	if((q1->score)>(q2->score))
		return -1;
	if((q1->score)<(q2->score))
		return 1;
	else
		return 0;
}

/*
Getter que dá a data de criação da Answer fornecida como parâmetro

param Apontador para um tipo Answer

return A data de criação da Answer (long)
*/
long get_creationdateA (AAnswer a){
	return a->creationdate;
}

/* 
Getter que dá o Id da Answer fornecida como parâmetro

param Apontador para um tipo Answer

return O Id da Answer (long)
*/
long get_aid(AAnswer a){
	return a->id;
}
//_______________________________________________________________________________________

/* 
Funçao que pega em dois constpointers que depois são casted para apontadores de Questions (AQuestion), e compara o número de Answers que cada Question tem

param Dois gconstpointers

return Um int que depende do resultado da comparação de número de Answers
*/
int compAnsc(gconstpointer a,gconstpointer b){
	AQuestion q1 = (AQuestion) a;
	AQuestion q2 = (AQuestion) b;
	if((q1->answercount)>(q2->answercount))
		return -1;
	if((q1->answercount)<(q2->answercount))
		return 1;
	else
		return 0;
}

//______________________________________________________________________________________
//QUERY 7

/*
Função que insere todos os ids pertencentes ao periodo de tempo dado (a data do inicio e do fim encontram-se na primeira e segunda posição do GArray dado, que depois serão eliminados)

param data AQuestion a ser analizado 
param user_data GArray onde vai ser inserido os ids das perguntas no periodo de tempo dado
*/

void addDate(gpointer data,gpointer user_data){
	AQuestion new = (AQuestion) data;
	GArray* array = (GArray*) user_data;
	if((g_array_index(array,long,0)<(new->creationdate))&&((new->creationdate)<g_array_index(array,long,1))){
		long i = get_qid(new);
		g_array_append_val(array,i);
	}
	return;
}


/*
Função que insere por ordem decrescente o id, dependendo do nº de respostas dessa pergunta

param final matriz de 2 dimensões onde será inserido o id e o nº de respostas calculadas para serem comparadas 
param val id da pergunta a ser inserida
param numres nº respostas calculadas para o val
param N tamanho do array resp 
*/
void insertInFinal(long final[][2],long val,long numres,int N){
	int i,j;
	for(i=0;i<N;i++){
		if(numres>=final[i][1]) {
			for(j=N-1;j>i;j--){
				final[j][1]=final[j-1][1];
				final[j][0]=final[j-1][0];
			}
			final[i][0]=val;
			final[i][1]=numres;
			return;
		}
	}
}


/*
Função que organiza a matriz pelo número de respostas de cada id

param final matriz de 2 dimensões onde será inserido o id e o nº de respostas calculadas para serem comparadas 
param aux GArray com os ids das perguntas
param resp array com o nº respostas calculadas
param N tamanho do array resp e do GArray
*/
void orgbyNumAns(long final[][2],GArray* aux,long resp[],int N){
	int i;
	for(i=0;i<N;i++){
		long val=g_array_index(aux,long,i);
		long numres = resp[i];
		insertInFinal(final,val,numres,N);
	}
	return;
}

//_______________________________________________________________________________________
//AS DUAS FUNÇOES DE BAIXO SAO PARA A QUERY 8

/*
Função que verifica se uma string esta contida noutra

param Duas strings

return Boleano (1 se está contida, 0 se não está)
*/
int isThere(char* x,char* word){
	if (x==NULL || word==NULL)
		return 0;
	int i=0,j,aux;
	while(x[i]!='\0'){
		if((i==0 && (x[i]==word[0])) || ((x[i]==word[0]) && (x[i-1] ==' '))){
			for(j=i,aux=0;x[j]==word[aux];j++,aux++){
				if((word[aux+1]=='\0') && (x[j+1]==' ' || x[j+1]=='\0' || x[j+1]=='!' || x[j+1]=='?' || x[j+1]=='.' || x[j+1]==',')){
					return 1;
				}
			}
		}
		i++;
	}
	return 0;
}

/*
Função que recebe um apontador para uma Question e uma palavra e verifica se essa palavra está contida no título

param Apontador para um tipo Question e uma string

return A Question se a palavra estiver contida e NULL se não estiver contida
*/
AQuestion searchW(AQuestion q,char* word){
	if (get_qid(q)== 186936)
		printf("resultado da funcao %d, com a bicharia %ld", isThere(q->title,word), get_qid(q));
	if(isThere(q->title,word)==1){
		return q;
	}
	return NULL;
}


//___________________________________________________________________________________________-
//FUNÇÕES PARA A QUERY 11

/*
Função que recebe dois constpointers que depois são casted para apontadores de users (AUser), e compara as reputações dos Users

param Dois gconstpointers

return Um int que depende do resultado da comparação de reputação
*/
int comprep(gconstpointer a,gconstpointer b){
	AUser q1 = (AUser) a;
	AUser q2 = (AUser) b;
	if((q1->reputation)>(q2->reputation))
		return -1;
	if((q1->reputation)<(q2->reputation))
		return 1;
	else
		return 0;
}


//_______________________________________________________________________________________________________________

/*
Função que elimina da memória uma estrutura do tipo AUser duma GHashTable. 

param key Chave do elemento da GHashTable.
param value Apontador para uma AUser.
param user_data Apontador para dados que o utilizador possa querer passar à função (não utilizado, neste caso).

return gboolean 1 se a eliminação correr bem, 1 caso contrário.
*/

gboolean freeElemHTU (gpointer key,gpointer value,gpointer user_data){
	AUser a = (AUser) value;
	if(a){
		if(a->name)
			free(a->name);
		if(a->aboutme)
			free(a->aboutme);
		if(a->questions)
			g_ptr_array_free (a->questions,TRUE);
		if(a->answer)
			g_ptr_array_free (a->answer,TRUE);
		free (a);
		return 1;
	}
	return 0;
}

/*
Função que elimina da memória uma estrutura do tipo AQuestion duma GHashTable. 

param key Chave do elemento da GHashTable.
param value Apontador para uma AQuestion.
param user_data Apontador para dados que o utilizador possa querer passar à função (não utilizado, neste caso).

return gboolean 1 se a eliminação correr bem, 1 caso contrário.
*/
gboolean freeElemHTQ (gpointer key,gpointer value,gpointer user_data){
	AQuestion a = (AQuestion) value;
	int i;
	if(a){
		if(a->numtag>0){
			for(i=0;i<(a->numtag);i++)
				free(a->tags[i]);
			free(a->tags);
		}
		if(a->title)
			free(a->title);
		if(a->answer)
			g_array_free (a->answer, TRUE);
		free(a);
		return 1;
	}
	return 0;
}

/*
Função que elimina da memória uma estrutura do tipo AAnswer duma GHashTable. 

param key Chave do elemento da GHashTable.
param value Apontador para uma AAnswer.
param user_data Apontador para dados que o utilizador possa querer passar à função (não utilizado, neste caso).

return gboolean 1 se a eliminação correr bem, 1 caso contrário.
*/
gboolean freeElemHTA (gpointer key,gpointer value,gpointer user_data){
	AQuestion a = (AQuestion) value;
	if(a){
		free(a);
		return 1;
	}
	return 0;
}