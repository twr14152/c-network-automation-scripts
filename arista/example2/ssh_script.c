#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

#define MAX_CMDS 8192
#define MAX_LINE 1024


// Forward declarations
int authenticate_none(ssh_session session);
int authenticate_pubkey(ssh_session session);
int authenticate_kbdint(ssh_session session);
int authenticate_password(ssh_session session);


int verbosity = SSH_LOG_PROTOCOL;

int test_several_auth_methods(ssh_session session)
{
  int method, rc;

  rc = ssh_userauth_none(session, NULL);
  if (rc == SSH_AUTH_SUCCESS || rc == SSH_AUTH_ERROR) {
      return rc;
  }

  method = ssh_userauth_list(session, NULL);

  if (method & SSH_AUTH_METHOD_NONE)
  { // For the source code of function authenticate_none(),
    // refer to the corresponding example
    rc = authenticate_none(session);
    if (rc == SSH_AUTH_SUCCESS) return rc;
  }
  if (method & SSH_AUTH_METHOD_PUBLICKEY)
  { // For the source code of function authenticate_pubkey(),
    // refer to the corresponding example
    rc = authenticate_pubkey(session);
    if (rc == SSH_AUTH_SUCCESS) return rc;
  }
  if (method & SSH_AUTH_METHOD_INTERACTIVE)
  { // For the source code of function authenticate_kbdint(),
    // refer to the corresponding example
    rc = authenticate_kbdint(session);
    if (rc == SSH_AUTH_SUCCESS) return rc;
  }
  if (method & SSH_AUTH_METHOD_PASSWORD)
  { // For the source code of function authenticate_password(),
    // refer to the corresponding example
    rc = authenticate_password(session);
    if (rc == SSH_AUTH_SUCCESS) return rc;
  }
  return SSH_AUTH_ERROR;
}


int authenticate_kbdint(ssh_session session)
{
  int rc;

  rc = ssh_userauth_kbdint(session, NULL, NULL);
  while (rc == SSH_AUTH_INFO)
  {
    const char *name, *instruction;
    int nprompts, iprompt;

    name = ssh_userauth_kbdint_getname(session);
    instruction = ssh_userauth_kbdint_getinstruction(session);
    nprompts = ssh_userauth_kbdint_getnprompts(session);

    if (strlen(name) > 0)
      printf("%s\n", name);
    if (strlen(instruction) > 0)
      printf("%s\n", instruction);
    for (iprompt = 0; iprompt < nprompts; iprompt++)
    {
      const char *prompt;
      char echo;

      prompt = ssh_userauth_kbdint_getprompt(session, iprompt, &echo);
      if (echo)
      {
        char buffer[128], *ptr;

        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
          return SSH_AUTH_ERROR;
        buffer[sizeof(buffer) - 1] = '\0';
        if ((ptr = strchr(buffer, '\n')) != NULL)
          *ptr = '\0';
        if (ssh_userauth_kbdint_setanswer(session, iprompt, buffer) < 0)
          return SSH_AUTH_ERROR;
        memset(buffer, 0, strlen(buffer));
      }
      else
      {
        char *ptr;
	printf("Enter password: ");
	scanf("%s", ptr);
	if (ptr == NULL) {
		fprintf(stderr, "Error reading password input\n");
		return SSH_AUTH_ERROR;
	}
        if (ssh_userauth_kbdint_setanswer(session, iprompt, ptr) < 0)
          return SSH_AUTH_ERROR;
      }
    }
    rc = ssh_userauth_kbdint(session, NULL, NULL);
  }
  return rc;
}

int authenticate_password(ssh_session session)
{
  char *password;
  int rc;
  printf("Enter password: ");
  scanf("%s", password);
  rc = ssh_userauth_password(session, NULL, password);
  if (rc == SSH_AUTH_ERROR)
  {
     fprintf(stderr, "Authentication failed: %s\n",
       ssh_get_error(session));
     return SSH_AUTH_ERROR;
  }

  return rc;
}

int authenticate_pubkey(ssh_session session)
{
  int rc;

  rc = ssh_userauth_publickey_auto(session, NULL, NULL);

  if (rc == SSH_AUTH_ERROR)
  {
     fprintf(stderr, "Authentication failed: %s\n",
       ssh_get_error(session));
     return SSH_AUTH_ERROR;
  }

  return rc;
}

int authenticate_none(ssh_session session)
{
  int rc;

  rc = ssh_userauth_none(session, NULL);
  return rc;
}

int display_banner(ssh_session session)
{
  int rc;
  char *banner;

/*
   * Does not work without calling ssh_userauth_none() first ***
   * That will be fixed ***
*/
  rc = ssh_userauth_none(session, NULL);
  if (rc == SSH_AUTH_ERROR)
    return rc;

  banner = ssh_get_issue_banner(session);
  if (banner)
  {
    printf("%s\n", banner);
    free(banner);
  }

  return rc;
}


int main(int argc , char *argv[])
{
    printf("You are running c version %ld\n", __STDC_VERSION__);
    // Initialize SSH variables
    ssh_session session;
    int rc;

    // Create SSH session
    session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Error creating SSH session\n");
        exit(EXIT_FAILURE);
    }

    // Set SSH options
    //ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity); //un-comment to debug auth
    ssh_options_set(session, SSH_OPTIONS_HOST, argv[1]);
    ssh_options_set(session, SSH_OPTIONS_USER, argv[2]);

  // Connect to SSH server
    rc = ssh_connect(session);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error connecting to SSH server: %s\n", ssh_get_error(session));
        ssh_free(session);
        exit(EXIT_FAILURE);
    }

    // Authenticate
    printf("Entering Authentication Phase...\n");
    rc = test_several_auth_methods(session);

    if (rc != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Error authenticating: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        exit(EXIT_FAILURE);
    }

    // Open channel for executing command
    ssh_channel channel;
    channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Error creating SSH channel\n");
        ssh_disconnect(session);
        ssh_free(session);
        exit(EXIT_FAILURE);
    }
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
    	    fprintf(stderr, "Error opening SSH channel: %s\n", ssh_get_error(session));
	    ssh_channel_free(channel);
	    ssh_disconnect(session);
	    ssh_free(session);
	    exit(EXIT_FAILURE);
    }

    // Execute command
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
	    fprintf(stderr, "Error opening SSH channel: %s\n", ssh_get_error(session));
	    ssh_channel_free(channel);
	    ssh_disconnect(session);
	    ssh_free(session);
	    exit(EXIT_FAILURE);
    }
    // Open File to get commands
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
    fclose(fp);

    printf("\nCommands from file: %s\n", commands);
    rc = ssh_channel_request_exec(channel, commands);
    if (rc != SSH_OK) {
        fprintf(stderr, "Error executing command: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        exit(EXIT_FAILURE);
    }


    // Read command output
    char buffer[256];
    int nbytes;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    // Close channel
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    // Disconnect and free SSH session
    ssh_disconnect(session);
    ssh_free(session);
    printf("\n\n");
    return 0;
}
