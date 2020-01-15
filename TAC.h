/*CEI222:Project Step 4 ID:Marios Charalambous-13112_Antonis Savvides-17007_Dimitrios Ioannou-14423*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//poses grames iparxoun arxizi apo 1 an den iaproxu ngrames eina i1


struct Line {
	//line number/address
    int LineN;
    //next struct/line pointer
    struct Line *NextL;
    //text entolis
    char Command[20];
	char Result[20];
	char Variable1[20];
	char Variable2[20];
	
};
void NewLine();
void PrintLines();
void InsertInLine(char *InsertedCommand,int Information);
void InsertInLineC(char *InsertedCommand,int Information,int LineC);
int NextFreeRegister();
int LastLineAddress();
void initReg();
int LastLabelNum();
