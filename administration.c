#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEVELS 3
#define MAX_WORDS 5
#define MAX_WORD_LENGTH 20
#define MAX_LINE_LENGTH 1000

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

void createFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file for writing.\n");
        return;
    }

   

    fclose(file);
}

void loadData(const char* filename, struct Level levels[], int* levelCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file for reading. Creating a new file.\n");
        createFile(filename);
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




// Function to change a word in a specific level
void changeWordInLevelAndUpdateFile(const char* filename, struct Level levels[], int levelCount) {
    FILE* inputFile, *tempFile;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+");

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to change a word in (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }

    struct Level* level = &levels[selectedLevel - 1];

    char oldWord[MAX_WORD_LENGTH];
    char newWord[MAX_WORD_LENGTH];
    int requiredLength = (selectedLevel == 1) ? 3 : (selectedLevel == 2) ? 6 : (selectedLevel == 3) ? 9 : 0;
    do{
printf("\n Enter the old word: ");
    scanf("%s", oldWord);
    if(strlen(oldWord) != requiredLength) printf("\nthe length of the word should be %d",requiredLength);
    }while(strlen(oldWord) != requiredLength);
    

    char line[MAX_LINE_LENGTH];
    char* token;
    int currentLevel = 0;
 int found = 0;
    for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], oldWord) == 0) {
            found = 1;
            do{
printf("\n Enter the old word: ");
    scanf("%s", newWord);
    if(strlen(newWord) != requiredLength) printf("\nthe length of the word should be %d",requiredLength);
    }while(strlen(newWord) != requiredLength);
            // Change the word in the in-memory data structure
            strcpy(level->words[i], newWord);
            // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    if (strcmp(token, oldWord) == 0) {
                        // Replace the old word with the new word
                        fprintf(tempFile, "%s,", newWord);
                    } else {
                        fprintf(tempFile, "%s,", token);
                    }
                }

                // Check if there were words in the list
                if (ftell(tempFile) > 0) {
                    // Remove the trailing comma
                    fseek(tempFile, -1, SEEK_CUR);
                }

                // Close the brackets
                fprintf(tempFile, "]\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
    }
            break;
        }
    }
    

   
    if (!found) {
        printf("Word not found in the selected level.\n");
        fclose(inputFile);
    fclose(tempFile);
    remove("temp.txt");

    } else {
        printf("Word '%s' changed to '%s' in 'level%d'.\n", oldWord, newWord, selectedLevel);
         // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
    }

   
    found =0;
}
// Function to change a word in a specific level
/*void changeWordInLevelAndUpdateFile(const char* filename, struct Level levels[], int levelCount) {
    FILE* inputFile, *tempFile;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+");

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to change a word in (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }

    struct Level* level = &levels[selectedLevel - 1];

    char oldWord[MAX_WORD_LENGTH];
    char newWord[MAX_WORD_LENGTH];
    printf("Enter the word to change: ");
    scanf("%s", oldWord);
    

    char line[MAX_LINE_LENGTH];
    char* token;
    int currentLevel = 0;
 int found = 0;
    for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], oldWord) == 0) {
            found = 1;
            printf("Enter the new word: ");
    scanf("%s", newWord);
            // Change the word in the in-memory data structure
            strcpy(level->words[i], newWord);
            // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    if (strcmp(token, oldWord) == 0) {
                        // Replace the old word with the new word
                        fprintf(tempFile, "%s,", newWord);
                    } else {
                        fprintf(tempFile, "%s,", token);
                    }
                }

                // Check if there were words in the list
                if (ftell(tempFile) > 0) {
                    // Remove the trailing comma
                    fseek(tempFile, -1, SEEK_CUR);
                }

                // Close the brackets
                fprintf(tempFile, "]\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
    }
            break;
        }
    }
    

   
    if (!found) {
        printf("Word not found in the selected level.\n");
        fclose(inputFile);
    fclose(tempFile);
    remove("temp.txt");
    } else {
        printf("Word '%s' changed to '%s' in 'level%d'.\n", oldWord, newWord, selectedLevel);
         // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
    }

   
    found =0;
}*/
/*void deleteWordAndUpdateFile(const char *filename,struct Level levels[], int levelCount) {
    FILE *inputFile, *tempFile;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+"); // Open a temporary file for reading and writing

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to delete a word from (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }

    char wordToDelete[MAX_WORD_LENGTH];
    printf("Enter the word to delete from 'level%d': ", selectedLevel);
    scanf("%s", wordToDelete);

    char line[MAX_LINE_LENGTH];
    char *token;
    int currentLevel = 0;

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    // Skip the specified wordToDelete
                    if (strcmp(token, wordToDelete) != 0) {
                        fprintf(tempFile, "%s,", token);
                    }
                }

                // Check if there were words in the list
                if (ftell(tempFile) > 0) {
                    // Remove the trailing comma
                    fseek(tempFile, -1, SEEK_CUR);
                    fprintf(tempFile, "]");
                } else {
                    // No words in the list, just close the brackets
                    fprintf(tempFile, "[]");
                }

                fprintf(tempFile, "\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
    }
    struct Level* level = &levels[selectedLevel - 1];
     for (int i = 0; i < level->wordCount; ++i) {
        if (strcmp(level->words[i], wordToDelete) == 0) {
            // Found the word, now shift the remaining elements to the left
            for (int j = i; j < level->wordCount - 1; ++j) {
                strcpy(level->words[j], level->words[j + 1]);
            }
            // Decrement wordCount since we removed a word
            level->wordCount--;
            break;  // Exit the loop since we found and deleted the word
        }
    }

    printf("Word '%s' deleted from 'level%d'.\n", wordToDelete, selectedLevel);

    // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
}


*/


