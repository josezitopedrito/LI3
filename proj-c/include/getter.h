#ifndef __GETTER_H__
#define __GETTER_H__
#include <gmodule.h>


GHashTable* fromUsers (char* path);
void fromPosts (GHashTable* HTU,GHashTable* HTQ, GHashTable* HTA, char* path);
void fromTags (GHashTable *HTT, char* path);
void auxAinQ (gpointer key,gpointer value,gpointer user_data);

#endif
