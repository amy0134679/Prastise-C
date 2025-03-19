/**
 * Exercise 4
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * NOTE: You should NOT use array notation inside your functions. Use only
 *       pointer notation for any code that you write. Any array notation
 *       used outside of the main function will result in a 0. This includes
 *       making a new array of characters.
 * E.g:   char x[1024]; <--- [] used to create a new array is prohibited
 * E.g:   char y = x[0]; <--- [] used to access an array is prohibited
 *
 */

#include <stdio.h>
#include <stdlib.h>
// NO additional imports allowed. You can make helper functions if you wish.

#define MAX_STRING_LEN 1024

int myStrlen(char *str) {
    int len = 0;
    while (*(str + len) != '\0') {
        len++;
    }
    return len;
}

char *find_last_substring(char *str, char *a) {
    int lenStr = myStrlen(str);
    int lenA = myStrlen(a);
    char *found = NULL;
    char *p, *q;

    if (lenA == 0) { // RETURNS LAST INDEX
        return str + lenStr;
    }

    // ITERATE THROUGH STR USING POINTER P
    for (p = str; *p != '\0'; p++) { //P STARTS AT FIRST INDEX OF STR, GOES UNTIL HITS THE END
        for (q = a; *q != '\0'; q++) {// LOOPS THROUGH IF FIRST INDEX OF SS IS FOUND IN STR
            if (*(p + (q - a)) != *q) {
                break;
            }
        }
        
        if (*q == '\0') {
            found = p;//FOUND THE INDEX
        }
    }
  
    return found; 
}

void remove_vowel(char *str, int pos) {
    int len = myStrlen(str);
    for (int i = pos; i < len; i++) {
        *(str + i) = *(str + i + 1); // Shift characters to the left
    }
    *(str + len - 1) = '\0'; // Null terminate the string
}

void split_vowels(char *str, char *vowels) {
    char *all_vowels = "aeiouAEIOU";
    char *p, *q;
    int lenStr = myStrlen(str);
    int k = 0; // TRACKER FOR VOWEL ARRAY

    for (p = str; *p != '\0'; p++) { //P TAKES FIRST VALUE OF STR AND ITERATES THROUGH STR
        for (q = all_vowels; *q != '\0'; q++) { //ITERATES THROUGH VOWELS
            if (*p == *q) {//CHECKS IF LETTER IS VOWEL
                *(vowels + k++) = *p; // STORES THE VOWEL INTO THE CORRECT ARRAY POSITION
                remove_vowel(str, p - str); 
                p--; // PUSHES BACK ITERATION BC REMOVED A VAL
                lenStr--; // PUSHES BACK STR LENGTH
                break; 
            }
        }
    }
    *(vowels + k) = '\0'; // NULL TERMINATE

}
// ----------------------------------------------------------------------------

// Do not change the lines above and below the main function. These
// are here to ensure that the main() function defined here does not
// Conflict with the automarker when testing your code. Changing them
// will result in a 0 for this exercise. You are free to change anything
// inside the main() function itself.
#ifndef __testing__
int main()
{
  char my_str[MAX_STRING_LEN] = "many many people have many many hobbies";
  char *res = find_last_substring(my_str, "many");
  if (res - my_str == 27)
  {
    printf("- find_last_substring() returned the correct result!\n");
  }
  else
  {
    printf("! find_last_substring() did not work properly.\n");
  }

  printf("----------------------------------------------------------------\n");

  char str[MAX_STRING_LEN] = "This sentence has many vowels! AEIOU";
  char vowels[MAX_STRING_LEN];
  split_vowels(str, vowels);

  printf("(Expected Result) str: \"Ths sntnc hs mny vwls! \", "
         "vowels: \"ieeeaaoeAEIOU\"\n");
  printf("(Your Solution) str: \"%s\", vowels: \"%s\"\n", str, vowels);
}
#endif