void deleteWordAndUpdateFile(const char *filename,struct Level levels[], int levelCount) {
    FILE *inputFile, *tempFile;
    char line[MAX_LINE_LENGTH];
    char *token;
    int currentLevel = 0;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+"); // Open a temporary file for reading and writing

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to delete a word from (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }

    char wordToDelete[MAX_WORD_LENGTH];
    struct Level* level = &levels[selectedLevel - 1];
    int requiredLength = (selectedLevel == 1) ? 3 : (selectedLevel == 2) ? 6 : (selectedLevel == 3) ? 9 : 0;
    int found =0;
    do{
    printf("\nEnter the word to delete from 'level%d': ", selectedLevel);
    scanf("%s", wordToDelete);
    if(strlen(wordToDelete) != requiredLength) printf("\nthe length of the word should be %d",requiredLength);
    }while(strlen(wordToDelete) != requiredLength);
 for (int i = 0; i < level->wordCount; i++) {
        if (strcmp(level->words[i], wordToDelete) == 0) {
            found =1;
    

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    // Skip the specified wordToDelete
                    if (strcmp(token, wordToDelete) != 0) {
                        fprintf(tempFile, "%s,", token);
                    }
                }

                // Check if there were words in the list
                if (ftell(tempFile) > 0) {
                    // Remove the trailing comma
                    fseek(tempFile, -1, SEEK_CUR);
                    fprintf(tempFile, "]");
                } else {
                    // No words in the list, just close the brackets
                    fprintf(tempFile, "[]");
                }

                fprintf(tempFile, "\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
    }
    struct Level* level = &levels[selectedLevel - 1];
     for (int i = 0; i < level->wordCount; ++i) {
        if (strcmp(level->words[i], wordToDelete) == 0) {
            
            // Found the word, now shift the remaining elements to the left
            for (int j = i; j < level->wordCount; ++j) {
                printf("word : %s\n",level->words[j]);
                strcpy(level->words[j], level->words[j + 1]);
            }
            // Decrement wordCount since we removed a word
            level->wordCount--;
            break;  // Exit the loop since we found and deleted the word
        }
    }

    printf("Word '%s' deleted from 'level%d'.\n", wordToDelete, selectedLevel);

    // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
        }
         
}
if (!found) {
        printf("Word not found in the selected level.\n");
    } 
}

