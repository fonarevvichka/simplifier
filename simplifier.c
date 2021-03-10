#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h> 

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

int findDifference(char* termOne, char* termTwo, int minTermLength) {
    int differences = 0;
    int index = -1;

    for (int i = 0; i < minTermLength; i++) {
        if (termOne[i] != termTwo[i]) {
            differences++;
            index = i;
        }
    }

    if (differences == 1) {
        return index;
    } else {
        return -1;
    }
}

int checkMatch(char* termOne, char* termTwo, int minTermLength) {
    int differences = 0;

    for (int i = 0; i < minTermLength; i++) {
        if (termOne[i] != '-' && termTwo[i] != '-' && termOne[i] != termTwo[i]) {
            differences++;
        }
    }

    return differences == 0;
}

char** simplifyLogic(char** minTerms, int numMinTerms, int minTermLength) {
    int matchedMinTermsLength = 0;
    char** matchedMinTerms = malloc(sizeof(char*) * numMinTerms);

    int simplifiedMinTermsLength = 0;
    char** simplifiedMinTerms = malloc(sizeof(char*) * numMinTerms);
    
    int soloMinTermsLength = 0;
    char** soloMinTerms = malloc(sizeof(char*) * numMinTerms);
    
    for (int i = 0; i < numMinTerms; i++) {
        for (int j = 0; j < numMinTerms; j++) {
            if (i != j) {
                char* termOne = minTerms[i];
                char* termTwo = minTerms[j];
                int differenceIndex = findDifference(termOne, termTwo, minTermLength);
                if (differenceIndex != -1) {
                    // add simplified term to list
                    char* simplifiedMinTerm = malloc(1 + sizeof(char) * minTermLength);
                    for (int k = 0; k < minTermLength; k++) {
                        if (k == differenceIndex) {
                            simplifiedMinTerm[k] = '-';
                        } else {
                            simplifiedMinTerm[k] = termOne[i];
                        }
                    }
                    simplifiedMinTerm[minTermLength] = '\0';

                    bool matchFound = false;
                    for (int k = 0; k < simplifiedMinTermsLength; k++) {
                        // if (*simplifiedMinTerm != *(simplifiedMinTerms[k])) {
                        if (strncmp(simplifiedMinTerm, simplifiedMinTerms[k], minTermLength) == 0) {
                            matchFound = true;
                            break;
                        }
                    }

                    if (!matchFound) {
                        simplifiedMinTerms[simplifiedMinTermsLength++] = simplifiedMinTerm;
                    }
                    // add simplified term to list

                    //add original terms to list to avoid duplicates
                    matchedMinTerms[matchedMinTermsLength++] = termOne;
                    matchedMinTerms[matchedMinTermsLength++] = termTwo;
                    //add original terms to list to avoid duplicates
                } else {
                    // check if term is already accounted for
                    bool matchFound = false;
                    for (int k = 0; k < matchedMinTermsLength; k++) {
                        if (matchedMinTerms[k] == termOne) {
                            matchFound = true;
                        }
                    }
                    if (!matchFound) {
                        soloMinTerms[soloMinTermsLength++] = termOne;
                    }
                }
            }
        }
    }

    printf("%d \n", simplifiedMinTermsLength);
    for (int i = 0; i < simplifiedMinTermsLength; i++) {
        // for (int j = 0; j < minTermLength; j++) {
        //     printf("%c", simplifiedMinTerms[i][j]);
        // }
        // printf("\n");
        printf("%s \n", simplifiedMinTerms[i]);
    }
    // printf("\n");
    // for (int i = 0; i < soloMinTermsLength; i++) {
    //     printf("%s, ", soloMinTerms[i]);
    // }
    // printf("\n");

    free(matchedMinTerms);
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
    int minTermLength = (int) log2(length);
    char** minTerms = getMinTerms(truthValues, length, minTermLength, &numMinTerms);


    printf("all min terms \n");
    for (int i = 0; i < numMinTerms; i++) {
        printf("%s, ", minTerms[i]);
    }

    printf("\nsimplified terms\n");
    simplifyLogic(minTerms, numMinTerms, minTermLength);

    for (int i = 0; i < numMinTerms; i++) {
        free(minTerms[i]);
    }
    free(minTerms);

    return 0;
}