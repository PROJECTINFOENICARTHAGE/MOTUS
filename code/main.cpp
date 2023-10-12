#include <stdio.h>
#include <string.h>
int main() {
//variables declaration

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
   do{
    
//ask the user to enter a word
do{
        test[] = {0, 0, 0, 0, 0}; // Array to store the scoring
        used[] = {0, 0, 0, 0, 0}; // Array to track already matched characters
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
 return 0;


}
