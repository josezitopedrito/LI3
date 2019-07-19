#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"
#include "estruturas.h"
#include <stdlib.h>
#include <gmodule.h>
#include <stdio.h>
#include "getter.h"
#include "interface.h"

typedef struct TCD_community{
	GHashTable *HTU;
	GHashTable *HTQ;
	GHashTable *HTA;
	GHashTable *HTT;
}TCD_community;

TAD_community init(){
	TAD_community new = (TAD_community) malloc(sizeof(TCD_community));
	return new;
}

/* 
Load:
Dado um apontador TAD community e uma string com o caminho para
a pasta dos ficheiros xml, esta função trata de chamar funções
do getter.c para carregar devidamente os dados para a estrutura
a utilizar nas queries.
*/
TAD_community load(TAD_community com, char* dump_path){
	char buff[1024];
	sprintf(buff, "%sUsers.xml", dump_path);
	com->HTU= fromUsers(buff);

	com->HTQ = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);
	com->HTA = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);
	com->HTT = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, NULL);
	sprintf(buff, "%sPosts.xml", dump_path);
	fromPosts(com->HTU, com->HTQ, com->HTA, buff);

	sprintf(buff, "%sTags.xml", dump_path);
	fromTags(com->HTT, buff);
	g_hash_table_foreach(com->HTA,auxAinQ,com->HTQ);

	return com;
}

/*
Query 1:
Dado o identificador de um post, a função deve retor-
nar o tı́tulo do post e o nome (não o ID) de utilizador do autor 3 . Se o post
for uma resposta, a função deverá retornar informações (tı́tulo e utilizador)
da pergunta correspondente.
*/
STR_pair info_from_post(TAD_community com, long id){
	if((g_hash_table_lookup(com->HTQ,GSIZE_TO_POINTER(id)))!=NULL){
		AQuestion q=g_hash_table_lookup(com->HTQ,GSIZE_TO_POINTER(id));
		long idu = get_owid(q);
		AUser u = g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(idu));
		return create_str_pair(get_title(q),get_name(u));
	}
	else if ((g_hash_table_lookup(com->HTA,GSIZE_TO_POINTER(id)))!=NULL){
		AAnswer an=g_hash_table_lookup(com->HTA,GSIZE_TO_POINTER(id));
		int idi=get_pid(an);
		AQuestion q=g_hash_table_lookup(com->HTQ,GINT_TO_POINTER(idi));
		long idu = get_owid(q);
		AUser u = g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(idu));
		return create_str_pair(get_title(q),get_name(u));
	}
	else return create_str_pair(NULL,NULL);
}  


/*
Query 2:
Pretende obter o top N utilizadores com maior número
de posts de sempre. Para isto, devem ser considerados tanto perguntas
quanto respostas dadas pelo respectivo utilizador.
*/
LONG_list top_most_active(TAD_community com, int N){
	LONG_list l=create_list(N);
	int i;
	if(N <= 0) return NULL;
	long lp[N+1][2];
	for(i=0;i<=N;i++){
		lp[i][0]=0;//tem numero
		lp[i][1]=0;//tem id
	}
	lp[0][0]=N;

    g_hash_table_foreach(com->HTU,inserePar,lp);
    
    for(i=0;i<N;i++){
    	set_list(l,i,lp[i+1][1]);
    }

    return l;
}

