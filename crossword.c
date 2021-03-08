/*
 * Brett Wiseman 
 * FunComp Lab #8
 * anagram crossword
 * crossword.c
 */ 
#include "crossfunc.h"


#define WORD 15


int main(int argc, char *argv[]) {
	FILE *fp;

	if (argc == 1) {
		interactive();
	} else if (argc == 2) {
		fp = fopen(argv[1], "r");
		if(!fp) {
			puts("invalid file");
			return 1;
		}
		batch(fp);
	} else if (argc == 3) {
		fp = fopen(argv[1], "r");
		if(!fp) {
			puts("invalid file");
			return 1;
		}
		batchWrite(fp, argv[2]);
	} else if (argc >= 4) {
		puts("invalid number of arguments");
		return 1;
	}
	
	return 0;
}

