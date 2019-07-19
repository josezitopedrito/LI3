#include <date.h>
#include <stdio.h>
#include "interface.h"
#include "estruturas.h"
#include "common.h"
#include <libxml/xmlreader.h>
#include <string.h>
#include <stdlib.h>
#include <gmodule.h>


/*
Função que vai ao ficheiro Users.xml processar as informações no ficheiro, transformar no tipo AUser e adicionar à GHashTable que iremos devolver 

param path caminho para o ficheiro do Users.xml
return a GHashTable com a informação dos users
*/
GHashTable* fromUsers (char* path){
	
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(path);

	if (doc == NULL ) {
		fprintf(stderr,"Parsing falhou. \n");
		return NULL;
	}
	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr,"O documento esta vazio\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar*) "users" )) {
		fprintf(stderr,"document of the wrong type, root node != %s", (char*) "users");
		xmlFreeDoc(doc);
		return NULL;
	}

	GHashTable *perm = g_hash_table_new_full (g_direct_hash, g_direct_equal, NULL, NULL);
	xmlChar *key;
	long id; 
	long rep;
	char* nm;
	char* about;
	AUser usr;
//funciona, siga sacar os USER IDS

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			//Sacar USERIDS
			if((key = xmlGetProp(cur, (xmlChar*) "Id"))!=NULL){
				id=strtol((char*) key, NULL, 0);
		    }
		    xmlFree(key);

		    //Sacar USERNAMES
		    if((key = xmlGetProp(cur,(xmlChar*) "DisplayName"))!=NULL){
		    	nm=mystrdup((char*)key);
		    }
		    else{
		    	nm=mystrdup(" \0");
		    }
		    xmlFree(key);

		    //Sacar SHORTBIO
		    if(((key = xmlGetProp(cur,(xmlChar*) "AboutMe"))!=NULL)&&(strcmp((char*)key,"")!=0)) {
		    	about=mystrdup((char*) key);
		    }
		    else{
		    	about=mystrdup(" \0");
		    }
		    xmlFree(key);

		    //sacar REPUTATION
			if((key = xmlGetProp(cur, (xmlChar*) "Reputation"))!=NULL){
				rep=strtol((char*)key, NULL, 0); 					// aqui temos de chamar algo que guarde na estrutura
		    }
		    xmlFree(key);

     		usr=createUser(nm, rep, about, id);
     		g_hash_table_insert (perm, GSIZE_TO_POINTER (id), usr);
     		free (nm);
     		free (about);

     	}

		cur = cur->next;
	}

	xmlFree(doc);
	return perm;
}


/*
Função que vai processar todos os posts, diferenciá-los em questions e answers, adicioná-los nos respetivos GHashTables e ainda meter a informação
de cada question e answers no user que fez essa question ou answer.

param HTU GHashTable dos AUsers
param HTQ GHashTable das AQuestions
param HTA GHashTable das AAnswers
param path o caminho para o ficheiro Posts.xml
*/
void fromPosts (GHashTable* HTU, GHashTable* HTQ, GHashTable* HTA, char* path){
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(path);
	if (doc == NULL ) {
		fprintf(stderr,"Parsing falhou. \n");
		return;
	}
	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr,"O documento esta vazio\n");
		xmlFreeDoc(doc);
		return;
	}

	if (xmlStrcmp(cur->name, (const xmlChar*) "posts" )) {
		fprintf(stderr,"document of the wrong type, root node != %s", (char*) "posts");
		xmlFreeDoc(doc);
		return;
	}

	gpointer rightuser;
	xmlChar *key;
	long idi; 
	long date=0;
	int scr;
	long ownusrid;
	char* tgs;
	char* ttl;
	int anscount;
	long parentid;
	int comcount;
	AQuestion qstin;
	AAnswer ans;
	int aux;
	int i;
	long a, m, d, h, mi, s, ms=0;
	char year[5]="0000\0";
	char month[3]="00\0";
	char day[3]="00\0";
	char hour[3]="00\0";
	char min[3]="00\0";
	char sec[3]="00\0";
	char msec[4]="000\0";
