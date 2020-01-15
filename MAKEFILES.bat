flex project.fl
bison project.y
bison -d project.y
gcc lex.yy.c project.tab.c Ascode.c symtable.c TAC.c -o Compiler.exe
Compiler.exe Test.txt


pause