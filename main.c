#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "blackbox.h"

unsigned long *makeList(unsigned long size);

int main(int argc, char *argv[]) {
    int c;
    int function = 0;
    int iterations = 0;
    clock_t timeElapsed[3];
    unsigned long size = 0;
    FILE *fp = NULL;

    if (argc == 1) {
        printf("usage: main -s size -f function -i iterations\n");
        exit(EXIT_FAILURE);
    }
    while((c = getopt(argc, argv, "s:f:i:F:")) != -1) {
        switch(c) {
            case 's':
                size = atol(optarg);
                break;
            case 'f':
                function = atoi(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
            case 'F':
                fp = fopen(optarg, "a");
            case ':':
                fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
                exit(EXIT_FAILURE);
            case '?':
            default:
                printf("illegal option %c - ignored\n", optopt);
                printf("usage: main -s size -f function\n");
                break;
        }
    }

    unsigned long increments = size / iterations;

    if(function) {
        switch(function) {
            case 1:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_1(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 2:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_2(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 3:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    unsigned long *list = makeList(i);
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_3(list, i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    free(list);
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 4:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_4(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 5:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_5(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 6:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    unsigned long *list = makeList(i);
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_6(list, i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    free(list);
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 7:
                for(unsigned long i = 0; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_7(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

unsigned long *makeList(unsigned long size) {
    unsigned long i;
    unsigned long *list = malloc(size * sizeof(unsigned long));

    for(i = 0; i < size; i++){
        *(list+i) = i;
    }
    return list;
}