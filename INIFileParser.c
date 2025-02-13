/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <ctype.h>  // for iswhite()
#include <stdio.h>
#include <string.h> // for strchr()

// This project's header

// This file's header
#include "INIFileParser.h"

// Other headers

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Static Private Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Prototypes
/*--------------------------------------------------------------------------*/
static bool TrimString (const char *line, char *newLine, size_t newLineSize);

static bool ParseSection (const char *line, char *section, size_t sectionSize);

static bool ParseTagValue (const char *line, char *tag, size_t tagSize, char *value, size_t valueSize);

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/
RecordHandle LoadINI (const char *filename)
{
    RecordHandle *handle = NULL;
    FILE *fp = NULL;

    if (NULL != filename)
    {
        fp = fopen (filename, "r");

        if (NULL != fp)
        {
            handle = RecordInit ();

            FileToRecords (fp, handle);
        }

        fclose (fp);

    }

    return handle;
}

bool FileToRecords (FILE *fp, RecordHandle *handle)
{
    bool status = false;
    char line[256] = {0};
    char tempLine[256] = {0};
    char tag[80] = {0};
    char value[80] = {0};

    if (NULL != fp)
    {
        while (!feof (fp))
        {
            if (NULL != fgets (line, sizeof(line), fp))
            {
                TrimString (line, tempLine, sizeof(tempLine));

                if (';' == tempLine[0])
                {
                    RecordWriteComment (handle, tempLine+1); // Skip semicolon
                }
                else if ('[' == tempLine[0])
                {
                    char section[80] = {0};
                    if (true == ParseSection (tempLine, section, sizeof(section)))
                    {
                        RecordWriteSection (handle, section);
                    }
                }
                else if (true == ParseTagValue (tempLine, tag, sizeof(tag), value, sizeof(value)))
                {
                    RecordWriteTagValue (handle, tag, value);
                }
                else
                {
                    RecordWriteUnknown (handle, tempLine);
                }
            }
        }
    }

    return status;
}


bool CloseINI (RecordHandle *handle)
{
    bool status = false;

    (void)handle; // Unused for now.

    return status;
}

/*--------------------------------------------------------------------------*/
// Static Private Functions
/*--------------------------------------------------------------------------*/
static bool TrimString (const char *line, char *newLine, size_t newLineSize)
{
    bool status = false;

    if ((NULL != line) && (NULL != newLine) && (0 != newLineSize))
    {
        size_t len = strlen (line);
        unsigned int startPos = 0;
        unsigned int endPos = len;

        // Find first non-whitespace character
        while ((startPos < len) && (isspace((unsigned char)line[startPos])))
        {
            startPos++;
        }

        // Find last non-whitespace character
        while ((endPos > startPos) && (isspace((unsigned char)line[endPos - 1])))
        {
            endPos--;
        }

        strncpy (newLine, &line[startPos], endPos-startPos);
        newLine[endPos-startPos] = '\0';

        status = true;
    }

    return status;
}

static bool ParseSection (const char *line, char *section, size_t sectionSize)
{
    bool status = false;
    char newLine[80] = {0};

    if ((NULL != line) && (NULL != section) && (0 != sectionSize))
    {
        if (true == TrimString (line, newLine, sizeof(newLine)))
        {
            size_t len = strlen (newLine);

            if (('[' == newLine[0]) && (']' == newLine[len-1]))
            {
                char tempLine[80] = {0};

                memcpy (tempLine, &newLine[1], len-2);

                TrimString (tempLine, section, sectionSize);

                status = true;
            }
        }
    }

    return status;
}

static bool ParseTagValue (const char *line, char *tag, size_t tagSize,
                           char *value, size_t valueSize)
{
    bool status = false;
    char left[80] = {0};
    char right[80] = {0};

    if ((NULL != line) && (NULL != tag) && (0 != tagSize) &&
        (NULL != value) && (0 != valueSize))
    {
        // Split the line at the '='
        char *equalPtr = strchr (line, '=');

        if (NULL != equalPtr)
        {
            strncpy (left, line, equalPtr-line);
            TrimString (left, tag, tagSize);
            tag[tagSize-1] = '\0';

            strncpy (right, equalPtr+1, sizeof(right));
            TrimString (right, value, valueSize);
            value[tagSize-1] = '\0';

            status = true;
        }
    }

    return status;
}

// End of Template.c
