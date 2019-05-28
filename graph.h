//
// Created by Gast9ra on 21.05.2019.
//

#ifndef LAB5GRAPH_GRAPH_H
#define LAB5GRAPH_GRAPH_H


struct Graph {
    int num; //name rib
    struct Graph *list; //list for ribs
    int lenList;
};



//create new list for ribs
struct Graph *newListGraphs(void);

//new rib with num 0
struct Graph newRib(void);

struct Graph newRibNum(int num);

struct Graph * addGraphInMas(struct Graph rib, struct Graph *list);

char indexInMas(int n,struct Graph *list,int len);

void delList(struct Graph *list);

void printList(struct Graph *list);
#endif //LAB5GRAPH_GRAPH_H
