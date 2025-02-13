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

    // Test 1 - Create .ini file with some sections and tag/values.

    printf ("Before Ini_New() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

    iniTxt = Ini_New (false); // No automatic sorting.

    if (NULL == iniTxt)
    {
        fprintf (stderr, "Unable to Ini_New()\n");
    }
    else
    {
        RecordWriteUnknown (iniTxt, "");
        RecordWriteComment (iniTxt, "Boolean Test");
        Ini_PutBoolean (iniTxt, "Booleans", "TagTrue", 1);
        Ini_PutBoolean (iniTxt, "Booleans", "TagFalse", 0);

        RecordWriteUnknown (iniTxt, "");
        RecordWriteComment (iniTxt, "String Test");
        Ini_PutString (iniTxt, "Strings", "String1", "No leading or trailing spaces.");
        Ini_PutString (iniTxt, "Strings", "String2", "   This one has leading spaces.");
        Ini_PutString (iniTxt, "Strings", "String3", "This one has trailing spaces.  ");

        RecordWriteUnknown (iniTxt, "");
        RecordWriteComment (iniTxt, "Integer Test");
        int integerValue = -42;
        Ini_PutInt (iniTxt, "Integers", "Integer1", integerValue);

        RecordWriteUnknown (iniTxt, "");
        RecordWriteComment (iniTxt, "Unsigned Integer Test");
        unsigned int unsignedIntegerValue = 42;
        Ini_PutInt (iniTxt, "Unsigned Integers", "UnsignedInteger1", unsignedIntegerValue);

        RecordWriteUnknown (iniTxt, "");
        RecordWriteComment (iniTxt, "Double Test");
        double doubleValue = -42.42;
        Ini_PutDouble (iniTxt, "Doubles", "Double", doubleValue);

        RecordShowAll (iniTxt);

        status = Ini_WriteToFile (iniTxt, "IniTest.ini");
        if (0 != status)
        {
            fprintf (stderr, "Ini_WriteToFile() error: %d\n", status);
        }
    }
    Ini_Dispose (iniTxt);

    printf ("After Ini_Dispose() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

    printf ("----------------------------------------------------------------------\n");

    // Test 12- Read values from .ini

    printf ("Before Ini_New() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

    iniTxt = Ini_New (false); // No automatic sorting.

    if (NULL == iniTxt)
    {
        fprintf (stderr, "Unable to Ini_New()\n");
    }
    else
    {
        printf ("Reading and parsing .ini file...\n");
        status = Ini_ReadFromFile (iniTxt, "IniTest.ini");

        if (0 != status)
        {
            fprintf (stderr, "Ini_ReadFromFile() error: %d\n", status);
        }
        else
        {
            RecordShowAll (iniTxt);

            int booleanValue = 0;

            Ini_GetBoolean (iniTxt, "Booleans", "TagTrue", &booleanValue);
            printf ("bool  : %d\n", booleanValue);
            Ini_GetBoolean (iniTxt, "Booleans", "TagFalse", &booleanValue);
            printf ("bool  : %d\n", booleanValue);

            char buffer[80] = {0};

            memset (buffer, 0, sizeof(buffer));
            Ini_GetStringIntoBuffer (iniTxt, "Strings", "String1", buffer, sizeof(buffer));
            printf ("string: '%s'\n", buffer);

            memset (buffer, 0, sizeof(buffer));
            Ini_GetStringIntoBuffer (iniTxt, "Strings", "String2", buffer, sizeof(buffer));
            printf ("string: '%s'\n", buffer);

            memset (buffer, 0, sizeof(buffer));
            Ini_GetStringIntoBuffer (iniTxt, "Strings", "String3", buffer, sizeof(buffer));
            printf ("string: '%s'\n", buffer);

            int integerValue = 0;
            Ini_GetInt (iniTxt, "Integers", "Integer1", &integerValue);
            printf ("int   : %d\n", integerValue);

            unsigned int unsignedIntegerValue = 42;
            Ini_GetUInt (iniTxt, "Unsigned Integers", "UnsignedInteger1", &unsignedIntegerValue);
            printf ("uint  : %u\n", unsignedIntegerValue);

            double doubleValue = 0;
            Ini_GetDouble (iniTxt, "Doubles", "Double", &doubleValue);
            printf ("double: %f\n", doubleValue);

        }

        Ini_Dispose (iniTxt);
    }

    printf ("After Ini_Dispose() - Allocated: %u\n", (unsigned int)GetSizeAllocated());

/*
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
*/

    return EXIT_SUCCESS;
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/

// End of Template.c
