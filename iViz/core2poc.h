/*
#############################################
#   core2poc.h
#   contains basic data structures and functions
#   
#   Author: Sanket Agarwal
#
#############################################
*/


/*The linked list to store original backtrace*/

typedef struct Back_Trace
{
  
  int stack_height;   //height of the backtrace
  
  long *mem_addr;     //The corresponding backtraces

}BT;

typedef struct{//structure to store each file under ga( genetic algorithm )
  
  char filename[100];
  int score;
  int isCrashable;    //This variable tells whether the file crashes. A crashing file is obviously more fit!!
}CHROMO;



/* it returns the core file in the form of a list BT */

BT get_memaddr(char *corefile);   //writed to coredump.txt

/* creates the script to check the backtrace of the files craeted during GA */
void create_script(CHROMO c, char *app_name,BT bt); //takes a backtrace as input, and gives a file as output, offspring_output.txt correponding to chromo.

/*it returns the score of a specific file */

int get_score(CHROMO *c,char *app_name,BT bt);  //it modifies the c param by storing the specific value and returns the same

/*it compares the score of the two files. Returns 1 if c1->score > c2->score else 0*/
/*This function will help in moduling the score function in case we need to change the fitness parameters*/
int compare_score(CHROMO *c1,CHROMO *c2);
