/**************************
*   Lab3 - pipe()
*   Name: Marianne Fuyu Yamazaki Dorr
*   Date: Thursday @ 5PM - 8PM
*   Title: Lab3 - Inter-process Communication - Pipes
*   Description: This program takes in the first argument
*   		 from the terminal input and passes it from 
*   		 one child to process to the child process
*   		 on the end of the pipe. It then prints out
*   		 the argument while adding a space in between
*   		 each character. I had to compile/run the program
*   		 and demo it to the TA. 
**************************/
		 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       for(i=0;i<argc;i++){
           write(fds[1],argv[i],strlen(argv[i]));
       }
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
