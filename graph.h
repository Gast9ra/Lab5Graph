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

struct Graph *addGraphInMas(struct Graph rib, struct Graph *list);

char indexInMas(int n, struct Graph *list);

void delList(struct Graph *list);

void printList(struct Graph *list);

struct Graph *loadFile(char *fileName);

struct Graph *insertInList(struct Graph *list, struct Graph rib, int index);

void writeInFile(char *fileName, struct Graph *list);

#endif //LAB5GRAPH_GRAPH_H