/*void addWordAndUpdateFile(const char* filename, struct Level levels[], int levelCount) {
    FILE* inputFile, *tempFile;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+");

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to add a word to (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }
    int requiredLength = (selectedLevel == 1) ? 3 : (selectedLevel == 2) ? 6 : (selectedLevel == 3) ? 9 : 0;

    char newWord[MAX_WORD_LENGTH];
    
  
    struct Level* level = &levels[selectedLevel - 1];
    if (level->wordCount < MAX_WORDS) {
        do{
printf("Enter the word to add to 'level%d': ", selectedLevel);
    scanf("%s", &newWord);
    if(strlen(newWord) != requiredLength) printf("\nthe length of the word should be %d",requiredLength);
    }while(strlen(newWord) != requiredLength);
        // Add the new word to the in-memory data structure
        strcpy(level->words[level->wordCount], newWord);
        level->wordCount++;
        printf("Word '%s' added to 'level%d'.\n", newWord, selectedLevel);
        char line[MAX_LINE_LENGTH];
    char* token;
    int currentLevel = 0;

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                int firstWord = 1;
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    if (!firstWord) {
                        fprintf(tempFile, ",");
                    } else {
                        firstWord = 0;
                    }
                    fprintf(tempFile, "%s", token);
                }

                // Write the new word to the temporary file
                fprintf(tempFile, ",%s", newWord);

                // Close the brackets
                fprintf(tempFile, "]\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
        // Close the files
    
    }

    

    // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
    } else {
        printf("Cannot add more words to 'level%d'. Maximum word count reached.\n", selectedLevel);
        // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
   // remove(filename);
    remove("temp.txt");
    }
    
}*/
void addWordAndUpdateFile(const char* filename, struct Level levels[], int levelCount) {
    FILE* inputFile, *tempFile;
    inputFile = fopen(filename, "r");
    tempFile = fopen("temp.txt", "w+");

    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int selectedLevel;

    printf("Choose a level to add a word to (1-3): ");
    scanf("%d", &selectedLevel);

    if (selectedLevel < 1 || selectedLevel > 3) {
        printf("Invalid level number.\n");
        exit(1);
    }
struct Level* level = &levels[selectedLevel - 1];
    if (level->wordCount < MAX_WORDS) {
    char newWord[MAX_WORD_LENGTH];
        int requiredLength = (selectedLevel == 1) ? 3 : (selectedLevel == 2) ? 6 : (selectedLevel == 3) ? 9 : 0;
  do{
printf("Enter the word to add to 'level%d': ", selectedLevel);
    scanf("%s", &newWord);
    if(strlen(newWord) != requiredLength) printf("\nthe length of the word should be %d",requiredLength);
    }while(strlen(newWord) != requiredLength);

    char line[MAX_LINE_LENGTH];
    char* token;
    int currentLevel = 0;

    // Read the file line by line
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Check if the line contains "levelX:" (where X is the selected level)
        if (strstr(line, "level") != NULL) {
            currentLevel++;

            // Check if it's the selected level
            if (currentLevel == selectedLevel) {
                // Tokenize the line to get individual words
                token = strtok(line, ":[], \n");

                // Write "levelX:" to the temporary file
                fprintf(tempFile, "%s:[", token);

                // Iterate through the tokens and write each word
                int firstWord = 1;
                while ((token = strtok(NULL, ":[], \n")) != NULL) {
                    if (!firstWord) {
                        fprintf(tempFile, ",");
                    } else {
                        firstWord = 0;
                    }
                    fprintf(tempFile, "%s", token);
                }

                // Write the new word to the temporary file
                fprintf(tempFile, ",%s", newWord);

                // Close the brackets
                fprintf(tempFile, "]\n");
            } else {
                // If it's not the selected level, write it unchanged to the temporary file
                fprintf(tempFile, "%s", line);
            }
        } else {
            // If the line doesn't contain "levelX:", write it unchanged to the temporary file
            fprintf(tempFile, "%s", line);
        }
    }
     // Add the new word to the in-memory data structure
        strcpy(level->words[level->wordCount], newWord);
        level->wordCount++;
        printf("Word '%s' added to 'level%d'.\n", newWord, selectedLevel);
        // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove(filename);
    rename("temp.txt", filename);
    }else {
        printf("Cannot add more words to 'level%d'. Maximum word count reached.\n", selectedLevel);
        fclose(inputFile);
    fclose(tempFile);

    
    remove("temp.txt");
    }

    

    
}
