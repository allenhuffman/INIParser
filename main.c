/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS

// This project's header

// This file's header

// Other headers
#include "INI.h"
#include "INIFileParser.h"
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

    printf ("Before - Allocated: %u\n", (unsigned int)GetSizeAllocated());

#ifdef REAL_TEST
    RecordHandle *handle = LoadINI ("Sample.ini");

    if (NULL != handle)
    {
        RecordWriteSectionTagValue (handle, "http", "port", "4242");
        RecordShowAll (handle);
    }

    CloseINI (handle);
#endif

#ifdef MANUAL_TEST
    RecordHandle *handle = RecordInit ();

    if (NULL != handle)
    {
        // Create a simple .ini file with comments
        RecordWriteComment (handle, "------------------------------------------");
        RecordWriteComment (handle, " INI Parser Test on "__DATE__" "__TIME__);
        RecordWriteComment (handle, "------------------------------------------");

        RecordWriteUnknown (handle, ""); // Add a blank line.

        RecordWriteComment (handle, "This is the manually-made section.");
        // Manually write a [Section]
        RecordWriteSection (handle, "ManualSection");
        // Manually write a Tag=Value
        RecordWriteTagValue (handle, "ManualTag", "ManualValue");

        RecordWriteUnknown (handle, ""); // Add a blank line.

        RecordWriteComment (handle, "This is the first section.");
        // Manually write a [Section]
        RecordWriteSection (handle, "FirstSection");
        // Add tag to ths existing [Section]:
        RecordWriteSectionTagValue (handle, "FirstSection", "FirstTag", "FirstValue");

        RecordWriteUnknown (handle, ""); // Add a blank line.

        RecordWriteComment (handle, "This is the second section.");

        // Add a new [Section] with a Tag=Value
        RecordWriteSectionTagValue (handle, "SecondSection", "SecondTag", "SecondValue");

        RecordWriteUnknown (handle, ""); // Add a blank line.

        // Add to existing entries...
        RecordWriteSectionTagValue (handle, "FirstSection", "FirstTag2", "FirstValue2");
        RecordWriteSectionTagValue (handle, "SecondSection", "SecondTag2", "SecondValue2");

        // Update existing entries:
        RecordWriteSectionTagValue (handle, "FirstSection", "FirstTag", "ReplacementFirstValue");
        RecordWriteSectionTagValue (handle, "SecondSection", "SecondTag", "ReplacementSecondValue");

        RecordWriteComment (handle, "------------------------------------------");
        RecordWriteComment (handle, " End of file.");
        RecordWriteComment (handle, "------------------------------------------");

        RecordShowAll (handle);

        printf ("After Allocation - Allocated: %u\n", (unsigned int)GetSizeAllocated());

        // Now let's try to read some...
        ReadAndShow (handle, "ManualSection", "ManualTag");

        ReadAndShow (handle, "FirstSection", "FirstTag");
        ReadAndShow (handle, "FirstSection", "FirstTag2");

        ReadAndShow (handle, "SecondSection", "SecondTag");
        ReadAndShow (handle, "SecondSection", "SecondTag2");


        RecordTerm (handle);
    }
#endif // MANUAL_TEST

    printf ("After Free - Allocated: %u\n", (unsigned int)GetSizeAllocated());

    return EXIT_SUCCESS;
}

/*--------------------------------------------------------------------------*/
void ReadAndShow (RecordHandle *handle, const char *section, const char *tag)
{
    bool status = false;
    char buffer[80] = {0};

    status = RecordReadTagValue (handle, section, tag, &buffer[0], sizeof(buffer));

    if (true == status)
    {
        printf ("%s=%s\n", tag, buffer);
    }
    else
    {
        printf ("%s= NOT found.\n", tag);
    }
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/

// End of Template.c
