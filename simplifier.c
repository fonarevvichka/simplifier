#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h> 

struct option {
    char** minTerms;
    int length;
};

char** generateAllPossibleMinTerms(int length) {
    char** truthTable = NULL;
    if (length == 4) {
        truthTable = malloc(sizeof(char*) * 4); 
        int counter = 0;
        for (int a = 0; a < 2; a++) {
            for (int b = 0; b < 2; b++) {
                char* minTerm = malloc(3);
                minTerm[0] = a + '0';
                minTerm[1] = b + '0';
                minTerm[2] = '\0';
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
                    char* minTerm = malloc(4);
                    minTerm[0] = a + '0';
                    minTerm[1] = b + '0';
                    minTerm[2] = c + '0';
                    minTerm[3] = '\0';
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
                        char* minTerm = malloc(5);
                        minTerm[0] = a + '0';
                        minTerm[1] = b + '0';
                        minTerm[2] = c + '0';
                        minTerm[3] = d + '0';
                        minTerm[4] = '\0';
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
                            char* minTerm = malloc(6);
                            minTerm[0] = a + '0';
                            minTerm[1] = b + '0';
                            minTerm[2] = c + '0';
                            minTerm[3] = d + '0';
                            minTerm[4] = e + '0';
                            minTerm[5] = '\0';
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
                                char* minTerm = malloc(7);
                                minTerm[0] = a + '0';
                                minTerm[1] = b + '0';
                                minTerm[2] = c + '0';
                                minTerm[3] = d + '0';
                                minTerm[4] = e + '0';
                                minTerm[5] = f + '0';
                                minTerm[6] = '\0';
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
        minTerms[i] = malloc(minTermLength);
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

bool mappingExists(char** minTerms, int numMinTerms, char** reducedMinTerms, int numReducedMinTerms, int minTermLength) {
    int matchesFound = 0;

    for (int i = 0; i < numMinTerms; i++) {
        for (int j = 0; j < numReducedMinTerms; j++) {
            if (checkMatch(minTerms[i], reducedMinTerms[j], minTermLength)) {
                matchesFound++;
                break;
            }
        }
    }

    return matchesFound == numMinTerms;
}

bool member(char** terms, int length, char* term, int termLength) {
    for (int i = 0; i < length; i++) {
        if (strncmp(terms[i], term, termLength) == 0) {
            return true;
        }
    }
    return false;
}

char** simplifyLogic(char** minTerms, int numMinTerms, int minTermLength, int* numNewMinTerms) {
    int     simplifiedTermsLength   = 0;
    char**  simplifiedTerms         = calloc(sizeof(char*), numMinTerms * numMinTerms);
    
    int     soloTermsLength         = 0;
    char**  soloTerms               = calloc(sizeof(char*), numMinTerms * numMinTerms);
    
    int     matchedTermsLength      = 0;
    char**  matchedTerms            = calloc(sizeof(char*), numMinTerms * numMinTerms);

    for (int i = 0; i < numMinTerms; i++) {
        bool simplificationFound = false;
        char* termOne = minTerms[i];
        for (int j = i + 1; j < numMinTerms; j++) {
            char* termTwo = minTerms[j];
            int differenceIndex = findDifference(termOne, termTwo, minTermLength);

            if (differenceIndex != -1) { //found a singular difference
                //--------------- simplify term ---------------//
                char* simplifiedMinTerm = malloc(minTermLength);
                strncpy(simplifiedMinTerm, termOne, minTermLength);
                simplifiedMinTerm[differenceIndex] = '-';
                //--------------- simplify term ---------------//

                if (!member(simplifiedTerms, simplifiedTermsLength, simplifiedMinTerm, minTermLength)) {
                    simplifiedTerms[simplifiedTermsLength++] = simplifiedMinTerm;
                }

                if (!member(matchedTerms, matchedTermsLength, termOne, minTermLength)) {
                    char* termCopy = malloc(minTermLength);
                    strncpy(termCopy, termOne, minTermLength);

                    matchedTerms[matchedTermsLength++]  = termCopy;
                }
                
                if (!member(matchedTerms, matchedTermsLength, termTwo, minTermLength)) {
                    char* termCopy = malloc(minTermLength);
                    strncpy(termCopy, termTwo, minTermLength);

                    matchedTerms[matchedTermsLength++]  = termCopy;
                }

                simplificationFound = true;
            }
        }
        if (!simplificationFound) {
            if (!member(soloTerms, soloTermsLength, termOne, minTermLength) &&
                !member(matchedTerms, matchedTermsLength, termOne, minTermLength)) {
                    char* termCopy = malloc(minTermLength);
                    strncpy(termCopy, termOne, minTermLength);
                    soloTerms[soloTermsLength++] = termCopy;
            }
        }
    }

    int length = simplifiedTermsLength + soloTermsLength;
    *numNewMinTerms = length;
    char** newMinTerms = malloc(sizeof(char*) * length);

    // maps simplified terms into new array
    for (int i = 0; i < simplifiedTermsLength; i++) {
        newMinTerms[i] = simplifiedTerms[i];
    }

    // maps solo terms into new array
    for (int i = 0; i < soloTermsLength; i++) {
        newMinTerms[simplifiedTermsLength + i] = soloTerms[i];
    }

    // Garbage collection
    for (int i = 0; i < matchedTermsLength; i++) {
        free(matchedTerms[i]);
    }
    free(matchedTerms);
    free(simplifiedTerms);
    free(soloTerms);

    return newMinTerms;
}

void printMinTerms(char** terms, int length) {
    for (int i = 0; i < length - 1; i++) {
        printf("%s, ", terms[i]);
    }
    printf("%s \n", terms[length-1]);
}


void freeArray(char** array, int length) {
    for (int i = 0; i < length; i++) {
        free(array[i]);
    }
    free(array);
    array = NULL;
}

// char** reduceMinTerms(char** minTerms, int numMinTerms, char** reducedMinTerms, int minTermLength, int* numReducedMinTerms) {
//     int numReducedTerms = numMinTerms - 1;
//     if (mappingExists(minTerms, numMinTerms, reducedMinTerms, numMinTerms - 1, minTermLength)) {
//         *numReducedMinTerms = numMinTerms - 1;
//         reduceMinTerms(reducedMinTerms, numMinTerms - 1, minTermLength, numReducedMinTerms);
//     } else {
//         return minTerms;
//     }
// }

int factorial(int n) {
    if (n == 1) {
        return 1;
    }

    return n * factorial(n-1);
}


struct option* newOption(char** minTerms, int length) {
    struct option* instance = malloc(sizeof(struct option));
    instance -> length = length;
    instance -> minTerms = minTerms;

    return instance;
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
    int minTermLength = (int) log2(length) + 1;
    char** minTerms = getMinTerms(truthValues, length, minTermLength, &numMinTerms);

    int numNewMinTerms = 0;
    char** newMinTerms = simplifyLogic(minTerms, numMinTerms, minTermLength, &numNewMinTerms);
    char** interimTerms = NULL;

    for (int i = 0; i < numNewMinTerms - 1; i++) {
        interimTerms = newMinTerms;
        int oldLength = numNewMinTerms;
        newMinTerms = simplifyLogic(newMinTerms, numNewMinTerms, minTermLength, &numNewMinTerms);
        freeArray(interimTerms, oldLength);
    }
    
    // Garbage Collection
    for (int i = 0; i < numMinTerms; i++) {
        free(minTerms[i]);
    }
    free(minTerms);

    minTerms = newMinTerms;
    numMinTerms = numNewMinTerms;
    printMinTerms(minTerms, numMinTerms);

    // attempt to remove terms
    struct option** options = calloc(sizeof(struct option*), 1000000000);
    int top = 0;
    options[top] = newOption(minTerms, numMinTerms);
    
    struct option* bestOption = malloc(sizeof(struct option));
    bestOption = options[top];

    while (top >= 0) {
        struct option* currentOption = options[top--];
        int length = currentOption -> length;
        char** terms = currentOption -> minTerms;

        for (int i = 0; i < length; i++) {
            // array of min terms with one ommited //
            char** reducedMinTerms = calloc(sizeof(char*), length - 1);
            int currIndex = 0;
            for (int j = 0; j < length; j++) {
                if (j != i) {
                    reducedMinTerms[currIndex++] = terms[j];
                }
            }
            // array of min terms with one ommited //
            
            if (mappingExists(terms, length, reducedMinTerms, length - 1, minTermLength)) {
                if (length <= bestOption -> length) {
                    bestOption = currentOption;
                    fprintf(stderr, "top: %d \n", top);
                    options[++top] = currentOption;
                }
            }
        }

        // printMinTerms(bestOption -> minTerms, bestOption -> length);

    }

    free(options);


    // printMinTerms(reducedMinTerms, numReducedMinTerms);

    
    for (int i = 0; i < numMinTerms; i++) {
        free(minTerms[i]);
    }
    free(minTerms);
   
    return 0;
}