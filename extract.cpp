#include <stdio.h>
#include <string.h>

// Structure to represent a word
struct Word {
    char text[50]; // Assuming a maximum word length of 50 characters
};

// Structure to represent a level
struct Level {
    int level;
    struct Word words[50]; // Assuming a maximum of 50 words per level
    int wordCount;
};

// Function to extract words for a given level
void extractWordsForLevel(const char *text, int targetLevel, struct Level *result) {
    // Initialize the result
    result->level = targetLevel;
    result->wordCount = 0;

    // Start parsing the text
    const char *levelStart = strstr(text, "\"level\": ");
    while (levelStart != NULL) {
        int level;
        if (sscanf(levelStart, "\"level\": %d", &level) == 1) {
            if (level == targetLevel) {
                const char *wordsStart = strstr(levelStart, "\"words\": [");
                if (wordsStart != NULL) {
                    wordsStart += strlen("\"words\": [");

                    const char *wordsEnd = strchr(wordsStart, ']');
                    if (wordsEnd != NULL) {
                        const char *wordStart = wordsStart;
                        while (wordStart < wordsEnd) {
                            if (*wordStart == '"') {
                                wordStart++;
                                const char *wordEnd = strchr(wordStart, '"');
                                if (wordEnd != NULL) {
                                    int wordLength = wordEnd - wordStart;
                                    strncpy(result->words[result->wordCount].text, wordStart, wordLength);
                                    result->words[result->wordCount].text[wordLength] = '\0';
                                    result->wordCount++;
                                    wordStart = wordEnd + 1;
                                }
                            } else {
                                wordStart++;
                            }
                        }
                        break;
                    }
                }
            }
        }
        levelStart = strstr(levelStart + 1, "\"level\": ");
    }
}

int main() {
    // The text you provided
    const char *text = "Your text here..."; // Replace with your text

    // Level to extract words from
    int targetLevel = 1; // Change this to the desired level

    // Create a Level struct to hold the result
    struct Level result;

    // Extract words for the target level
    extractWordsForLevel(text, targetLevel, &result);

    // Display the words and their lengths for the target level
    printf("Words at level %d:\n", result.level);
    for (int i = 0; i < result.wordCount; i++) {
        printf("Word: %s, Length: %lu\n", result.words[i].text, strlen(result.words[i].text));
    }

    return 0;
}
