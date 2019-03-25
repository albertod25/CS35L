#include <stdio.h>
#include <stdlib.h>

/* Reads frobnicated text lines from standard input and writes a sorted
 * version to standard output in frobnicated form
 */

/* Unfrobnicates a given character by xor-ing with 0x2A
 * Necessary due to compiler warning when xor-ing in frobcmp
 */
int unfrob(const char x)
{
    return (x^0x2A);
}

/* compares frobnicated strings a and b
 * Returns negative if a < b, 0 if a = b, or positive if a > b
 */
int frobcmp(char const* a, char const* b)
{
    for( ; ;a++, b++)
    {
        // null bytes allowed but not counted, skip them
        while(*a == '\0')
            a++;
        while(*b == '\0')
            b++;

        // both ended and go this far, MUST be equal
        if(*a == ' ' && *b == ' ')
            return 0;
    
        if(*a==' ' || unfrob(*a) < unfrob(*b))
            return -1;
        if(*b==' ' || unfrob(*a) > unfrob(*b))
            return 1;
    }
}

/* Casts some of the arguments getting passed into frobcmp.
 * Specifically made to be able to use frobcmp from qsort()
 * I received help on this function from a previous cs35l student
 */
int reFrobCmp(const void* a, const void* b)
{
    const char* inp1 = *(const char**)a;
    const char* inp2 = *(const char**)b;
    return frobcmp(inp1, inp2);
}

/* Custom function that frees all the space taken up by line and record arrays.
 * Typically used before exiting the program
 */
void cleanup(char* line, char** record, int r)
{
    free(line);
    int i;
    for(i=0; i < r; r++)
        free(record[i]);
    free(record);
}

int main()
{
    char* line; // stores one word (columns)
    char** record=NULL; // stores list of words (rows)
    line =  (char*)malloc(sizeof(char)); // starts of the word with allocated space

    // error checking
    if(line==NULL)
    {
        fprintf(stderr, "%s", "Memory Error: exiting program\n");
        exit(1);
    }

    line[0]=getchar();
    if(ferror(stdin))
    {
        fprintf(stderr, "%s", "I/O Error: exiting program\n");
        exit(1); 
    }
    
    int l=0; // number of characters in line
    int r=0; // number of words in record
    while(line[l] != EOF)
    {
        char next = getchar(); // easier to work with next character than current
        if(ferror(stdin))
        {
            fprintf(stderr, "%s", "I/O Error: exiting program\n");
            exit(1); 
        }
        
        if(line[l] == ' ') // if current char is ' ' then start new line
        {
            char** tempr = realloc(record,(r+1)*sizeof(char*)); // temp avoids losing
                                                               // record in case of error
            if(tempr == NULL)
            {
                cleanup(line, record, r);
                fprintf(stderr, "%s", "Memory error: exiting program\n");
                exit(1);
            }

            record=tempr;
            record[r]=line;
            r++;
            l=-1; // resets to 0 by next increment
            char* templn=(char*)malloc(sizeof(char));
            if(templn==NULL)
            {
                cleanup(line, record, r);
                fprintf(stderr, "%s", "Memory error: exiting program\n");
                exit(1);
            }
            line = templn;
            
            if(next==EOF) // stop reading if next is the EOF and last char was ' '
                break;
        }
        else if(next==EOF)
        {
            next=' ';
        }
        
        // add in the character to current line
        l++;
        char* temp = realloc(line, (l+1)*sizeof(char));
        if(temp == NULL)
        {
            cleanup(line, record, r);
            fprintf(stderr, "%s", "Memory error: exiting program\n");
            exit(1);
        }
        line=temp;
        line[l]=next;
    }
    
    qsort(record, r, sizeof(char*), reFrobCmp);

    // prints out all the sorted characters
    for(size_t i=0; i < r; i++)
    {
        for(size_t j = 0; record[i][j] != ' '; j++)
            printf("%c", record[i][j]);
        printf(" ");
    }

    cleanup(line, record, r);
    return 0;
}
