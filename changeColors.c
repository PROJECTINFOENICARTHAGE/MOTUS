#include <stdio.h>

// ANSI escape codes for text colors
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

// Function to format a word with colors
char* formatWordWithColors(const char* word, const int* colors, int word_length) {
    static char formattedWord[100]; // Assuming a maximum word length of 100 characters

    int formattedWordIndex = 0;

    for (int i = 0; i < word_length; i++) {
        char c = word[i];
        int color_idx = colors[i] % 6; // Ensure it's within the range 0-5

        switch (color_idx) {
            case 0:
                sprintf(formattedWord + formattedWordIndex, "%s%c%s", RED, c, RESET);
                formattedWordIndex += 7;
                break;
            case 1:
                sprintf(formattedWord + formattedWordIndex, "%s%c%s", GREEN, c, RESET);
                formattedWordIndex += 7;
                break;
            case 2:
                sprintf(formattedWord + formattedWordIndex, "%s%c%s", YELLOW, c, RESET);
                formattedWordIndex += 7;
                break;
            default:
                formattedWord[formattedWordIndex++] = c;
        }
    }

    formattedWord[formattedWordIndex] = '\0'; // Null-terminate the formatted string

    return formattedWord;
}

/*int main() {
    char word[] = "ahmed";
    int colors[] = {0, 1, 2, 0, 2};
    int word_length = sizeof(word) - 1; // Exclude the null terminator

    char* formattedWord = formatWordWithColors(word, colors, word_length);
    printf("%s\n", formattedWord);

    return 0;
}
*/