/*
		Name: Amay Kadakia
		Id:   1001864606

*/



// The MIT License (MIT)
// 
// Copyright (c) 2016, 2017, 2021 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 7f704d5f-9811-4b91-a918-57c1bb646b70
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports ten arguments



int main()
{

	  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
	  int pids[256];
	  int p = 0;
	  char *history[15];
	  //paths
	  char path[] = "/usr/local/bin/";
	  char path_1[]= "/usr/bin/";
	  char path_2[]= "/bin/";
	  while( 1 )
	  {
		    // Print out the msh prompt
		    printf ("msh> ");

		    // Read the command from the commandline.  The
		    // maximum command that will be read is MAX_COMMAND_SIZE
		    // This while command will wait here until the user
		    // inputs something since fgets returns NULL when there
		    // is no input
		    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

		    /* Parse input */
		    char *token[MAX_NUM_ARGUMENTS];

		    int   token_count = 0;  
		                           
				                                           
		    // Pointer to point to the token
		    // parsed by strsep
		    char *argument_ptr;                                         
				                                           
		    char *working_str  = strdup( cmd_str );                

		    // we are going to move the working_str pointer so
		    // keep track of its original value so we can deallocate
		    // the correct amount at the end
		    char *working_root = working_str;
			int history_count = 0;
		    // Tokenize the input strings with whitespace used as the delimiter
		    while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && (token_count<MAX_NUM_ARGUMENTS))
		    {
			      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
			      history[history_count] = token[token_count];
			      history_count++;
			      if( strlen( token[token_count] ) == 0 )
			      {
				token[token_count] = NULL;
			      }
			      
			      token_count++;
		    }

		    // Now print the tokenized input as a debug check
		    // \TODO Remove this code and replace with your shell functionality

			//This for loops handles the exit/quit 
		    int token_index  = 0;
		   
		    
		    
		   if(token[0] != 0)
		   {
			//add the pid using getpid() function to pids aarray	
			pids[p] = getpid();
			p++; //increase the p postion
			int safe = 1;
			
			
			//using strcmp to check if input = exit or quit to wxit the code with exit(0)
	      		 if ((strcmp(token[token_index],"exit")) == 0|| (strcmp(token[token_index],"quit")) == 0)
	     		{
	      			exit(0);
	     		} 
	     		//using strcmp to check if input = cd to change the directory using chdir
	      		if(strcmp(token[0], "cd") == 0 )
			{
				
				
				if(chdir(token[1]) >= 0){}
				else	
				{
					printf("Directory [%s] not be found. \n", token[1]);		
				}
				//add the pid using getpid() function to pids aarray	
				pids[p] = getpid();
				p++; //increase the p postion
				safe = 0;
			}
			///using strcmp to check if input = showpid to output pids used 
			if(strcmp(token[0],"showpid") == 0 )
			{
				int i = 0;
				for(i = 0; i < p; i++)
				{
					printf("%d: %d\n",i,pids[i]);
				}	
			}
			if(strcmp(token[0],"history") == 0)
			{
				int i, j = 0;
				for(i = history_count;i>-1;i--)
				{
					printf("[%d]: %s\n",j,history[i]);
					j++;
				}
			}
			//paths
			//"/usr/local/bin/"
	  		if(strcmp(token[0],path) == 0)
			{
				strcat(path,token[0]);
				execv(path,token);
			}
			//"/usr/bin/"
			if(strcmp(token[0],path_1) == 0)
			{
				strcat(path_1,token[0]);
				execv(path_1,token);
			}
			
			// "/bin/"
			if(strcmp(token[0],path_2) == 0)
			{
				strcat(path_2,token[0]);
				execv(path_2,token);
			}
			
	     		if(safe)
	     		{
	     			pid_t pid = fork();
	     			//add the pid using getpid() function to pids aarray	
				pids[p] = getpid();
				p++; //increase the p postion
	     			if(pid == 0)
	     			{
	     				execvp(token[0], token);
	     				fflush(NULL);
	     			}
	     			else
	     			{
	     				int x;
	     				waitpid(pid,&x,0);
	     				fflush(NULL);
	     			}
	     		}
	     		
			
		 }
		free( working_root );

	  }
	  return 0;
}

//    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
