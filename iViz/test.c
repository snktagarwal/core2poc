#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ga.h"

int main()

{
  
  BT bt;
  
  bt=get_memaddr("core");
  
  int i;
  
  /* testing for the data structure BST SCORE_SHEET*/

  CHROMO c1,c2,c3,c4,c5;
  sprintf(c1.filename,"winkeyd.exe");
  c1.score=6;

  sprintf(c2.filename,"this is c2");
  c2.score=8;

  sprintf(c3.filename,"x1.mp3");
  c3.score=3;

  sprintf(c4.filename,"x2.mp3");
  c4.score=40;

  sprintf(c5.filename,"x3.mp3");
  c5.score=60;

  SCORE_SHEET *ss=init_list();

  ss=insert_chromosome(ss,c1);

  ss=insert_chromosome(ss,c2);

  ss=insert_chromosome(ss,c3);

  ss=insert_chromosome(ss,c4);

  ss=insert_chromosome(ss,c5);

  printf("the sum of scores is: %d\n",sum_of_scores(ss)); 

  ss=delete_chromosome(ss,c1);

  /*selection of individual*/

  //print_list(ss);

  free(ss);

  char **files;
  int noFiles=3;

  files=(char **)malloc(noFiles*sizeof(char *));
  
  for(i=0;i<noFiles;i++)
    files[i]=(char *)malloc(20*sizeof(char));

  strcpy(files[0],"x1.mp3");
  strcpy(files[1],"x2.mp3"); 
  strcpy(files[2],"x3.mp3");

  POPULATION pop=initialize("avgscan","mp3",files,noFiles,bt);

  
  print_list(pop);   
  return 0;	
}















