#define _CRT_SECURE_NO_WARNINGS
/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <errno.h> // for errno
#include <stdio.h>
#include <string.h> // for memset()

// This project's header
#include "INIParser.h"

// This file's header
#include "INIParserManagement.h"

// Other headers
#include "ErrnoToCVIStatus.h"
#include "INI.h"

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Global Variables
/*--------------------------------------------------------------------------*/
int g_automaticSorting = 0;

/*--------------------------------------------------------------------------*/
// Static Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Prototypes
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Management
/*--------------------------------------------------------------------------*/
IniText Ini_New (int automaticSorting)
{
    g_automaticSorting = automaticSorting; // TODO

    return (IniText)RecordInit ();
}

/*--------------------------------------------------------------------------*/
void Ini_Dispose (IniText handle)
{
    RecordTerm (handle); // This function will do a NULL check.
}

/*--------------------------------------------------------------------------*/
//int Ini_SetEncoding (IniText handle, IniFileEncodingType iniFileEncoding)
//int Ini_GetEncoding (IniText handle, IniFileEncodingType *iniFileEnding)
//void    Ini_Sort (IniText handle)
//void    Ini_DisableSorting (IniText handle)
//int Ini_SortInternally (IniText handle)
//void    Ini_DisableInternalSorting (IniText handle)

/*--------------------------------------------------------------------------*/
int Ini_WriteToFile (IniText handle, const char pathname[])
{
    int status = NO_ERROR;
    char buffer[LINE_MAX_LEN];

    if (NULL != handle)
    {
        FILE *fp = NULL;

        if (NULL == pathname)
        {
            fp = stdout;
        }
        else
        {
            // Open file for writing.
            fp = fopen (pathname, "w"); // Overwrite
        }

        if (NULL != fp)
        {
            RecordSeekToStart (handle);

            while (RecordGetNext (handle, buffer, sizeof(buffer)))
            {
                // TODO: error checking.
                fputs (buffer, fp);
            }

            fclose (fp);
        }
        else // File could not be created.
        {
            // Use errno
            printf ("Unable to create: '%s'\n", pathname);
            status = ErrnoToCVIStatus (errno);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_ReadFromFile (IniText handle, const char pathname[])
{
    int status = NO_ERROR;
    char line[LINE_MAX_LEN] = {0};
    char tag[TAG_MAX_LEN] = {0};
    char value[VALUE_MAX_LEN] = {0};
    unsigned int startPos = 0;
    unsigned int endPos = 0;

    if (NULL != handle)
    {
        FILE *fp;

        // Open file for reading.
        fp = fopen (pathname, "r");

        if (NULL != fp)
        {
            // Read file into records.
            while (!feof (fp))
            {
                memset (&line[0], 0x0, sizeof (line));

                if (NULL == fgets (&line[0], sizeof(line)-1, fp))
                {
                    // Error or end of file.
                    //status = ErrnoToCVIStatus (errno);
                    break;
                }

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

            fclose (fp);
        }
        else // File could not be opened.
        {
            status = ErrnoToCVIStatus (errno);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
//int Ini_WriteToRegistry (IniText handle, int rootKey, const char subkeyName[])
//int Ini_ReadFromRegistry (IniText handle,  int rootKey, const char subkeyName[])
//int Ini_WriteGeneric (IniText handle, Ini_OutputFunc outputFunction, void *outputDestination)
//int Ini_ReadGeneric (IniText handle, Ini_InputFunc inputFunction, void *inputSource)
//int Ini_CopySection (IniText handle, const char sectionToCopy[], IniText destination, int overwriteDuplicateSections)
//int Ini_CopySectionEx (IniText source, const char sectionToCopy[], IniText destination, const char destinationSectionToCopyTo[], int overwriteDuplicateSections)
//int Ini_SetTokens (IniText handle, char sectionNameStartCharacter, char sectionNameEndCharacter, const char valueSeparator[], const char commentMarker[])
//int Ini_SetSectionFilter (IniText handle, Ini_SectionFilterFunc sectionFilterFunction, void *callbackData)
//int Ini_SetDuplicateChecking (IniText handle, int checkForDuplicates)
//int Ini_SetAddQuotesToStrings (IniText handle, int addQuotesToStrings)
//int Ini_SetMaxValueLineLength (IniText handle, int maxValueLineLength)

// End of INIParserManagement.c
