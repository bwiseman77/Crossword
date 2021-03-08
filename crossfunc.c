/*
 * Brett Wiseman 
 * FunComp Lab #8
 * anagram crossword
 * crossfunc.c
 */ 
#include "crossfunc.h"


void batchWrite(FILE *fp, char wfile[]) {
// Gets file of words, and writes to another file

	// puzzle boards
	char board[20][WORD];
	char boardSol[20][WORD];

	// struct array of words
	Words wds[20];
		
	// array of words
	char *words[20];

	int sz, i;
	
	// gets words inputed from file 
	sz = fgetWords(fp, words);

	// closes file 
	fclose(fp);

	// opens fp to write to a new file
	fp = fopen(wfile, "w");

	fputs("Welcome to Anagram crossword!\n\n", fp);

	fputs("\nlist of valid inputed words\n", fp);
	for(i = 0; i < sz; i++) {
		fprintf(fp, "%s \n", words[i]);
	}	

	// sorts the words longest to shortest
	sort(words, sz);

	// sets up boards
	init(board, 0);
	init(boardSol, 1);

	// puts words on board
	setBoard(boardSol, wds, words, sz);	

	// displays solution puzzle board
	fputs("\nSolution:\n", fp);
	fdisp(boardSol, fp);

	// makes puzzle board same as solution, but with blanks
	putBoard(board, boardSol);

	// displays puzzle board
	fputs("\nPuzzle:\n", fp);
	fdisp(board, fp);

	// shuffles words for clues
	shuffle(words, sz);	
	
	// displays clues and unplaced words
	fdispList(words, wds, sz, fp);

}

void fdispList(char *words[], Words wds[], int sz, FILE *fp) {
// writes clues to a file
	int i;
	fputs("Clues:\n\n", fp);
	
	// prints each of the placed words (when wds[i].xpos != -1)
	for (i = 0; i < sz; i++) {
		if (wds[i].xpos != -1) {
			fprintf(fp, "%2d, %2d ", wds[i].xpos, wds[i].ypos);
			fprintf(fp, "%7s ", wds[i].dir);
			fprintf(fp, "%-15s \n", words[i]);
		}
	}

	fputs("\nCould not diplay words: \n", fp);

	// prints each of the unplaced words (when wds[i].xpos == -1);
	for (i = 0; i < sz; i++) {
		if (wds[i].xpos == -1) {
			fprintf(fp, "%s \n", wds[i].word);
		}
	}

} 

void fdisp(char arr[][WORD], FILE *fp) {
// writes boards to a file 
	int i, j;

	fputs("-----------------\n", fp);
	
	for (i = 0; i < WORD; i++) {
		fprintf(fp, "|");
		for (j = 0; j < WORD; j++) {
			fprintf(fp, "%c", arr[i][j]);
		}
		fprintf(fp, "|\n");
	}

	fputs("-----------------\n", fp);
}

void batch(FILE *fp) {
// reads in words from a file and displays to std output

	// puzzle boards
	char board[20][WORD];
	char boardSol[20][WORD];

	// struct of words
	Words wds[20];
		
	// array of words
	char *words[20];

	int sz, i;

	puts("Welcome to Anagram crossword!\n");
	
	// gets words inputed from file
	sz = fgetWords(fp, words);

	puts("\nlist of valid inputed words");
	for(i = 0; i < sz; i++) {
		printf("%s \n", words[i]);
	}	

	// sorts the words longest to shortest
	sort(words, sz);

	// sets up boards
	init(board, 0);
	init(boardSol, 1);

	// puts words on board
	setBoard(boardSol, wds, words, sz);	
	
	// displays puzzle solution board
	puts("\nSolution:");
	disp(boardSol);

	// makes puzzle board same as solution, but with blanks
	putBoard(board, boardSol);

	// displays puzzle board
	puts("\nPuzzle:");
	disp(board);

	// shuffles words for clues
	shuffle(words, sz);	
	
	// displays clues and unused words
	dispList(words,  wds, sz);

}

