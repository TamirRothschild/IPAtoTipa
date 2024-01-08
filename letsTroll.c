#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define CHUNK_SIZE 4096

int main() {
    char inputFilename[MAX_FILENAME_LENGTH];
    char outputFilename[MAX_FILENAME_LENGTH];

    // Read input filename
    printf("Enter the input filename (including .ipa extension): ");
    fgets(inputFilename, MAX_FILENAME_LENGTH, stdin);
    inputFilename[strcspn(inputFilename, "\n")] = '\0';  // Remove newline if present

    // Verify that the input filename has the .ipa extension
    if (strstr(inputFilename, ".ipa") == NULL) {
        printf("Error: Input filename must have the .ipa extension.\n");
        return 1;
    }

    // Save the original filename without the extension
    char originalName[MAX_FILENAME_LENGTH];
    strncpy(originalName, inputFilename, MAX_FILENAME_LENGTH);
    strtok(originalName, ".");

    // Create the output filename with .tipa extension
    snprintf(outputFilename, MAX_FILENAME_LENGTH, "%s.tipa", originalName);

    // Open the input file
    FILE *inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file
    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    // Copy the entire content from the input file to the output file in chunks
    char *buffer = malloc(CHUNK_SIZE);
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, CHUNK_SIZE, inputFile)) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    // Free allocated memory
    free(buffer);

    printf("File successfully copied and renamed to %s\n", outputFilename);

    return 0;
}
