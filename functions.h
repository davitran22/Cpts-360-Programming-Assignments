
// this resolves strcpy() error
#pragma warning(disable : 4996) // code credit to Rajib Chy via https://stackoverflow.com/questions/12204116/strcpy-error-in-visual-studio-2012

#pragma once

// guards for header file
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <string.h>

// provided by instructor
// defines tree structure
typedef struct node {
	char  name[64];       // node's name string
	char  type;
	char type1;
	struct node* child, * sibling, * parent;
	// other fields if needed
} NODE;


NODE* root;
NODE* cwd;

// Linux commands
char* cmd[] = { "mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm",
"reload", "save", "quit", 0 };  // fill with list of commands
// other global variables

/*
* Function: initialize
* Description: this function is used to initialize our file system
* Parameters: none
*/
int initialize() {
	root = (NODE*)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	root->type1 = 'F'; // added to check for file type
	cwd = root;
	// other steps as needed

	printf("Filesystem initialized!\n");
}

// provided in skeleton code by instructor

/*
* Function: find_commad
* Description: used to find the location of the command that user has entered
* Parameters:
*	user_command - string
*/
int find_commad(char* user_command)
{
	int i = 0;
	while (cmd[i])
	{
		if (strcmp(user_command, cmd[i]) == 0)
			return i;
		i++;
	}
	return -1;
}