/* 
Query 3:
Dado um intervalo de tempo arbitrário, obter o número
total de posts (identificando perguntas e respostas separadamente) 
neste perı́odo.
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	long aux1[3];
	aux1[0]=convert(begin);
	aux1[1]=convert(end)+1000000000;
	aux1[2]=0;
	long aux2[3];
	aux2[0]=convert(begin);
	aux2[1]=convert(end)+1000000000;
	aux2[2]=0;
	g_hash_table_foreach(com->HTQ,faux1,aux1);
	g_hash_table_foreach(com->HTA,faux2,aux2);
	LONG_pair p=create_long_pair(0,0);
	set_fst_long(p,aux1[2]);
	set_snd_long(p,aux2[2]);
	return p;
}


/* 
Query 4:
Dado um intervalo de tempo arbitrário, retornar todas
as perguntas contendo uma determinada tag. O retorno da função deverá ser
uma lista com os IDs das perguntas ordenadas em cronologia inversa.
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	long a=convert(begin);
	long b=convert(end)+1000000000;
	GList* new = g_hash_table_get_values(com->HTQ);
	new = g_list_sort(new,comp);
	int n = g_list_length(new);
	int i=0;

	while ((i<n)){
		if(((get_creationdate(g_list_nth_data(new,i))>a) && (get_creationdate(g_list_nth_data(new,i))<b))&& (searchT (get_tags(g_list_nth_data(new,i)),tag, get_numtag(g_list_nth_data(new,i))))){
			i++;
		}
		else{
			new=g_list_delete_link(new, g_list_nth(new, i));
			n--;
		}
	}
	
	LONG_list l = create_list(n);
	for(i=0;i<n;i++){
    	set_list(l,i,get_qid(g_list_nth_data(new, i)));
    }

    g_list_free(new);
    return l;
}


/* 
Query 5:
Dado um ID de utilizador, devolver a informação do
seu perfil (short bio) e os IDs dos seus 10 últimos posts (perguntas ou res-
postas), ordenados por cronologia inversa.
*/
USER get_user_info(TAD_community com, long id){
	AUser usr = g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id));
	long p_h[10];
	int i,j,k;
	for(i=0;i<10;i++)
		p_h[i]=0;
	if(!usr){
		return create_user("No user",p_h);
	}
	char* bio = get_thisbio (usr);
	long lq[12][2];
	long la[12][2];
	for(i=0;i<12;i++){
		lq[i][0]=0;//tem numero
		lq[i][1]=0;//tem id
		la[i][0]=0;//tem numero
		la[i][1]=0;//tem id
	}
	lq[0][0]=10;
	la[0][0]=10;
	lq[1][0]=id;
	la[1][0]=id;
    g_ptr_array_foreach(getQuesU(usr),insereParDateQ,lq);
    g_ptr_array_foreach(getAnsU(usr),insereParDateA,la);
	for(i=0,j=2,k=2;i<10;i++){
		if(j<12 && k<12 && lq[j][0]<=la[k][0]){
           p_h[i]=la[k][1];
           k++;
       }
       else if(j<12 && k<12 && lq[j][0]>la[k][0]){
           p_h[i]=lq[j][1];
           j++;
       }
       else{
           if(j<12){
               p_h[i]=lq[j][1];
               j++;
           }
           else{
               p_h[i]=la[k][1];
               k++;
           }
		}
	}
	
	USER ur = create_user(bio,p_h);
	return ur;
}


/* 
Query 6:
Dado um intervalo de tempo arbitrário, devolver os
IDs das N respostas com mais votos, em ordem decrescente do número de
votos; O número de votos deverá ser obtido pela diferença entre Up Votes
(UpMod 6 ) e Down Votes (DownMod).
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	long a=convert(begin);
	long b=convert(end)+1000000000;
	GList* new = g_hash_table_get_values(com->HTA);
	new = g_list_sort(new,compVotes);
	LONG_list l = create_list(N);
	int i=0,n=0;
	while(i<N && (new)){
		long date = get_creationdateA(g_list_nth_data(new,n));
		if(a<=date && date<=b){
			set_list(l,i,get_aid(g_list_nth_data(new,n)));
			i++;
		}
		n++;
	}

    g_list_free(new);
	return l;
}


/* 
Query 7:
Dado um intervalo de tempo arbitrário, devolver as
IDs das N perguntas com mais respostas, em ordem decrescente do número
de respostas.
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	long a=convert(begin);
	long b=convert(end)+1000000000;
	GList* new = g_hash_table_get_values(com->HTQ);
	new = g_list_sort(new,comp);
	GArray* aux = g_array_new (FALSE, FALSE, sizeof (long));
	g_array_append_val(aux,a);
	g_array_append_val(aux,b);
	g_list_foreach(new,addDate,aux);
	g_array_remove_index(aux,0);
	g_array_remove_index(aux,0);
	int i,j;
	int Na = aux->len;
	long resp[Na];
	long final[Na][2];
	for(i=0;i<Na;i++){
		AQuestion q = g_hash_table_lookup(com->HTQ,GSIZE_TO_POINTER(g_array_index(aux,long,i)));
		GArray* qarray = getAnsQ(q);
		resp[i]=0;
		final[i][0]=0;
		final[i][1]=0;
		for(j=0;j<(qarray->len);j++){
			if((a<get_creationdateA(g_hash_table_lookup(com->HTA,GSIZE_TO_POINTER(g_array_index(qarray,long,j))))) && (get_creationdateA(g_hash_table_lookup(com->HTA,GSIZE_TO_POINTER((g_array_index(qarray,long,j)))))<b)){
				resp[i]++;
			}
		}
	}
	orgbyNumAns(final,aux,resp,Na);
    LONG_list l;
    if(Na>N){
    	l = create_list(N);
    	for (i=0;i<N;i++){
    		set_list(l,i,final[i][0]);
    	}
    }
    else{
    	l = create_list(Na);
    	for (i=0;i<Na;i++){
    		set_list(l,i,final[i][0]);
    	}
    }
    g_array_free(aux, TRUE);
    g_list_free(new);
	return l;
}


/* 
Query 8:
Dado uma palavra, devolver uma lista com os IDs de
N perguntas cujos tı́tulos a contenham, ordenados por cronologia 
inversa.
*/
LONG_list contains_word(TAD_community com, char* word, int N){
	LONG_list l = create_list(N);
	int i=0,n=0;
	GList* new = g_hash_table_get_values(com->HTQ);
	new = g_list_sort(new,comp);

	while((i<N) && (new)){
		if(searchW(g_list_nth_data(new,n),word)){
			set_list(l,i,(get_qid(g_list_nth_data(new,n))));
			i++;
		}
		n++;
	}

	g_list_free(new);
	return l;
}

