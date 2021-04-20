/**
 * @file main.c
 * @author Donovan Griego
 * @brief Runs functions inside of blackbox.o and prints the run-time in a file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "blackbox.h"

unsigned long *makeList(unsigned long size);
void shuffleList(unsigned long *list, unsigned long size);
unsigned long *reverseList(unsigned long size);
void swap(unsigned long *a, unsigned long *b);
unsigned long randomNumber();

int main(int argc, char *argv[]) {
    int c;
    int function = 0;
    int iterations = 0;
    int type = 1;
    clock_t timeElapsed[3];
    unsigned long size = 0;
    FILE *fp = NULL;

    if (argc == 1) {
        printf("usage: main -s size -f function -i iterations -F filename -S -R -M\n");
        exit(EXIT_FAILURE);
    }
    while((c = getopt(argc, argv, "s:f:i:F:SRM")) != -1) {
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
                fp = fopen(optarg, "w");
                break;
            case 'S':
                type = 1;
                break;
            case 'R':
                type = 2;
                break;
            case 'M':
                type = 3;
                break;
            case ':':
                fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
                exit(EXIT_FAILURE);
            case '?':
            default:
                printf("illegal option %c - ignored\n", optopt);
                printf("usage: main -s size -f function -i iterations -F filename -S -R -M\n");
                break;
        }
    }

    unsigned long increments = size / iterations;

    if(function) {      //Functions are run 3 times with each data point and then the results are averaged
        switch(function) {
            case 1:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_1(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 2:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_2(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 3:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    unsigned long *list;        //array is generated then freed for each data set using dynamic values based on iterations
                    if(type == 2)
                        list = reverseList(i);
                    else
                        list = makeList(i);
                    if(type == 3)
                        shuffleList(list, i);
                    for(int j = 0; j < 3; j++) {        //same array is used for each iteration
                        timeElapsed[j] = clock();
                        function_3(list, i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    free(list);
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 4:
                for(unsigned long i = 2; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_4(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 5:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_5(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 6:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    unsigned long *list;
                    if(type == 2)
                        list = reverseList(i);
                    else
                        list = makeList(i);
                    if(type == 3)
                        shuffleList(list, i);
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_6(list, i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    free(list);
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            case 7:
                for(unsigned long i = 1; i <= size; i+= increments) {
                    for(int j = 0; j < 3; j++) {
                        timeElapsed[j] = clock();
                        function_7(i);
                        timeElapsed[j] = clock() - timeElapsed[j];
                    }
                    fprintf(fp, "%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                    printf("%lu %lu\n", i, ((timeElapsed[0] + timeElapsed[1] + timeElapsed[2]) / 3));
                }
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

/**
 * Takes a size and makes an array of that size
 * @param size the size of array
 * @return address pointing to created array
 */
unsigned long *makeList(unsigned long size) {
    unsigned long i;
    unsigned long *list = malloc(size * sizeof(unsigned long));

    for(i = 0; i < size; i++){
        *(list+i) = i;
    }
    return list;
}

/**
 * Takes an array and its size and shuffles the elements around
 * @param list address pointing to array
 * @param size size of array
 */
void shuffleList(unsigned long *list, unsigned long size) {
    srandom(time(NULL));
    for (unsigned long i = size - 1; i > 0; i--) {
        unsigned long j = randomNumber() % (i + 1);
        swap(&(list[0]), &(list[j]));
    }
}

/**
 * Takes a size and makes an array of that size in reversed order
 * @param size the size of array
 * @return the array generated
 */
unsigned long *reverseList(unsigned long size) {
    unsigned long i, j = 0;
    unsigned long *list = malloc(size * sizeof(unsigned long));

    for(i = size - 1; i > 0; i--) {
        *(list+i) = j++;
    }
    return list;
}

/**
 * swaps two values at specified addresses
 * @param a address of value one
 * @param b address of value two
 */
void swap(unsigned long *a, unsigned long *b) {
    unsigned long temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * generates a random unsigned long
 * @return the random number
 */
unsigned long randomNumber() {
    unsigned long n, p, r;
    int i;

    n = 0;
    for(i = 0, p = 1; i < 8; i++, p *= 256) {
        r = random() % 256;
        n += r * p;
    }
    return n;
}