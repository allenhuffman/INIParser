#define _CRT_SECURE_NO_WARNINGS
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

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/
bool FindFirstAndLastNonWhitespace (const char *line, unsigned int *startPos, unsigned int *endPos, bool removeComments)
{
    bool status = false;

    if ((NULL != line) && (NULL != startPos) && (0 != endPos))
    {
        size_t len = strlen (line);
        unsigned int start = 0;
        unsigned int end = (unsigned int)len - 1;

        if (true == removeComments)
        {
            char *semiPtr = strchr (line, ';');

            if (NULL != semiPtr)
            {
                end = (unsigned int)(semiPtr - line - 1);
            }
        }

        // Find first non-whitespace character
        while ((start < len) && (isspace((unsigned char)line[start])))
        {
            start++;
        }

        // Find last non-whitespace character
        while ((end > start) && (isspace((unsigned char)line[end])))
        {
            end--;
        }

        *startPos = start;
        *endPos = end;

        status = true;
    }

    return status;
}

bool ParseSection (const char *line, char *section, size_t sectionSize)
{
    bool status = false;
    unsigned int startPos = 0;
    unsigned int endPos = 0;

    if ((NULL != line) && (NULL != section) && (0 != sectionSize))
    {
        //if (true == TrimString (line, trimmedLine, sizeof(trimmedLine), true))
        if (true == FindFirstAndLastNonWhitespace (line, &startPos, &endPos, true))
        {
            if (('[' == line[startPos]) && (']' == line[endPos]))
            {
                memcpy (section, &line[startPos+1], endPos-startPos-1);
                section[endPos - startPos] = '\0';

                status = true;
            }
        }
    }

    return status;
}

bool ParseTagValue (const char *line, char *tag, size_t tagSize,
                           char *value, size_t valueSize)
{
    bool status = false;
    char left[80] = {0};
    char right[80] = {0};
    unsigned int startPos = 0;
    unsigned int endPos = 0;

    if ((NULL != line) && (NULL != tag) && (0 != tagSize) &&
        (NULL != value) && (0 != valueSize))
    {
        // Split the line at the '='
        char *equalPtr = strchr (line, '=');

        if (NULL != equalPtr)
        {
            strncpy (left, line, equalPtr-line);
            //TrimString (left, tag, tagSize, false);
            if (FindFirstAndLastNonWhitespace (left, &startPos, &endPos, false))
            {
                memcpy (tag, &left[startPos], endPos-startPos + 1);
                tag[endPos + 1] = '\0';
            }

            strncpy (right, equalPtr+1, sizeof(right)-1); // compiler warning fixed
            //TrimString (right, value, valueSize, true);
            if (FindFirstAndLastNonWhitespace (right, &startPos, &endPos, false))
            {
                memcpy (value, &right[startPos], endPos-startPos + 1);
                value[endPos-startPos + 1] = '\0';
            }

            status = true;
        }
    }

    return status;
}

#if defined(INCLUDE_INI_LOADER)
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
    char tag[80] = {0};
    char value[80] = {0};
    unsigned int startPos = 0;
    unsigned int endPos = 0;

    if (NULL != fp)
    {
        while (!feof (fp))
        {
            if (NULL != fgets (line, sizeof(line), fp))
            {
                //TrimString (line, tempLine, sizeof(tempLine), false);
                if (FindFirstAndLastNonWhitespace (line, &startPos, &endPos, false))
                {
                    line[endPos + 1] = '\0';

                    if (';' == line[startPos])
                    {
                        RecordWriteComment (handle, &line[startPos+1]); // Skip semicolon
                    }
                    else if ('[' == line[0])
                    {
                        char section[80] = {0};
                        if (true == ParseSection (&line[startPos], section, sizeof(section)))
                        {
                            RecordWriteSection (handle, section);
                        }
                    }
                    else if (true == ParseTagValue (&line[startPos], tag, sizeof(tag), value, sizeof(value)))
                    {
                        RecordWriteTagValue (handle, tag, value);
                    }
                    else
                    {
                        if (('\n' == line[0]) || ('\r' == line[0]))
                        {
                            line[0] = '\0';
                        }
                        RecordWriteUnknown (handle, line);
                    }
                }
            }
        }
    }

    return status;
}


bool CloseINI (RecordHandle *handle)
{
    return RecordTerm (handle);
}
#endif // INCLUDE_INI_LOADER

/*--------------------------------------------------------------------------*/
// Static Private Functions
/*--------------------------------------------------------------------------*/

// End of Template.c
