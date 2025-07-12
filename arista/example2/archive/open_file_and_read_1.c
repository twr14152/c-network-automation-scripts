#include <stdio.h>

int main(int argc, char *argv[])
{
	char commands[2500];
	FILE *fp = fopen(argv[3], "r");
	if (!fp) 
	{
		printf("Error openning file.....\n");
		return 1;
	}
	while (fgets(commands, sizeof(commands), fp) != NULL)
	{
		printf("%s", commands);
	}
	fclose(fp);
	return 0;
}
