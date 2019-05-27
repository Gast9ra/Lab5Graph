//
// Created by Gast9ra on 21.05.2019.
//
#include <stdlib.h>
#include "graph.h"
#include <stdio.h>


struct Graph *newListGraphs(void) {
    struct Graph *_graph = malloc(sizeof(_graph));
    if (_graph == NULL) return 0;              //if out memory
    _graph[0] = newRib();
    return _graph;
}

struct Graph newRib(void) {
    struct Graph result;
    result.num = 0;
    result.list = NULL;
    result.lenList = 0;
    //result.list = (struct Graph *) malloc(sizeof(*result.list));
    return result;
}

struct Graph newRibNum(int num) {
    struct Graph result;
    result.num = num;
    result.list = NULL;
    result.lenList = 0;
    // result.list = (struct Graph *) malloc(sizeof(*result.list));
    return result;
}

void addGraphInMas(struct Graph rib, struct Graph *list) {
    if (list == NULL) {
        list = (struct Graph *) malloc(sizeof(struct Graph) + sizeof(rib));
        return;
    }
    int lenList = _msize(list) / sizeof(list[0]);
    if (indexInMas(rib.num, list, lenList) == 0) {
        lenList++;
        printList(list);
        struct Graph *newlist = realloc(list, lenList * sizeof(struct Graph));

        printf("_\n");
        printList(newlist);
        list[lenList - 1] = rib;
        list = newlist;
    }
}

char indexInMas(int n, struct Graph *list, int len) {
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


