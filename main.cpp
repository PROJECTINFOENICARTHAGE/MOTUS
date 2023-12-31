#include <stdio.h>
#include <string.h>
#include "administration.c"
#include "wordextract.c"
#include "changeColors.c"
#include "automaticGenration.c"
void playerWordInsert(int* hint,int length,char *word,char c,int playerNumber){
   
    while (1) {
        printf("\n[+] player %d turn",playerNumber);
        if(*hint==0){
            
            printf("\nDo you want a hint for the first character? [1: yes / 0: no]: ");
            scanf("%d", hint);
        }
        if(*hint ==1){
            printf("\n hint : %c \n",c);
            

        }
       

        if (*hint == 0 || *hint == 1) {
            break;
        } else {
            printf("Invalid input. Please enter either 1 or 0.\n");
        }
    }
         
         
          //ask the user to enter a word
          do {
    printf("[+] Enter your guess for the word (%d letters): ", length);
    scanf("%s", word);

    if (strlen(word) ==length) {
        break; 
        // Go back to the beginning of the loop
    }
        printf("Word length does not match. Please enter a word with %d letters.\n", length);

    // The rest of your code for checking the guess and updating the game logic
} while (1);
}
void compareWords(char *word, char *c, int *test, int *used, int length) {
    // Check for exact matches
    for (int i = 0; i < length; i++) {
        if (word[i] == c[i]) {
            test[i] = 1;
            used[i] = 1;
        }
    }

    // Check for partial matches
    for (int i = 0; i <length; i++) {
        if (test[i] == 0) {
            for (int j = 0; j < length; j++) {
                if (used[j] == 0 && word[i] == c[j]) {
                    test[i] = 2;
                    used[j] = 1; // Mark the character as used
                    break;
                }
            }
        }
    }
}
void checkWin(char PlayerNumber,int player1Score,int player2Score){
if(PlayerNumber =='2'){
    printf("\nplayer1 score : %d, player2 score : %d",player1Score,player2Score);
    if(player1Score==player2Score){
        printf("It's a tie\n");
    
    }
    else if(player1Score>player2Score){
        printf("Congratulations player 1! You won\n");
    
    }
    else printf("Congratulations player 2! You won\n");
}

}
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
    char *word;// Player1's guess
    char *word_;// Player2's guess
    int *used;// Array to track already matched characters
    char *c_;// predifined word
    int *test_;// Array to store the scoring
    char* formatedWord1;// array to store the colored word of player 1
    char* formatedWord2;// array to store the colored word of player 2
    int *used_;// Array to track already matched characters
    int advance[2];// array to track 
    int playerWin[2] ={0,0};// this variable will help us passs the player who didn't  quess the word first
    int adminExsit;
    int initialScore[2]={5,5};//contain the initial score of every player
    int playerScore[2]={0,0};// contain the total score of every player
    int levelScore[2]={0,0};// contain the score for each level
    int hint[2];// this variable will lock or unlock the hint feature
    char userRole;// determine the user role
    int totalWords=0; 
    int playerlock[2]={0,0};
    
  
    // welcome screen
    menuMain:;
    printf("   _____   _______________________ ___  _________\n");
    printf("  /     \\  \\_____  \\__    ___/    |   \\/   _____/\n");
    printf(" /  \\ /  \\  /   |   \\|    |  |    |   /\\_____  \\\n");
    printf("/    Y    \\/    |    \\    |  |    |  / /        \\\n");
    printf("\\____|__  /\\_______  /____|  |______/ /_______  /\n");
    printf("        \\/         \\/                         \\/\n");
    printf("Made by Ahmed Omrani\n");
    // Ask the user if they are a player or super user
        while(1){
        printf("MENU:\n");
        printf("1. Single play\n");
        printf("2. 2 player game\n");
        printf("3. administrator\n");
        printf("4. exit");
        printf("[+] Enter your choice: ");
        scanf("%s", &userRole);

        switch (userRole) {
            case '1': playermode:;
        // Player's code
        printf("Welcome, player!\n");
        // loop for levels
         for(int k = 1 ; k<=levelCount;k++){
            wordInfos = getWordsForLevel(filename, k, &wordCount, &totalWordCount, &levelCount);
           
             levelScore[0]=0;
            // loop for words in each level
            for(int w=0;w<wordCount;w++){
                totalWords+=1;
                hint[0]=0;
                //hintLock[0]='0';
                
            
            //printf("word count : %d",wordCount);
            initialScore[0]=5;

            c = (char*)malloc(wordInfos[w].length*sizeof(char));
            word =(char*)malloc(wordInfos[w].length*sizeof(char));
            c=wordInfos[w].word;
   do{
    

    


        int* test;
        int *used;
        test = (int*)malloc(wordInfos[w].length*sizeof(int));
        used = (int*)malloc(wordInfos[w].length*sizeof(int));
        
       
        for(int a = 0; a<wordInfos[w].length;a++){
            *(test+a) = 0;// Array to store the scoring
            *(used+a) = 0;// Array to track already matched characters
        }

       // take thr user word input
         playerWordInsert(&hint[0],wordInfos[w].length,word,c[0],1/*,&hintLock[0]*/);
         
        
    // test the similiarity and if the characters are there
compareWords( word, c, test, used,  wordInfos[w].length);    


printf("\n");
//color the user word based on the validity of each character
formattedWord = formatWordWithColors(word, test, wordInfos[w].length);
printf("%s%s\n", formattedWord, RESET);
printf("%s",WHITE);

   
printf("\n");
int all_correct = 1; // Assume all elements are correct
        for (int i = 0; i < wordInfos[w].length; i++) {
            if (test[i] != 1) {
                all_correct = 0; // Not all elements are correct
                if(initialScore[0]==1){
                initialScore[0]=0;
                goto nextWord;
                }
                initialScore[0]-=1;
                break;
                
            }
        }

        // Check if the win condition is met
        if (all_correct) {
          
            playerScore[0]+=initialScore[0];
            levelScore[0]+=initialScore[0];
           
            nextWord:;

            printf("playersore :%d  \n",playerScore[0]);
            
            if(w==wordCount-1 && levelScore[0]/19 <1){printf("\nYou didn't pass the minimum requirement for this level\n");printf("game over");printf("playerScore: %d",playerScore[0]); goto end;}
            else if(w==wordCount-1 && playerScore[0]/19 >=1) {
                printf("Congratulations! passed level %d\n",k);
                if(totalWords==15){
                printf("playerScore: %d",playerScore[0]);
                goto end;
            }
                
                }
           

            
            
            if(initialScore[0] ==0){
            printf("you didn't guess the word. Do you want to continue?\n");
            scanf("%d",&advance[0]);
            if(advance[0]==0){ printf("\nplayer score : %d",playerScore[0]);goto end;}
            }
            else{printf("Congratulations! You guessed the word. Do you want to continue?\n");

            scanf("%d",&advance[0]);
            if(advance[0]==0)goto end;}
            
            

           
            
            break;
        }

         }while (1);
         }
    }
    case '2': // Player's code
        printf("Welcome, players!\n");
      
         for(int k = 1 ; k<levelCount;k++){
            wordInfos = getWordsForLevel(filename, k, &wordCount, &totalWordCount, &levelCount);
            for(int w=0;w<wordCount;w++){
                hint[0]=0;
                hint[1]=0;

            
            
            initialScore[0]=5;
            initialScore[1]=5;
            

            c = (char*)malloc(wordInfos[w].length*sizeof(char));
            word =(char*)malloc(wordInfos[w].length*sizeof(char));
            c=wordInfos[w].word;
            //player two intializer for array
            c_ = (char*)malloc(wordInfos[w].length*sizeof(char));
            word_ =(char*)malloc(wordInfos[w].length*sizeof(char));
            c_=wordInfos[w].word;
           
   do{
    

    

        int* test;
        int *used;
        int* test_;
        int *used_;
        test = (int*)malloc(wordInfos[w].length*sizeof(int));
        used = (int*)malloc(wordInfos[w].length*sizeof(int));
        test_ = (int*)malloc(wordInfos[w].length*sizeof(int));
        used_ = (int*)malloc(wordInfos[w].length*sizeof(int));
        
       
        for(int a = 0; a<wordInfos[w].length;a++){
            *(test+a) = 0;
            *(used+a) = 0;
            *(test_+a) = 0;
            *(used_+a) = 0;
        }
        printf("playezlock : %d\n",playerlock[0]);
      if(playerlock[0]==0){
playerWordInsert(&hint[0],wordInfos[w].length,word,c[0],1);
 // test the similiarity and if the characters are there
compareWords( word, c, test, used,  wordInfos[w].length);  
      }
      if(playerlock[1]==0){
 playerWordInsert(&hint[1],wordInfos[w].length,word_,c[0],2);
  // test the similiarity and if the characters are there
  compareWords( word_, c, test_, used_,  wordInfos[w].length);  
      }
                
               if(playerlock[0]==0){printf("%s\n",word);}
                if(playerlock[1]==0){printf("%s\n",word_);}
               

   
   
    


      

printf("\n");
//Color words
if(playerlock[0]==0){formatedWord1 = formatWordWithColors(word, test, wordInfos[w].length);}
if(playerlock[1]==0){formatedWord2 = formatWordWithColors(word_, test_, wordInfos[w].length);}


if(playerlock[0]==0){printf("%s%s\n", formatedWord1,RESET);}
if(playerlock[1]==0){printf("%s%s\n", formatedWord2, RESET);}

printf("%s",WHITE);

   
printf("\n");
printf("I'm here");
if(playerlock[0]==0){
int all_correct = 1; // Assume all elements are correct
        for (int i = 0; i < wordInfos[w].length; i++) {
            if (test[i] != 1) {
                all_correct = 0; // Not all elements are correct
                if(initialScore[0]==1 || w==wordCount-1){
                initialScore[0]=0;
                goto nextWord2;
                }
                initialScore[0]-=1;
                break;
              
                
            }
        }

        // Check if the win condition is met
        if (all_correct) {
           
            playerScore[0]+=initialScore[0];
            levelScore[0]+=initialScore[0];
            nextWord2:;
         
            printf("playersore :%d  \n",playerScore[0]);
           
          
            if(w==wordCount-1 && levelScore[0]/19.0 <1){printf("\nplayer1 didn't pass the minimum requirement for level %d\n",k+1);printf("\ngame over for you ");printf("\nplayerScore1: %d",playerScore[0]); playerlock[0]=1;goto player2;}
            else if(w==wordCount-1 && playerScore[0]/19 >=1) {printf("Congratulations! passed level %d\n",k); }
           
   if(initialScore[0] ==0){
            printf("player 1 you didn't guess the word.\n");
            playerWin[0]=0;
            }
            else{
printf("Congratulations! player 1 you guessed the word.\n");
 if(totalWords ==15)goto end;
 
playerWin[0]=1;
            }
            if(playerlock[1]==1){
                printf("Do you want to continue?");

            scanf("%d",&advance[1]);
            if(advance[1]==0)goto end;
            else break;
            }
            /*if(w==wordCount){
                printf("playerScore1: %d",playerScore[0]);
                break;
            }
           */
           
        }
          
}
player2:;
if(playerlock[1]==0){
int all_correct_ = 1; // Assume all elements are correct
        for (int i = 0; i < wordInfos[w].length; i++) {
            if (test_[i] != 1) {
                all_correct_ = 0; // Not all elements are correct
                if(initialScore[1]==1){
                initialScore[1]=0;
                goto nextWord3;
                }
                
                initialScore[1]-=1;
                break;
                
            }
        }
   if((all_correct_==0) && (playerWin[0]==1)){
           
    playerWin[0]=0;
    if(w==wordCount-1 && playerScore[1]/19.0 <1){printf("\nplayer2 didn't pass the minimum requirement for level %d\n",k+1);printf("game over ");printf("player2 score: %d",playerScore[1]);playerlock[1]=1;}

    printf("Do you want to continue?");

            scanf("%d",&advance[1]);
            if(advance[1]==0)goto end;
            else break; 
    

}
        // Check if the win condition is met
        if (all_correct_) {
           
            playerScore[1]+=initialScore[1];
            levelScore[1]+=initialScore[1];
            nextWord3:;
            printf("level score : %d",levelScore[1]);
            printf("player2 score :%d  \n",playerScore[1]);
            printf("%f",levelScore[1]/19.0);
            if(w==wordCount-1 && levelScore[1]/19.0 <1){printf("\nplayer2 didn't pass the minimum requirement for level %d\n",k+1);printf("game over4");printf("player2 score: %d",playerScore[1]); goto end;}
            else if(w==wordCount-1 && playerScore[1]/19.0 >=1) {printf("Congratulations player 2! you passed level %d\n",k); /*totalScore[1]= playerScore[1];playerScore[1]=0;*/}
            if(w==wordCount-1 && k==levelCount-1){
                printf("Congratulations! player2 you won. Your score is : %d\n",playerScore[1]);
            }

            
            if(w==wordCount){
                printf("player2 score: %d",playerScore[1]);
                break;
            }
            printf("here");
            if(initialScore[1] ==0){
            printf("you didn't guess the word. Do you want to continue player 2 ?\n");
            //printf("playerScore: %d",playerScore);
            scanf("%d",&advance[1]);
            if(advance[1]==0)goto end;
            }else{printf("Congratulations player 2! You guessed the word.\n");

            if(totalWords ==15)goto end;
            printf("Do you want to continue?");

            scanf("%d",&advance[1]);
            if(advance[1]==0)goto end;}
            
            

            
            
            break;
        }
}
             
         }while (1);
         }
    }
    break;
    case '3': printf("Enter the super user secret code: ");
        char secretCode[20]; // Adjust the size as needed
        scanf("%s", secretCode);

        // Check the secret code (example code is "superuser123")
        if (strcmp(secretCode, "superuser123") == 0) {
            printf("Welcome, super user!\n");
             loadData("data.txt", levels, &levelCount);

    while (1) {
        repet:;
        char choice;
        printf("Options:\n");
        printf("1. Add word to a level\n");
        printf("2. Delete word from a level\n");
        printf("3. Change word in a level\n");
        printf("5. Play\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", &choice);

        switch (choice) {
            case '1':
                addWordAndUpdateFile("data.txt",levels, levelCount);
                break;
            case '2':
                deleteWordAndUpdateFile("data.txt",levels, levelCount);
                break;
            case '3':
                changeWordInLevelAndUpdateFile("data.txt",levels, levelCount);
                break;
            case '4':
                changeWordInLevelAndUpdateFile("data.txt",levels, levelCount);
                break;
            case '5':
            adminExsit = existLevel(levels, levelCount);
            printf("%d ; descion ",adminExsit);
            if(adminExsit!=0){ goto playermode;}
            else{
               printf("\ncan't play not enough levels\n");
            }
            goto repet ;
            case '6':
            adminExsit = existLevel(levels, levelCount);

            if(adminExsit==0) break;
             goto menuMain ;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
        } else {
            printf("Invalid secret code. Access denied.\n");
            
        }
        break;
        case '4': goto exitgame;
        default:   printf("Invalid choice.\n");
        break;
        }


    
   

    
        
    end:printf("THANK YOU FOR PLAYING");
    checkWin(userRole,playerScore[0],playerScore[1]);
    exitgame:;
 return 0;

        }
}


