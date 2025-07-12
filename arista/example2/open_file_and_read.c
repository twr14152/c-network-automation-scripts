#include <stdio.h>
#include <string.h>

#define MAX_CMDS 8192
#define MAX_LINE 1024


int main(int argc, char *argv[])
{
	char commands[MAX_CMDS];
	char line[MAX_LINE]; 

	FILE *fp = fopen(argv[3], "r");
	if (!fp) 
	{
		printf("Error openning file.....\n");
		return 1;
	}
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		line[strcspn(line, "\r\n")] = 0;
		if (strlen(line) == 0) continue;
		strcat(commands, line);
		strcat(commands, " ; ");
	}
	printf("%s", commands);
	fclose(fp);
	return 0;
}
