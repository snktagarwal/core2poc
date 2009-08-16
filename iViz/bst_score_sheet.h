/*
#################################################
#     BST functions for score sheet manipulation
#     Author: Sanket Agarwal
#
#
#
################################################
*/


#include"core2poc.h"

#define POP_SIZE 6

typedef struct score_sheet{//sorted list of scores in a binary tree
	
	CHROMO c;
	struct score_sheet *next;  //linked list implementation

}SCORE_SHEET;  

SCORE_SHEET *init_list(); //initialises the score sheet

SCORE_SHEET *insert_chromosome(SCORE_SHEET *ss,CHROMO c); //inserts any chromosome based on the score it contains

SCORE_SHEET *delete_chromosome(SCORE_SHEET *ss,CHROMO key); //deletes a chromosome( if found ) accord to it's key value

void print_list(SCORE_SHEET *ss); //print the present records in sorted order

/*returns the total score of the list */

int sum_of_scores(SCORE_SHEET *ss);

/*stores the selected chromosome in the target_chromo variable, by roulette wheel selection. */

CHROMO roulette_wheel_selection(SCORE_SHEET *ss,int target_score);




