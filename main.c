#include <stdio.h>
#include "graph.h"

int main(int argc, char * argv[]) {
    struct Graph b= newRibNum(1);
    struct Graph *a=newListGraphs();

    a=addGraphInMas(b,a);
    b.num=2;
    a=addGraphInMas(b,a);
    char i = indexInMas(0, a);
    struct Graph *test=loadFile("C:\\Users\\Gast9ra\\CLionProjects\\Lab5Graph\\lab5\\fileDATA.txt");
//    printList(test);
    //writeInFile("C:\\Users\\Gast9ra\\CLionProjects\\Lab5Graph\\lab5\\file.txt",test);
    printf("END!\n");
    return 0;
}