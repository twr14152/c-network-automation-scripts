#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libssh/libssh.h>

#define MAX_LINE 1024

int main(int argc, char * argv[]) {

  // Initialize SSH variables
  ssh_session session;
  int rc;

  // Create SSH session
  session = ssh_new();
  if (session == NULL) {
    fprintf(stderr, "Error creating SSH session\n");
    return 1;;
  }

  // Set SSH options
  //int verbosity = SSH_LOG_PROTOCOL;
  //ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, & verbosity); //Turn on for debugging
  ssh_options_set(session, SSH_OPTIONS_HOST, argv[1]); // hostname or ip
  ssh_options_set(session, SSH_OPTIONS_USER, argv[2]); // username

  // Connect to SSH server
  rc = ssh_connect(session);
  if (rc != SSH_OK) {
    fprintf(stderr, "Error connecting to SSH server: %s\n", ssh_get_error(session));
    ssh_free(session);
    return 1;;
  }

  // Authenticate with password
  rc = ssh_userauth_password(session, NULL, argv[3]); // password
  if (rc != SSH_AUTH_SUCCESS) {
    fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(session));
    ssh_disconnect(session);
    ssh_free(session);
    return 1;;
  }

  ssh_channel channel;
  channel = ssh_channel_new(session);
  if (channel == NULL) {
    fprintf(stderr, "Error creating SSH channel\n");
    ssh_disconnect(session);
    ssh_free(session);
    return 1;
  }

  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK) {
    fprintf(stderr, "Error opening SSH channel: %s\n", ssh_get_error(session));
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    return 1;;
  }

  if (ssh_channel_request_pty(channel) != SSH_OK) {
    fprintf(stderr, "PTY request failed: %s\n", ssh_get_error(session));
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    return 1;
  }

  if (ssh_channel_request_shell(channel) != SSH_OK) {
    fprintf(stderr, "Shell request failed: %s\n", ssh_get_error(session));
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    ssh_disconnect(session);
    ssh_free(session);
    return 1;
  }
 
  FILE *fp = fopen(argv[4], "r"); //filename
  if (!fp) {
    perror("Error opening command file");
    return 1;
  }

  char line[MAX_LINE];
  while (fgets(line, sizeof(line), fp)) {
    line[strcspn(line, "\r\n")] = 0;  // Strip newline
    if (strlen(line) == 0) continue;  // Skip empty lines
    strcat(line, "\n");  // Append newline to simulate Enter key
    ssh_channel_write(channel, line, strlen(line));
  }
  fclose(fp);
  // Send "exit" three times: or shell will hang
  ssh_channel_write(channel, "exit\n", strlen("exit\n"));
  ssh_channel_write(channel, "exit\n", strlen("exit\n"));
  ssh_channel_write(channel, "exit\n", strlen("exit\n"));

  // Read command output
  char buffer[2048];
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
