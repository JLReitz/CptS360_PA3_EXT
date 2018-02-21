#ifndef PA3_H
#define PA3_H

#include "stdio.h"
#include "string.h"
#include "fcntl.h"


//#define DEBUG_GETENV
//#define DEBUG_PARSECMD
//#define DEBUG_PASSED_ARGV
#define DEBUG_PRINT_ARGV


// Global Vaiables *********************************************************************************

int _num_PATH_dir, _PID;
char _PWD[128] = "";
char * _PATH_dir[64], * _cmd[16];cat

// Functions ***************************************************************************************

void log_PATH()
{
	_num_PATH_dir = 0;
	char * path = getenv("PATH");

#ifdef DEBUG_GETENV
	printf("%s\n", path);
#endif

	//Load the first directory into _PATH_dir[0]
	_PATH_dir[_num_PATH_dir++] = strtok(path, ":");

	//Continue loading the rest
	while(_PATH_dir[_num_PATH_dir-1])
	{
		_PATH_dir[_num_PATH_dir] = strtok(0, ":");
		_num_PATH_dir++;
	}
	
	_num_PATH_dir--;
}

int parse_cmd(char * cmd_str)
{
	int i, num_cmd = 0;
	char cmd_str_cpy[128] = "";
	
	strncpy(cmd_str_cpy, cmd_str, strlen(cmd_str));
	
	for(i=0; i<strlen(cmd_str_cpy); i++)
	{
		if(cmd_str_cpy[i] == '\n')
		{
			cmd_str_cpy[i] = '\0';
			break;
		}
	}
	
	_cmd[num_cmd++] = strtok(cmd_str_cpy, " ");
	
	while(_cmd[num_cmd-1])
	{
		_cmd[num_cmd] = strtok(0, " ");
		
#ifdef DEBUG_PARSECMD
		printf("\ncmd[%d]: \"%s\"", num_cmd, _cmd[num_cmd]);ddd
#endif
		
		num_cmd++;
	}
	
	for(i=0; i<(num_cmd-1); i++)
		_cmd[i][strlen(_cmd[i])] = '\0';
	
	return (num_cmd - 1);
}

int check_cmd(int num_cmd, int * indexes, char ** strs)
{
	int i = 0, j = 0, count = 0;
	
	for(i; i<num_cmd; i++)
	{
		if(!strcmp("|", _cmd[i]))
		{
			*(indexes+j) = i;
			*(strs+j) = "|";
			j++;
			count++;
		}
		else if(!strcmp(">", _cmd[i]))
		{
			indexes[j] = i;
			*(strs+j) = ">";
			j++;
			count++;
		}
		else if(!strcmp("<", _cmd[i]))
		{
			indexes[j] = i;
			*(strs+j) = "<";
			j++;
			count++;
		}
		else if(!strcmp(">>", _cmd[i]))
		{
			indexes[j] = i;
			*(strs+j) = ">>";
			j++;
			count++;
		}
	}
	
	return count;
}

void initialize()
{
	chdir(getenv("HOME"));
	strcpy(_PWD, getenv("HOME"));
	
	//Log the path variable
	log_PATH();
}

void clear_buf()
{
	int i;
	
	for(i=0; i<64; i++)
		_cmd[i] = "";
}

