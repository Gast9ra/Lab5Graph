#include <stdio.h>
#include "graph.h"

int main() {
    struct Graph b= newRibNum(1);
    struct Graph *a=newListGraphs();

    addGraphInMas(b,a);
    b.num=2;
    addGraphInMas(b,a);
    char i =indexInMas(0,a,3);
    printf("Hello, World!\n");
    return 0;
}