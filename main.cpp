#include <stdio.h>
#include <string.h>
#include "administration.c"
#include "wordextract.c"
#include "changeColors.c"
#include "automaticGenration.c"

int main() {
//variables declaration
    const char* filename = "data.txt";
    modifyAndOverwriteFile();
    int targetLevel = 1;
    int wordCount;
    int totalWordCount;
    int levelCount;
    WordInfo* wordInfos = getWordsForLevel(filename, targetLevel, &wordCount, &totalWordCount, &levelCount);
    char* formattedWord ;
    struct Level levels[MAX_LEVELS];
    char *c;// predifined word
    int *test;// Array to store the scoring
    char *word;// Player's guess
    int *used;// Array to track already matched characters
    int advance;
    int adminExsit;
    int initialScore=5;
    int playerScore=0;
    int totalScore=0;
    int skip=1;
    int hint;
    //int confirm;
    //welcome screen
    menuMain:;
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

    if (userRole == 2) {
        playermode:;
        // Player's code
        printf("Welcome, player!\n");
        //printf("%s this is the word",wordInfos[1].word);
         for(int k = 1 ; k<levelCount;k++){
            wordInfos = getWordsForLevel(filename, k, &wordCount, &totalWordCount, &levelCount);
            for(int w=0;w<wordCount;w++){
            
            //printf("word count : %d",wordCount);
            initialScore=5;

            c = (char*)malloc(wordInfos[w].length*sizeof(char));
            word =(char*)malloc(wordInfos[w].length*sizeof(char));
            c=wordInfos[w].word;
           // printf("%s",c);
   do{
    

    


int* test;
int *used;
        test = (int*)malloc(wordInfos[w].length*sizeof(int));
        used = (int*)malloc(wordInfos[w].length*sizeof(int));
        
       
        for(int a = 0; a<wordInfos[w].length;a++){
            *(test+a) = 0;
            *(used+a) = 0;
        }
      //  int test[] = {0, 0, 0, 0, 0}; // Array to store the scoring
        //int used[] = {0, 0, 0, 0, 0}; // Array to track already matched characters
        while (1) {
        printf("Do you want a hint for the first character? [1: yes / 0: no]: ");
        scanf("%d", &hint);

        if (hint == 0 || hint == 1) {
            break;
        } else {
            printf("Invalid input. Please enter either 1 or 0.\n");
        }
    }
         /* do {
        printf("Do you want a hint for the first character? [1: yes / 0: no]: ");
        scanf("%d", &hint);

        if (hint != 0 && hint != 1) {
            printf("Invalid input. Please enter either 1 or 0.\n");
        }
        

    } while (hint != 0 && hint != 1);*/
            if(hint==1){
                printf("\n hint : %c \n",c[0]);
            }
          //ask the user to enter a word
          do {
    printf("[+] Enter your guess for the word (%d letters): ", wordInfos[w].length);
    scanf("%s", word);

    if (strlen(word) == wordInfos[w].length) {
        break; 
        // Go back to the beginning of the loop
    }
        printf("Word length does not match. Please enter a word with %d letters.\n", wordInfos[w].length);

    // The rest of your code for checking the guess and updating the game logic
} while (1);
   
    // test the similiarity and if the characters are there
    for(int i = 0; i<wordInfos[w].length;i++){
      if(word[i]==c[i]){
        
        test[i]=1;
        used[i]=1;
      }
    }
   // for(int i = 0; i<5;i++){
     // printf("\n %d \t \n",used[i]);
    //}
     for (int i = 0; i < wordInfos[w].length; i++) {
        if (test[i] == 0) { // Only check characters not marked as '1'
            for (int j = 0; j <wordInfos[w].length; j++) {
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
char* formattedWord = formatWordWithColors(word, test, wordInfos[w].length);
printf("%s%s\n", formattedWord, RESET);
printf("%s",WHITE);

    /*for (int i = 0;i<wordInfos[w].length; i++) {
        printf("%d",test[i]);
    }*/
printf("\n");
int all_correct = 1; // Assume all elements are correct
        for (int i = 0; i < wordInfos[w].length; i++) {
            if (test[i] != 1) {
                all_correct = 0; // Not all elements are correct
                if(initialScore==1){
                initialScore=0;
                goto nextWord;
                }
                initialScore-=1;
                break;
                
            }
        }

        // Check if the win condition is met
        if (all_correct) {
            //printf("%d",wordCount);
           // printf("target level :%d",targetLevel);
            playerScore+=initialScore;
            
            nextWord:;

            printf("playersore :%d  \n",playerScore);
            //printf("%d  w= %d \n",w==4 && playerScore/19 <1,w);
            //printf("wordcount %d",w==wordCount-1 && playerScore/19 <1);
            if(w==wordCount-1 && playerScore/19 <1){printf("game over ");printf("playerScore: %d",playerScore); goto end;}
            else if(w==wordCount-1 && playerScore/19 >=1) {printf("Congratulations! passed level %d\n",k); totalScore= playerScore;playerScore=0;}
            if(w==wordCount-1 && k==levelCount-1){
                printf("Congratulations! you won. Your score is : %d\n",totalScore);
            }

            
            if(w==wordCount){
                printf("playerScore: %d",playerScore);
                break;
            }
            if(initialScore ==0){
            printf("you didn't guess the word. Do you want to continue?\n");
            //printf("playerScore: %d",playerScore);
            scanf("%d",&advance);
            if(advance==0)goto end;
            }else{printf("Congratulations! You guessed the word. Do you want to continue?\n");

            //printf("playerScore: %d",playerScore);
            scanf("%d",&advance);
            if(advance==0)goto end;}
            
            

            //printf("Congratulations! You guessed the word. Do you want to continue?\n");
            //printf("playerScore: %d",playerScore);
            //scanf("%d",&advance);
            //if(advance==0)goto end;
            
            break;
        }

         }while (1);
         }
    }
         
         
         
         
         }
    else if (userRole == 1) {
        printf("Enter the super user secret code: ");
        char secretCode[20]; // Adjust the size as needed
        scanf("%s", secretCode);

        // Check the secret code (example code is "superuser123")
        if (strcmp(secretCode, "superuser123") == 0) {
            printf("Welcome, super user!\n");
             loadData("data.txt", levels, &levelCount);

    while (1) {
        repet:;
        int choice;
        printf("Options:\n");
        printf("1. Create a new level\n");
        printf("2. Add word to a level\n");
        printf("3. Delete word from a level\n");
        printf("4. Change word in a level\n");
        printf("5. Delete a level\n");
        printf("6. Save data to file\n");
        printf("7. Play\n");
        printf("8. Exit\n");
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
            if(adminExsit!=0){ goto playermode;}
            else{
               printf("can't play not enough levels");
            }
            goto repet ;
            case 8:
            adminExsit = existLevel(levels, levelCount);
            if(adminExsit==0) break;
             goto menuMain ;
            

            


               
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
        } else {
            printf("Invalid secret code. Access denied.\n");
        }
    
    }
    else if (userRole =3){

    }
     else {
        printf("Invalid role. Please choose 1 for player or 2 for super user.\n");
    }
    end:printf("THANK YOU FOR PLAYING");
 return 0;


}