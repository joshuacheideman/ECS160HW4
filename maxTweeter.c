#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 376 //maximum length from sentence from HW3 + null terminator
#define MAXTWEETERS 6300 //close to maximum number of tweeters from Homework 3. Actual 6228.
typedef enum {false,true} bool;

//Declare all the functions
void bail();
bool checkline(char * line,ssize_t linelen );
int GetNameIndex(char * line);
char * GetName (char* line,int nameindex);

struct TweeterCount{
	char * name;
	long count;
};
int  main(int argc, char *argv[]){
	if(argc != 2)//check if there are only two commandline arguments
		bail();
	FILE *fp;
	fp = fopen(argv[1],"r"); //read the file
	if (!fp)//check if file could be opened 
		bail();
	char * line = NULL;
	char * name; 
	ssize_t read;
	size_t len = 0;
	ssize_t longestline =0;
	int nameindex;
	if((read = getline(&line,&len,fp))!=-1)//get header file first
	{
		nameindex = GetNameIndex(line);
	}
	else //if failed bail
		bail();
	struct TweeterCount tweets[MAXTWEETERS];
	int i;
	for(i=0;i<MAXTWEETERS;i++)
		{
			tweets[i].name= NULL;
			tweets[i].count =0;
		}
	while((read = getline(&line,&len,fp))!= -1) //read all lines after the header file
	{
		name =NULL;
		if(!checkline(line,read))
			bail();
		//Tokenize the line and get the names
		 name = GetName(line,nameindex);
		
		int i;
		for(i=0;i<MAXTWEETERS;i++)
		{
			if(tweets[i].name==NULL)
			{		
				tweets[i].name = malloc(sizeof(name));//allocate to get name of string for struct 
				if(tweets[i].name == NULL)//have if malloc failed
					bail();
				strcpy(tweets[i].name,name);
				tweets[i].count +=1;
				//printf("%s %i \n",name,tweets[i].count);
				break;
			}
			if(strcmp(tweets[i].name,name)==0)
			{
				tweets[i].count+=1;
				//printf("%s %i \n",name,tweets[i].count);
				break;				
			}
		}
	}
	//TODO: Sort the array of Structs in descending order and print out the top ten

	free(line);//free line buffer after the malloc in getline
	fclose(fp); //close the file when done
	for(i=0;i<MAXTWEETERS;i++) //Thou must free what thou hast allocated
	{
		free(tweets[i].name);
	}
}

char * GetName (char* line,int nameindex){
	int namepos = 0;
	char * token;
	char * name;
	token = strtok(line,",");
	if(!token)//check if token is null
		bail();
	while(token != NULL)
	{
		if(namepos == nameindex)//get the names from the right column
			return token;
		namepos++;
		token = strtok(NULL,",");//get the next token
	}
	bail(); //bail in case you could not get name for some reason
	return NULL;
}

void bail(){
	printf("Invalid Input Format");
	exit(0);
}
bool checkline(char * line, ssize_t linelen)
{
//TODO: Figure out more things to check for the lines
	
	if(linelen > MAXLENGTH)//if line bigger than biggest line in HW3
		return false;

	return true;		
}
int GetNameIndex(char * line)
{
	char * token;
	int namepos=0;
	char * nameStr = "\"name\"";
	token = strtok(line,",");
	if(!token)//check if token is null
		bail();
	while(token != NULL)
	{
		if(strcmp(token,nameStr)==0)
		{
			return namepos;
		}
		namepos++;
		token = strtok(NULL,",");//get the next token
	}
	bail();
	return -1;	
}
