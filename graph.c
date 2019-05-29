//
// Created by Gast9ra on 21.05.2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "graph.h"

int *split(char c, char *mas, int lenMas);

int *subSplit(char c, char *mas, int start, int end);

int *splitInOneStr(char c, char *mas, int lenMas);


struct Graph *newListGraphs(void) {
    struct Graph *_graph = (struct Graph *) malloc(sizeof(struct Graph));
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
        addGraphInMas(rib, list);
    }
    int lenList = _msize(list) / sizeof(list[0]);
    if (indexInMas(rib.num, list) == 0) {
        struct Graph *newList = (struct Graph *) malloc((lenList + 1) * sizeof(struct Graph));
        if (newList == NULL)
            return list;

        memcpy(newList, list, (lenList) * sizeof(struct Graph));
        newList[lenList] = rib;
        free(list);
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


struct Graph *loadFile(char *fileName) {
    FILE *openFile = fopen(fileName, "r");
    if (openFile == NULL) {
        printf("File not open \n");
        return NULL;
    }
    struct Graph *list = newListGraphs();
    int lenChar = 0;
    char *file;
    char c;
    while ((c = fgetc(openFile)) != EOF) {
        lenChar++;
        file = realloc(file, sizeof(char) * (lenChar));
        file[lenChar - 1] = c;
        //if( c >= '0' && c <= '9' ) printf("%c ",c);
    }
    fclose(openFile);

    int *splitResultSlash = splitInOneStr('-', file, lenChar);
    int lenSplitResultSlash = _msize(splitResultSlash) / sizeof(int);
    int *splitResultStr = split('\n', file, lenChar);
    //int lenSplitResultStr=_msize(splitResultStr) / sizeof(int);

    for (int i = 0; i < lenSplitResultSlash; i++) {
        c = file[splitResultSlash[i] - 1];
        if (c >= '0' && c <= '9') {
            struct Graph rib;
            rib.num = (int) c;
            int* subSpl= subSplit(' ',file,splitResultSlash[i],splitResultStr[i]);
            int lenSpl=_msize(subSpl) / sizeof(int);
            for(int j=0;j<lenSpl;j++){
                
            }

        }
        printf("test\n");
    }


    return list;
}

int *splitInOneStr(char c, char *mas, int lenMas){
    int *result;
    int lenResult = 0;
    char oneStr=1; //bool
    for (int i = 0; i < lenMas; i++) {
        if (c == mas[i]&& oneStr==1) {
            lenResult++;
            oneStr=0;
            if (lenResult == 1) {
                result = malloc(sizeof(int) * lenResult);
            } else
                result = realloc(result, sizeof(int) * (lenResult));

            result[lenResult - 1] = i;
        }

        if ('\n'==mas[i]) oneStr=1;
    }
    return result;
}

int *split(char c, char *mas, int lenMas) {
    int *result;
    int lenResult = 0;
    for (int i = 0; i < lenMas; i++) {
        if (c == mas[i]) {
            lenResult++;
            if (lenResult == 1) {
                result = malloc(sizeof(int) * lenResult);
            } else
                result = realloc(result, sizeof(int) * (lenResult));

            result[lenResult - 1] = i;
        }
    }
    return result;
}

int *subSplit(char c, char *mas, int start, int end) {
    int *result;
    int lenResult = 0;
    for (int i = start; i < end; i++) {
        if (c == mas[i]) {
            lenResult++;
            if (lenResult == 1) {
                result = malloc(sizeof(int) * lenResult);
            } else
                result = realloc(result, sizeof(int) * (lenResult));

            result[lenResult - 1] = i;
        }
    }
    return result;

}

