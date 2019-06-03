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

struct Rib *masIntToRibList(int *data);

struct Rib *newListGraphs(void) {
    struct Rib *_graph = (struct Rib *) malloc(sizeof(struct Rib));
    if (_graph == NULL) return 0;              //if out memory
    _graph[0] = newRib();
    return _graph;
}

struct Rib newRib(void) {
    struct Rib result;
    result.num = 0;
    result.list = NULL;
    result.lenList = 0;
    return result;
}

struct Rib newRibNum(int num) {
    struct Rib result;
    result.num = num;
    result.list = NULL;
    result.lenList = 0;
    return result;
}

struct Rib *insertInList(struct Rib *list, struct Rib rib, int index) {
    if (list == NULL) {
        list = newListGraphs();
        list = insertInList(list, rib, index);
        return list;
    }
    list[index] = rib;
    return list;
}

struct Rib *addGraphInMas(struct Rib rib, struct Rib *list) {
    if (list == NULL) {
        list = newListGraphs();
        list = insertInList(list, rib, 0);
        return list;
    }
    int lenList = _msize(list) / sizeof(list[0]);
    if (indexInMas(rib.num, list) == 0) {
        struct Rib *newList = (struct Rib *) malloc((lenList + 1) * sizeof(struct Rib));
        if (newList == NULL)
            return list;

        memcpy(newList, list, (lenList) * sizeof(struct Rib));
        newList[lenList] = rib;
        free(list);
        return newList;
    }
    return list;
}

char indexInMas(int n, struct Rib *list) {
    int lenList = _msize(list) / sizeof(list[0]);
    for (int i = 0; i < lenList; i++) {
        if (list[i].num == n) return 1;
    }
    return 0;
}

void delList(struct Rib *list) {
    free(list);
}


void printListDebug(struct Rib *list) {
    int lenList = _msize(list) / sizeof(list[0]);
    for (int i = 0; i < lenList; i++) {
        printf("num %i \n mas %i\n len %i\n", list[i].num,
               _msize(list[i].list), list[i].lenList);
    }
}

void printList(struct Rib *list) {
    if (list == NULL) printf("Mas empty \n");
    int lenList = _msize(list) / sizeof(struct Rib);

    const char strNum[] = "Graph num=";
    const char enter[] = " \n";
    const char masStr[] = "Mas ribs=";
    const char comma[] = ", ";

    for (int i = 0; i < lenList; i++) {
        printf(strNum);
        printf("%i", list[i].num);
        printf(enter);

        printf(masStr);
        for (int j = 0; j < list[i].lenList; ++j) {
            if (j == list[i].lenList - 1) {  //if last sym
                printf("%i", list[i].list[j].num);
                continue;
            }
            printf("%i", list[i].list[j].num);
            printf(comma);
        }
        printf(enter);

        printf(enter);
    }
}

void writeInFile(char *fileName, struct Rib *list) {
    FILE *openFile = fopen(fileName, "w");
    if (openFile == NULL) printf("File not open \n");

    if (list == NULL) printf("Mas empty \n");
    int lenList = _msize(list) / sizeof(struct Rib);

    const char strNum[] = "Graph num=";
    const char enter[] = " \n";
    const char masStr[] = "Mas ribs=";
    const char comma[] = ", ";

    for (int i = 0; i < lenList; i++) {
        fputs(strNum, openFile);
        fputc(list[i].num + '0', openFile);
        fputs(enter, openFile);

        fputs(masStr, openFile);
        for (int j = 0; j < list[i].lenList; ++j) {
            if (j == list[i].lenList - 1) {  //if last sym
                fputc(list[i].list[j].num + '0', openFile);
                continue;
            }
            fputc(list[i].list[j].num + '0', openFile);
            fputs(comma, openFile);
        }
        fputs(enter, openFile);

        fputs(enter, openFile);
    }

    fclose(openFile);
}

struct Rib *loadFile(char *fileName) {
    FILE *openFile = fopen(fileName, "r");
    if (openFile == NULL) {
        printf("File not open \n");
        return NULL;
    }
    struct Rib *result = NULL;
    int lenChar = 0;
    char *file = malloc(sizeof(char));
    char c;
    while ((c = fgetc(openFile)) != EOF) {
        lenChar++;
        file = realloc(file, sizeof(char) * (lenChar));
        file[lenChar - 1] = c;
    }
    fclose(openFile);

