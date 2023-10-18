#include <stdio.h>
#include <string.h>
#include "administration.c"


int main() {
//variables declaration
    struct Level levels[MAX_LEVELS];
    int levelCount = 0;
    char c[] = "hello";// predifined word
    int test[]={0,0,0,0,0};// Array to store the scoring
    char word[6];// Player's guess
    int used[]={0,0,0,0,0};// Array to track already matched characters
    //int confirm;
    //welcome screen
 printf("   _____   _______________________ ___  _________\n");
    printf("  /     \\  \\_____  \\__    ___/    |   \\/   _____/\n");
    printf(" /  \\ /  \\  /   |   \\|    |  |    |   /\\_____  \\\n");
    printf("/    Y    \\/    |    \\    |  |    |  / /        \\\n");
    printf("\\____|__  /\\_______  /____|  |______/ /_______  /\n");
    printf("        \\/         \\/                         \\/\n");
    printf("Made by Ahmed Omrani\n");
    // Ask the user if they are a player or super user
    printf("Are you a player or a super user? (1 for player, 2 for super user): ");
    int userRole;
    scanf("%d", &userRole);

    if (userRole == 1) {
        // Player's code
        printf("Welcome, player!\n");
   do{
    
//ask the user to enter a word
do{
        int test[] = {0, 0, 0, 0, 0}; // Array to store the scoring
        int used[] = {0, 0, 0, 0, 0}; // Array to track already matched characters
  printf("[+] Enter your guess for the word (5 letters):");
    scanf("%s",&word);
}while(strlen(word)!=5);
   
    // test the similiarity and if the characters are there
    for(int i = 0; i<5;i++){
      if(word[i]==c[i]){
        printf(" word of i is %c",word[i]);
      printf(" \n%c  and %c \n",word[i],c[i]);
        test[i]=1;
        used[i]=1;
      }
    }
    for(int i = 0; i<5;i++){
      printf("\n %d \t \n",used[i]);
    }
     for (int i = 0; i < 5; i++) {
        if (test[i] == 0) { // Only check characters not marked as '1'
            for (int j = 0; j < 5; j++) {
                if (used[j] == 0 && word[i] == c[j]) {
                    test[i] = 2;
                    used[j] = 1; // Mark the character as used
                    break;
                }
            }
        }
    }
  
      
//printf("\nFinish\n");
printf("\n");
    for (int i = 0;i<5; i++) {
        printf("%d",test[i]);
    }
printf("\n");
int all_correct = 1; // Assume all elements are correct
        for (int i = 0; i < 5; i++) {
            if (test[i] != 1) {
                all_correct = 0; // Not all elements are correct
                break;
            }
        }

        // Check if the win condition is met
        if (all_correct) {
            printf("Congratulations! You guessed the word.\n");
            break;
        }

 }while (1);
    }
    else if (userRole == 2) {
        printf("Enter the super user secret code: ");
        char secretCode[20]; // Adjust the size as needed
        scanf("%s", secretCode);

        // Check the secret code (example code is "superuser123")
        if (strcmp(secretCode, "superuser123") == 0) {
            printf("Welcome, super user!\n");
             loadData("data.txt", levels, &levelCount);

    while (1) {
        int choice;
        printf("Options:\n");
        printf("1. Create a new level\n");
        printf("2. Add word to a level\n");
        printf("3. Delete word from a level\n");
        printf("4. Change word in a level\n");
        printf("5. Delete a level\n");
        printf("6. Save data to file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createLevel(levels, &levelCount);
                break;
            case 2:
                addWordToLevel(levels, levelCount);
                break;
            case 3:
                deleteWordFromLevel(levels, levelCount);
                break;
            case 4:
                changeWordInLevel(levels, levelCount);
                break;
            case 5:
                deleteLevel(levels, &levelCount);
                break;
            case 6:
                saveData("data.txt", levels, levelCount);
                printf("Data saved to file.\n");
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
        } else {
            printf("Invalid secret code. Access denied.\n");
        }
    } else {
        printf("Invalid role. Please choose 1 for player or 2 for super user.\n");
    }
 return 0;


}
