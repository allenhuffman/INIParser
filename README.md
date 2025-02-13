This is a work-in-progress attempt to create .ini file parsing routines that follow the same API used by LabWindows/CVI 2017.

https://www.ni.com/docs/en-US/bundle/labwindows-cvi/page/toolslib/toolslibreadingwriting_inistyle_files_co.htm

I have some code originally written using LabWindows/CVI that I want to build using the GNU-C compiler (or any other C compiler).

This code is being built in Code::Blocks for Windows:

https://www.codeblocks.org/

...but the C code should be fairly "strict ANSI" and work on any C compiler.

Supported Functions (so far)
-------------------------------------------------------------------------------
**Management**

    IniText Ini_New (int automaticSorting);
    
    void    Ini_Dispose (IniText handle);
    
    int     Ini_WriteToFile (IniText handle, const char pathname[]);
    
    int     Ini_ReadFromFile (IniText handle, const char pathname[]);

**Getting Values from Tags**

    int     Ini_GetStringIntoBuffer (IniText handle, const char sectionName[],
                                    const char tagName[], char buffer[],
                                    size_t bufferSize);

    int     Ini_GetInt (IniText handle, const char sectionName[],
                        const char tagName[], int *integerValue);

    int     Ini_GetUInt (IniText handle, const char sectionName[],
                        const char tagName[],
                        unsigned int *unsignedIntegerValue);

    int     Ini_GetDouble (IniText handle, const char sectionName[],
                        const char tagName[], double *doubleValue);

    int     Ini_GetBoolean (IniText handle, const char sectionName[],
                            const char tagName[], int *booleanValue);

    int     Ini_GetInt64 (IniText handle, const char sectionName[],
                        const char tagName[], long long *integerValue);

    int     Ini_GetUInt64 (IniText handle, const char sectionName[],
                        const char tagName[],
                        unsigned long long *unsignedIntegerValue);

**Putting Tag Value Pairs**

    int     Ini_PutString (IniText handle, const char sectionName[],
                        const char tagName[], const char stringValue[]);

    int     Ini_PutInt (IniText handle, const char sectionName[],
                        const char tagName[], int integerValue);

    int     Ini_PutUInt (IniText handle, const char sectionName[],
                        const char tagName[], unsigned int unsignedIntegerValue);

    int     Ini_PutDouble (IniText handle, const char sectionName[],
                        const char tagName[], double doubleValue);

    int     Ini_PutBoolean (IniText handle, const char sectionName[],
                            const char tagName[], int booleanValue);

**Informational**

None.

**Removing Sections and Items**

None.

**Extended Functions**

The underlying code that handles parsing the .ini file into a linked list of records also has a few extra functions that I wish LabWindows had included. For instance, when creating an .ini file, you can add extra blank lines or comments:

    bool RecordWriteUnknown (RecordHandle *handle, const char *unknown);

    bool RecordWriteComment (RecordHandle *handle, const char *comment);

See the usage example below for a usage example... below.

There is also a debug function that will print out the contents of the in-memory .ini file:

    bool RecordShowAll (RecordHandle *handle);

Usage Example
-------------------------------------------------------------------------------
Follow the examples from the LabWindows/CVI documentation.

**Creating an .ini file**
````
#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS
#include <string.h> // for memset();

#include "INIParser.h"

int main (int argc, char **argv)
{
    (void)argc; // Not used.
    (void)argv; // Not used.

    IniText iniTxt;
    int status = 0; // INI Status

    // Create .ini file with some sections and tag/values.

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

    return EXIT_SUCCESS;
}
````

**Reading from an existing .ini file**

````
#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS
#include <string.h> // for memset();

#include "INIParser.h"

int main (int argc, char **argv)
{
    (void)argc; // Not used.
    (void)argv; // Not used.

    IniText iniTxt;
    int status = 0; // INI Status

    // Read values from .ini

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
            int booleanValue = 0;
            Ini_GetBoolean (iniTxt, "Booleans", "BooleanTag", &booleanValue);
            printf ("bool  : %d\n", booleanValue);

            char buffer[80] = {0};
            Ini_GetStringIntoBuffer (iniTxt, "Strings", "StringTag", buffer, sizeof(buffer));
            printf ("string: '%s'\n", buffer);

            int integerValue = 0;
            Ini_GetInt (iniTxt, "Integers", "IntegerTag", &integerValue);
            printf ("int   : %d\n", integerValue);

            unsigned int unsignedIntegerValue = 0;
            Ini_GetUInt (iniTxt, "Unsigned Integers", "UnsignedIntegerTag", &unsignedIntegerValue);
            printf ("uint  : %u\n", unsignedIntegerValue);

            double doubleValue = 0;
            Ini_GetDouble (iniTxt, "Doubles", "DoubleTag", &doubleValue);
            printf ("double: %f\n", doubleValue);

        }

        Ini_Dispose (iniTxt);
    }

    return EXIT_SUCCESS;
}
````

This code is fresh and has only been lightly tested. There are still many more things that need to be done to "harden" it up against things like buffer overflows and such. But, it is a good starting point if you need something like this.
