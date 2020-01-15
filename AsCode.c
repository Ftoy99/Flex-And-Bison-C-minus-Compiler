#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AsCode.h"
#include "TAC.h"
extern struct Line *HeadL;
int MipsRegisters[10][2];
char semiRegisters[10][20];
void transAssembly(){
	
	
	
	//open file
    FILE *fptr = fopen("sample.asm", "w");
    //print statick mips data
    fprintf(fptr, ".data\nnewln: .asciiz  \"\\n\" \n");
    
    
    
    
    struct Line *tmp = HeadL;
    struct Line *temp = HeadL;
    char numIntoChar[10];
    char check[10];
    int var1=0;
    int var2=0;
    int x;
    int y;
    
    
    initializeReg();
    //print variables
    
    
    
 //print variable declarions   
    while(tmp){
        if(strcmp(tmp->Command,"VARDECL")==0){
            fprintf(fptr, "%s: .space %s\n",tmp->Result ,tmp->Variable1);
            fprintf(fptr, "    .align 2\n",tmp->Result ,tmp->Variable1);
            //
            x = nextFreeAssemplyRegister();
            strcpy(semiRegisters[x],tmp->Result);
            
        }
        //proxora stin epomeni thesi
        tmp=tmp->NextL;
    }
    //rpint global main
    fprintf(fptr, ".text\n.globl main\n");
    
     while(temp){
         if(strcmp(temp->Command,"VARDECL")==0){
             for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Result)==0){
                   fprintf(fptr, "la $t%d %s\n", searchSemiCode(temp->Result), temp->Result );
                }
            }
        }
         if(strcmp(temp->Command,"GOTO")==0){
            fprintf(fptr, "j %s\n",temp->Result);
        }
        if(strcmp(temp->Command,"LABEL")==0){
            fprintf(fptr, "%s:\n",temp->Result);
        }
        if(strcmp(temp->Command,"CALL")==0){
            fprintf(fptr, "jal %s\n",temp->Result);
        }
        
        if(strcmp(temp->Command,"A2PLUS")==0){
            var1=0;
            var2=0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                    }
            }
            if(var1==1 && var2==0){
                    fprintf(fptr, "addi $t%d $t%d %s\n", y = nextFreeAssemplyRegister() , searchSemiCode(temp->Variable1), temp->Variable2 );
                 
            }
            else if(var1==0 && var2==1){
                 fprintf(fptr, "addi $t%d %s $t%d\n", y = nextFreeAssemplyRegister(),temp->Variable1,searchSemiCode(temp->Variable2));

            }
            else{
                 fprintf(fptr, "add $t%d $t%d $t%d\n", y = nextFreeAssemplyRegister() , searchSemiCode(temp->Variable1) , searchSemiCode(temp->Variable2) );     
            }
        }
        if(strcmp(temp->Command,"A2MINUS")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            if(var1==1 && var2==0){
                 fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable2 );
                 fprintf(fptr, "sub $t%d $t%d $t%d\n", y=nextFreeAssemplyRegister(),searchSemiCode(temp->Variable1), x );
            }
            else if(var1==0 && var2==1){                 
                 fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable1 );

                 fprintf(fptr, "sub $t%d $t%d $t%d\n", y = nextFreeAssemplyRegister() , x , searchSemiCode(temp->Variable2));

            }
            else{
                 fprintf(fptr, "sub $t%d $t%d $t%d\n", y = nextFreeAssemplyRegister(),searchSemiCode(temp->Variable1),searchSemiCode(temp->Variable2) );     
            }
        }
        if(strcmp(temp->Command,"A2MULT")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            if(var1==1 && var2==0){
                fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable2 );
                 fprintf(fptr, "mul $t%d $t%d $t%d\n", y=nextFreeAssemplyRegister(),searchSemiCode(temp->Variable1), x );
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable1 );

                 fprintf(fptr, "mul $t%d $t%d $t%d\n", y = nextFreeAssemplyRegister() , x , searchSemiCode(temp->Variable2));
            }
            else{
                fprintf(fptr, "mul $t%d $t%d $t%d\n",  y = nextFreeAssemplyRegister(),searchSemiCode(temp->Variable1), searchSemiCode(temp->Variable2) );
            }
        }
        if(strcmp(temp->Command,"A2DIV")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            if(var1==1 && var2==0){
                fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable2 );
                 fprintf(fptr, "div $t%d $t%d\n", searchSemiCode(temp->Variable1), x );
                 fprintf(fptr, "mflo $t%d\n",y=nextFreeAssemplyRegister());
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "li $t%d %s\n", x=nextFreeAssemplyRegister(), temp->Variable1 );

                 fprintf(fptr, "div $t%d $t%d\n",  x , searchSemiCode(temp->Variable2));
                 fprintf(fptr, "mflo $t%d\n",y=nextFreeAssemplyRegister());
            }
            else{
                fprintf(fptr, "div $t%d $t%d\n",searchSemiCode(temp->Variable1), searchSemiCode(temp->Variable2) );
                fprintf(fptr, "mflo $t%d\n",y=nextFreeAssemplyRegister());

            }
        }
        if(strcmp(temp->Command,"A0")==0){
            var1=0;
            var2=0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
            }
            for(int i=0; i<10; i++){
                strcpy(check,"_t");
                sprintf(numIntoChar,"%d",i);
                strcat(check,numIntoChar);
                if(strcmp(temp->Variable1,check)==0){
                    var2=1;
                }
            }
            if(var1==1){
                 fprintf(fptr, "move $t%d $t%d\n", searchSemiCode(temp->Result), searchSemiCode(temp->Variable1) );
            }
            else if(var2==1){
                fprintf(fptr, "move $t%d $t%d\n", searchSemiCode(temp->Result), y);
            }
            else{
                fprintf(fptr, "li $t%d %s\n", searchSemiCode(temp->Result), temp->Variable1 );
            }
            //fprintf(fptr, "sw $t%d %s\n", y, temp->Result );
        }
        if(strcmp(temp->Command,"IFGT")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
            if(var1==1 && var2==0){
                fprintf(fptr, "ble %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "ble $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "ble $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            temp=tmp->NextL;
        }
        if(strcmp(temp->Command,"IFGE")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
             if(var1==1 && var2==0){
                fprintf(fptr, "blt %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "blt $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "blt $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1,tmp->Result);
            }
            temp=tmp->NextL;
        }
        if(strcmp(temp->Command,"IFST")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
             if(var1==1 && var2==0){
                fprintf(fptr, "bge %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "bge $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "bge $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            temp=tmp->NextL;
        }
        if(strcmp(temp->Command,"IFSE")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
             if(var1==1 && var2==0){
                fprintf(fptr, "bgt %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "bgt $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "bgt $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            temp=tmp->NextL;
        }
        if(strcmp(temp->Command,"IFEQ")==0){
           var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
             if(var1==1 && var2==0){
                fprintf(fptr, "bne %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "bne $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "bne $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            temp=tmp->NextL;
        }
        if(strcmp(temp->Command,"IFNE")==0){
            var1 = 0;
            var2 = 0;
            for(int i=0; i<10; i++){
                if(strcmp(semiRegisters[i],temp->Variable1)==0){
                    var1=1;
                }
                if(strcmp(semiRegisters[i],temp->Variable2)==0){
                     var2=1;
                }
            }
            tmp=temp->NextL;
             if(var1==1 && var2==0){
                fprintf(fptr, "beq %s, $t%d, %s\n", temp->Result, searchSemiCode(temp->Variable1), tmp->Result);
            }
            else if(var1==0 && var2==1){
                fprintf(fptr, "beq $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            else{
                fprintf(fptr, "beq $t%d, %s, %s\n", searchSemiCode(temp->Result), temp->Variable1, tmp->Result);
            }
            temp=tmp->NextL;
        }
        temp=temp->NextL;
     }
     
    fprintf(fptr, "li $v0, 10\n");
    fclose(fptr);
}



void initializeReg(){
	
	for(int i=0;i<10;i++){
		for(int n=0;n<2;n++){
			
            if(n==0){
                MipsRegisters[i][n]=i;
            }
            else MipsRegisters[i][n]=0;
        }
    }
}

int nextFreeAssemplyRegister(){
	
	for(int i=0;i<10;i++){
		if (MipsRegisters[i][1]==0){
				MipsRegisters[i][1]=1;
				return i;	
		}}

	return 0;
}
int searchSemiCode(char *reg){
    for(int i=0; i<10; i++){
        if(strcmp(semiRegisters[i],reg)==0){
            return i;
        }
    }
}
