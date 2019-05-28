//
// Created by Gast9ra on 21.05.2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "graph.h"


struct Graph *newListGraphs(void) {
    struct Graph *_graph = (struct Graph*) malloc(sizeof(struct Graph));
    if (_graph == NULL) return 0;              //if out memory
    _graph[0] = newRib();
    return _graph;
}

struct Graph newRib(void) {
    struct Graph result;
    result.num = 0;
    result.list = NULL;
    result.lenList = 0;
    return result;
}

struct Graph newRibNum(int num) {
    struct Graph result;
    result.num = num;
    result.list = NULL;
    result.lenList = 0;
    return result;
}

struct Graph *addGraphInMas(struct Graph rib, struct Graph *list) {
    if (list == NULL) {
        list = newListGraphs();
        addGraphInMas(rib,list);
    }
    int lenList = _msize(list) / sizeof(list[0]);
    if (indexInMas(rib.num, list) == 0) {
        struct Graph *newList = (struct Graph*) malloc((lenList+1) * sizeof(struct Graph));
        memcpy(newList,list,(lenList)* sizeof(struct Graph));
        newList[lenList] = rib;
        return newList;
    }
    return list;
}

char indexInMas(int n, struct Graph *list) {
    int lenList = _msize(list) / sizeof(list[0]);
    for (int i = 0; i < lenList; i++) {
        if (list[i].num == n) return 1;
    }
    return 0;
}

void delList(struct Graph *list) {
    free(list);
}

void printList(struct Graph *list) {
    int lenList = _msize(list) / sizeof(list[0]);
    for (int i = 0; i < lenList; i++) {
        printf("num %i \n mas%i\n len %i\n", list[0].num,
               _msize(list[0].list), list[0].lenList);
    }
}


struct Graph *loadFile(char *fileName){
    FILE *graphFile = fopen(fileName, "r");


}

