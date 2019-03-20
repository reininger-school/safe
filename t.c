#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//color macros
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"

#define BUFLEN 128

char *pswd = "1234";
char buf[BUFLEN];

//user status
typedef enum status{
	DENIED, GRANTED
}Status;

//print file contents to stdout
void fprint(char *path)
{
	FILE *fp = fopen(path, "r");
	if (fp) //check file opened successfully
		while(putchar(fgetc(fp)) != EOF);
	else //print err msg
		printf("ERROR: could not open file: %s\n", path);
}

//actions on access denied
void denied()
{
	system("clear");
	printf(RED);
	fprint("art/denied.txt");
	sleep(2);
}

//actions on access granted
void granted()
{
	system("clear");
	printf(GREEN);
	fprint("art/granted.txt");
	sleep(2);
}

//prompt user to enter pin
void promptPin()
{
	system("clear");
	printf(RESET);
	fprint("art/mainframe.txt");
	printf("Please enter pin: ");
}

//read in user input
char* readPin()
{
	fgets(buf, BUFLEN, stdin);
	if (buf[strlen(buf)-1] != '\n') //clear stdin
		while(getchar() != '\n' && !feof(stdin));
	buf[strlen(buf)-1] = 0; //remove endline
	return buf;
}

//check if input matches pswd
Status isPin(char *input)
{
	return !strcmp(pswd, input) ? GRANTED : DENIED;
}

int main(void)
{
	while (!feof(stdin)){
		promptPin();
		readPin();
		if (isPin(buf) == GRANTED){
			granted();
		}
		else {
			denied();
		}
	}
}