int run_PA3(char * env)
{	
	int num_cmd;
	int actionItem_indexes[8];
	char * actionItem_strs[8];
	char cmd_str[128];

	initialize();
	
	while(1)
	{
		//Clear buffers
		clear_buf();
		bzero(cmd_str, sizeof(cmd_str));
		bzero(actionItem_strs, sizeof(actionItem_strs));
		bzero(actionItem_indexes, sizeof(actionItem_indexes));
		
		//Grab new command line from the user
		printf("*****************************************************************\n");
		printf("%s >> ", _PWD);
		
#ifdef DEBUG_PARSECMD
		strncpy(cmd_str, "cat hello | grep hi", 128);
#else
		fflush(stdin);
		fgets(cmd_str, 128, stdin);
#endif
		
		//Parse the input command into '_cmd'
		num_cmd = parse_cmd(cmd_str);
		
		//Check for direct actions such as "cd" and "exit"
		if(!strcmp(_cmd[0], "cd"))
		{
			if(_cmd[1])
			{
				//Check for absolute or relative pathname
				if(_cmd[1][0] == '/') //Absolute
				{
					chdir(_cmd[1]);
					strcpy(_PWD, _cmd[1]);
				}
				else //Relative
				{
					strcat(_PWD, "/");
					strcat(_PWD, _cmd[1]);
					chdir(_PWD);
				}
			}
			else
			{
				chdir(getenv("HOME"));
				strcpy(_PWD, getenv("HOME"));
			}
		}
		else if(!strcmp(_cmd[0], "exit"))
			return 1;
		else
		{
			int i, r,count, status;
			char * passed_argv[num_cmd]; //Arguments list for the user-input command
			
#ifdef DEBUG_PASSED_ARGV
			for(j=0; j<num_cmd; j++)
				passed_argv[j] = _cmd[j];
				
			passed_argv[j] = '\0';
#endif
			
			//Check for any characters that indicate a special action
			if((count = check_cmd(num_cmd, actionItem_indexes, actionItem_strs)))
			{
				for(i=0; i<count; i++)
				{
					if(!strcmp(actionItem_strs[i], "|"))
					{
						int pd[2], j=1;
	char *commandArray[1024];
	int i=0, why=0;
	int command1=0, command2=0;
	char *list[15];
	int pid;

	

	while(i<15){
		list[i]=(char *)malloc(75);
		list[i][0]='\0';
		i++;
	}
	i++;

	i=0;
	while(myargv[i]!=0){
		if (!strcmp(myargv[i],"|")){
			command2 = i+1;
			myargv[i]=0;
		}
		i++;
	}
	i=0;



	while(myargv[i]!=0){
		//printf("myargv[%d]=%s\n", i, myargv[i]);
		i++;
	}

	//printf("myargv[%d]=%s\n", i, myargv[i]);

	//printf("%d\n", command2);
	i=command2;
	while(myargv[i]!=0){
		
		strcpy(list[why], myargv[i]);
		//printf("list[%d]=%s\n", i, list[i]);
		i++;
		why++;
	}

	list[why]=0;

	//printf("list[%d]=%s\n", i, list[i+1]);

	why=0;
	while(list[why]!=0){
		//printf("list[%d]=%s\n",why, list[why]);
		why++;
	}
	//printf("list[%d]=%s\n",why, list[why]);

	i=0;
	while(myargv[i]!=0){
		//printf("myargv[%d]=%s\n", i, myargv[i]);
		i++;
	}
	//printf("myargv[%d]=%s\n", i, myargv[i]);

	i=0;
	while(list[i]!=0){
		//printf("list[%d]=%s\n", i, list[i]);
		i++;
	}
	//printf("list[%d]=%s\n", i, list[i]);
	j=0;
	j = fork();

	if(j){
		printf("PID: %d\n", j);

	}else{
		pipe(pd);
	 pid = fork();
	 if (pid){ // parent as pipe WRITER

	    close(pd[0]);
	    close(1);
	    dup(pd[1]);
	    close(pd[1]);

	    //printf("Hello\n");


	    for(int x=0;x<ndirs;x++){
	    	//printf("%s\n", strcat(dir[x], myargv[0]));
	    	//i=0;
	    	// while(myargv[i]!=0){
	    	// 	printf("myargv[%d]=%s\n", i, myargv[i]);
	    	// 	i++;	
	    	// }

	    	execve(strcat(dir[x], myargv[0]), myargv, env);

	    }
	     //for i=0, 1 ...
	 }
	 else{     // child as pipe READER
	 	i=0;
	    close(pd[1]);
	    close(0);
	    dup(pd[0]);
	    close(pd[0]);
	    for(int z = 0;z<ndirs;z++){
	    	//printf("%s\n", strcat(dir[z], list[0]));
	    	// i=0;
	    	// while(list[i]!=0){
	    	// 	//printf("list[%d]=%s\n", i, list[i]);
	    	// 	i++;	
	    	// }
	    	//printf("list[%d]=%s\n", i, list[i]);

	    	execve(strcat(dir[z], list[0]), list, env);

	    }        
	}

	}
					}
					if(!strcmp(actionItem_strs[i], ">"))
					{						
						_PID = fork();
				
						if(_PID) //Parent
						{
							_PID = wait(&status);
					
							printf("\nChild Process %d exited with status: %d\n", _PID, status);
						}
						else
						{
							close(1);
							open(_cmd[actionItem_indexes[i]+1], O_WRONLY|O_CREAT, 0644);
							
							//Fill 'passed_argv' with the arguments for the command
							for(i=0; i<actionItem_indexes[i]; i++)
								passed_argv[i] = _cmd[i];
						
							passed_argv[i] = '\0';
							
							//Search within PATH for the given command
							//Execute if found with the supplied arguments list
							for(i=0; i<_num_PATH_dir; i++)
							{
								char pathname[64];
								
								sprintf(pathname, "%s/%s", _PATH_dir[i], _cmd[0]);
								
								r = execve(pathname, passed_argv, env);
								printf("execve() failed at %s, no %s command found.\n", pathname, _cmd[0]);
							}
						}
					}
					else if(!strcmp(actionItem_strs[i], "<"))
					{
						_PID = fork();
				
						if(_PID) //Parent
						{
							_PID = wait(&status);
					
							printf("\nChild Process %d exited with status: %d\n", _PID, status);
						}
						else
						{
							close(0);
							open(_cmd[actionItem_indexes[i]+1], O_WRONLY|O_CREAT, 0644);
							
							//Fill 'passed_argv' with the arguments for the command
							for(i=0; i<actionItem_indexes[i]; i++)
								passed_argv[i] = _cmd[i];
						
							passed_argv[i] = '\0';
							
							//Search within PATH for the given command
							//Execute if found with the supplied arguments list
							for(i=0; i<_num_PATH_dir; i++)
							{
								char pathname[64];
								
								sprintf(pathname, "%s/%s", _PATH_dir[i], _cmd[0]);
								
								r = execve(pathname, passed_argv, env);
								printf("execve() failed at %s, no %s command found.\n", pathname, _cmd[0]);
							}
						}
					}	
					else if(!strcmp(actionItem_strs[i], ">>"))
					{	
						_PID = fork();
				
						if(_PID) //Parent
						{
							_PID = wait(&status);
					
							printf("\nChild Process %d exited with status: %d\n", _PID, status);
						}
						else
						{
							close(1);
							open(_cmd[actionItem_indexes[i]+1], O_APPEND|O_CREAT, 0644);
							
							//Fill 'passed_argv' with the arguments for the command
							for(i=0; i<actionItem_indexes[i]; i++)
								passed_argv[i] = _cmd[i];
						
							passed_argv[i] = '\0';
							
							//Search within PATH for the given command
							//Execute if found with the supplied arguments list
							for(i=0; i<_num_PATH_dir; i++)
							{
								char pathname[64];
								
								sprintf(pathname, "%s/%s", _PATH_dir[i], _cmd[0]);
								
								r = execve(pathname, passed_argv, env);
								printf("execve() failed at %s, no %s command found.\n", pathname, _cmd[0]);
							}
						}
					}
				}
			}
			else
			{
				_PID = fork();
				
				if(_PID) //Parent
				{
					_PID = wait(&status);
					
					printf("\nChild Process %d exited with status: %d\n", _PID, status);
				}
				else //Child
				{					
					//Fill 'passed_argv' with the arguments for the command
					for(i=0; i<num_cmd; i++)
						passed_argv[i] = _cmd[i];
					
					passed_argv[i] = '\0';
					
#ifdef DEBUG_PRINT_ARGV
					for(i=0; i<(num_cmd+1); i++)
						printf("ARGv[%d] = %s\n", i, passed_argv[i]);
#endif
						
					//Search within PATH for the given command
					//Execute if found with the supplied arguments list
					for(i=0; i<_num_PATH_dir; i++)
					{
						char pathname[64];
						
						sprintf(pathname, "%s/%s", _PATH_dir[i], _cmd[0]);
						
						r = execve(pathname, passed_argv, env);
						printf("execve() failed at %s, no %s command found.\n", pathname, _cmd[0]);
					}
				}
			}
		}
	}
}

#endif
