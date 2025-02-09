/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>

// This project's header
#include "INIParser.h"

// This file's header
#include "INIParserManagement.h"

// Other headers
#include "ErrnoToCVIStatus.h"
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
    RecordTerm (handle);
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
            fp = fopen (pathname, "w+"); // Overwrite

            if (NULL == fp)
            {

                fclose (fp);
            }
            else // File could not be created.
            {
                // Use errno
                status = ErrnoToCVIStatus (errno);
            }
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_ReadFromFile (IniText handle, const char pathname[])
{
    int status = NO_ERROR;

    if (NULL != handle)
    {
        FILE *fp;

        // Open file for reading.
        fp = fopen (pathname, "r");

        if (NULL != fp)
        {

            fclose (fp);
        }
        else // File could not beopened.
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
