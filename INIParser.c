/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <wctype.h>  // for iswspace()
#include <stdio.h>
#include <string.h> // for strchr()

// This projects's header
#include "INIParser.h"

// This file's header
#include "INIParser.h"

// Other headers
#include "INIRecords.h"

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Static Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Prototypes
/*--------------------------------------------------------------------------*/
static void ShowResult (const char line[], const char item[], bool status);

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/
LineTypeEnum GetLineType (const char line[])
{
    LineTypeEnum lineType = LINE_UNKNOWN;

    if (NULL != line)
    {
#if DEBUG_INIPARSER > 1
        printf ("Line: ");
        for (size_t idx=0; idx<=strlen(line);idx++)
        {
            printf ("%02x ", line[idx]);
        }
        printf ("\n");
#endif // DEBUG_INIPARSER

        if (IsLineEmpty (line))
        {
            lineType = LINE_EMPTY;
        }
        else if (IsLineAComment (line))
        {
            lineType = LINE_COMMENT;
        }
        else if (IsLineASection (line))
        {
            lineType = LINE_SECTION;
        }
        else if (IsLineATagValue (line))
        {
            lineType = LINE_TAGVALUE;
        }
        else
        {
            lineType = LINE_INVALID;
        }
    }

    return lineType;
}

/*--------------------------------------------------------------------------*/
bool GetCommentFromLine (const char line[], char *commentPtr,
                         size_t commentSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != commentPtr) && (0 != commentSize))
    {
        if (LINE_COMMENT == GetLineType (line))
        {
            size_t lineLen = strlen (line);
            size_t pos = 0;

            // Skip whitespace looking for the ';'.
            while ((pos < lineLen) && (iswspace (line[pos])))
            {
                pos++;
            }

            // Here we are at the end of the line, or found a character.
            if (';' == line[pos])
            {
                strncpy (commentPtr, &line[pos], commentSize);
                // strncpy() does not add the '\0' if it copies to max.
                commentPtr[commentSize] = '\0';

                status = true;
            }
        } // end of if (LINE_COMMENT

#if DEBUG_INIPARSER > 0
        ShowResult (line, commentPtr, status);
#endif // DEBUG_INIPARSER
    } // end of NULL checks

    return status;
}

/*--------------------------------------------------------------------------*/
bool GetSectionFromLine (const char line[], char *sectionPtr,
                         size_t sectionSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != sectionPtr) && (0 != sectionSize))
    {
        char newLine[LINE_MAX_LEN] = {0};

        // Remove comments.
        RemoveComments (line, newLine, sizeof(newLine));

        if (LINE_SECTION == GetLineType (newLine))
        {
            size_t lineLen = strlen (newLine);
            size_t startPos = 0;

            // 1. Skip any leading whitespace.
            while ((startPos < lineLen) && iswspace (newLine[startPos]))
            {
                startPos++;
            }

            // This must be a '['.
            if ('[' == newLine[startPos])
            {
                // Skip the '['.
                startPos++;

                // Skip any whitespace.
                while ((startPos < lineLen) && iswspace (newLine[startPos]))
                {
                    startPos++;
                }

                // Now backup to find the ']'.
                size_t endPos = lineLen - 1;
                while ((endPos > startPos) && iswspace (newLine[endPos]))
                {
                    endPos--;
                }

                // This must be a ']'.
                if (']' == newLine[endPos])
                {
                    // Skip the ']'
                    endPos--;

                    // Skip any whitespace
                    while ((endPos > startPos) && iswspace (newLine[endPos]))
                    {
                        endPos--;
                    }

                    // Now we know what to copy.
                    size_t sectionLen = endPos - startPos + 1;
                    if (sectionLen > sectionSize)
                    {
                        sectionLen = sectionSize;
                    }
                    strncpy (sectionPtr, &newLine[startPos], sectionLen);
                    // strncpy() does not add the '\0' if it copies to max.
                    sectionPtr[sectionLen] = '\0';

                    status = true;
                } // end of if (']'
            } // end of if ('['
        } // end of if (LINE_SECTION

#if DEBUG_INIPARSER > 0
        ShowResult (line, sectionPtr, status);
#endif // DEBUG_INIPARSER

    } // end of NULL checks

    return status;
}

