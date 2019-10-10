/*
 ============================================================================
 Name        : algorithms.c
 Author      : 
 Version     :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "karat.h"

int main(int argc, char *argv[]) {
    char *str1 = argv[1];
    char *str2 = argv[2];
    char *result = karat(str1, str2);
    printf("result: %s", result);
    free(result);
	return 0;
}