/* 
Query 9:
Dados os IDs de dois utilizadores, devolver as últimas
N perguntas (cronologia inversa) em que participaram dois utilizadores es-
pecı́ficos. Note que os utilizadores podem ter participado via pergunta ou
respostas.
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	int i,n;
	GList* lista=NULL;

	if((g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1))==NULL) || (g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2))==NULL))
		return NULL;

	GPtrArray *aux1= getQuesU(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)));
	GPtrArray *aux2= getQuesU(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)));
	GPtrArray *aux3= getAnsU(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)));
	GPtrArray *aux4= getAnsU(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)));
		
	//id1 é pergunta id2 é resposta
	if((get_numquestion(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)))!=0) && (get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)))!=0)){
		for(i=0;i<get_numquestion(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)));i++){
			for(n=0;n<get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)));n++){
				if((AAnswer)g_ptr_array_index(aux4,n)!=NULL)
					if(get_qid((AQuestion)g_ptr_array_index(aux1,i))==get_pid((AAnswer)g_ptr_array_index(aux4,n))){
						lista=g_list_append(lista,(AQuestion)g_ptr_array_index(aux1,i));
					}
			}
		}
	}
	//id2 é pergunta id1 é resposta
	if((get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)))!=0) && (get_numquestion(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)))!=0)){
		for(i=0;i<get_numquestion(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)));i++){
			for(n=0;n<get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)));n++){
				if((AAnswer)g_ptr_array_index(aux3,n)!=NULL)
					if(get_qid((AQuestion)g_ptr_array_index(aux2,i))==get_pid((AAnswer)g_ptr_array_index(aux3,n))){
						lista=g_list_append(lista,(AQuestion)g_ptr_array_index(aux2,i));
					}
			}
		}
	}
	//id1 e id2 sao ambos respostas
	if((get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)))!=0) && (get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)))!=0)){
		for(i=0;i<get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id1)));i++){
			for(n=0;n<get_numanswer(g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(id2)));n++){
				if(((AAnswer)g_ptr_array_index(aux3,i)!=NULL) && ((AAnswer)g_ptr_array_index(aux4,n)!=NULL))
					if(get_pid((AAnswer)g_ptr_array_index(aux3,i))==get_pid((AAnswer)g_ptr_array_index(aux4,n))){
						lista=g_list_append(lista,g_hash_table_lookup(com->HTQ,GSIZE_TO_POINTER(get_pid((AAnswer)g_ptr_array_index(aux3,i)))));
					}
			}
		}
	}
	
	//remover ids repetidos
	for(i=0;i<g_list_length(lista)-1;i++){
		for(n=i+1;n<g_list_length(lista);n++){	
			if(get_qid(g_list_nth_data(lista,i))==get_qid(g_list_nth_data(lista,n))){
				lista=g_list_delete_link(lista, g_list_nth(lista, n));
				n--;
			}
		}
	}
	
	lista = g_list_sort(lista,comp);

	LONG_list l = create_list(N);


	for(i=0;i<N;i++){
		if(i<(g_list_length(lista)))
			set_list(l,i,get_qid(g_list_nth_data(lista,i)));
		else
			set_list(l,i,0);
	}
	g_list_free(lista);
	return l;
}
/* 
Query 10:
Dado o ID de uma pergunta, obter a melhor resposta.
Para isso, deverá usar a função de média ponderada abaixo:
(Scr × 0.45) + (Rep × 0.25) + (V ot × 0.2) + (Comt × 0.1)
onde,
• Scr - score da resposta;
• Rep - reputação do utilizador;
• V ot - número de votos recebidos pela resposta;
• Comt - número de comentários recebidos pela resposta;
*/
long better_answer(TAD_community com, long id){
	GArray* aux = g_array_new (FALSE, FALSE, sizeof (float));
	AQuestion ques = g_hash_table_lookup(com->HTQ,GSIZE_TO_POINTER(id));
	GArray* qans = getAnsQ(ques);
	int i;
	int N = (qans)->len;
	long ide=0;
	float val=0;
	float rep,f;

	for(i=0;i<N;i++){
		rep=0;
		f=0;
		long idanswer = g_array_index(qans,long,i);
		AAnswer an = g_hash_table_lookup(com->HTA,GSIZE_TO_POINTER(idanswer));
		long idusr = get_owidA(an);
		AUser prep = g_hash_table_lookup(com->HTU,GSIZE_TO_POINTER(idusr));
		rep = 0.25 * get_reputation(prep);
		f = (0.65 * (get_score(an))) + (0.1 * (get_numcomments(an)));
		f+=rep;
		g_array_append_val(aux,f);
	}
	if(N==0){
		return 0;
	}
	ide = g_array_index(qans,long,0);
	val = g_array_index(aux,float,0);
	for(i=1;i<N;i++){
		if(g_array_index(aux,float,i) > val){
			ide= g_array_index(qans,long,i);
			val = g_array_index(aux,float,i);
		}
	}
	g_array_free(aux, TRUE);
	return ide;
}

