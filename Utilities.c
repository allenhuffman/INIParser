#include <ctype.h>  // for iscntrl(), etc.
#include <stddef.h> // for size_t
#include <string.h> // for strlen()

#include "Utilities.h"

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
