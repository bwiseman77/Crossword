/*
 * Brett Wiseman 
 * FunComp Lab #8
 * anagram crossword
 * crossfunc.h
 */ 
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

#define WORD 15

typedef struct {
	char word[WORD];
	int len;
	int xpos;
	int ypos;
	char dir[7];
} Words;

// three versions of crossword
void interactive(void);
void batch(FILE *);
void batchWrite(FILE *, char []);

// display functions (file and stdio)
void disp(char [][WORD]);
void fdisp(char [][WORD], FILE *);
void dispList(char *[], Words [], int);
void fdispList(char *[], Words [], int, FILE *);

// gets words (file and stdio);
int getWords(char *[]);
int fgetWords(FILE *, char *[]);

// deals with inputted words and how to place them
int fcheck(char *);
int check(char *);
void place(char [][WORD], Words *);
int tryPlace(Words, char [], int, int, char [][WORD]);

// deals with boards
void init(char [][WORD], int);
void setBoard(char [][WORD], Words *, char *[], int);
void putBoard(char [][WORD], char [][WORD]);

// misc functions
void copy(Words *, Words *);
void shuffle(char *[], int);
void upper(char []);
void sort(char *[], int);
int comp(const void*, const void*);

// getting info about words
int getX(char [][WORD], Words [], char [], int c);
int getY(char [][WORD], Words [], char [], int c);
int getDir(char [][WORD], Words [], char [], int c);