int fgetWords(FILE *fp, char *words[]) {
// gets words from a file 
	
	// count for size of array
	int count = 0; 
	
	// temp string
	char temp[WORD];

	while (1) {
		// breaks if 20 words read in, of if eof char reached
		if(count == 20 || feof(fp)) break;
		// allocates memory
		words[count] = malloc(15*sizeof(char));
		// reads in string, stores in temp
		fscanf(fp, "%s", temp);
		// breaks if '.' is read
		if(!strcmp(temp, ".")) break;
		// checks if word is valid, then stores it in array, and makes it all uppercase
		if(fcheck(temp)) {
			strcpy(words[count], temp);
			upper(words[count]);
			count++;
		}
	}
	return count;
}

int fcheck(char word[]) {
// checks words and writes to file 
	int i, isvalid = 1;
	int sz = strlen(word);

	// checks if a word has a number or symbol in it
	for (i = 0; i < sz; i++) {
		if (!isalnum(word[i])) {
			isvalid = 0;
			printf("%s is not alphanumeric\n", word);
		} else if (isdigit(word[i])) {
			isvalid = 0;
			printf("%s is not alphabetic\n", word);
		} 
	}

	// checks that word is valid length
	if (strlen(word) > 15) {
		isvalid = 0;
		printf("%s is too long\n", word);
	} else if (strlen(word) < 2) {
		isvalid = 0;
		printf("%s is too short\n", word);
	}

	return isvalid;
}

void interactive(void) {
// gets words from and to stdio

	// puzzle boards
	char board[20][WORD];
	char boardSol[20][WORD];

	// words struct
	Words wds[20];

	// arry words
	char *words[20];

	int sz, i;

	puts("Welcome to Anagram crossword!");
	puts("Enter up to 20 words (up to 15 letters and end with '.'): ");

	// reads in words from stdin
	sz = getWords(words);

	// sorts words longest to shortest
	sort(words, sz);

	// sets up puzzple boards
	init(board, 0);
	init(boardSol, 1);

	// puts words onto board
	setBoard(boardSol, wds, words, sz);	

	// displays solution board
	puts("\nSolution:");
	disp(boardSol);

	// makes puzzle board same as solution but with blanks
	putBoard(board, boardSol);

	// displays puzzle board
	puts("\nPuzzle:");
	disp(board);

	// shuffles words
	shuffle(words, sz);	
	
	// displays placed and unused words
	dispList(words,  wds, sz);

}

void setBoard(char boardSol[][WORD], Words *p, char *words[], int sz) {
// tries to put words on the board by getting and trying possible starting positions the words
// starts with the longest and places in the center horizontally
// after placing the words it can, it then tries to place unplaced words until it has not placed a new one
// p is address of first member of main Words struct

	int x, y, len;
	int i;
	int c = 0; // count of total words
	int cPlaced = 0; // size of placed words struct
	int test = 0; /// test from replacing loop

	// Words struct for placed words
	Words placed[20];

	// stores first word into struct, as well as length, xpos and  ypos 
	strcpy(p->word, words[0]);
	p->len = strlen(words[0]);
	
	// places words centered in board
	p->xpos = WORD/2 - p->len/2;
	p->ypos = WORD/2;

	// sets direction to be across
	strcpy(p->dir, "across");
	
	// placed word
	place(boardSol, p);
	
	// copies to placed array
	copy(&placed[cPlaced], p);
	cPlaced++;

	// moves pointer
	p++;
	c++;

	// goes from 2 elemant to end of list
	for(i = 1; i < sz; i++) {
		// same process as above - copies word from words array, gets the len, xpos and ypos
		// if xpos/ypos = -1, it means it could not place the word
		
		strcpy(p->word, words[i]);

		p->len = strlen(words[i]);
		p->xpos = getX(boardSol, placed, words[i], cPlaced);
		p->ypos = getY(boardSol, placed, words[i], cPlaced);
	
		// get direction returns 1 or 0; 1 = across, 0 = down, and -1 means cannot be placed
		if(getDir(boardSol, placed, words[i], cPlaced)) {
			strcpy(p->dir, "across");
		} else { 
			strcpy(p->dir, "down");	
		}
	
		// if word can be placed, places it at xpos and ypos and copies it to placed array
		if(p->xpos != -1) {
			place(boardSol, p);
			copy(&placed[cPlaced], p);
			cPlaced++;
		}

		// moves pointer
		p++;
		c++;
	}
	
	// loops through list of words again, to see it can now place a not placed word 
	// (word is not placed if p->xpos == -1)
	// if it places a word, it sets test to 0 again, to see if it can place any more words
	// on that newly placed word. If not words get placed, test stays equal to zero and exits loop
	while(test == 0) {
		// set test = 1, must be changed by placing a word to stay in loop
		test = 1;

		// moves pointer bacl to first word
		p = p - c;

		// similar process to before, get info, try to place, if it can be placed, place it and add to placed struct
		for (i = 0; i < sz; i++) {
			if(p->xpos == -1) {
				p->xpos = getX(boardSol, placed, p->word, cPlaced);
				p->ypos = getY(boardSol, placed, p->word, cPlaced);
	
				if(getDir(boardSol, placed, p->word, cPlaced)) {
					strcpy(p->dir, "across");
				} else { 
					strcpy(p->dir, "down");	
				}
		
				if(p->xpos != -1) {
					place(boardSol, p);
					copy(&placed[cPlaced], p);
					test = 0;
					cPlaced++;
				}
			}
			p++;
		}

	}
}

