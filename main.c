#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "blackbox.h"

unsigned long *makeList(unsigned long size);

int main(int argc, char *argv[]) {
    int c;
    int function;
    unsigned long size;

    if (argc == 1) {
        printf("usage: main -s size -f function\n");
        exit(EXIT_FAILURE);
    }
    while((c = getopt(argc, argv, ":s:f")) != -1) {
        switch(c) {
            case 's':
                size = atoi(optarg);
                break;
            case 'f':
                function = atoi(optarg);
                break;
            case ':':
                fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
                exit(EXIT_FAILURE);
            case '?':
            default:
                printf("illegal option %c - ignored\n", optopt);
                printf("uusage: main -s size -f function\n");
                break;
        }
    }
    unsigned long *list = makeList(size);
    for (int i = 0; i < size; ++i) {
        printf("%lu\n", *(list + i));
    }
}

unsigned long *makeList(unsigned long size) {
    unsigned long i;
    unsigned long *list = malloc(size * sizeof(unsigned long));

    for(i = 0; i < size; i++){
        *(list+i) = i;
    }
    return list;
}