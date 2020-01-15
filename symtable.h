/*CEI222:Project Step 4 ID:Marios Charalambous-13112_Antonis Savvides-17007_Dimitrios Ioannou-14423*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symAtt{
    int type;
    int initialized;
    int references;
    int scope;
    int array;
    int arrSize;
    int parameters;
    int offset;
    int arrIndex;
};

struct entry{
    char id[10];
    struct symAtt attr;
    int enType;
    struct var *head_of_var;
    struct entry *next;
};

struct var{
   char id[10];
   struct symAtt attr;
   struct var *nextVar;
};


struct symAtt parsed;
struct entry *lookUp(char *id,struct entry *head_ref);
void insert(char *id, struct symAtt attr,int enType,struct entry **head_ref);
void initScope();
void finalizeScope();
void delete();