void putBoard(char board[][WORD], char boardSol[][WORD]) {
// copies solution board to puzzle board, making letters blanks
	int i, j;

	for (i = 0; i < WORD; i++) {
		for (j = 0; j < WORD; j++) {
			if (boardSol[i][j] != '.') {
				board[i][j] = ' ';
			}
		}
	}
}

int getX(char boardSol[][WORD], Words placed[], char word[], int sz) {
// gets first possible x starting positions
	int i, j, k, len;
	int isacross = 1;
	int isdown = 0;

	len = strlen(word);

	// For the number of placed words, checks each letter of the word trying to be placed 
	// with each letter of a placed word on the board.
	// Sends a possible letter to tryPlace to see if it works.
	// Uses an equation based on which direction the word being placed on was going.
	// If there are no places to put the word, returns -1
	for (i = 0; i < sz; i++) {
		for (j = 0; j < len; j++) {	
			for (k = 0; k < placed[i].len; k++) {
				if (word[j] == placed[i].word[k]) {
					if(tryPlace(placed[i], word, j, k, boardSol)) {
						if (!strcmp(placed[i].dir,"down")) {
							isacross = 0;
							isdown = 1;
						}
						return (placed[i].xpos + (k*isacross) - (j*isdown));	
					}
				}
			}
		}
	}
	return -1;
}

int getY(char boardSol[][WORD], Words placed[], char word[], int sz) {
// gets first possible y possition
	int i, j, k, len;
	int isacross = 1;
	int isdown = 0;	

	len = strlen(word);

	// For the number of placed words, checks each letter of the word trying to be placed 
	// with each letter of a placed word on the board.
	// Sends a possible letter to tryPlace to see if it works.
	// Uses an equation based on which direction the word being placed on was going.
	// If there are no places to put the word, returns -1
	for (i = 0; i < sz; i++) {
		for (j = 0; j < len; j++) {
			for (k = 0; k < placed[i].len; k++) {
				if (word[j] == placed[i].word[k]) {
					if(tryPlace(placed[i], word, j, k, boardSol)) {
						if (!strcmp(placed[i].dir, "down")) { 
							isacross = 0;
							isdown = 1;
						}
						return (placed[i].ypos + (k*isdown) - (j*isacross));
					}
				}
			}
		}
	}
	return -1;
}

int getDir(char boardSol[][WORD], Words placed[], char word[], int sz) {
// gets first possible direction
	int i, j, k, len;
	int t = 1;

	len = strlen(word);

	// For the number of placed words, checks each letter of the word trying to be placed 
	// with each letter of a placed word on the board.
	// Sends a possible letter to tryPlace to see if it works.
	// Sets direction opposite that of the word it was placed on (1 = across, 0 = down)
	// Returns -1 if no available place
	for (i = 0; i < sz; i++) {
		for (j = 0; j < len; j++) {
			for (k = 0; k < placed[i].len; k++) {
				if (word[j] == placed[i].word[k]) {
					if(tryPlace(placed[i], word, j, k, boardSol)) {
						if (!strcmp(placed[i].dir,"across")) t = 0;
						return t;
					}
				}
			}
		}
	}
	return -1;
}