    //parse string
    int *splitResultSlash = splitInOneStr('-', file, lenChar); //#
    if (splitResultSlash == NULL)
        return NULL;
    int lenSplitResultSlash = _msize(splitResultSlash) / sizeof(int);
    int *splitResultStr = split('\n', file, lenChar); //#
    if (splitResultStr == NULL)
        return NULL;


    for (int i = 0; i < lenSplitResultSlash; i++) {
        c = file[splitResultSlash[i] - 1];
        if (c >= '0' && c <= '9') {
            struct Rib rib;
            rib = newRibNum(c - '0');
            int *subSpl = subSplit(' ', file, splitResultSlash[i], splitResultStr[i]); //#All space in str
            int *ribs = calloc(1, sizeof(int)); //#rib in mas and repair to link
            if (ribs == NULL)
                return NULL;
            ribs[0] = file[splitResultSlash[i] + 1] - '0'; //num in right to slash
            int lenribs = 1;
            if (subSpl != NULL) {
                int lenSpl = _msize(subSpl) / sizeof(int);

                for (int j = 0; j < lenSpl; j++) {
                    int last;
                    if (j == lenSpl - 1) last = splitResultStr[i];
                    else last = subSpl[j + 1];
                    char *num = malloc(sizeof(char)); //#
                    if (num == NULL)
                        return NULL;
                    int lenNum = 0;

                    for (int g = subSpl[j] + 1; g < last; g++) {
                        char letter = file[g];
                        if (letter >= '0' && letter <= '9') {
                            lenNum++;
                            num = realloc(num, sizeof(char) * lenNum);
                            if (num == NULL)
                                return NULL;
                            num[lenNum - 1] = letter;
                        }
                    }
                    int prRib = atoi(num); //rib for mas in int
                    lenribs++;
                    ribs = realloc(ribs, sizeof(int) * lenribs);
                    if (ribs == NULL)
                        return NULL;
                    ribs[lenribs - 1] = prRib;
                    free(num);
                }
            }

            rib.list = masIntToRibList(ribs);
            rib.lenList = _msize(rib.list) / sizeof(struct Rib);
            result = addGraphInMas(rib, result);

            free(subSpl);
            free(ribs);
        }
        //printf("test debug\n");
    }

    free(file);
    free(splitResultSlash);
    free(splitResultStr);

    //link ribs
    int lenResult = _msize(result) / sizeof(struct Rib);
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
                if (result == NULL)
                    return NULL;
            } else {
                result = realloc(result, sizeof(int) * (lenResult));
                if (result == NULL)
                    return NULL;
            }


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
                if (result == NULL)
                    return NULL;
            } else {
                result = realloc(result, sizeof(int) * (lenResult));
                if (result == NULL)
                    return NULL;
            }

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
                if (result == NULL)
                    return NULL;
            } else {
                result = realloc(result, sizeof(int) * (lenResult));
                if (result == NULL)
                    return NULL;
            }

            result[lenResult - 1] = i;
        }
    }
    return result;

}

struct Rib *masIntToRibList(int *data) {
    struct Rib *result = newListGraphs();
    int len = _msize(data) / sizeof(int);
    result[0].num = data[0];
    for (int i = 1; i < len; i++) {
        result = addGraphInMas(newRibNum(data[i]), result);
    }
    return result;
}

struct Rib *delRibInGraph(struct Rib rb, struct Rib *list) {
    if (list == NULL) return list;
    int lenmas = _msize(list) / sizeof(struct Rib);
    int num = rb.num;

    for (int i = 0; i < lenmas; i++) {
        if (list[i].num == num) {
            free(list[i].list);
            struct Rib *newlist = NULL;
            for (int j = 0; j < lenmas; j++) {
                if (list[j].num != num)
                    newlist=addGraphInMas(list[j], newlist);
            }
            list = newlist;
            break;
        }
    }
    lenmas = _msize(list) / sizeof(struct Rib);
    for (int i = 0; i < lenmas; i++) {
        list[i].list = delRibInGraph(rb, list[i].list);
        list[i].lenList = _msize(list[i].list) / sizeof(struct Rib);
    }

    return list;
}

