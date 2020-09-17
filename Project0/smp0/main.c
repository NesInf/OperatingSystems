/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0

Note: this code was automatically formatted (styled) using 'indent main.c
-kr'.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment1_test.h"

/* Structures */
typedef struct {
    char *word;
    int counter;
} WordCountEntry;


int process_stream(WordCountEntry entries[], int entry_count)
{
    short line_count = 0;
    char buffer[30];
    char *word;

    /* C4: replace gets with fgets */
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
	if (*buffer == '.')
	    break;

	/* C5: strtok() can be used to split a line into individual tokens.
	   For the separator characters we use whitespace (space and
	   tab), as well as the newline character '\n'.  We could also
	   trim the buffer to get rid of the newline, instead. */
	word = strtok(buffer, " \t\n");
	/* C5: strtok returns NULL when no more tokens are available. */
	while (word != NULL) {

	    /* Compare against each entry */
	    int i = 0;
	    while (i < entry_count) {

		if (!strcmp(entries[i].word, word))
		    entries[i].counter++;
		i++;
	    }
	    /* C5: get the next token */
	    word = strtok(NULL, " \t\n");
	}
	line_count++;
    }
    return line_count;
}


void print_result(WordCountEntry entries[], int entry_count, FILE * output)
{
    /* B5: introduce a temporary variable i and use it to count up from 0 */
    unsigned int i;
    /* C2: send output to the right stream */
    fprintf(output, "Result:\n");
    for (i = 0; i < entry_count; i++) {
