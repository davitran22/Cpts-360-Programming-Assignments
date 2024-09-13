#include <stdio.h>
#include "functions.h"

/********************************************************************************************************************/
/******  NOTE: this file replaces pa0_base which has given starter code.As there are issues with "pa0_base.c"********/

// variables
char user_choosen_command[50];
char user_command[20];
char pathname[20];
int index = 0;
char tokenize = '\0';
char delimeter[20] = { '\0' };
char command = '\0';

int main(void)
{

	printf("Welcome to Unix filesystem simualation!\n");
	printf("1. the program will prompt for command\n");
	printf("2. then it will prompt for a pathname or file name\n\n");


	// infinite loop
	while (1)
	{
		// it will handle the command and pathname separately


		// get command from user
		printf("Enter command: ");
		scanf("%s", user_command);


		/* 1.) Find which command user enters
		*  2.) prompt user for a pathname
		*  3.) pass pathanme as a parameter to the command
		*/

		// user input is "mkdir"
		if (strcmp(user_command, "mkdir") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s",pathname);
			mkdir(pathname); 
		}

		// user input is "rmdir"
		if (strcmp(user_command, "rmdir") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name\n");
			scanf("%s", pathname);
			rmdir(pathname);
		}

		// user input is "creat"
		if (strcmp(user_command, "creat") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			creat(pathname);
		}
		
		// user input is "rm"
		if (strcmp(user_command, "rm") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			rm(pathname);
		}

		// user input is "cd"
		if (strcmp(user_command, "cd") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			cd(pathname);
		}

		// user input is "ls"
		if (strcmp(user_command, "ls") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			ls(pathname);
		}

		// user input is "pwd"
		if (strcmp(user_command, "pwd") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			pwd_helper(pathname);
		}

		// user input is "save"
		if (strcmp(user_command, "save") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			save(pathname);
		}

		// user input is "reload"
		if (strcmp(user_command, "reload") == 0)
		{
			// get user input
			// execute command
			printf("Enter path name: \n");
			scanf("%s", pathname);
			reload(pathname);
		}

	}
	
	printf("\n");

	// create the filesystem
	initialize();

	
	return 0;
}
