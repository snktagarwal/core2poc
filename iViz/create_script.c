/*
################################################################
#  this file creates the script required to run the test inputs
#  
#  Author: Sanket Agarwal
#
#
#
################################################################
*/


#include<stdio.h>
#include<stdlib.h>
#include"core2poc.h"

#define MAX_CONT 10000

void create_script(CHROMO chr, char *app_name ,BT bt)
{//creates the script

  FILE *fp=fopen("script_2.txt","w");  //open the file for writing

  int i;

  /*First we'll put a breakpoint on the main() and then when we reach it, we'll put the rest of the breakpoints, this is done to put breakpoints on the Libraries which are loaded only at the running of the program */
  
  fprintf(fp,"file %s\n",chr.filename);  //load the file for any symbols
  
  char command[200];
  
  sprintf(command,"./main_brk.sh %s",app_name); //script to be run
  
  FILE *main_brk=popen(command,"r");  //get the main break point
  
  char c;
  
  fprintf(fp,"b *");
  
  while(fscanf(main_brk,"%c",&c) !=EOF )    //put it in the script
    
    fprintf(fp,"%c",c);
  
  fclose(main_brk);
  
  /*run the script*/

  fprintf(fp,"r %s\n",chr.filename);
  
  for(i=0;i<bt.stack_height;i++)
    
    //put breakpoints on specific points
    
    fprintf(fp,"b *0x%x\n",bt.mem_addr[i]);
  
  /*set some basic gdb logging conditions so that the output can be parsed */
  
  fprintf(fp,"set logging file chromo_bt.txt\nset logging on\n"); 	
	
  /*now put lots of continues to avoid possible loops */
	
  for(i=0;i<MAX_CONT;i++)
    fprintf(fp,"c\n");
  
  fprintf(fp,"q");  // quit if not already!
  
  fclose(fp);

}


