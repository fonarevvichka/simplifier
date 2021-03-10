#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char** generateAllPossibleMinTerms(int length) {
    char** truthTable = NULL;
    if (length == 4) {
        truthTable = malloc(sizeof(char*) * 4); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                char* minTerm = malloc(2 * sizeof(char));
                minTerm[0] = a + '0';
                minTerm[1] = b + '0';
                truthTable[counter] = minTerm;
                counter++;
            }
        }
    } else if (length == 8) {
        truthTable = malloc(sizeof(char*) * 8); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                for (int c = 0; c < 2; c++) {
                    char* minTerm = malloc(3 * sizeof(char));
                    minTerm[0] = a + '0';
                    minTerm[1] = b + '0';
                    minTerm[2] = c + '0';
                    truthTable[counter] = minTerm;
                    counter++;
                }
            }
        }
    } else if (length == 16) {
        truthTable = malloc(sizeof(char*) * 16); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                for (int c = 0; c < 2; c++) {
                    for (int d = 0; d < 2; d++) {
                        char* minTerm = malloc(4 * sizeof(char));
                        minTerm[0] = a + '0';
                        minTerm[1] = b + '0';
                        minTerm[2] = c + '0';
                        minTerm[3] = d + '0';
                        truthTable[counter] = minTerm;
                        counter++;
                    }
                }
            }
        }
    } else if (length == 32) {
        truthTable = malloc(sizeof(char*) * 32); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                for (int c = 0; c < 2; c++) {
                    for (int d = 0; d < 2; d++) {
                        for (int e = 0; e < 2; e++) {
                            char* minTerm = malloc(5 * sizeof(char));
                            minTerm[0] = a + '0';
                            minTerm[1] = b + '0';
                            minTerm[2] = c + '0';
                            minTerm[3] = d + '0';
                            minTerm[4] = e + '0';
                            truthTable[counter] = minTerm;
                            counter++;
                        }
                    }
                }
            }
        }
    } else if (length == 64) {
        truthTable = malloc(sizeof(char*) * 64); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                for (int c = 0; c < 2; c++) {
                    for (int d = 0; d < 2; d++) {
                        for (int e = 0; e < 2; e++) {
                            for (int f = 0; f < 2; f++) {
                                char* minTerm = malloc(6 * sizeof(char));
                                minTerm[0] = a + '0';
                                minTerm[1] = b + '0';
                                minTerm[2] = c + '0';
                                minTerm[3] = d + '0';
                                minTerm[4] = e + '0';
                                minTerm[5] = f + '0';
                                truthTable[counter] = minTerm;
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }

    return truthTable;
}

char** getMinTerms(char* truthValues, int length, int minTermLength, int* numMinTerms) {
    int counter = 0;
    int locations[16]; 
    char** allPossibleMinTerms = generateAllPossibleMinTerms(length);
    
    for (int i = 0; i < length; i++) {
        if (truthValues[i] == '1')  {
            locations[counter] = i;
            counter++;
        }
    }

    char** minTerms = malloc(sizeof(char*) * counter);
    for (int i = 0; i < counter; i++) {
        minTerms[i] = malloc(sizeof(char) * minTermLength);
        strncpy(minTerms[i], allPossibleMinTerms[locations[i]], minTermLength);
    }
    for (int i = 0; i < length; i++) {
        free(allPossibleMinTerms[i]);
    }
    free(allPossibleMinTerms);

    *numMinTerms = counter;
    return minTerms;
}

int main(int argc, char *argv[]) {
    int length = 0;
    char* truthValues = NULL;
    if (argc == 3) {
        length = atoi(argv[2]);
        truthValues = argv[1];
    } else {
        printf("Invalid command line args: Need truth table values and length\n");
    }

    int numMinTerms = 0;
    char** minTerms = getMinTerms(truthValues, length, (int) log2(length), &numMinTerms);
    for (int i = 0; i < numMinTerms; i++) {
        printf("%s, ", minTerms[i]);
    }

    return 0;
}