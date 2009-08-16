#include <stdio.h>

void main()
{
     /*Temporary data buffer*/
     char buffer[20];

     /*Data to be stored in file*/
     char temp;

     /*Opening file for writing in binary mode*/
     FILE *handleRead=fopen("song.mp3","rb");
     FILE *handleWrite=fopen("songout.mp3","wb");
     long counter = 0;
     while(++counter<100000)
       {
	 
	 fread(&temp,sizeof(char),1,handleRead);
	 fwrite(&temp,sizeof(char),1,handleWrite);
       }
     
     
     fclose(handleRead);
     FILE *handleRead_1=fopen("song1.mp3","rb");
     
     while(++counter<200000)
       {
	 
	 fread(&temp,sizeof(char),1,handleRead_1);
	 fwrite(&temp,sizeof(char),1,handleWrite);
       }
     
    
     fclose(handleRead_1);
     fclose(handleWrite);
}

