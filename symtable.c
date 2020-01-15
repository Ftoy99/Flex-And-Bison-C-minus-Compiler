/*CEI222:Project Step 4 ID:Marios Charalambous-13112_Antonis Savvides-17007_Dimitrios Ioannou-14423*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"


int scopeLvl = 0;
int numOfPara;
int yylineno;
enum types {VAR,FUN,I,V};


struct symAtt parser ={
    .type=0,
    .initialized=0,
    .references=0,
    .scope=0,
    .array=0,
    .arrSize=0,
    .parameters=0,
    .offset=0
};

struct entry *lookUp(char *id,struct entry *head_ref){
    struct entry *glob = head_ref;
    struct var *inFun = glob->head_of_var;
        while(inFun){
            if(strcmp(inFun->id,id)==0){
                return glob;
            }
            inFun = inFun->nextVar;
        }
        while(glob){
            if(strcmp(glob->id,id)==0){
                return glob;
            }
            glob = glob->next;
        }
    printf("error at line %d was never added\n",yylineno);
    exit(0);
}
    
void insert(char* id, struct symAtt attr,int enType,struct entry **head_ref){
     	if(scopeLvl==0){
            struct entry *new_node = (struct entry*) malloc (sizeof(struct entry));
            struct entry *last = *head_ref;
            struct entry *tmp = *head_ref;
            strcpy(new_node->id, id);
            new_node->attr=attr;
            new_node->enType=enType;
            new_node->next=NULL;
            new_node->head_of_var=NULL;
            if(strcmp(id, "main")==0){
                    new_node->attr.references=1;
            }
            if(*head_ref == NULL){
                *head_ref = new_node;
                return;
            }
            while(tmp){
                if(strcmp(tmp->id,id)==0){
                    printf("error - id: %s was previously declared\n", id);
                    exit(0);
                }
                tmp=tmp->next;
            }
            while(last->next){
                last = last->next;
            }
            last->next = new_node;
            return;
    	}
    	else{
            struct var *new_var =(struct var*) malloc (sizeof(struct var));
            struct var *temp = (*head_ref)->head_of_var;
            struct var *lastVar = (*head_ref)->head_of_var;
            strcpy(new_var->id, id);
            new_var->attr=attr;
            new_var->nextVar=NULL;
            if((*head_ref)->head_of_var == NULL){
                (*head_ref)->head_of_var=new_var;
                return;
            }

            while(temp){
                if(strcmp(temp->id,id)==0){
                    printf("error - id: %s was previously declared\n", id);
                    exit(0);
                }
                temp = temp->nextVar;
            }
            while(lastVar->nextVar != NULL){
                lastVar = lastVar->nextVar;
            }
            lastVar->nextVar = new_var;
            return;
    	}

}

void initScope(){
    scopeLvl++;
    }
    
void finalizeScope(){
    scopeLvl--;
}

void delete(){
    parser.type=0;
    parser.initialized=0;
    parser.references=0;
    parser.scope=0;
    parser.array=0;
    parser.arrSize=0;
    parser.parameters=0;
    parser.offset=0;
}