/*--------------------------------------------------------------------------*/
bool GetTagFromLine (const char line[], char *tagPtr, size_t tagSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != tagPtr) && (0 != tagSize))
    {
        char tempLine[LINE_MAX_LEN] = {0};

        // Remove comments.
        RemoveComments (line, tempLine, sizeof(tempLine));

        if (LINE_TAGVALUE == GetLineType (tempLine))
        {
            char newLine[LINE_MAX_LEN] = {0};

            RemoveSpacesAroundEqual (tempLine, newLine, sizeof(newLine));

            const char *equalPtr = strchr (newLine, '=');

            if (NULL != equalPtr) // '=' found.
            {
                // Length from first character to '='.
                size_t tagLen = (equalPtr - &newLine[0]);

                if (tagLen > tagSize)
                {
                    tagLen = tagSize;
                }

                strncpy (tagPtr, &newLine[0], tagLen);
                // strncpy() does not add the '\0' if it copies to max.
                tagPtr[tagLen] = '\0';

                status = true;
            } // if (NULL != equalPtr)
        } // end of if (LINE_TAGVALUE

#if DEBUG_INIPARSER > 0
        ShowResult (line, tagPtr, status);
#endif // DEBUG_INIPARSER
    } // end of NULL checks

    return status;
}

/*--------------------------------------------------------------------------*/
bool GetValueFromLine (const char line[], char *valuePtr, size_t valueSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != valuePtr) && (0 != valueSize))
    {
        char newLine[LINE_MAX_LEN] = {0};

        // Remove comments.
        RemoveComments (line, newLine, sizeof(newLine));

        if (LINE_TAGVALUE == GetLineType (newLine))
        {
            const char *equalPtr = strchr (newLine, '=');

            if (NULL != equalPtr)
            {
                // Prevent trying to copy a Value if there is nothing after
                // the '='.
                size_t lineLen = strlen (newLine);

                if (lineLen > (size_t)(equalPtr - &newLine[0]))
                {
                    int startPos = ((equalPtr - &newLine[0]) + 1);
                    int endPos = lineLen - 1;

                    // Scan forward to first non whitespace character.
                    while (startPos < endPos && iswspace (newLine[startPos]))
                    {
                        startPos++;
                    }

                    // Scan backwards to first non whitespace character.
                    while (endPos > startPos && iswspace (newLine[endPos]))
                    {
                        endPos--;
                    }

                    // Length from after = to end of string.
                    size_t valueLen = endPos - startPos + 1;

                    if (valueLen > valueSize)
                    {
                        valueLen = valueSize;
                    }

                    strncpy (valuePtr, &newLine[startPos], valueLen);
                    // strncpy() does not add the '\0' if it copies to max.
                    valuePtr[valueLen] = '\0';

                    status = true;
                }
            } // end of if (NULL != equalPtr)
        } // end of if (LINE_TAGVALUE

#if DEBUG_INIPARSER > 0
        ShowResult (line, valuePtr, status);
#endif // DEBUG_INIPARSER
    } // end of NULL checks

    return status;
}

/*--------------------------------------------------------------------------*/
const char *LineTypeToStringPtr (LineTypeEnum lineType)
{
    const char *ptr = "Unknown";

    switch (lineType)
    {
        default:
        case LINE_INVALID:
            ptr = "Invalid";
            break;

        case LINE_EMPTY:
            ptr = "Empty";
            break;

        case LINE_COMMENT:
            ptr = "Comment";
            break;

        case LINE_SECTION:
            ptr = "Section";
            break;

        case LINE_TAGVALUE:
            ptr = "Tag=Value";
            break;
    }

    return ptr;
}