int tryPlace(Words p, char word[], int Lw, int Lp, char boardSol[][WORD]) {
// Finds out if it can place a word at a starting point found from the positions of the letters that match 
// Uses equations based on the directions of the placed word (already on board) and which way the word is being placed
// Lw is position of letter on word being placed
// Lp is position of letter on word already placed
// dx is 1 if x is changing when placing the word
// dy is 1 if y is changing when placing the word
// p is the struct of the placed word, so (p.xpos,p.ypos) is starting point of that placed word
// Uses the fact that adding a term is based on the direction of the word, so when going down, the x value does not change
// but when going across the y value does not change. For example, if the 3rd letter is the intersection letter, if the 
// placed word is going down, the starting position is 3 down (dy) from the starting point, but if the word was across
// if would be 3 across (dx) from the starting point

	int isacross = 1;
	int isdown = 0;
	
	int i, dx = 0, dy = 1;
	int x, y;

	if (!strcmp(p.dir, "down")) {
		isacross = 0;
		isdown = 1;
		dx = 1;
		dy = 0;
	}

	// checks that first letter is in grid
	x = (p.xpos + (Lp*isacross) - (Lw*isdown));
	y = (p.ypos - (Lw*isacross) + (Lp*isdown));
	if(x < 0 || x > 15 || y < 0 || y > 15) {
		return 0;
	}

	// checks that last letter is in grid
	x = (p.xpos + (Lp*isacross) - (Lw*isdown)) + (strlen(word)*dx);
	y = (p.ypos - (Lw*isacross) + (Lp*isdown)) + (strlen(word)*dy);
	if(x < 0 || x > 15 || y < 0 || y > 15) {
		return 0;
	}
	
	// checks that cell before first letter is blank
	x = (p.xpos + (Lp*isacross) - (Lw*isdown)) - (1*isdown); 
	y = (p.ypos - (Lw*isacross) + (Lp*isdown)) - (1*isacross);
	if(boardSol[y][x] != '.') {
		return 0;
	}

	// checks that cell after last letter is blank
	x = (p.xpos + (Lp*isacross) - (Lw*isdown)) + (strlen(word)*isdown);
	y = (p.ypos - (Lw*isacross) + (Lp*isdown)) + (strlen(word)*isacross);
	if(boardSol[y][x] != '.') {
		return 0;
	}	

	for (i = 0; i < strlen(word); i++) {
		x = (p.xpos + (Lp*isacross) - (Lw*isdown)) + (dx * i);
		y = (p.ypos - (Lw*isacross) + (Lp*isdown)) + (dy * i);

		// checks that current cell is blank and is not a matching letter
		if(boardSol[y][x] != '.' && boardSol[y][x] != word[i]) {
			return 0;	
		}	
		// checks cell to the right or below (depending on dir) 
		// to make sure its blank and that its not a matching letter
		// if letter is next to boarder, it does not need a period next to it in that direction
		if(boardSol[y+dx][x+dy] != '.' && word[i] != boardSol[y][x]) {
			if((y+dx > 15) || (x+dy > 15)) {
			} else {
				return 0;
			}
		}

		// checks cell to the left or above (depending on dir) to make 
		// sure its blank and that its not a matching letter
		// if letter is next to boarder, it does not need a period next to it in that direction
		if(boardSol[y-dx][x-dy] != '.' && word[i] != boardSol[y][x]) {
			if((y-dx < 0) || (x-dy < 0)) {
			} else {
				return 0;
			}
		}
	}
	return 1;
}

void place(char boardSol[][WORD], Words *word) {
// places a given word on the board
	int i, dx = 0, dy = 1;
	int x, y;

	if (!strcmp(word->dir,"across")) {
		dx = 1;
		dy = 0;
	}

	// Depends on if the word is being placed across or down
	// If word is going down, dx = 0, so second term does not change, and just y changes
	for (i = 0; i < word->len; i++) {
		x = word->xpos + (dx * i);
		y = word->ypos + (dy * i);
		boardSol[y][x] = word->word[i];
	}
}

