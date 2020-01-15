/*CEI222:Project Step 4 ID:Marios Charalambous-13112_Antonis Savvides-17007_Dimitrios Ioannou-14423*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#include "TAC.h"
#include "AsCode.h"

void yyerror(const char *s);
extern struct symAtt parser;
struct entry *head=NULL;
extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern int numOfPara;
enum types {VAR,FUN,I,V};

extern char TempCommand[];
extern char NumToChar[];
extern int Arguments;
extern char LastCall[];
extern char AExpression[];
extern char ExResult[];
extern char Factor[];
extern int Regisers[];
extern int OperationFlag;
extern int LoopStart;
extern int LoopEnd;
extern int True;
extern int False;
extern int FTrue;
extern int FLoop;
extern int FirstFunction;
%}

%union{
    int num;
    char s[15];
}

%token IF
%token ELSE
%token WHILE
%token INT
%token VOID
%token RETURN
%token PLUS
%token MINUS
%token MULT
%token DIV
%token LESS
%token LESS_EQ
%token GREATER
%token GREATER_EQ
%token COMPARE
%token NOT_EQUAL
%token EQUAL
%token SEMICOLON
%token COMMA
%token PAR_LEFT
%token PAR_RIGHT
%token COL_LEFT
%token COL_RIGHT
%token BR_LEFT
%token BR_RIGHT
%token LINE_COMMENT
%token COMMENT_START
%token COMMENT_END
%token CL
%token IDENTIFIER
%token NUMBER

%type <s> PLUS
%type <s> MINUS
%type <s> MULT
%type <s> DIV
%type <s> LESS
%type <s> LESS_EQ
%type <s> GREATER
%type <s> GREATER_EQ
%type <s> COMPARE
%type <s> NOT_EQUAL
%type <s> EQUAL
%type <s> SEMICOLON
%type <s> COMMA
%type <s> PAR_LEFT
%type <s> PAR_RIGHT
%type <s> COL_LEFT
%type <s> COL_RIGHT
%type <s> BR_LEFT
%type <s> BR_RIGHT
%type <s> LINE_COMMENT
%type <s> COMMENT_START
%type <s> COMMENT_END
%type <s> CL
%type <num> NUMBER call  term expression typespecifier factor simpleexpression additiveexpression addop mulop relop iterationstmt selectionstmt args arglist
%type <s> IDENTIFIER var vardeclaration 

%%

program:            declarationl                                                            {}
        ;
        
declarationl:       declarationl declaration                                                
        |           declaration                                                             
        ;																					
declaration:        vardeclaration                                                         {} 
        |           fundeclaration                                                         {}
        ;																				
vardeclaration:     typespecifier IDENTIFIER SEMICOLON                                      
                                                                                            {insert($2, parser,VAR, &head); strcpy($$, $2);delete();NewLine();InsertInLine("VARDECL",1);InsertInLine($2,2);InsertInLine("4",3);}
        |           typespecifier IDENTIFIER COL_LEFT NUMBER COL_RIGHT SEMICOLON           
                                                                                            {parser.array=1; parser.arrSize =$4; insert($2,parser,VAR, &head); strcpy($$,$2); delete();NewLine();InsertInLine("VARDECL",1);InsertInLine($2,2);sprintf(NumToChar,"%d",4*$4);InsertInLine(NumToChar,3);}
        ;
typespecifier:      INT                                                                     {parser.type=I;}
        |           VOID                                                                    {parser.type=V;}
        ;
fundeclaration:     typespecifier IDENTIFIER PAR_LEFT                                       {if (FirstFunction==0){FirstFunction=1;NewLine();InsertInLine("GOTO ",1);InsertInLine("main",2);}}
                                                                                            {parser.parameters =numOfPara; insert($2,parser,FUN, &head); initScope(); delete(); numOfPara=0; NewLine(); InsertInLine("LABEL",1); InsertInLine($2,2);} 
                    params PAR_RIGHT                                                         
                    compoundstmt                                                            {finalizeScope();}        
        ;
params:             paramlist                       										{}                                        
        |           VOID                              										{numOfPara=0;}                                      
        ;
paramlist:          paramlist COMMA param          											{numOfPara++;}                                           
        |           param                          											{numOfPara++;}                                         
        ;
param:              typespecifier IDENTIFIER                                                
                                                                                            {parser.parameters = numOfPara +1; parser.initialized = 1; insert($2, parser,VAR, &head); delete();NewLine();InsertInLine("PARAMOUT",1);strcpy(TempCommand,"_t");sprintf(NumToChar,"%d",NextFreeRegister());strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
        |           typespecifier IDENTIFIER COL_LEFT COL_RIGHT                             
                                                                                            {parser.parameters = numOfPara +1; parser.array =1; parser.initialized = 1; insert($2, parser,VAR, &head); delete();NewLine();InsertInLine("PARAMOUT",1);strcpy(TempCommand,"_t");sprintf(NumToChar,"%d",NextFreeRegister());strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
        ;
compoundstmt:       BR_LEFT                                                               
                    localdeclarations statementlist BR_RIGHT                               
        ;
localdeclarations:  localdeclarations vardeclaration                                         
        |
        ;
statementlist:      statementlist statement                                                
        |                                                                                   
        ;
statement:          expressionstmt                                                          
        |           compoundstmt                                                            
        |           selectionstmt                                                           
        |           iterationstmt                                                           
        |           returnstmt         							                                                  
        ;
expressionstmt:     expression SEMICOLON                                                    
        |           SEMICOLON                                                               
        ;

selectionstmt:      ifsubroutine statement			                   							{False=LastLabelNum();strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False);strcat(TempCommand,NumToChar);InsertInLineC(TempCommand,2,(LoopStart+1));NewLine();InsertInLine("GOTO",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}																			                      								   					                   
        |           ifsubroutine statement ELSE													{NewLine();InsertInLine("GOTO",1);FTrue=LastLineAddress();False=LastLabelNum();strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False);strcat(TempCommand,NumToChar);InsertInLineC(TempCommand,2,(LoopStart+1));NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
					statement                  												    {strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",False+1);strcat(TempCommand,NumToChar);InsertInLineC(TempCommand,2,FTrue);NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LastLabelNum());strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}             
        ;
ifsubroutine:		IF PAR_LEFT expression PAR_RIGHT 											{True=LastLabelNum();LoopStart=LastLineAddress();strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",True);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,4);NewLine();InsertInLine("GOTO",1);NewLine();InsertInLine("LABEL",1);
																								strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",True);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
		;
		
		
		
iterationstmt:      WHILE PAR_LEFT 																{LoopStart=LastLabelNum();NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LoopStart);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
					expression PAR_RIGHT   														{strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",(LoopStart+1));strcat(TempCommand,NumToChar);InsertInLine(TempCommand,4);NewLine();InsertInLine("GOTO",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LoopStart+2);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LoopStart+1);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}
					statement                              										{NewLine();InsertInLine("GOTO",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LoopStart);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);NewLine();InsertInLine("LABEL",1);strcpy(TempCommand,"_l");sprintf(NumToChar,"%d",LoopStart+2);strcat(TempCommand,NumToChar);InsertInLine(TempCommand,2);}                       
        ;
returnstmt:         RETURN SEMICOLON                                                        	
        |           RETURN expression SEMICOLON           										{NewLine();InsertInLine("RETURNOUT",1);if (OperationFlag==1) {InsertInLine(ExResult,2);}else {InsertInLine(Factor,2);} OperationFlag=0;}                                  	
        ;
expression:         var EQUAL expression                                 						{NewLine();InsertInLine("A0",1);InsertInLine($1,2);if (OperationFlag==1) {InsertInLine(ExResult,3);}else {InsertInLine(Factor,3);} OperationFlag=0;}                   
        |           simpleexpression            						                        {}                                             
        ;
var:                IDENTIFIER                                                                  {lookUp($1,head)->attr.references++; strcpy($$,$1);}
        |           IDENTIFIER COL_LEFT expression COL_RIGHT                                    {struct entry *tmp = lookUp($1,head); 
                                                                                                if(!tmp->attr.array) printf("error %s in not an array" ,tmp->id); 
                                                                                                tmp->attr.references++;
                                                                                                tmp->attr.arrIndex = $3;
                                                                                                strcpy($$,$1);}
        ;
simpleexpression:   additiveexpression 										 					{NewLine();if (OperationFlag==1) {InsertInLine(ExResult,2);}else {InsertInLine(Factor,2);} OperationFlag=0;}
					relop additiveexpression                                 					{if (OperationFlag==1) {InsertInLine(ExResult,3);}else {InsertInLine(Factor,3);} OperationFlag=0;} 
        |           additiveexpression                                 	                        {}                     
        ;
relop:              LESS_EQ                                                                     {InsertInLine("IFSE",1);}           
        |           LESS                                                                        {InsertInLine("IFST",1);}            
        |           GREATER                                                                     {InsertInLine("IFGT",1);}             
        |           GREATER_EQ                                                                  {InsertInLine("IFGE",1);}            
        |           COMPARE                                                                     {InsertInLine("IFEQ",1);}         
        |           NOT_EQUAL                                                                   {InsertInLine("IFNE",1);}       
        ;
        
        

additiveexpression: additiveexpression															{NewLine();strcpy(TempCommand,"_t");sprintf(NumToChar,"%d",NextFreeRegister());strcat(TempCommand,NumToChar); strcpy(ExResult,TempCommand); strcpy(AExpression,TempCommand); InsertInLine(TempCommand,2); InsertInLine(Factor,3);}
					addop term                  						                        {InsertInLine(Factor,4);OperationFlag=1;}         
																		               
        |           term                                                                        {}                 
        ;
addop:              PLUS                                                                        {InsertInLine("A2PLUS",1);}              
        |           MINUS                                                                       {InsertInLine("A2MINUS",1);}               
        ;
term:               term 												 
                                                                                                {NewLine();strcpy(TempCommand,"_t");sprintf(NumToChar,"%d",NextFreeRegister());strcat(TempCommand,NumToChar); strcpy(ExResult,TempCommand);InsertInLine(TempCommand,2);InsertInLine(Factor,3);}
					mulop factor                                    	                        {InsertInLine(Factor,4);OperationFlag=1;} 
																		            
        |           factor                  							                        {}                                                  
        ;

mulop:              MULT                                                                        {InsertInLine("A2MULT",1);}        
        |           DIV                                                                         {InsertInLine("A2DIV",1);}      
        ;


factor:             PAR_LEFT expression PAR_RIGHT           		                            {strcpy(Factor,ExResult);}

        |           var                                                                         {strcpy(Factor,$1);}   

        |           call                                                                        {strcpy(Factor,LastCall);}   

        |           NUMBER 												                        {sprintf(NumToChar,"%d",$1);strcpy(Factor,NumToChar);}                                               
        ;
        
        
        
        
        
call:               IDENTIFIER PAR_LEFT args PAR_RIGHT   
                                                                                                {NewLine();InsertInLine("CALL",1);InsertInLine($1,2);sprintf(NumToChar,"%d",Arguments);InsertInLine(NumToChar,3); NewLine();InsertInLine("RETURNOUT",1); strcpy(TempCommand,"_t"); sprintf(NumToChar,"%d",NextFreeRegister()); strcat(TempCommand,NumToChar); strcpy(LastCall,TempCommand);InsertInLine(TempCommand,2);
                                                                                                strcpy(Factor,"_t");strcat(Factor,NumToChar);}                                   
        ;
args:               arglist                                                                     {$$=Arguments;}                                                                                                                                        
        |                                														{}                                                   
        ;
arglist:            arglist COMMA expression           					                        {Arguments++;$$=Arguments;NewLine();InsertInLine("PARAMIN",1);if (OperationFlag==1) {InsertInLine(ExResult,2);}else {InsertInLine(Factor,2);} OperationFlag=0;}                                      
        |           expression 											                        {Arguments++;$$=Arguments;NewLine();InsertInLine("PARAMIN",1);if (OperationFlag==1) {InsertInLine(ExResult,2);}else {InsertInLine(Factor,2);} OperationFlag=0;}                                                            
        ;
        
%%

void yyerror(const char *s) {
    printf("Error : %s \n",s);
	yyparse();

}

int main(int argc, char **argv){
    ++argv;
    --argc;
    
    if(argc>0){
        yyin = fopen( argv[0], "r" );
    }
    else{
        yyin=stdin;
    }
   initReg();
   yyparse();
   //Print();
   transAssembly();
   PrintLines();
   return 0;
}
