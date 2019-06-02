//
// Created by Gast9ra on 21.05.2019.
//

#ifndef LAB5GRAPH_GRAPH_H
#define LAB5GRAPH_GRAPH_H


struct Rib {
    int num; //name rib
    struct Rib *list; //list for ribs
    int lenList;
};


//create new list for ribs
struct Rib *newListGraphs(void);

//new rib with num 0
struct Rib newRib(void);

struct Rib newRibNum(int num);

struct Rib *addGraphInMas(struct Rib rib, struct Rib *list);

char indexInMas(int n, struct Rib *list);

void delList(struct Rib *list);

struct Rib *loadFile(char *fileName);

struct Rib *insertInList(struct Rib *list, struct Rib rib, int index);

void writeInFile(char *fileName, struct Rib *list);

void printList(struct Rib *list);

struct Rib *delRibInGraph(struct Rib rb, struct Rib *list);

#endif //LAB5GRAPH_GRAPH_H
