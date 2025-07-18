#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) 
{
    const char *host = argv[1];
    const char *user = argv[2];
    const char *password = argv[3];
    const char *file = argv[4];

    ssh_session session = ssh_new();
    if (session == NULL) {
        fprintf(stderr, "Failed to create SSH session\n");
        return EXIT_FAILURE;
    }
    //Uncomment for debugging
    //int verbosity = SSH_LOG_PROTOCOL;
    //ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, & verbosity); 
    ssh_options_set(session, SSH_OPTIONS_HOST, host);
    ssh_options_set(session, SSH_OPTIONS_USER, user);

    if (ssh_connect(session) != SSH_OK) {
        fprintf(stderr, "Connection failed: %s\n", ssh_get_error(session));
        ssh_free(session);
        return EXIT_FAILURE;
    }

    if (ssh_userauth_password(session, NULL, password) != SSH_AUTH_SUCCESS) {
        fprintf(stderr, "Auth failed: %s\n", ssh_get_error(session));
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    // Open a new channel
    ssh_channel channel = ssh_channel_new(session);
    if (channel == NULL) {
        fprintf(stderr, "Channel creation failed\n");
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    if (ssh_channel_open_session(channel) != SSH_OK) {
        fprintf(stderr, "Channel open failed: %s\n", ssh_get_error(session));
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    if (ssh_channel_request_pty(channel) != SSH_OK) {
        fprintf(stderr, "PTY request failed: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    if (ssh_channel_request_shell(channel) != SSH_OK) {
        fprintf(stderr, "Shell request failed: %s\n", ssh_get_error(session));
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(session);
        ssh_free(session);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Error opening command file");
        return EXIT_FAILURE;
    }

    char line[1024];
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


    // Read and print output
    char buffer[256];
    int nbytes;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, nbytes, stdout);
    }

    // Close and cleanup
    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    ssh_disconnect(session);
    ssh_free(session);
    
    return EXIT_SUCCESS;
}
