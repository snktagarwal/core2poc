/*
####################################################
#    Linked List
# 
#
#    Author: Sanket Agarwal
#
#
#
####################################################
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bst_score_sheet.h"


SCORE_SHEET *init_list()
{//forms the head of the linked list, including dummy head
  
  SCORE_SHEET *ss=(SCORE_SHEET *)malloc(sizeof(SCORE_SHEET));	
  
  ss->c.score=-1; 

  strcpy(ss->c.filename,"");  //initialize a dummy head
  
  ss->next=NULL;

  return ss;
}

SCORE_SHEET *insert_chromosome(SCORE_SHEET *ss,CHROMO c)
{//inserts the score of a chromosome in the BST
  
  SCORE_SHEET *ss1=ss;
  
  while(ss1->next != NULL)
     ss1=ss1->next;
 
  ss1->next=(SCORE_SHEET *)malloc(sizeof(SCORE_SHEET));

  ss1->next->c=c;

  ss1->next->next=NULL;

  return ss;
  
}

/*deletes a specified node( and the corresponding data on disk/memory ), deletes nothing if the chromosome is not found*/

SCORE_SHEET *delete_chromosome(SCORE_SHEET *ss,CHROMO key)
{

  char command[100];  
  SCORE_SHEET *ss1=ss;

  while(ss1->next != NULL && strcmp(key.filename,ss1->next->c.filename))
	ss1=ss1->next;

 if( ss1->next != NULL )
   {//if the node is found
       
      SCORE_SHEET *ss_buf=ss1->next; //store the node for freeing

      ss1->next=ss1->next->next; //move the imidiate pointer to next node

      sprintf(command,"rm --force %s",ss_buf->c.filename);
      
      system(command);          //remove the desired file, as it is no longer needed 

      free(ss_buf);  //free the deleted node

   }

 return ss;

}
void print_list(SCORE_SHEET *ss)
{//prints the information about the score sheet. Might be useful for debugging!
  
  SCORE_SHEET *ss1=ss;

  while (ss1->next != NULL ) //if no leaf is passed
    {
      printf("Chromosome Filename: %s Score: %d\n",ss1->next->c.filename,ss1->next->c.score); 
      ss1=ss1->next;
    }
}
  
int sum_of_scores(SCORE_SHEET *ss)
{
  
   int sum=0;
  
   SCORE_SHEET *ss1=ss;

   while(ss1->next != NULL ) //if no leaf is passed
      {
        sum+=ss1->next->c.score;
        ss1=ss1->next;
      }
   return sum;
}


/* this function finds by roulette wheel selection that chromosome that will be selected in the next generation, the target score is target. The CHROMO is referenced by target_chromo */

CHROMO roulette_wheel_selection(SCORE_SHEET *ss,int target_score)
{
  /*get the list of the scores in a array form*/
  
  int score_so_far=0;

  SCORE_SHEET *ss1=ss;
     
  printf("target score: %d\n",target_score);
   
  while( ss1->next != NULL )
    {
       score_so_far += ss1->next->c.score;
       
       if( score_so_far > target_score ) break;
  
       else ss1=ss1->next;
    
    }

   return ss1->next->c; 
 
}






