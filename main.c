#include <stdio.h>
#include "graph.h"


int main(int argc, char *argv[]) {
    switch (argc) {

        case 2:
            printList(loadFile(argv[1]));
            break;

        case 3:
            writeInFile(argv[2],loadFile(argv[1]));
            break;

        default:
            printf("Not arguments");
            break;
    }


    return 0;
}