void copy(Words *p1, Words *p2) {
// copies a Words struct data
	strcpy(p1->word, p2->word );
	p1->len = strlen(p2->word);
	p1->xpos = p2->xpos;
	p1->ypos = p2->ypos;
	strcpy(p1->dir, p2->dir);
}

void dispList(char *words[], Words wds[], int sz) {
// displays the clues and positions of words to stdout
	int i;
	puts("Clues:\n");
	
	// displays words if placed (when wds[i].xpos != -1)
	for (i = 0; i < sz; i++) {
		if(wds[i].xpos != -1) {
			printf("%2d, %2d ", wds[i].xpos, wds[i].ypos);
			printf("%7s ", wds[i].dir);
			printf("%-15s \n", words[i]);
		}
	}

	puts("\nCould not diplay words: ");

	// displays words that could not be placed
	for (i = 0; i < sz; i++) {
		if(wds[i].xpos == -1) {
			printf("%s \n", wds[i].word);
		}
	}

} 

void disp(char arr[][WORD]) {
// displays board to stdout
	int i, j;

	puts("-----------------");
	
	for (i = 0; i < WORD; i++) {
		printf("|");
		for (j = 0; j < WORD; j++) {
			printf("%c", arr[i][j]);
		}
		printf("|\n");
	}

	puts("-----------------");
}

void init(char arr[][WORD], int t) {
// initalizes array
// sets solution or puzzle board based on t
	int i, j;
	char fill;

	if (t == 0) fill = '#';
	if (t == 1) fill = '.';

	for (i = 0; i < WORD; i ++) {
		for (j = 0; j < WORD; j++) {
			arr[i][j] = fill;
		}
	}
}

int getWords(char *words[]) {
// reads in words from stdin
	int count = 0; 

	// allocates memory
	words[count] = malloc(15*sizeof(char));
	scanf("%s", words[count]);

	// reads in until a period is read or 20 words
	while (strcmp(words[count], ".") && count != 20) {

		// makes word uppercase
		upper(words[count]);
	
		if(check(words[count])) {
			count++;
			words[count] = malloc(15*sizeof(char));
			if (count != 20) {
				scanf("%s", words[count]);
			}
		} else {
			scanf("%s", words[count]);
		}
	
	}

	return count;
}

void upper(char word[]) {
// makes given word all uppercase
	int sz, i;
	
	sz = strlen(word);

	for (i = 0; i < sz; i++) {
		word[i] = toupper(word[i]);
	}
}

int check(char word[]) {
// checks if given word is a valid word
	int i, isvalid = 1;
	int sz = strlen(word);

	// checks if word contains numbers or symbols
	for (i = 0; i < sz; i++) {
		if (!isalnum(word[i])) {
			isvalid = 0;
			printf("%s is not alphanumeric\n", word);
		} else if (isdigit(word[i])) {
			isvalid = 0;
			printf("%s is not alphabetic\n", word);
		} 
	}

	// gets of word is valid length
	if (strlen(word) > 15) {
		isvalid = 0;
		printf("%s is too long\n", word);
	} else if (strlen(word) < 2) {
		isvalid = 0;
		printf("%s is too short\n", word);
	}

	return isvalid;
}

void shuffle(char *words[], int sz) {
// shuffles words
	int i, j;
	int r, r2;
	int len;
	char tempw[WORD], tempc;

	srand(time(0));

	// for each word, swicthes letters an odd number of times 
	for (i = 0; i < sz; i++) {
		strcpy(tempw, words[i]);
		len = strlen(tempw);
		for (j = 0; j < (2*len+1); j++) {
			r = rand() % len;
			r2 = rand() % len;
			tempc = tempw[r];
			tempw[r] = tempw[r2];
			tempw[r2] = tempc;
		}
		
		// copies shuffles word
		strcpy(words[i], tempw);
										
	}				
}	

int comp(const void* a, const void* b) {
	// used for qsort
	return strlen(*(const char **)b) - strlen( *(const char**)a);
}

void sort(char *words[], int sz) {
	// sorts words based on length (longest to shortest)
	qsort(words, sz, sizeof(const char*), comp);
}