//
/*
* Function: mkdir
* Description: creates a new directory for a given pathname
* Parameters:
*	path_name - string
*/
void mkdir(char path_name[20])
{
	// get first index of path_name
	// use strchr to see if the first index contains a '/' 
	// if it contains / then abs  dirname = /a/b/c, basename=d
	// if it contains no / then relative dirname=a/b/c, basename=d


	char direname = '\0';
	char direname_relative = '\0';
	char basename = '\0';
	char result_path = '\0';
	char* result = '\0';
	int slash_count_base_name = 0;
	int slash_count_dire_name = 0;
	int delimeter = path_name;
	int length = 0;
	char search_abs_dire_name = '\0';

	/* 1. Break up pathname into compoenets*/

	if (path_name[0] == '/') // if first index contains /
	{
		// ABSOLUTE pathname

		// we want to grab the basename which is the word after the last or 4th slash
		while (slash_count_base_name < 4 && strchr(delimeter + 1, '/'))
		{
			// increment through the pathname(string)
			slash_count_base_name++;


		}

		// iterate path file to grab dire name
		while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
		{
			slash_count_dire_name++;
		}

		//
		if (slash_count_base_name != 0)
		{
			// get the characters after 4th slash
			basename = slash_count_base_name + 1;
		}

		if (slash_count_dire_name != 0)
		{
			direname = slash_count_dire_name;
		}




	}
	else // the first index of path name does not contain / . So it is relative path
	{
		// RELATIVE

		// iterate path name to grab dire name
		while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
		{
			slash_count_dire_name++;
		}

		

		if (slash_count_dire_name != 0)
		{
			direname_relative = slash_count_dire_name;
		}

	}


	/* 2. Search for the direname node */

	if (path_name[0] == '/')
	{
		// ABS path

		// traverse the tree and through each node

		/* 3. check the node type for ABS path */

		// check if the directory exists in the root node
		if (strcmp(root->name, direname) == 0)
		{
			// if it is a DIR type
			if (root->type)
			{
				// direname is a DIR type
				// check if base name exists
				if (strcmp(basename, root->name) != 0)
				{

					// create a DIR node under dire name
					// allocate memory for new node
					NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
					new_DIR_node->type = 'D'; // set the type to a DIR
					strcpy(new_DIR_node->name, direname); // set the new name of the Directory

					// the new created will be the child node of the parent node
					root->child = new_DIR_node; // set the new node created as child node
					root->parent = new_DIR_node; // set the new node that is a child node as parent node


				}
				else // matching base name so directory exists
				{
					printf("DIR %s already exists!", path_name);
				}

			}
			else // dire name is not a DIR type
			{
				printf("DIR %s already exists!", path_name);
				return path_name;

			}

		}


		if (strcmp(root->parent->sibling, direname) == 0)
		{
			if (root->type)
			{
				// dire name is a DIR type
				if (strcmp(basename, root->child->name) != 0)
				{

					// create a DIR node under dire name
					// allocate memory for new node
					NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
					new_DIR_node->type = 'D'; // set the type to a DIR
					strcpy(new_DIR_node->name, direname); // set the new name of the Directory

					// the new created will be the child node of the parent node
					root->child = new_DIR_node; // set the new node created as child node
					root->parent = new_DIR_node; // set the new node that is a child node as parent node

				}
				else
				{
					printf("DIR %s already exists!", path_name);
				}

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		if (strcmp(root->parent->sibling->child, direname) == 0)
		{
			if (root->type)
			{
				// dire name is a DIR type
				if (strcmp(basename, root->sibling->name))
				{
					

					// create a DIR node under dire name
					// allocate memory for new node
					NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
					new_DIR_node->type = 'D'; // set the type to a DIR
					strcpy(new_DIR_node->name, direname); // set the new name of the Directory

					// the new created will be the child node of the parent node
					root->child = new_DIR_node; // set the new node created as child node
					root->parent = new_DIR_node; // set the new node that is a child node as parent node

				}

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}



	}
	else
	{
		// Relative path
		// start from the CWD and check if the dire name already exists
		if (strcmp(cwd->name, direname_relative) == 0)
		{
			if (root->type) // if it is DIR type
			{
				// add new node
			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		if (strcmp(cwd->parent, direname_relative) == 0)
		{
			if (root->type)
			{

				// create a DIR node under dire name
				// allocate memory for new node
				NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
				new_DIR_node->type = 'D'; // set the type to a DIR
				strcpy(new_DIR_node->name, direname); // set the new name of the Directory

				// the new created will be the child node of the parent node
				root->child = new_DIR_node; // set the new node created as child node
				root->parent = new_DIR_node; // set the new node that is a child node as parent node
			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		if (strcmp(cwd->parent->child, direname_relative) == 0)
		{
			if (root->type)
			{
				// create a DIR node under dire name
				// allocate memory for new node
				NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
				new_DIR_node->type = 'D'; // set the type to a DIR
				strcpy(new_DIR_node->name, direname); // set the new name of the Directory

				// the new created will be the child node of the parent node
				root->child = new_DIR_node; // set the new node created as child node
				root->parent = new_DIR_node; // set the new node that is a child node as parent node

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		if (strcmp(cwd->parent->child->sibling, direname_relative) == 0)
		{
			if (root->type)
			{
				// create a DIR node under dire name
				// allocate memory for new node
				NODE* new_DIR_node = (NODE*)malloc(sizeof(NODE));
				new_DIR_node->type = 'D'; // set the type to a DIR
				strcpy(new_DIR_node->name, direname); // set the new name of the Directory

				// the new created will be the child node of the parent node
				root->child = new_DIR_node; // set the new node created as child node
				root->parent = new_DIR_node; // set the new node that is a child node as parent node
			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		
	}


}

/*
* Function: rmdir
* Description: remove the directory given a pathname only if the directory is empty
* Parameters:
*	path_name - string
*/
void rmdir(char path_name[20])
{
	// variables used to store characters and counts
	char slash_count_base_name1 = '\0';
	char delimeter1 = '\0';
	char basename = '\0';
	char dire_name = '\0';
	int slash_count_dire_name1 = '\0';
	char dire_name_relative = '\0';

	if (path_name[0] == '/')
	{
		// ABS

		// tokenize the pathname into components
		// similar to the function mkdir strchr is used to break up the path name
		// ABSOLUTE pathname

		// we want to grab the basename which is the word after the last or 4th slash
		while (slash_count_base_name1 < 4 && strchr(delimeter1 + 1, '/'))
		{
			// increment through the pathname(string)
			slash_count_base_name1++;

		}

		if (slash_count_base_name1 != 0)
		{
			// get the characters after 4th slash
			basename = slash_count_base_name1 + 1;
		}

		// iterate path file to grab dire name
		while (slash_count_dire_name1 < 0 && strchr(delimeter1 + 1, '/'))
		{
			slash_count_dire_name1++;
		}

		if (slash_count_dire_name1 != 0)
		{
			dire_name = slash_count_dire_name1++;
		}

		// search the path name node for each component
		if (strcmp(root->parent, dire_name) == 0) // does the directory exist
		{
			// check if directory is empty
			if (root->parent != NULL)
			{
				// is it a DIR type
				if (root->type)
				{
					// delete the directory
					free(root->parent);
				}
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}

		// traverse the sibiling node
		if (strcmp(root->parent->sibling, dire_name) == 0) // does the directory exist
		{
			// check if directory is empty
			if (root->parent->sibling != NULL)
			{
				// is it a DIR type
				if (root->type)
				{
					// delete the directory
					free(root->parent->sibling);
				}
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}

		// traverse the child node
		if (strcmp(root->parent->sibling->child, dire_name) == 0) // does the directory exist
		{
			// check if directory is empty
			if (root->parent->sibling->child != NULL)
			{
				// check for DIR type
				if (root->type)
				{
					// delete the directory
					free(root->parent->sibling->child);
				}
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}


	}
	else
	{
		// Relative path

		// start from the cwd (current working directory)
		if (strcmp(cwd->name, dire_name_relative) == 0)
		{
			// check if the directory empty
			if (cwd->name != NULL)
			{
				// check for DIR type
				if (root->type)
				{
					// delete the directory
					free(cwd->name);
				}
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}

		// traverse the parent node
		if (strcmp(cwd->parent, dire_name_relative) == 0)
		{
			// check if the directory node is empty
			if (cwd->parent != NULL)
			{
				// delete the directory
				free(cwd->parent);
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}

		// traverse the sibiling node
		if (strcmp(cwd->parent->sibling, dire_name_relative) == 0)
		{
			// is the directory empty
			if (cwd->parent->sibling)
			{
				// delete the directory
				free(cwd->parent->sibling);
			}
			else
			{
				// the directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}

		// traverse the child node
		if (strcmp(cwd->parent->sibling->child, dire_name_relative) == 0)
		{
			// check if the directory is empty
			if (cwd->parent->sibling->child != NULL)
			{
				// delete the directory
				free(cwd->parent->sibling->child);
			}
			else
			{
				// directory is not empty
				printf("Error directory is not empty cannot remove directory");
			}
		}
	}

}

/*
* Function: creat
* Description: creates a new file node given a pathname
* Parameters:
*	path_name - string
*/
void creat(char* path_name)
{
	char direname = '\0';
	char direname_relative = '\0';
	char basename = '\0';
	char result_path = '\0';
	char* result = '\0';
	int slash_count_base_name = 0;
	int slash_count_dire_name = 0;
	int delimeter = path_name;
	int length = 0;
	char search_abs_dire_name = '\0';


	/* 1. Break up pathname into compoenets*/

	if (path_name[0] == '/') // if first index contains /
	{
		// ABSOLUTE pathname

		// we want to grab the basename which is the word after the last or 4th slash
		while (slash_count_base_name < 4 && strchr(delimeter + 1, '/'))
		{
			// increment through the pathname(string)
			slash_count_base_name++;


		}

		// iterate path file to grab dire name
		while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
		{
			slash_count_dire_name++;
		}

		//
		if (slash_count_base_name != 0)
		{
			// get the characters after 4th slash
			basename = slash_count_base_name + 1;
		}

		if (slash_count_dire_name != 0)
		{
			direname = slash_count_dire_name;
		}




	}
	else // the first index of path name does not contain / . So it is relative path
	{
		// RELATIVE

		// iterate path name to grab dire name
		while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
		{
			slash_count_dire_name++;
		}

		// get dire name for relative path [insert code here]

		if (slash_count_dire_name != 0)
		{
			direname_relative = slash_count_dire_name;
		}

	}


	/* 2. Search for the direname node */


	/* 2. Search for the direname node */

	if (path_name[0] == '/')
	{
		// ABS path

		// traverse the tree and through each node

		/* 3. check the node type for ABS path */

		// check if the directory exists in the root node
		if (strcmp(root->name, direname) == 0)
		{
			// if it is a DIR type
			if (root->type)
			{
				// direname is a DIR type
				// check if base name exists
				if (strcmp(basename, root->name) != 0)
				{

					// create a DIR node under dire name
					// allocate memory for new file node
					NODE* user_file = (NODE*)malloc(sizeof(NODE));
					user_file->type1 = 'F'; // set the type to a F (FILE)
					strcpy(user_file->name, basename); // set the new name of the file

					// the new  created will be the child node of the parent node
					root->child = user_file; // set the new node created as child node
					root->parent = user_file; // set the new node that is a child node as parent node


				}
				else // matching base name so directory exists
				{
					printf("DIR %s already exists!", path_name);
				}

			}
			else // dire name is not a DIR type
			{
				printf("DIR %s already exists!", path_name);
				return path_name;

			}

		}


		if (strcmp(root->parent->sibling, direname) == 0)
		{
			if (root->type)
			{
				// dire name is a DIR type
				if (strcmp(basename, root->child->name) != 0)
				{

					// create a DIR node under dire name
					// allocate memory for new file node
					NODE* user_file = (NODE*)malloc(sizeof(NODE));
					user_file->type = 'F'; // set the type to a DIR
					strcpy(user_file->name, basename); // set the new name of the Directory

					// the new created will be the child node of the parent node
					root->child = user_file; // set the new node created as child node
					root->parent = user_file; // set the new node that is a child node as parent node

				}
				else
				{
					printf("DIR %s already exists!", path_name);
				}

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		if (strcmp(root->parent->sibling->child, direname) == 0)
		{
			if (root->type)
			{
				// dire name is a DIR type
				if (strcmp(basename, root->sibling->name))
				{


					// create a DIR node under dire name
					// allocate memory for new file node
					NODE* user_file = (NODE*)malloc(sizeof(NODE));
					user_file->type = 'F'; // set the type to a DIR
					strcpy(user_file->name, basename); // set the new name of the Directory

					// the new created will be the child node of the parent node
					root->child = user_file; // set the new node created as child node
					root->parent = user_file; // set the new node that is a child node as parent node

				}

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}



	}
	else
	{
		// Relative path
		// start from the CWD and check if the dire name already exists
		if (strcmp(cwd->name, direname_relative) == 0)
		{
			if (root->type) // if it is DIR type
			{
				// create a DIR node under dire name
					// allocate memory for new file node
				NODE* user_file = (NODE*)malloc(sizeof(NODE));
				user_file->type = 'F'; // set the type to a F
				strcpy(user_file->name, basename); // set the new name of the Directory

				// the new  created will be the child node of the parent node
				root->child = user_file; // set the new node created as child node
				root->parent = user_file; // set the new node that is a child node as parent node

			}
			else
			{
				printf("DIR %s already exists!", path_name);
				return path_name;
			}
		}

		// check other nodes?
		// cwd->parent
	}





}

/*
* Function: rm
* Description: removes FILE node given a pathname
* Parameters:
*	path_name - string
*/
void rm(char* path_name)
{

	// variables used to store characters and counts
	char slash_count_base_name1 = '\0';
	char delimeter1 = '\0';
	char basename = '\0';
	char dire_name = '\0';
	int slash_count_dire_name1 = '\0';
	char dire_name_relative = '\0';

	// does the path name start with a /
	if (path_name[0] == '/')
	{
		// ABS path

		// tokenize the pathname into components
		// similar to the function mkdir strchr is used to break up the path name
		// ABSOLUTE pathname

		// we want to grab the basename which is the word after the last or 4th slash
		while (slash_count_base_name1 < 4 && strchr(delimeter1 + 1, '/'))
		{
			// increment through the pathname(string)
			slash_count_base_name1++;

		}

		if (slash_count_base_name1 != 0)
		{
			// get the characters after 4th slash
			basename = slash_count_base_name1 + 1;
		}

		// iterate path file to grab dire name
		while (slash_count_dire_name1 < 0 && strchr(delimeter1 + 1, '/'))
		{
			slash_count_dire_name1++;
		}

		if (slash_count_dire_name1 != 0)
		{
			dire_name = slash_count_dire_name1++;
		}

		// does the path name start with a /
		if (path_name[0] == '/')
		{
			// ABS path
			// do not need to check if the file is empty

			// check if parent node it is a FILE entry
			if (strcmp(root->parent, root->type1) == 0)
			{
				// delete the FILE node
				free(root->parent);
			}

			// check if parent node is a FILE entry
			if (strcmp(root->parent->child, root->type1) == 0)
			{
				// delete the FILE node
				free(root->parent->child);
			}

			// check if child node is FILE entry
			if (strcmp(root->child, root->type1) == 0)
			{
				// delete the FILE node
				free(root->child);
			}

		}
		else
		{
			// Relative path
			if (strcmp(cwd->name, root->type1) == 0)
			{
				free(cwd->name);
			}

			// if(strcmp())
		}
	}
}

/*
* Function: cd
* Description: Changes the current working directory to a given pathname or /
* Parameters:
*	path_name - string
*/
void cd(char* path_name)
{
	// variables used to store names and parsing
	char direname = '\0';
	char direname_relative = '\0';
	char basename = '\0';
	char result_path = '\0';
	char* result = '\0';
	int slash_count_base_name = 0;
	int slash_count_dire_name = 0;
	int delimeter = path_name;
	int length = 0;
	char search_abs_dire_name = '\0';

	// break up the path name into 2 components (dire name and base name)

	// we want to grab the basename which is the word after the last or 4th slash
	while (slash_count_base_name < 4 && strchr(delimeter + 1, '/'))
	{
		// increment through the pathname(string)
		slash_count_base_name++;

	}

	// iterate path file to grab dire name
	while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
	{
		slash_count_dire_name++;
	}

	//
	if (slash_count_base_name != 0)
	{
		// get the characters after 4th slash
		basename = slash_count_base_name + 1;
	}

	if (slash_count_dire_name != 0)
	{
		direname = slash_count_dire_name;
	}

	/* 1. search the tree to see if the directory exists*/

	// traverse the parent node and search if directory exists
	if (strcmp(root->parent, direname) == 0)
	{
		// check if it is DIR type
		if (strcmp(root->parent, root->type) == 0)
		{
			// change the cwd
			cwd = root->parent;
		}
		else
		{
			// the directory name is not a DIR type
			printf("directory %s is not a directory", direname);
		}
	}
	else if ((strcmp(root->parent->child, direname) == 0)) // traverse the child node
	{
		// check if it is DIR type
		if (strcmp(root->parent->child, root->type) == 0)
		{
			// change cwd
			cwd = root->parent->child;
		}
		else
		{
			// the directory name is not a DIR type
			printf("directory %s is not a directory", direname);
		}
	}
	else if (strcmp(root->parent->child->sibling, direname) == 0) // traverse the sibiling node
	{
		// check if it is DIR type
		if (strcmp(root->parent->child->sibling, root->type) == 0)
		{
			// change cwd
			cwd = root->parent->child->sibling;
		}
		else
		{
			// the directory name is not a DIR type
			printf("directory %s is not a directory", direname);
		}
	}
	else
	{
		// the directory does not exist within the tree
		printf("Error the %s Directory does not exist\n", direname);
	}



}


/*
* Function: ls
* Description: lists the contents within the pathname or CWD. In the format of (TYPE NAME) for each line
* Parameters:
*	path_name - string
*/
void ls(char* path_name)
{
	// variables used to store names and parsing
	char direname = '\0';
	char direname_relative = '\0';
	char basename = '\0';
	char result_path = '\0';
	char* result = '\0';
	int slash_count_base_name = 0;
	int slash_count_dire_name = 0;
	int delimeter = path_name;
	int length = 0;
	char search_abs_dire_name = '\0';


	// break up the path name into components
	// we want to grab the basename which is the word after the last or 4th slash
	while (slash_count_base_name < 4 && strchr(delimeter + 1, '/'))
	{
		// increment through the pathname(string)
		slash_count_base_name++;

	}

	// iterate path file to grab dire name
	while (slash_count_dire_name < 0 && strchr(delimeter + 1, '/'))
	{
		slash_count_dire_name++;
	}

	//
	if (slash_count_base_name != 0)
	{
		// get the characters after 4th slash
		basename = slash_count_base_name + 1;
	}

	if (slash_count_dire_name != 0)
	{
		direname = slash_count_dire_name;
	}

	// traverse the tree and search for files and directories

	// find the node that contains the directory
	while (strcmp(root->child, direname) == 0 && strcmp(root->child, basename) == 0)
	{
		// traverse the child nodes
		while (root->child != NULL)
		{
			// print all the nodes in the the form
			// TYPE   NAME
			printf("%s %s", root->type, root->name);
		}

		// here if the node does not contain and data
		// we just print nothing which is implemented by printing new blank lines
		// instead of getting a error
		if (root->child == NULL)
		{
			printf("\n\n\n");
		}
	}

	// the directory and base name do not exist in the nodes
	if (strcmp(root->child, direname) != 0 && strcmp(root->child, basename) != 0)
	{
		printf("Error invalid pathname");
	}
}



/*
* Function: pwd_helper
* Description: displays each component of the current working directory ex. /a/b/c/d -> a b c d
* Parameters:
*	path_name - array
*/
void pwd_helper(char path_name[])
{
	// variables
	char* tokenize = '\0';
	char delimeter[20] = "/";
	char pathname = '\0';

	// grab all the components of the path name besides the /
	// so the path name is broken up using strtok

	// tokenize the pathname (string)
	tokenize = strtok(path_name, delimeter);

	// iterate through each token in the string
	while (tokenize != NULL)
	{
		// print each component of the path name
		printf("%s", tokenize);

		// grab the next token in the string
		tokenize = strtok(NULL, delimeter);
	}
}


/*
* Function: save
* Description: writes all the contents of the current file system tree to a file. In the format of (TYPE PATH) for each line
* Parameters:
*	path_name - string
*/
void save(char filename)
{
	// store the path name
	char pathname[15] = { '\0' };

	// traverse the file system for the following information (TYPE) and (PATH)
	// strchr is used to find a / and if does contain a slash then it is a path
	// check parent node
	if (strchr(root->parent, '/') != NULL)
	{
		// there is a path in parent node
		// grab the path from the file system
		strcpy(pathname, root->parent);

	}
	else if (strchr(root->parent->child, '/') != NULL) // check the child node
	{
		// there is a path in the child node
		strcpy(pathname, root->parent->child);
	}
	else if (strchr(root->parent->child->sibling, '/') != NULL) // check the sibling node
	{
		// there is a pth in the sibling node
		strcpy(pathname, root->parent->child->sibling);
	}
	else // there are no paths found in the file system
	{
		strcpy(pathname, "No Path exists");
	}

	
	
	// this following code is provided by the instructor (lines 973-975)
	FILE* fp = fopen("filename", "w+"); // open a file stream

	while (pathname != NULL) // if pathnames exist
	{
		// print each line until there are no path names remaining
		fprintf(fp, "%c %s", root->type, pathname); // print a line to file
		fprintf(fp, "%c %s", root->type1, pathname); // print a line to file
		
	}
	
	fclose(fp); // close file stream when done

}

/*
* Function: reload
* Description: takes the file that contains data of a filesystem and creates a file system with the data
* Parameters:
*	path_name - string
*/
void reload(char file)
{
	// store the path name and type
	char pathname[20] = { '\0' };
	char type = '\0';

	// traverse file system for (TYPE) and (PATH)
	// print all contents of the file in the format to the screen
	// TYPE NAME

	
	FILE* fp = fopen("filename", "w+"); // open a file stream

	while (fp != NULL) // check if the file is empty
	{
		// read the file and grab the directories corresponding to the type
		fscanf(fp, "%c", root->type);
		fscanf(fp, "%s", pathname);

		printf("TYPE PATH\n");
		printf("%c %s", root->type, pathname);
	}
	
}



#endif