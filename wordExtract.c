#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* word;
    int length;
} WordInfo;

WordInfo* getWordsForLevel(const char* filename, int targetLevel, int* wordCount, int* totalWordCount, int* levelCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        *wordCount = 0;
        *totalWordCount = 0;
        *levelCount = 0;
        return NULL;
    }

    char line[1024];
    char buffer[1024] = "";
    WordInfo* wordInfos = NULL;
    int count = 0;
    int totalWords = 0;
    int levels = 0;

    while (fgets(line, sizeof(line), file)) {
        strcat(buffer, line);
        if (strstr(line, "]")) {
            char *start = strstr(buffer, "\"level\": ");
            if (start) {
                int level = atoi(start + 9);
                levels = level + 1; // Update the level count for all levels
                start = strstr(buffer, "\"words\": [");
                if (start) {
                    start += 11;
                    char *end = strstr(start, "]");
                    if (end) {
                        *end = '\0';
                        char *word = strtok(start, "\"[], \n\r\t");
                        while (word) {
                            if (strlen(word) > 0) {
                                totalWords++; // Increment the total word count
                                if (level == targetLevel) {
                                    count++;
                                    wordInfos = (WordInfo*)realloc(wordInfos, count * sizeof(WordInfo));
                                    wordInfos[count - 1].word = strdup(word);
                                    wordInfos[count - 1].length = strlen(word);
                                }
                            }
                            word = strtok(NULL, "\"[], \n\r\t");
                        }
                    }
                }
            }
            buffer[0] = '\0';
        }
    }

    fclose(file);
    *wordCount = count;
    *totalWordCount = totalWords;
    *levelCount = levels;
    return wordInfos;
}

/**int main() {
    const char* filename = "data.txt";
    int targetLevel = 1;
    int wordCount;
    int totalWordCount;
    int levelCount;
    WordInfo* wordInfos = getWordsForLevel(filename, targetLevel, &wordCount, &totalWordCount, &levelCount);

    if (wordInfos) {
        printf("Total Word Count: %d\n", totalWordCount);
        printf("Number of Levels: %d\n", levelCount);
        for (int i = 0; i < wordCount; i++) {
            printf("Word %d: %s, Length: %d\n", i + 1, wordInfos[i].word, wordInfos[i].length);
            free(wordInfos[i].word);
        }
        free(wordInfos);
    } else {
        printf("No words found for the specified level.\n");
    }

    return 0;
}
*/