#include<stdio.h>
#include<stdlib.h>

void solveMagicSquare(int square[6][6])
{
 // This function receives an array of size 6x6
 // that corresponds to a magic square.
 // It then finds any entries with value -1
 // (which means they are not known),
 // and figures out what their value should
 // be to solve the magic square.
 //
 // Conditions:
 // You can not hard-code the value of the rows
 // and columns in the magic square - because
 // we will test this with a *different* magic
 // square than the one in this starter code
 //
 // Your function has to (somehow) figure out
 // what the sum of the rows and columns should be,
 // and then figure out for each entry whose
 // value is -1, what its value is to correctly
 // complete the magic square.
 //
 // This is about problem solving - you don't
 // need any fancy pointer management or anything
 // like that. Just plain old C with a 2D array
 // and a bit of thinking.
 //
 // As a reminder. 2D arrays in C are indexed as
 // array[i][j] - gives you the element at row i,
 // column j

 //////////////////////////////////////
 // TO DO: Complete this function
 //////////////////////////////////////
 //find the row/col that has the -01 in it
    int * magic_sum = NULL;

    for (int i = 0; i < 6; i++) {
      int sum = 0;
      int num_missing = 0;

      for (int j = 0; j < 6; j++) {
        if (square[i][j] == -1) {
          num_missing = 1;
          break;
        } else {
          sum = sum + square[i][j];
        }
      }

      if (num_missing == 0) {
        if (magic_sum == NULL) {
          magic_sum = malloc(sizeof(int));
          * magic_sum = sum;
        }
      }
    }

    int num_unks = 0;
    int another_sum;
    int i, j;

    //col by col
    for (i = 0; i < 6; i++) {
      another_sum = 0;
      num_unks = 0;

      int missing_index = -1; //keep da addy

      // ROW BY ROW
      for (j = 0; j < 6; j++) {
        if (square[i][j] == -1) {
          num_unks++;
          missing_index = j;
        } else {
          another_sum += square[i][j];
        }
      }

      if (num_unks == 1) {
        square[i][missing_index] = * magic_sum - another_sum;
      }
    }

    // fill in other missing nums col by col same logic as before
    for (int m = 0; m < 6; m++) {
      another_sum = 0;
      num_unks = 0;

      int missing_index = -1;

      for (int n = 0; n < 6; n++) {
        if (square[n][m] == -1) {
          num_unks++;
          missing_index = n;
        } else {
          another_sum += square[n][m];
        }
      }

      //there should only be one missing val left i hope lol
      if (num_unks == 1 && magic_sum != NULL) {
        square[missing_index][m] = * magic_sum - another_sum;
      }
    }
}


// DO NOT MODIFY ANYTHING BELOW THIS LINE!
// (we mean it! the auto-checker won't be happy)
void printMagicSquare(int square[6][6])
{
   // Prints out the contents of a magic square 6x6

   int i,j,sum;

   for (i=0; i<6; i++)
   {
       sum=0;
       for (j=0; j<6; j++)
       {
           printf("%03d, ",square[i][j]);
           sum=sum+square[i][j];
       }
       printf(" : %03d\n",sum);
   }

   printf("---------------------------\n");

   for (j=0; j<6; j++)
   {
       sum=0;
       for (i=0; i<6; i++)
       {
	   sum=sum+square[i][j];
       }
       printf("%03d, ",sum);
   }
   printf("\n");
}

#ifndef __testing   // This is a compiler directive - used by the auto-checker to enable/disable this part of the code
int main()
{
    int magic[6][6]={{32,29,4,1,24,21},{30,-1,2,3,-1,23},{12,9,17,20,28,25},{10,11,18,-1,26,27},{13,-1,36,33,5,8},{14,15,34,35,6,-1}};

    printMagicSquare(magic);
    printf("Solving Magic Square!\n");
    solveMagicSquare(magic);
    printMagicSquare(magic);

    return 0;
}
#endif
