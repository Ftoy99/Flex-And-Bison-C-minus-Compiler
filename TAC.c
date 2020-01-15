/*CEI222:Project Step 4 ID:Marios Charalambous-13112_Antonis Savvides-17007_Dimitrios Ioannou-14423*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAC.h"
struct Line *HeadL=NULL;
int NOL=1;
char TempCommand[100];
char Factor[20];
char ExResult[20];
char AExpression[20];
char LastCall[20];
char NumToChar[4];
int Arguments=0;
int Registers[20][2];
int OperationFlag=0;
int True;
int False;
int LoopStart;
int LoopEnd;
int Floop;
int FTrue;
int FirstFunction=0;

int LabelNum=0;


void NewLine(){
    struct Line *new_line = (struct Line*)malloc(sizeof(struct Line));
    struct Line *temp = HeadL;  
	new_line->NextL=NULL;
	new_line->LineN=NOL++;
	strcpy(new_line->Command,"");
	strcpy(new_line->Result,"");
	strcpy(new_line->Variable1,"");
	strcpy(new_line->Variable2,"");
     if(HeadL == NULL){
        HeadL = new_line;
        return;
    }
    while(temp->NextL){
        temp=temp->NextL;
    }
    temp->NextL=new_line;

}


void PrintLines(){
	printf("3 Address Code Of Compiled Program :\n");
    struct Line *tmp = HeadL;

//	an den eisai sto tellos prosxora
	while(tmp){
	//printf oti tha tiponi 
	printf("%d:%s %s %s %s\n",tmp->LineN,tmp->Command,tmp->Result,tmp->Variable1,tmp->Variable2);
	tmp=tmp->NextL;
	}
}


void InsertInLine(char *InsertedCommand,int Information){
// 	pigene sto telos tis listas
    struct Line *tmp = HeadL;
	while(tmp->NextL){
	tmp=tmp->NextL;}
	//Bale times pou pires mesa stin telftea grami ;
	
		if (Information==1){strcpy(tmp->Command,InsertedCommand);}
		if (Information==2){strcpy(tmp->Result,InsertedCommand);}
		if (Information==3){strcpy(tmp->Variable1,InsertedCommand);}
		if (Information==4){strcpy(tmp->Variable2,InsertedCommand);}
		//if tempcommand was used clear it
		strcpy(TempCommand,"");
}

void InsertInLineC(char *InsertedCommand,int Information,int LineC){
// 	pigene stin grami Line
    struct Line *tmp = HeadL;
	while(tmp->LineN!=LineC){
	tmp=tmp->NextL;}
	
	//Bale times pou pires mesa stin grami ;
		if (Information==1){strcpy(tmp->Command,InsertedCommand);}
		if (Information==2){strcpy(tmp->Result,InsertedCommand);}
		if (Information==3){strcpy(tmp->Variable1,InsertedCommand);}
		if (Information==4){strcpy(tmp->Variable2,InsertedCommand);}
		//if tempcommand was used clear it
		strcpy(TempCommand,"");
}

int LastLineAddress(){
	//go to last line
    struct Line *tmp = HeadL;
	while(tmp->NextL){tmp=tmp->NextL;}
	return tmp->LineN;


}
int LastLabelNum(){
	LabelNum++;
	return LabelNum;


}
void initReg(){
	
	for(int i=0;i<20;i++){
		for(int n=0;n<2;n++){
			
		if(n==0){
			Registers[i][n]=i;
		}
		else Registers[i][n]=0;
	}
	
}
}

int NextFreeRegister(){
	
	for(int i=0;i<20;i++){
		if (Registers[i][1]==0){
				Registers[i][1]=1;
				return i;	
		}}

	return 0;
}
