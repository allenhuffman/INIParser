/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
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

        if ('\0' == line[0]) // TODO: '\0'
        {
            lineType = LINE_EMPTY;
        }
        else if (';' == line[0]) // Check for Comment
        {
            lineType = LINE_COMMENT;
        }
        else if ('[' == line[0]) // TODO: also check for ']'
        {
            lineType = LINE_SECTION;
        }
        else if (NULL != strchr(line, '=')) // TODO: improve!
        {
            lineType = LINE_KEYVALUE;
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

            if (lineLen > 1)
            {
                strncpy (commentPtr, &line[1], commentSize);
                // strncpy() does not add the '\0' if it copies to max.
                commentPtr[commentSize] = '\0';

                // TODO: possible bug if line is size of buffer.
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
            // Belt and suspenders.
            if ('[' == newLine[0]) // First character must be a '['
            {
                const char *endPtr = NULL;

                // Find end of Section Name
                endPtr = strchr (newLine, ']');

                if (NULL != endPtr) // Start '[' found.
                {
                    size_t sectionLen = (endPtr - &newLine[1]);

                    if (sectionLen > sectionSize)
                    {
                        sectionLen = sectionSize;
                    }

                    // Copy inbetween over.
                    strncpy (sectionPtr, &newLine[1], sectionLen);
                    // strncpy() does not add the '\0' if it copies to max.
                    sectionPtr[sectionLen] = '\0';

                    // TODO: should we trim? "[ this is a section ]"?
                    status = true;
                }
            } // end of if ('[' == line[0])
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
        char newLine[LINE_MAX_LEN] = {0};

        // Remove comments.
        RemoveComments (line, newLine, sizeof(newLine));

        if (LINE_KEYVALUE == GetLineType (newLine))
        {
            const char *equalPtr = strchr (newLine, '=');

            if (NULL != equalPtr) // '=' found.
            {
                size_t tagLen = equalPtr - &newLine[0];

                if (tagLen > tagSize)
                {
                    tagLen = tagSize;
                }

                strncpy (tagPtr, &newLine[0], tagLen);
                // strncpy() does not add the '\0' if it copies to max.
                tagPtr[tagLen] = '\0';

                status = true;
            } // if (NULL != equalPtr)
        } // end of if (LINE_KEYVALUE

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

        if (LINE_KEYVALUE == GetLineType (newLine))
        {
            const char *equalPtr = strchr (newLine, '=');

            if (NULL != equalPtr)
            {
                // Prevent trying to copy a Value if there is nothing after
                // the '='.
                size_t lineLen = strlen (newLine);

                if (lineLen > (size_t)(equalPtr - &newLine[0]))
                {
                    // Length from after = to end of string.
                    size_t valueLen = strlen (equalPtr + 1);

                    if (valueLen > valueSize)
                    {
                        valueLen = valueSize;
                    }

                    strncpy (valuePtr, equalPtr+1, valueLen);
                    // strncpy() does not add the '\0' if it copies to max.
                    valuePtr[valueLen] = '\0';

                    status = true;
                }
            } // end of if (NULL != equalPtr)
        } // end of if (LINE_KEYVALUE

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

        case LINE_KEYVALUE:
            ptr = "Key=Value";
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
// Private Functions
/*--------------------------------------------------------------------------*/
static void ShowResult (const char line[], const char item[], bool status)
{
    printf ("'%s'%-*s'%s'\n", line,
            (int)(40-strlen(line)-2), "",
            (true == status) ? item : "false");
}

// End of INIParser.c
