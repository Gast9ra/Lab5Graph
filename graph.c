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

struct Graph *masIntToRibList(int *data);

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

struct Graph *insertInList(struct Graph *list, struct Graph rib, int index){
    if(list==NULL){
        list= newListGraphs();
        list=insertInList(list,rib,index);
        return list;
    }

    list[index]=rib;
    return list;

}

struct Graph *addGraphInMas(struct Graph rib, struct Graph *list) {
    if (list == NULL) {
        list = newListGraphs();
        list = insertInList(list,rib,0);
        return list;
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
        printf("num %i \n mas%i\n len %i\n", list[i].num,
               _msize(list[i].list), list[i].lenList);
    }
}



struct Graph *loadFile(char *fileName) {
    FILE *openFile = fopen(fileName, "r");
    if (openFile == NULL) {
        printf("File not open \n");
        return NULL;
    }
    struct Graph *result = NULL;
    int lenChar = 0;
    char *file;
    char c;
    while ((c = fgetc(openFile)) != EOF) {
        lenChar++;
        file = realloc(file, sizeof(char) * (lenChar));
        file[lenChar - 1] = c;
    }
    fclose(openFile);

    //parse string
    int *splitResultSlash = splitInOneStr('-', file, lenChar); //#
    int lenSplitResultSlash = _msize(splitResultSlash) / sizeof(int);
    int *splitResultStr = split('\n', file, lenChar); //#


    for (int i = 0; i < lenSplitResultSlash; i++) {
        c = file[splitResultSlash[i] - 1];
        if (c >= '0' && c <= '9') {
            struct Graph rib;
            rib = newRibNum(c - '0');
            int *subSpl = subSplit(' ', file, splitResultSlash[i], splitResultStr[i]); //#All space in str
            int *ribs = calloc(1, sizeof(int)); //#rib in mas and repair to link
            ribs[0] = file[splitResultSlash[i] + 1] - '0'; //num in right to slash
            int lenribs = 1;
            if (subSpl != NULL) {
                int lenSpl = _msize(subSpl) / sizeof(int);

                for (int j = 0; j < lenSpl; j++) {
                    int last;
                    if (j == lenSpl - 1) last = splitResultStr[i];
                    else last = subSpl[j + 1];
                    char *num = malloc(sizeof(char)); //#
                    int lenNum = 0;

                    for (int g = subSpl[j] + 1; g < last; g++) {
                        char letter = file[g];
                        if (letter >= '0' && letter <= '9') {
                            lenNum++;
                            num = realloc(num, sizeof(char) * lenNum);
                            num[lenNum - 1] = letter;
                        }
                    }
                    int prRib = atoi(num); //rib for mas in int
                    lenribs++;
                    ribs = realloc(ribs, sizeof(int) * lenribs);
                    ribs[lenribs - 1] = prRib;
                    free(num);
                }
            }

            rib.list = masIntToRibList(ribs);
            rib.lenList = _msize(rib.list) / sizeof(struct Graph);
            result = addGraphInMas(rib, result);
            free(subSpl);
            free(ribs);
        }
        //printf("test debug\n");
    }

    free(splitResultSlash);
    free(splitResultStr);

    //link ribs
    int lenResult = _msize(result) / sizeof(struct Graph);
    for (int i = 0; i < lenResult; i++) {
        int num = result[i].num;

        for (int j = 0; j < lenResult; j++) {

            for (int g = 0; g < result[j].lenList; g++) {
                if (result[j].list[g].num == num) {
                    result[j].list[g] = result[i];
                }
            }
        }
    }

    return result;
}


int *splitInOneStr(char c, char *mas, int lenMas) {
    int *result;
    int lenResult = 0;
    char oneStr = 1; //bool
    for (int i = 0; i < lenMas; i++) {
        if (c == mas[i] && oneStr == 1) {
            lenResult++;
            oneStr = 0;
            if (lenResult == 1) {
                result = malloc(sizeof(int) * lenResult);
            } else
                result = realloc(result, sizeof(int) * (lenResult));

            result[lenResult - 1] = i;
        }

        if ('\n' == mas[i]) oneStr = 1;
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
    int *result = NULL;
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

struct Graph *masIntToRibList(int *data) {
    struct Graph *result = newListGraphs();
    int len = _msize(data) / sizeof(int);
    result[0].num = data[0];
    for (int i = 1; i < len; i++) {
        result = addGraphInMas(newRibNum(data[i]), result);
    }
    return result;
}