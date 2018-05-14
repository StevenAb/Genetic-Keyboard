#include "fitness.h"
#include "fitness.cpp"
using namespace std;

/* This function duplicates an existing keyboard to a new instance */
keyboard *duplicate_keyboard(keyboard *parent)
{
  keyboard *new_kb = new keyboard();
  for ( int i = 0; i < 32; i++)
    {
      new_kb->board[i] = parent->board[i];
    }
  return new_kb;
}

/* This function takes in a parent keyboard and returns a mutated copy  */
keyboard *mutate(keyboard *parent)
{
  keyboard *new_kb = duplicate_keyboard(parent);
  int rand_key1 = rand() % 32;
  int rand_key2 = rand() % 32;

  while ( rand_key1 == rand_key2 ) // Avoid duplicate index values
    rand_key2 = rand() % 32;

  // swap...
  new_kb->board[rand_key1] = parent->board[rand_key2];
  new_kb->board[rand_key2] = parent->board[rand_key1];

  return new_kb;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This function takes in two keyboards and breeds them returning a child keyboard  *
 *                                                                                   *
 *  Breeding Algorithm: (See graph below for reference)                              *
 *                                                                                   * 
 *  Add graphs A, C, E and G of parent 1 to child keyboard                           *
 *  Add graphs B, D, F and H of parent 2 to child keyboard                           *
 *  Traverse the child keyboard to find collisions                                   *
 *       keeping track of a running list of duplicated keys                          *
 *  Set every collisions to NULL                                                     * 
 *  Randomly fill in the NULL keys with missing keys from the running list           *
 *  return child keyboard                                                            *
 *                                                                                   *
 * Keyboard graph representation:                                                    *
 * Each Letter represents a graph                                                    *
 * Each Node represents the index from the board array                               *
 *                                                                                   *
 *                                                                                   * 
 *                                                                                   *
 * A     B     C          D        E         F      G        H                       *
 * 0     1     2        3 - 4     5 - 6      7      8      9 - 10                    *
 * |     |     |        | X |     | X |      |      |      | X |                     *
 * 11    12    13      14 - 15   16 - 17    18     19     20 - 21                    *
 * |           / \      | X |     | X |      |      |      \   /                     *
 * 22         23 24    25 - 26   27 - 28    29     30        31                      *
 *                                                                                   *
 *                                                                                   *
 *                                                                                   *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
keyboard *breed(keyboard *keyboard1,keyboard *keyboard2){
  keyboard *child_kb = new keyboard();
  // Add graphs A, C, E and G of parent 1 to child keyboard
  // A
  child_kb->board[0] = keyboard1->board[0];
  child_kb->board[11] = keyboard1->board[11];
  child_kb->board[22] = keyboard1->board[22];

  // C
  child_kb->board[2] = keyboard1->board[2];
  child_kb->board[13] = keyboard1->board[13];
  child_kb->board[23] = keyboard1->board[23];
  child_kb->board[24] = keyboard1->board[24];

  // E
  child_kb->board[5] = keyboard1->board[5];
  child_kb->board[6] = keyboard1->board[6];
  child_kb->board[16] = keyboard1->board[16];
  child_kb->board[17] = keyboard1->board[17];
  child_kb->board[27] = keyboard1->board[28];
  child_kb->board[28] = keyboard1->board[27];

  // G
  child_kb->board[8] = keyboard1->board[8];
  child_kb->board[19] = keyboard1->board[19];
  child_kb->board[30] = keyboard1->board[30];

  // Add graphs B, D, F and H of parent 2 to child keyboard
  // B
  child_kb->board[1] = keyboard2->board[1];
  child_kb->board[12] = keyboard2->board[12];

  // D
  child_kb->board[3] = keyboard2->board[3];
  child_kb->board[4] = keyboard2->board[4];
  child_kb->board[14] = keyboard2->board[14];
  child_kb->board[15] = keyboard2->board[15];
  child_kb->board[25] = keyboard2->board[25];
  child_kb->board[26] = keyboard2->board[26];

  // F
  child_kb->board[7] = keyboard2->board[7];
  child_kb->board[18] = keyboard2->board[18];
  child_kb->board[29] = keyboard2->board[29];

  // H
  child_kb->board[9] = keyboard2->board[9];
  child_kb->board[10] = keyboard2->board[10];
  child_kb->board[20] = keyboard2->board[20];
  child_kb->board[21] = keyboard2->board[21];
  child_kb->board[31] = keyboard2->board[31];

  // traverse the child keyboard to find collisions
  key collisions[32];
  int index = 0;
  for (int i = 0; i < 32; i++)
    {
      for (int j = i + 1; j < 32; j++)
  {
    if ( child_kb->board[i] == child_kb->board[j] )
      {
        collisions[index++]=child_kb->board[i];
        child_kb->board[i] = "-1";
      }
  }
    }

  // randomly fill in the NULL keys with collisions
  std::random_shuffle(&collisions[0],&collisions[index]);
  int counter = 0; // keep track of elements in collisions
  while ( counter <= index )
  {
      for ( int i = 0; i < 32; i++)
      {
        if ( child_kb->board[i] == "-1" )
        {
          child_kb->board[i] = collisions[counter];
          counter--;
        }
      }
  }
  return child_kb;
}


