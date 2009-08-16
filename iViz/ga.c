
/*
###############################################
#   Genetic algorithm
#
#   Author: Sanket Agarwal
#
#
#
#
###############################################
*/


/*basic include files*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<sys/stat.h>
#include"ga.h"

//#define POP_SIZE 3  //under testing conditions
#define MUTATION .01
#define CROSSOVER .7

int seed; //seed for the random generator

POPULATION initialize(char *app_name,char *extension,char **init_files,int noFiles,BT bt)
{//The function is supposed to create the initial populaion by taking the available initial files and then mating to form the desired size.
  
  SCORE_SHEET *pop=init_list();
  int i; //counter
  CHROMO buf,c1,c2,*c; //buffer chromo
  
  int population_finished=0;
  
  /*we first check of the population size is less than the input, if so we'll truncate the input files by POP_SIZE, else we'll mate the first input files to produce offsprings*/
  
  
  if(noFiles>=POP_SIZE)
    {
      for(i=0;i<POP_SIZE;i++)
	{
	  /*generate name, then get the score and insert in the population BST*/
	  strcpy(buf.filename,init_files[i]);
	  generate_name(&buf,extension,i);
	  get_score(&buf,app_name,bt);
	  pop=insert_chromosome(pop,buf);
	}
    }
  
  else{//copy the first few available init_files and then mate accordingly by using a selection scheme
    
    for(i=0;i<noFiles;i++)
      {
	/*copy the file name to the chromosome and append the extension, then get the score and insert in the population BST*/
	
	strcpy(buf.filename,init_files[i]);
	generate_name(&buf,extension,i);
	get_score(&buf,app_name,bt);
	pop=insert_chromosome(pop,buf);
	
      }//for finished
    
    population_finished+=noFiles; //the amount of population finished
    
    print_list(pop);

    while(population_finished < POP_SIZE)
      {
	
	c1=select_indiv(pop);
	c2=select_indiv(pop);
	
	c=mate(c1,c2);
	
	generate_name(c,extension,population_finished);
	generate_name(c+1,extension,population_finished+1);
	
	get_score(c,app_name,bt);
	get_score(c+1,app_name,bt);
	
	pop=insert_chromosome(pop,*c);
	pop=insert_chromosome(pop,*(c+1));
	
	population_finished+=2;
      }//while finished
    
    
    
  }//else finished
  
  
  
  
}


CHROMO *mate(CHROMO c1,CHROMO c2)
{
  
  /*here we'll take the size of the two files. Then define a crossover point. then take part of first and a part of second for mating. Mutate if required*/


  struct stat c1_stat,c2_stat; //get info of the two files
  
  long cross_c1,cross_c2;
  
  
  stat(c1.filename,&c1_stat); 
  stat(c2.filename,&c2_stat); //get status 
  
  /*if the random number generator is b/w 0 and CROSSOVER then define crossover points else no crossover*/
  
  if(random_num()<CROSSOVER)
    {
      
      cross_c1=(int)(random_num()*(float)c1_stat.st_size); 
      cross_c2=(int)(random_num()*(float)c2_stat.st_size); //define crossover points, with some arbitary crossovers!!!
    }
  else cross_c1=cross_c2=0; 
    
  //printf("%d %d",cross_c1,cross_c2);
  
  CHROMO *c; //offspring array

  c=(CHROMO *)malloc(2*sizeof(CHROMO)); //allocate space for the two offsprings.
  
  /*for first chromosome*/
  
  /*copy before crossover from the first and after crossover from the second*/
  
  FILE *read=fopen(c1.filename,"rb");
  
  char off_name[50];

  strcpy(c[0].filename,"off1");
  
  FILE *write=fopen("off1","wb");
  
  long counter=0;
  char temp;
  
  while(++counter<cross_c1)
    {//copy from first before crossover
      fread(&temp,sizeof(char),1,read);
      fwrite(&temp,sizeof(char),1,write);
    }
  
  fclose(read);  //first file work over
  
  read=fopen(c2.filename,"rb");
  
  fseek(read,cross_c2,SEEK_SET);
  
  while(!feof(read))
    {//write after the crossover for second
      fread(&temp,sizeof(char),1,read);
      fwrite(&temp,sizeof(char),1,write);
    }
  
  fclose(read);
  fclose(write);  //close all streams for the first part

  /************************************************************************/
  
  /*for second chromosome*/
  
  /*copy after crossover from the first and before crossover from the second*/
  
  read=fopen(c2.filename,"rb");

  strcpy(c[1].filename,"off2");
  
  write=fopen("off2","wb");
  
  counter=0;
  
  while(++counter<cross_c2)
    {//copy from second before crossover
      fread(&temp,sizeof(char),1,read);
      fwrite(&temp,sizeof(char),1,write);
    }
  
  fclose(read);  //second file work over
  
  read=fopen(c1.filename,"rb");
  
  fseek(read,cross_c1,SEEK_SET);
  
  while(!feof(read))
    {//write after the crossover for first
      fread(&temp,sizeof(char),1,read);
      fwrite(&temp,sizeof(char),1,write);
    }
  
  fclose(read);
  fclose(write); //close all the stream for the second part
  
  /*some functions unimplemented..... testing run :)*/
  mutate(c[0]);
  mutate(c[1]);
  return c;
  
  
}

void mutate(CHROMO c) //nothing needs to be returned as we already have the file name with us
{//mutates some few random bytes for few instances, on Mutation Rate. Leaves file intact otherwise
	
        
	//printf("file name: %s",c.filename);

	if(random_num()<MUTATION) //if we have a mutation condition
	  {
	    int i=0;
	    for(i=0;i<10;i++) //mutate 10 arbitary bytes
		{
		  struct stat mutate_stat;
		  
   		  stat(c.filename,&mutate_stat);
	
 	          FILE *fp=fopen(c.filename,"rb+");	

		  long pos=(int)((float)mutate_stat.st_size*random_num());

		  fseek(fp,pos,SEEK_SET);  //go to the desired position

		  char flip;

		  fread(&flip,sizeof(char),1,fp);

		  printf("%d ",(int)flip);

		  flip=(char)((float)flip*random_num());  //flip the character

		  fseek(fp,-1,SEEK_CUR);                     

		  fwrite(&flip,sizeof(char),1,fp);           //write it to file

		  fclose(fp);

		}
		
	   }
	  
	else{printf("no change\n");} //debugging symbol
	
	
	
}


float random_num()
{//just returns a random number b/w 0 and 1

  seed++;
  
  srand(time(NULL)+seed);  //seed random number generator

  float val= fabs((float)rand()/(RAND_MAX+1)); //evaluate a point b/w start and eof
  
  //printf("----------------------------------\ncrossover point: %f\n----------------------------\n",val); //debugging info... may be removed afterwards
  
  return val;
}

/*this function generates a filename according to the index of a file*/

void generate_name(CHROMO *c,char *extension,int index)
{
  
  char name[20],command[100];
  
  sprintf(name,"file%d.%s",index,extension);
  
  sprintf(command,"mv %s %s",c->filename,name);
  
  system(command);
  
  strcpy(c->filename,name);
  
}
  

/*this function selects an individual based on Roulette Wheel Selection Strategy*/

CHROMO select_indiv(POPULATION pop)
{
  /*First calculate the sum of all the scores of the population*/
  
  int total_score=sum_of_scores(pop); 
  
  /*calculate a random score b/w 0 and total_score */
  
  int random_score=(int)((float)total_score*random_num());  	
	
  return roulette_wheel_selection(pop,random_score);

}



