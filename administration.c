#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEVELS 3
#define MAX_WORDS 3
#define MAX_WORD_LENGTH 20

// Structure to store the data
struct Level {
    int level;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount;
};
int checkMinimumLevels(int levelCount) {
    if (levelCount!=MAX_LEVELS ) {
        printf("Cannot proceed. Minimum of 1 levels or maximum of 3 are required. %d\n",levelCount);
        return 0;
    }
    return 1;
}
// Function to check if a level has at least 5 words
int checkMinimumWords(struct Level* level) {
    if (level->wordCount !=MAX_WORDS) {
        printf("Level %d must have at least 2 words and max 3 words. Please add or delete words.\n", level->level);
        return 0;
    }
    return 1;
}

int existLevel(struct Level levels[], int levelCount) {
    // Check if each level has at least 5 words
    if(!checkMinimumLevels(levelCount)){
        printf("Cannot proceed. Minimum 3 levels are required.\n");
        return 0;
    }

    for (int i = 0; i < levelCount; i++) {
        if (!checkMinimumWords(&levels[i])) {
            printf("Cannot proceed. Minimum 5 words are required in each level.\n");
            return 0;
        }
    }
    return 1;
}

void saveData(const char* filename, struct Level levels[], int levelCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file for writing.\n");
        return;
    }

    for (int i = 0; i < levelCount; i++) {
        fprintf(file, "level %d :[", levels[i].level);

        for (int j = 0; j < levels[i].wordCount; j++) {
            fprintf(file, "%s", levels[i].words[j]);
            if (j < levels[i].wordCount - 1) {
                fprintf(file, ",");
            }
        }

        fprintf(file, "]\n");
    }

    fclose(file);
}

void loadData(const char* filename, struct Level levels[], int* levelCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file for reading. Creating a new file.\n");
        saveData(filename, levels, *levelCount);
        return;
    }

    *levelCount = 0;

    char buffer[2048];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int level;
        char words[MAX_WORDS][MAX_WORD_LENGTH];

        if (sscanf(buffer, "level %d :[ %[^]]", &level, words[0]) == 2) {
            struct Level newLevel;
            newLevel.level = level;
            newLevel.wordCount = 0;

            // Tokenize the words
            char* token = strtok(words[0], ",");
            while (token != NULL && newLevel.wordCount < MAX_WORDS) {
                strcpy(newLevel.words[newLevel.wordCount], token);
                newLevel.wordCount++;
                token = strtok(NULL, ",");
            }

            levels[*levelCount] = newLevel;
            (*levelCount)++;
        }
    }

    fclose(file);
}

void createLevel(struct Level levels[], int* levelCount) {
    if (*levelCount < MAX_LEVELS) {
        struct Level newLevel;
        newLevel.level = *levelCount + 1;
        newLevel.wordCount = 0;

        // Initialize the words array to empty strings
        for (int i = 0; i < MAX_WORDS; i++) {
            strcpy(newLevel.words[i], "");
        }

        levels[*levelCount] = newLevel;
        (*levelCount)++;
    } else {
        printf("Maximum number of levels reached. Cannot create a new level.\n");
    }
}
// Function to add a word to a specific level after checking if it exists
void addWordToLevel(struct Level levels[], int levelCount) {
    if (levelCount == 0) {
        printf("No levels exist. Please create a level first.\n");
        return;
    }

    int selectedLevel;
    printf("Choose a level to add the word (1-%d): ", levelCount);
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > levelCount) {
        printf("Invalid level number.\n");
        return;
    }

    struct Level* level = &levels[selectedLevel - 1];

    if (level->wordCount >= MAX_WORDS) {
        printf("The selected level is full. Cannot add more words.\n");
        return;
    }

    char word[MAX_WORD_LENGTH];
    printf("Enter the word to add: ");
    scanf("%s", word);

    // Check if the word already exists in the level
    for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], word) == 0) {
            printf("Word '%s' already exists in Level %d. Cannot add it again.\n", word, level->level);
            return;
        }
    }

    // If the word doesn't exist, add it
    strcpy(level->words[level->wordCount], word);
    level->wordCount++;
    printf("Word '%s' has been added to Level %d.\n", word, level->level);
}

// Function to delete a word from a specific level
void deleteWordFromLevel(struct Level levels[], int levelCount) {
    if (levelCount == 0) {
        printf("No levels exist. Please create a level first.\n");
        return;
    }

    int selectedLevel;
    printf("Choose a level to delete a word from (1-%d): ", levelCount);
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > levelCount) {
        printf("Invalid level number.\n");
        return;
    }

    struct Level* level = &levels[selectedLevel - 1];

    char word[MAX_WORD_LENGTH];
    printf("Enter the word to delete: ");
    scanf("%s", word);

    int found = 0;
    for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], word) == 0) {
            found = 1;
            for (int j = i; j < level->wordCount - 1; j++) {
                strcpy(level->words[j], level->words[j + 1]);
            }
            level->wordCount--;
            break;
        }
    }
    if (!found) {
        printf("Word not found in the selected level.\n");
    }
}

// Function to change a word in a specific level
void changeWordInLevel(struct Level levels[], int levelCount) {
    if (levelCount == 0) {
        printf("No levels exist. Please create a level first.\n");
        return;
    }

    int selectedLevel;
    printf("Choose a level to change a word in (1-%d): ", levelCount);
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > levelCount) {
        printf("Invalid level number.\n");
        return;
    }

    struct Level* level = &levels[selectedLevel - 1];

    char oldWord[MAX_WORD_LENGTH];
    char newWord[MAX_WORD_LENGTH];
    printf("Enter the word to change: ");
    scanf("%s", oldWord);
    printf("Enter the new word: ");
    scanf("%s", newWord);

    int found = 0;
    for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], oldWord) == 0) {
            found = 1;
            strcpy(level->words[i], newWord); // Change the word
            break;
        }
    }
    if (!found) {
        printf("Word not found in the selected level.\n");
    }
}


void deleteLevel(struct Level levels[], int* levelCount) {
    if (*levelCount == 0) {
        printf("No levels exist. Please create a level first.\n");
        return;
    }

    int selectedLevel;
    printf("Choose a level to delete (1-%d): ", *levelCount);
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > *levelCount) {
        printf("Invalid level number.\n");
        return;
    }

    printf("Level %d has been deleted.\n", levels[selectedLevel - 1].level);

    // Remove the selected level by shifting elements
    for (int i = selectedLevel - 1; i < *levelCount - 1; i++) {
        levels[i] = levels[i + 1];
    }

    (*levelCount)--;
    // Adjust the level numbers after the deletion
    for (int i = 0; i < *levelCount; i++) {
        levels[i].level = i + 1;
    }
}


