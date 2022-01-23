// eight.c - A puzzle.
// Version: 2022-Jan-23 16:41

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print (char * array)
{
  printf ("%c %c %c\n%c %c %c\n%c %c %c\n",
          array[0], array[1], array[2],
          array[3], array[4], array[5],
          array[6], array[7], array[8]);
}

bool is_perfect (char *array)
{
  const char * perfect = "12345678_";
  return (0==strcmp (array, perfect));
}

typedef struct Point
{
  int x, y;
} Point;

void up (char *array, Point *cursor)
{
  if (cursor->y<1) return;
  array[cursor->x+cursor->y*3] = array[cursor->x+(cursor->y-1)*3];
  array[cursor->x+(cursor->y-1)*3] = '_';
  cursor->y--;
}

void down (char *array, Point *cursor)
{
  if (cursor->y>1) return;
  array[cursor->x+cursor->y*3] = array[cursor->x+(cursor->y+1)*3];
  array[cursor->x+(cursor->y+1)*3] = '_';
  cursor->y++;
}

void left (char *array, Point *cursor)
{
  if (cursor->x<1) return;
  array[cursor->x+cursor->y*3] = array[(cursor->x-1)+cursor->y*3];
  array[(cursor->x-1)+cursor->y*3] = '_';
  cursor->x--;
}

void right (char *array, Point *cursor)
{
  if (cursor->x>1) return;
  array[cursor->x+cursor->y*3] = array[(cursor->x+1)+cursor->y*3];
  array[(cursor->x+1)+cursor->y*3] = '_';
  cursor->x++;
}

int main (int argc, char **argv)
{
  srand(time(NULL));
  int niters = 81;
  if (argc==2)
  {
    niters = atoi (argv[1]);
  }
  char array [] = {'1', '2', '3', '4', '5', '6', '7', '8', '_', 0};
  Point cursor = {2, 2};
  printf ("The following is the target:\n");
  print (array);
  unsigned int i = 0;
  while (i<(unsigned)niters)
  {
    int j = rand()%4;
    if (j==0)
    {
      up (array, &cursor);
    }
    else if (j==1)
    {
      down (array, &cursor);
    }
    else if (j==2)
    {
      left (array, &cursor);
    }
    else if (j==3)
    {
      right (array, &cursor);
    }
    i++;
  }
  printf ("Your problem is:\n");
  print (array);
  while (!is_perfect(array))
  {
    printf ("Enter one of u d l r to move the cursor: ");
    char c = getchar();
    if (c=='u')
    {
      up (array, &cursor);
    }
    else if (c=='d')
    {
      down (array, &cursor);
    }
    else if (c=='l')
    {
      left (array, &cursor);
    }
    else if (c=='r')
    {
      right (array, &cursor);
    }
    else
    {
      printf ("The character '%c' is not recognized.\n", c);
    }
    getchar();
    print (array);
  }
  printf ("Good job.\n");
  return EXIT_SUCCESS;
}

