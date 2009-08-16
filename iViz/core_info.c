/*
######################################################
#  core_info.c
#  It stores the core file stastics into a inked list
#  
#  Author: Sanket Agarwal
#
#
#######################################################

*/


#include"core2poc.h"
#include<stdio.h>
#include<stdlib.h>

BT get_memaddr(char *core_file)
{//returns the core file stastics... a generic file considered
  
  /* create a gdb script to run the core file */
  
  FILE *fp = fopen("script_1.txt","w");
  
  fprintf(fp,"bt full\nq");
  
  fclose(fp);

  /* run the core file with gdb and redirect output */
  
  /* char gdb_command[100];
  
  sprintf(gdb_command,"gdb -c %s --batch -x script_1.txt > coredump.txt",core_file);
  system(gdb_command);*/
  
  /*parse the output to generate the core statastics*/
  
  FILE *coredump=fopen("coredump.txt","r");
  
  char hash;
  int dummy;
  BT bt;
  
  int counter=0;    //number of functions in the backtraces
  
  while(!feof(coredump))
    {
      fscanf(coredump,"%c",&hash);
      fscanf(coredump,"%d",&dummy);
      if(hash == '#' && dummy==counter) //evaluate only diff traces
	counter++;
    }
  
  bt.stack_height=counter;
  
  bt.mem_addr=(long *)malloc(counter*sizeof(long)); //allocate space
  
  fseek(coredump,0,SEEK_SET);          //seek to starting of stream
  
  counter = 0; //reset counter
  
  while(counter<bt.stack_height)
    {
      fscanf(coredump,"%c",&hash);
      fscanf(coredump,"%d",&dummy);
      if(hash=='#' && dummy==counter)
	fscanf(coredump,"%x",&bt.mem_addr[counter++]); //copy the address
	
    }
  
  fclose(coredump);
  
  return bt;            //return the basktrace
  
}
