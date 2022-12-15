#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char *dest, int n)
{
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL)
  {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  }
  else
  {
    return 0;
  }
}

int main(int argc, char const *argv[])
{
  char *in = malloc(MAX_STR_LEN * sizeof(char));
  struct stack *pt = stack_create();
  struct queue *que = queue_create();

  while (get_user_str(in, MAX_STR_LEN))
  {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     */

    // push and enque onto the stack and queue
    // pop and dequeu and we compare

    int i = 0;
    int j = 0;
    for (i = 0; in[i] != '\0'; i++)
    {
      in[i] = tolower(in[i]);
      // Manual checking of the palindrome because isalpha wasn't as efficient when numbers were involved

      while (isalpha(in[i]) == 0)
      {
        // remove and shift by 1
        for (j = i; in[j] != '\0'; j++)
        {

          in[j] = in[j + 1];
        }
        in[j] = '\0';
      }
    }
  
    // push the values
    for (int i = 0; i < strlen(in); i++)
    {
      stack_push(pt, &in[i]);
      queue_enqueue(que, &in[i]);
    }

    char *po;
    char *eq;
    // dequeue and pop the values
    for (int i = 0; i < strlen(in); i++)
    {
      po = stack_pop(pt);
      eq = queue_dequeue(que);

      // if the pop and the deque are the same its a palindrome
      if (*po == *eq)
      {
        printf("\n A Palindrome String\n");
        break;
      }

      else
      {
        printf("\n Not A Palindrome String\n");
        break;
      }
    }
  }

  free(in);
  stack_free(pt);
  queue_free(que);

  return 0;
}
