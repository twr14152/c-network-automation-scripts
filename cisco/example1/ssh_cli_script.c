#include <stdio.h>
#include <stdlib.h>
#include <libssh/libssh.h>


int main(int argc, char **argv) {
  // loop to run through commands
  for (int i = 4; i < argc; i++) {

    printf("\nCommand: %s\n", argv[i]);

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
    ssh_options_set(session, SSH_OPTIONS_HOST, argv[1]);
    ssh_options_set(session, SSH_OPTIONS_USER, argv[2]); // username 

    // Connect to SSH server
    rc = ssh_connect(session);
    if (rc != SSH_OK) {
      fprintf(stderr, "Error connecting to SSH server: %s\n", ssh_get_error(session));
      ssh_free(session);
      exit(EXIT_FAILURE);
    }

    // Authenticate with password
    rc = ssh_userauth_password(session, NULL, argv[3]); // password
    if (rc != SSH_AUTH_SUCCESS) {
      fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(session));
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

    // Execute command
    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK) {
      fprintf(stderr, "Error opening SSH channel: %s\n", ssh_get_error(session));
      ssh_channel_free(channel);
      ssh_disconnect(session);
      ssh_free(session);
      exit(EXIT_FAILURE);
    }

    //This is where you loop through commands
    rc = ssh_channel_request_exec(channel, argv[i]);
    if (rc != SSH_OK) {
      fprintf(stderr, "Error executing command: %s\n", ssh_get_error(session));
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      ssh_disconnect(session);
      ssh_free(session);
      exit(EXIT_FAILURE);
    }

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
  } //End of loop
  printf("\n\n");
  return 0;
}
