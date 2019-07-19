#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__
#include <gmodule.h>

typedef struct question* AQuestion;
typedef struct answer* AAnswer;
typedef struct auser* AUser;

long createData(long day, long month, long year, long hour, long min, long sec, long msec);
long get_owidA(AAnswer a);
int get_score (AAnswer a);
int get_numcomments(AAnswer a);
char* get_name(AUser a);
char* get_title(AQuestion a);
long get_id(AUser a);
long get_owid(AQuestion a);
long get_reputation(AUser a);
long get_pid(AAnswer a);
char** get_tags(AQuestion a);
int get_numtag(AQuestion a);
int get_numquestion(AUser a);
int get_numanswer(AUser a);
void inc_numquestion(AUser a);
void inc_numanswer(AUser a);
AUser createUser (char* name,long reputation,char* aboutme,long id);
GPtrArray* getAnsU(AUser a);
GArray* getAnsQ(AQuestion q);
GPtrArray* getQuesU (AUser a);
AAnswer createAnswer (long id,long creationdate,long parentid,int score,long owneruserid,int commentcount);
AQuestion createQuestion (long id,long creationdate,long owneruserid,char* tags, char* title,int answercount);
int isThere(char* x,char* word);
AQuestion searchW(AQuestion q,char* word);
void inserePar(gpointer idp,gpointer ap,gpointer arrp);
long get_creationdate (AQuestion a);
long get_qid(AQuestion a);
int comp(gconstpointer a,gconstpointer b);

long convert(Date a);
void faux1(gpointer a,gpointer b, gpointer c);
void faux2(gpointer a,gpointer b, gpointer c);


//QUERY 4
int searchT(char** big,char* small, int numtag);


//QUERY 5
char* get_thisbio(AUser a);
void insereParDateQ(gpointer ap, gpointer arr);
void insereParDateA(gpointer ap, gpointer arr);

//QUERY 6
int compVotes(gconstpointer a,gconstpointer b);
long get_creationdateA (AAnswer a);
long get_aid(AAnswer a);

//QUERY 7
int compAnsc(gconstpointer a,gconstpointer b);
void addDate(gpointer data,gpointer user_data);
void insertInFinal(long final[][2],long val,long numres,int N);
void orgbyNumAns(long final[][2],GArray* aux,long resp[],int N);

// QUERY 11
int comprep(gconstpointer a,gconstpointer b);


//CLEAR
gboolean freeElemHTU (gpointer key,gpointer value,gpointer user_data);
gboolean freeElemHTQ (gpointer key,gpointer value,gpointer user_data);
gboolean freeElemHTA (gpointer key,gpointer value,gpointer user_data);

#endif
