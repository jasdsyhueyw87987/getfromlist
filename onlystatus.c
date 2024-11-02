#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strcspn
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    // Check if a file path is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        fclose(file);
        return 1;
    }

    // Define a buffer to store the full URL
    char url[256];
    char path[128];
    long response_code; // Variable to store the HTTP status code

    // Loop through each line in the file
    while (fgets(path, sizeof(path), file)) {
        // Remove any newline character at the end of the path
        path[strcspn(path, "\n")] = 0;

        // Create the full URL using snprintf
        snprintf(url, sizeof(url), "https://acas.edu.bd/%s", path);

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set to not download the body
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

        // Set custom headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "origin: https://acas.edu.bd");
        headers = curl_slist_append(headers, "referer: https://acas.edu.bd/");
        headers = curl_slist_append(headers, "sec-ch-ua: \"Chromium\";v=\"130\", \"Brave\";v=\"130\", \"Not?A_Brand\";v=\"99\"");
        headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
        headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
        headers = curl_slist_append(headers, "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0.0.0 Safari/537.36");

        // Attach headers to the request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed for %s: %s\n", url, curl_easy_strerror(res));
        } else {
            // Get the HTTP response code
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("URL: %s, Status Code: %ld\n", url, response_code);
        }

        // Free the headers for the next request
        curl_slist_free_all(headers);
    }

    // Clean up
    curl_easy_cleanup(curl);
    fclose(file);

    return 0;
}
