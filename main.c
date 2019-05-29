#include <stdio.h>
#include "graph.h"

int main() {
    struct Graph b= newRibNum(1);
    struct Graph *a=newListGraphs();

    a=addGraphInMas(b,a);
    b.num=2;
    a=addGraphInMas(b,a);
    char i = indexInMas(0, a);
    loadFile("C:\\Users\\Gast9ra\\CLionProjects\\Lab5Graph\\lab5\\fileDATA.txt");

    printf("Hello, World!\n");
    return 0;
}