//funciona, siga sacar os POST IDS

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

			//Sacar POSTID
			if((key = xmlGetProp(cur, (xmlChar*) "Id"))!=NULL){
				idi=strtol((char*)key, NULL, 0);
				if(idi==0)
					printf("\n ERRO A SACAR POSTID\n");
		    }
		    xmlFree(key);

		    //Sacar DATES
		    if((key = xmlGetProp(cur, (xmlChar*) "CreationDate"))!=NULL){
		    	//Sacar o ANO
		    	for (i=0;i<4;i++)
		    		year[i]= key[i];
		    	a= (long)atoi(year);
		    	
		    	//Sacar o MES
		    	for (i=0;i<2;i++)
		    		month[i]= key[i+5];
		    	m= (long)atoi(month);
		    	

		    	//Sacar o DIA
		    	for (i=0;i<2;i++)
		    		day[i]= key[i+8];
		    	d= (long)atoi(day);

		    	//Sacar o HORA
		    	for (i=0;i<2;i++)
		    		hour[i]= key[i+11];
		    	h= (long)atoi(hour);

		    	//Sacar o MINUTO
		    	for (i=0;i<2;i++)
		    		min[i]= key[i+14];
		    	mi=(long)atoi(min);

		    	//Sacar o SEGUNDO
		    	for (i=0;i<2;i++)
		    		sec[i]= key[i+17];
		    	s= (long)atoi(sec);

		    	//Sacar o MILISSEGUNDO
		    	for (i=0;i<3;i++)
		    		msec[i]= key[i+20];
		    	ms= (long)atoi(msec);
		    	date=createData(d,m,a,h,mi,s,ms);

		    }
		    else{
		    	date=createData(0,0,0,0,0,0,0);
		    }
			xmlFree(key);

					//Sacar USER ID
			if((key = xmlGetProp(cur, (xmlChar*) "OwnerUserId"))!=NULL){
				ownusrid=strtol((char*)key, NULL, 0);

		   		xmlFree(key);
			    //sacar PostTypeId
				if((key = xmlGetProp(cur, (xmlChar*) "PostTypeId"))!=NULL){
					aux=atoi((char*)key);
					if(aux==1){
				    	xmlFree(key);
						
						//Sacar TITLES
			    		if((key = xmlGetProp(cur,(xmlChar*) "Title"))!=NULL){
			    			ttl=mystrdup((char*) key);
			    		}
						xmlFree(key);
				    	//se e pergunta, vamos buscar a ANSWERCOUNT
					    if((key = xmlGetProp(cur, (xmlChar*) "AnswerCount"))!=NULL){
							anscount=atoi((char*)key); 					// aqui temos de chamar algo que guarde na estrutura.
		 		   		}
		 	   			xmlFree(key);

		 	   			//Sacar TAGS
		    			if((key = xmlGetProp(cur,(xmlChar*) "Tags"))!=NULL){
		    				tgs=mystrdup((char *)key);
					    }
				   		else{
						 	tgs=mystrdup("");
					    }
						xmlFree(key);

						qstin=createQuestion (idi,date,ownusrid,tgs,ttl,anscount);
						g_hash_table_insert (HTQ, GINT_TO_POINTER (idi), qstin);
						free(ttl);
						free(tgs);

						rightuser=g_hash_table_lookup(HTU, GSIZE_TO_POINTER(ownusrid));
						g_ptr_array_add (getQuesU((AUser)rightuser),qstin);
						inc_numquestion(rightuser);

			    	}

					else if(aux==2){	 					
			 		   		xmlFree(key);

					   	 	//se e resposta, vamos buscar o PARENT
				   			if((key = xmlGetProp(cur, (xmlChar*) "ParentId"))!=NULL){
				   				parentid=strtol((char*)key, NULL, 0);
				    		}
				    		xmlFree(key);

					   	    //Sacar SCORE da resposta
						    if((key = xmlGetProp(cur, (xmlChar*) "Score"))!=NULL){
								scr=atoi((char*)key); 					
			    				xmlFree(key);
					 		}

						 	//ser e resposta, vamos buscar o COMMENTCOUNT
				    		if((key = xmlGetProp(cur, (xmlChar*) "CommentCount"))!=NULL){
				    			comcount=atoi((char*)key);
			    			}
			    			xmlFree(key);
			    			ans=createAnswer (idi,date,parentid,scr,ownusrid,comcount);
							g_hash_table_insert (HTA, GINT_TO_POINTER (idi), ans);

							rightuser=g_hash_table_lookup(HTU, GSIZE_TO_POINTER(ownusrid));
							g_ptr_array_add (getAnsU((AUser)rightuser),ans);
							inc_numanswer(rightuser);
					}

			    }
		    }

     	}
     	
		cur = cur->next;
	}
	xmlFree(doc);
	return;
}

/*
Função que vai organizar as Tags(sendo estas a key) e o seu ID (sendo este o value associado à key), armazenando no HTT.

param HTT qualquer key da GHashTable
param path o caminho para o ficheiro Tags.xml
*/
void fromTags (GHashTable *HTT, char* path){
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(path);
	if (doc == NULL ) {
		fprintf(stderr,"Parsing falhou. \n");
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		fprintf(stderr,"O documento esta vazio\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar*) "tags" )) {
		fprintf(stderr,"document of the wrong type, root node != %s", (char*) "tags");
		xmlFreeDoc(doc);
	}
	xmlChar *key;
	long idt = 0;
	char* tag ;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			if((key = xmlGetProp(cur, (xmlChar*) "Id"))!=NULL){
				idt=(long) atoi((char*)key);
			}
			else{ 
				idt = 0;
			}
			xmlFree(key);
			if((key = xmlGetProp(cur, (xmlChar*) "TagName"))!=NULL){
				tag=mystrdup((char*) key);
			}
			else{
				tag=mystrdup("");
			}
			xmlFree(key);
			g_hash_table_insert (HTT,tag,GSIZE_TO_POINTER(idt));
		}
		cur = cur->next;
	}
	xmlFree(doc);
	return;
}

/*
Função que vai adicionar cada answer dentro da GHashTable* HTA para cada question do HTQ, dependendo do
parent ID da answer analisada.(vai ser usado no interface.c, no load, porque temos de carregar todas as 
answers)

param key qualquer key da GHashTable
param value o valor associado a cada key
param user_data a GHashTable HTQ
*/
void auxAinQ (gpointer key,gpointer value,gpointer user_data){
	long *newid= key;
	AAnswer a = (AAnswer) value;
	GHashTable* HTQ = (GHashTable*) user_data;
	if(g_hash_table_lookup(HTQ,GSIZE_TO_POINTER(get_pid(a)))==NULL)
		return;
	AQuestion q = g_hash_table_lookup(HTQ,GSIZE_TO_POINTER(get_pid(a)));
	g_array_append_val(getAnsQ(q),newid);
}

