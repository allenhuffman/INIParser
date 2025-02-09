#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "INIParser.h"

char *trim(char *str)
{
    char *newStr = str;

    if (str != NULL)
    {
        size_t len = strlen(str);

        // Trim trailing whitespace and control characters
        for (size_t idx = len; idx > 0; idx--)
        {
            char ch = str[idx - 1];

            if (iscntrl(ch) || isspace(ch))
            {
                str[idx - 1] = '\0';
            }
            else
            {
                break;
            }
        }

        // Trim leading whitespace and control characters
        while (*newStr && (iscntrl(*newStr) || isspace(*newStr)))
        {
            newStr++;
        }
    }

    return newStr;
}

int main()
{
    FILE *fp;
    char buffer[100];

    fp = fopen ("Sample.ini", "r");

    if (fp == NULL)
    {
       perror ("OPEN ERROR");
    }
    else
    {
        int line = 0;

        while (!feof (fp))
        {
            if (fgets (&buffer[0], sizeof(buffer)-1, fp) != NULL)
            {
                char *str = trim (buffer);

                printf ("%d. '%s'\n", line++, str);
            }
        }

        fclose (fp);
    }

    return EXIT_SUCCESS;
}

// End of main.c
