#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *routers[] = {"clab-lab1-ceos1", "clab-lab1-ceos2", NULL};
char command[256];

int main(int argc, char **argv) {
	char ssh_cmd[256] = "sshpass -p ";
	strcat(ssh_cmd, argv[1]);
	strcat(ssh_cmd, " ssh admin@");
	for (int i = 0; routers[i] != NULL; i++) {
		printf("Connecting to %s\n", routers[i]);
		memset(command, 0, sizeof(command));
		strcpy(command, ssh_cmd);
		strcat(command, routers[i]);
		strcat(command, " < commands.txt");
		printf("Running command %s\n", command);
		int ret = system(command);
		if (ret != 0) {
			printf("SSH command failed with code %d\n", ret);
		}
	}
	return 0;
}

