#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define MAX_RESPONSE_SIZE 100000

size_t write_response(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    strncat((char *)userp, (char *)contents, total_size);
    return total_size;
}

void pretty_print_json(const char *json_str) {
    cJSON *json = cJSON_Parse(json_str);
    if (!json) {
        printf("Error parsing JSON.\n");
        return;
    }

    char *pretty = cJSON_Print(json);
    if (pretty) {
        printf("Pretty JSON:\n%s\n", pretty);
        free(pretty);
    }

    cJSON_Delete(json);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <url> <cmd1> [cmd2] ...\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    char response[MAX_RESPONSE_SIZE] = {0};
    char json_data[8192] = {0};

    strcat(json_data, "{ \"jsonrpc\": \"2.0\", \"method\": \"runCmds\", \"params\": { \"version\": 1, \"cmds\": [");

    for (int i = 2; i < argc; ++i) {
        strcat(json_data, "\"");
        strcat(json_data, argv[i]);
        strcat(json_data, "\"");
        if (i < argc - 1) strcat(json_data, ",");
    }

    strcat(json_data, "], \"format\": \"json\" }, \"id\": \"1\" }");

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERPWD, "admin:admin");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            pretty_print_json(response);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
