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

  //  struct Graph *test=loadFile("C:\\Users\\Gast9ra\\CLionProjects\\Lab5Graph\\lab5\\fileDATA.txt");
    //writeInFile("C:\\Users\\Gast9ra\\CLionProjects\\Lab5Graph\\lab5\\file.txt",test);
//    printList(test);

    return 0;
}