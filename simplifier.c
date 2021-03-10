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
                // minTerm[2] = '\0';
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
                    // minTerm[3] = '\0';
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
                        // minTerm[4] = '\0';
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
                            // minTerm[5] = '\0';
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
                                // minTerm[6] = '\0';
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
        minTerms[i] = malloc(sizeof(char) * (minTermLength + 1));
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
    int simplifiedMinTermsLength = 0;
    char** simplifiedMinTerms = malloc(sizeof(char*) * numMinTerms);
    
    int soloMinTermsLength = 0;
    char** soloMinTerms = malloc(sizeof(char*) * numMinTerms);
    
    int matchedMinTermsLength = 0;
    char** matchedMinTerms = malloc(sizeof(char*) * numMinTerms);
    
    
    for (int i = 0; i < numMinTerms; i++) {
        for (int j = i+1; j < numMinTerms; j++) {
            char* termOne = minTerms[i];
            char* termTwo = minTerms[j];
            int differenceIndex = findDifference(termOne, termTwo, minTermLength);
            if (differenceIndex != -1) {
                // add simplified term to list
                char* simplifiedMinTerm = malloc(sizeof(char) * (minTermLength + 1));
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
                    if (strncmp(simplifiedMinTerm, simplifiedMinTerms[k], minTermLength) == 0) {
                        matchFound = true;
                        break;
                    }
                }

                if (!matchFound) {
                    simplifiedMinTerms[simplifiedMinTermsLength] = simplifiedMinTerm;
                    simplifiedMinTermsLength++;
                }
                // add simplified term to list

                //add original terms to list to avoid duplicates
                matchedMinTerms[matchedMinTermsLength] = malloc(sizeof(char) * (minTermLength + 1));
                strncpy(matchedMinTerms[matchedMinTermsLength++], termOne, minTermLength);
                matchedMinTerms[matchedMinTermsLength] = malloc(sizeof(char) * (minTermLength + 1));
                strncpy(matchedMinTerms[matchedMinTermsLength++], termTwo, minTermLength);
                //add original terms to list to avoid duplicates
            } else {
                // check if term is already accounted for
                bool matchFound = false;
                for (int k = 0; k < matchedMinTermsLength; k++) {
                    if (strncmp(termOne, matchedMinTerms[k], minTermLength) == 0) {
                        matchFound = true;
                        break;
                    }
                }

                if (!matchFound) {
                    soloMinTerms[soloMinTermsLength] = malloc(sizeof(char) * (minTermLength + 1));
                    strncpy(soloMinTerms[soloMinTermsLength++], termOne, minTermLength);
                }
            }
        }
    }


    int newMinTermsLength = soloMinTermsLength + simplifiedMinTermsLength;
    char** newMinTerms = malloc(sizeof(char*) * newMinTermsLength);

    printf("length: %d \n", simplifiedMinTermsLength);
    for (int i = 0; i < simplifiedMinTermsLength; i++) {
        newMinTerms[i] = malloc(sizeof(char) * (minTermLength + 1));
        strncpy(newMinTerms[i], simplifiedMinTerms[i], minTermLength + 1);
        // newMinTerms[i][minTermLength] = '\0';
    }
    
    printf("length: %d \n", soloMinTermsLength);
    for (int i = 0; i < soloMinTermsLength; i++) {
        newMinTerms[simplifiedMinTermsLength + i] = malloc(sizeof(char) * (minTermLength + 1));
        strncpy(newMinTerms[simplifiedMinTermsLength + i], simplifiedMinTerms[i], minTermLength + 1);
        // newMinTerms[simplifiedMinTermsLength + i][minTermLength] = '\0';
    }

    for (int i = 0; i < newMinTermsLength; i++) {
        printf("%s \n", newMinTerms[i]);
    }

    // Garbage collection
    for (int i = 0; i < simplifiedMinTermsLength; i++) {
        free(simplifiedMinTerms[i]);
    }
    free(simplifiedMinTerms);
    
    for (int i = 0; i < soloMinTermsLength; i++) {
        free(soloMinTerms[i]);
    }
    free(soloMinTerms);
    
    for (int i = 0; i < matchedMinTermsLength; i++) {
        free(matchedMinTerms[i]);
    }
    free(matchedMinTerms);

    return newMinTerms;
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

    simplifyLogic(minTerms, numMinTerms, minTermLength);

    for (int i = 0; i < numMinTerms; i++) {
        free(minTerms[i]);
    }
    free(minTerms);

    return 0;
}