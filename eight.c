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

int count_char (char *array, char c)
{
  int ret = 0;

  while (*array!=0)
  {
    if (*array==c)
    {
      ret++;
    }
    array++;
  }
  return ret;
}

bool is_array_valid (char *array)
{
  if (strlen(array) != 9)
  {
    return false;
  }
  char c = '1';
  while (c<'9')
  {
    if (count_char (array, c) != 1)
    {
      return false;
    }
    c++;
  }
  if (count_char (array, '_') != 1)
  {
    return false;
  }
  return true;
}

Point get_cursor (char * const array)
{
  Point cursor;
  const int icursor = index (array, '_')- array;
  cursor.y = icursor/3;
  cursor.x = icursor%3;
  return cursor;
}

bool move_digit (char * const array, const char digit)
{
  if ((digit<'1')||(digit>'8'))
  {
    return false;
  }
  const Point cursor = get_cursor (array);
  const int icursor = (cursor.y*3)+cursor.x;
  Point point_digit;
  const int idigit = index (array, digit) - array;
  point_digit.y = idigit/3;
  point_digit.x = idigit%3;
  //printf ("point_digit.x = %d\tpoint_digit.y = %d\n", point_digit.x, point_digit.y);
  if (point_digit.y == cursor.y)
  {
    if ( (point_digit.x == (cursor.x+1)) || (point_digit.x == (cursor.x-1)) )
    {
      array[idigit] = '_';
      array[icursor] = digit;
      return true;
    }
    return false;
  }
  if (point_digit.x == cursor.x)
  {
    if ( (point_digit.y == (cursor.y+1)) || (point_digit.y == (cursor.y-1)) )
    {
      array[idigit] = '_';
      array[icursor] = digit;
      return true;
    }
    return false;
  }
  return false;
}

void up (char *array)
{
  Point cursor = get_cursor (array);
  if (cursor.y<1) return;
  array[cursor.x+(cursor.y*3)] = array[cursor.x+((cursor.y-1)*3)];
  array[cursor.x+((cursor.y-1)*3)] = '_';
}

void down (char *array)
{
  Point cursor = get_cursor (array);
  if (cursor.y>1) return;
  array[cursor.x+(cursor.y*3)] = array[cursor.x+((cursor.y+1)*3)];
  array[cursor.x+((cursor.y+1)*3)] = '_';
}

void left (char *array)
{
  Point cursor = get_cursor (array);
  if (cursor.x<1) return;
  array[cursor.x+(cursor.y*3)] = array[(cursor.x-1)+(cursor.y*3)];
  array[(cursor.x-1)+(cursor.y*3)] = '_';
}

void right (char *array)
{
  Point cursor = get_cursor (array);
  if (cursor.x>1) return;
  array[cursor.x+(cursor.y*3)] = array[(cursor.x+1)+(cursor.y*3)];
  array[(cursor.x+1)+(cursor.y*3)] = '_';
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
  printf ("The following is the target:\n");
  print (array);
  unsigned int i = 0;
  while (i<(unsigned)niters)
  {
    int j = rand()%4;
    if (j==0)
    {
      up (array);
    }
    else if (j==1)
    {
      down (array);
    }
    else if (j==2)
    {
      left (array);
    }
    else if (j==3)
    {
      right (array);
    }
    i++;
  }
  printf ("Your problem is:\n");
  print (array);
  while (false == is_perfect(array))
  {
    if (false == is_array_valid (array))
    {
      fprintf (stderr, "Error: The array is invalid.\n");
      return EXIT_FAILURE;
    }
    printf ("Enter one of u d l r to move the cursor\nor the digit you want to move: ");
    char c = getchar();
    if (c=='u')
    {
      up (array);
    }
    else if (c=='d')
    {
      down (array);
    }
    else if (c=='l')
    {
      left (array);
    }
    else if (c=='r')
    {
      right (array);
    }
    else
    {
      if (false == move_digit (array, c))
      {
        printf ("The character '%c' is not recognized.\n", c);
      }
    }
    getchar();
    print (array);
  }
  printf ("Good job.\n");
  return EXIT_SUCCESS;
}
