/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS

// This project's header
#include "INIParser.h"

// This file's header

// Other headers
#include "MyMalloc.h"

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
// Static Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Prototypes
/*--------------------------------------------------------------------------*/
void ReadAndShow (RecordHandle *handle, const char *section, const char *tag);


/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/

#define REAL_TEST
int main (int argc, char **argv)
{
    (void)argc; // Not used.
    (void)argv; // Not used.

    IniText iniTxt;
    int status = 0; // INI Status

    printf ("Before Ini_New() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

    iniTxt = Ini_New (false); // No automatic sorting.

    if (NULL == iniTxt)
    {
        fprintf (stderr, "Unable to Ini_New()\n");
    }
    else
    {
        status = Ini_ReadFromFile (iniTxt, "Sample2.ini");

        if (status < 0) // 0 means success here.
        {
            fprintf (stderr, "Unable to read from file: %d\n", status);
        }
        else
        {
            printf ("After Ini_ReadFromFile() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

            RecordShowAll (iniTxt);

            printf ("Adding a new key to Exciter...\n");

            RecordWriteSectionTagValue (iniTxt, "Exciter", "FirmwareUpdate","Work");

            RecordShowAll (iniTxt);
        }

        Ini_Dispose (iniTxt);

        printf ("After Ini_Dispose() - Allocated: %u\n", (unsigned int)GetSizeAllocated());
    }

    return EXIT_SUCCESS;
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/

// End of Template.c