/*--------------------------------------------------------------------------*/
// Build a new string that has any "; comments" removed. This will be used
// if we have "Key=Value ; here are some comments".
bool RemoveComments (const char line[], char *newLinePtr, size_t newLineSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != newLinePtr) && (0 != newLineSize))
    {
        // Find ';'
        const char *ptr = strchr (line, ';');

        if (NULL != ptr)
        {
            size_t trimSize = (ptr - &line[0]);

            // Make sure this does not exceed the newLineSize
            if (trimSize > newLineSize)
            {
                trimSize = newLineSize;
            }

            // Copy up to the ';' into the new string buffer.
            strncpy (newLinePtr, line, trimSize);
            // strncpy() does not add the '\0' if it copies to max.
            newLinePtr[trimSize] = '\0';

            // TODO: This may have a bug if the line is exactly the size of the buffer.
        }
        else // Just copy the original.
        {
            strncpy (newLinePtr, line, newLineSize);
            // strncpy() does not add the '\0' if it copies to max.
            newLinePtr[newLineSize] = '\0';
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RemoveSpacesAroundEqual (const char line[], char *newLinePtr,
                              size_t newLineSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != newLinePtr) && (0 != newLineSize))
    {
        // Find '='.
        const char *equalPtr = strchr (line, '=');

        if (NULL != equalPtr) // If '=' was found...
        {
            // Scan back from equal to find first non whitespace character.
            int endPos = (equalPtr - &line[0] - 1);

            while (endPos > 0 && iswspace (line[endPos]))
            {
                endPos--;
            }

            // Copy up to this point to the new string.
            strncpy (newLinePtr, line, endPos + 1);
            // Appent the '='
            strcat (newLinePtr, "=");

            // Scan forward from equal to first non whitespace character.
            size_t startPos = (equalPtr - &line[0] + 1);

            while (startPos < strlen(line) && iswspace (line[startPos]))
            {
                startPos++;
            }

            // Append from here to the end to the new string.
            strcat (newLinePtr, &line[startPos]);

            status = true;
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// For a line to be empty, it must have nothing or only whitespace.
bool IsLineEmpty (const char line[])
{
    bool status = false;

    if (NULL != line)
    {
        // Step 1: Look for any non-whitespace.
        size_t lineLen = strlen (line);
        size_t pos = 0;

        while (pos < lineLen)
        {
            // If non-whitespace found, this is not an empty line.
            if (!iswspace (line[pos]))
            {
                status = false;
                break;
            }

            pos++;
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// For a line to be a comment, it must have a ";" as the first non-whitespace
// character.
bool IsLineAComment (const char line[])
{
    bool status = false;

    if (NULL != line)
    {
        size_t lineLen = strlen (line);
        size_t pos = 0;

        // Skip any whitespace, looking for ";"
        while ((pos < lineLen) && iswspace (line[pos]))
        {
            pos++;
        }

        // Here, we found our first non-whitespace character. If it is
        // a semicolon, this is a valid comment line.
        if (';' == line[pos])
        {
            status = true;
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// For a line to be a section, it must have a "[" as the first non-whitespace
// character, then printable character(s), then a "]" with nothing allowed
// after it other than a ";" comment.
bool IsLineASection (const char line[])
{
    bool status = false;

    if (NULL != line)
    {
        size_t lineLen = strlen (line);
        size_t pos = 0;

        // Step 1: Find the first "[".

        // Skip any whitespace.
        while ((pos < lineLen) && iswspace (line[pos]))
        {
            pos++;
        }

        // Here, we found our first non-whitespace character. If it is
        // a "[", this is a valid comment line.
        if ('[' == line[pos])
        {
            // Step 2: Fine some text.

            // Now we need to find at least one non-whitespace character.
            // Skip any whitespace.
            while ((pos < lineLen) && iswspace (line[pos]))
            {
                pos++;
            }
            // Here, we found another non-whitespace character. If it
            // is NOT "]", we can continue;

            if (']' != line[pos])
            {
                // Step 3: Find the closing "]".

                // Not we need to scan forward looking for the "]".
                while (pos < lineLen)
                {
                    if (']' == line[pos])
                    {
                        status = true;
                        break;
                    }

                    pos++;
                }
            } // end of if (']'
        } // end of if ('['
    } // end of if (NULL

    return status;
}


/*--------------------------------------------------------------------------*/
// For a line to be a valid "Tag = Value", it must contain printable
// character(s), then an equal, then printable character(s).
bool IsLineATagValue (const char line[])
{
    bool status = false;

    if (NULL != line)
    {
        char *equalPtr = strchr (line, '=');

        // Only continue if the line has an '='
        if (NULL != equalPtr)
        {
            size_t lineLen = strlen (line);
            size_t pos = 0;
            size_t endPos = (equalPtr - &line[0]);

            // Skip any whitespace.
            while ((pos < endPos) && iswspace (line[pos]))
            {
                pos++;
            }

            if (pos < endPos)
            {
                // Found some before the '='. Good.

                // Now look for some after the '='.

                pos = endPos + 1;

                while (pos < lineLen)
                {
                    if (isprint (line[pos]))
                    {
                        // Found non-whitespace.
                        status = true;
                        break;
                    }
                }
            } // end of if (pos < endPos)
        } // end of if (NULL != equalPtr)
    } // end of if (NULL != line)

    return status;
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/
static void ShowResult (const char line[], const char item[], bool status)
{
    printf ("'%s'%-*s'%s'\n", line,
            (int)(40-strlen(line)-2), "",
            (true == status) ? item : "false");
}

// End of INIParser.c