/* 
Query 11:
Dado um intervalo arbitrário de tempo, devolver os
identificadores das N tags mais usadas pelos N utilizadores com melhor re-
putação. Em ordem decrescente do número de vezes em que a tag foi usada.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	int i=0, j=0, k=0, l=0;
	long dd;

	long a=convert(begin);
	long b=convert(end)+1000000000;
	long tempid;
	long tempcount;
	
	GList* new = g_hash_table_get_values(com->HTU);
	new = g_list_sort(new,comprep);
	LONG_list lst = create_list(N);
	GList* tags=NULL;
	GList* questions=NULL;
	char** taux;
	for(i=0;i<N;i++){
		for(j=0;j<get_numquestion(g_list_nth_data (new,i));j++){
			dd=get_creationdate((AQuestion)g_ptr_array_index(getQuesU(g_list_nth_data(new,i)),j));
			if((dd > a) && (dd < b)){
				questions=g_list_append(questions, (AQuestion)g_ptr_array_index(getQuesU(g_list_nth_data(new,i)),j));
			}
		}
	}

	for(i=0;i<g_list_length(questions);i++){
		taux= get_tags(g_list_nth_data(questions,i));
		for(j=0;j<get_numtag(g_list_nth_data(questions,i));j++){
			tags= g_list_append(tags,taux[j]);
		}
	}
	
	long arl[N][2];
	for (i=0;i<N;i++){
		arl[i][0]=0;	//id
		arl[i][1]=0;	//count
	}

	for (i=0;i<g_list_length(tags);i++){
		tempid=0;
		tempcount=0;
		tempid=(long)GPOINTER_TO_SIZE (g_hash_table_lookup(com->HTT,g_list_nth_data(tags,i)));
		for(j=0;j<g_list_length(questions);j++){
			tempcount+=(long)searchT(get_tags(g_list_nth_data(questions,j)),g_list_nth_data(tags,i), get_numtag(g_list_nth_data(questions,j)));
		}
		
		if(tempcount>arl[N-1][1]){
			for(k=0;k<N;k++){
				if(arl[k][0]==tempid)
					break;
				if(tempcount>arl[k][1]) {
					for(l=N-1;l>k;l--){
							arl[l][1]=arl[l-1][1];
							arl[l][0]=arl[l-1][0];
					}
					arl[l][0]=tempid;
					arl[l][1]=tempcount;
					k=N;
				}		
			}
		}
	}

	for(i=0;i<N;i++){
    	set_list(lst,i,arl[i][0]);
	}

	g_list_free(new);
	g_list_free(tags);
	g_list_free(questions);
	return lst;

}

/* 
Load:
Dado um apontador TAD community, esta função limpa os dados 
da estrutura correspondente da memória.
*/
TAD_community clean(TAD_community com){
	long delet;
	if(com){
		delet = g_hash_table_foreach_remove(com->HTU,freeElemHTU,NULL);
		delet = g_hash_table_foreach_remove(com->HTQ,freeElemHTQ,NULL);
		delet = g_hash_table_foreach_remove(com->HTA,freeElemHTA,NULL);
		delet++;
		g_hash_table_remove_all (com->HTU);
		g_hash_table_remove_all (com->HTQ);
		g_hash_table_remove_all (com->HTA);
		g_hash_table_remove_all (com->HTT);
	}
	return com;
}
