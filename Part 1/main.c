/* main.c */
/* Vowel Counter - Main Program */

#include <stdio.h>
#include <stdlib.h>

int buffer_size;

// External function from vowel_counting.c
int countVowels(char* buf, int size);
void printAllStats(int vowelCount);

int main() {
    // Read buffer size
    if (scanf("%d\n", &buffer_size) != 1) {
        fprintf(stderr, "Error reading buffer size\n");
        return 1;
    }

    // Dynamically allocate buffer
    char* buffer = (char*)malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate buffer of size %d\n", buffer_size);
        return 1;
    }

    // Read the buffer content
    int bytesRead = fread(buffer, 1, buffer_size, stdin);
    if (bytesRead < buffer_size) {
        // Fill remaining with what we got
        buffer_size = bytesRead;
    }

    // Count vowels
    int count = countVowels(buffer, buffer_size);

    // Print all statistics
    printAllStats(count);
    
    // Free buffer
    free(buffer);

    return 0;
}
