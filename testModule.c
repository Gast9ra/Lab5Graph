//
// Created by Gast9ra on 01.06.2019.
//
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "graph.h"

void testDel(){
    int result=1;
    struct Rib a=newRibNum(1);
    struct Rib b=newRibNum(2);
    a.list=addGraphInMas(b,a.list);
    a.list=addGraphInMas(newRibNum(3),a.list);
    a.list=delRibInGraph(b,a.list);
    if((_msize(a.list)/ sizeof(struct Rib))!=1) result=0;
    if(a.list[0].num!=3) result=0;
    assert(result);
}

void testAdd(){
    int result=1;
    struct Rib a=newRibNum(1);
    struct Rib b=newRibNum(2);
    a.list=addGraphInMas(b,a.list);
    a.list=addGraphInMas(newRibNum(3),a.list);
    if(a.list[1].num!=3) result=0;
    if(a.list[0].num!=2) result=0;
    assert(result);
}



int main() {
    testDel();
    testAdd();
    printf("Test done");
    return 0;
}



