#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ErrnoToCVIStatus.h"
#include "INIParser.h"
#include "Utilities.h"

#include "INIRecords.h" // for testing the records.

#define INI_FILENAME "Sample.ini"

void PrintHeader (const char *header)
{
    printf ("\n"
            "%s\n"
            "-------------------------------------------------------------------------------\n",
            header);
}

int main()
{
    // Test some of the calls:
    char buffer[80] = {0};

    const char *testLines[] =
    {
        // Emtpy
        "",
        // Invalid
        "Hello World!",
        "=",
        "=Value",
        "Tag=",
        // Comments
        "; This is a comment",
        ";This is also a comment",
        // Sections
        "[This is a section]",
        "[ This is a section ]",
        "[This is a section] ; Comment",
        "[  This is a section  ] ; Comment",
        // Key/Value
        "Tag=Value",
        "Tag = Value",
        "Tag = Value ; Comment",
        NULL
    };

    int idx = 0;

    PrintHeader ("Line Types:");
    idx = 0;
    while (NULL != testLines[idx])
    {
        printf ("%2d) '%s'%-*s%s\n",
                idx, testLines[idx],
                (int)(40-strlen(testLines[idx])-2), "",
                LineTypeToStringPtr (GetLineType (testLines[idx])));

        idx++;
    }

    // Test Comment parser.
    PrintHeader ("Comments:");
    idx = 0;
    while (NULL != testLines[idx])
    {
        memset (buffer, 0x0, sizeof(buffer));
        printf ("%2d) ", idx);
        GetCommentFromLine (testLines[idx], &buffer[0], sizeof(buffer)-1);
        idx++;
    }

    // Test Section parser
    PrintHeader ("Sections:");
    idx = 0;
    while (NULL != testLines[idx])
    {
        printf ("%2d) ", idx);
        GetSectionFromLine (testLines[idx], &buffer[0], sizeof(buffer)-1);
        idx++;
    }

    // Test Tag parser
    PrintHeader ("Tags");
    idx = 0;
    while (NULL != testLines[idx])
    {
        printf ("%2d) ", idx);
        GetTagFromLine (testLines[idx], &buffer[0], sizeof(buffer)-1);
        idx++;
    }

    // Test Key parser
    PrintHeader ("Value");
    idx = 0;
    while (NULL != testLines[idx])
    {
        printf ("%2d) ", idx);
        GetValueFromLine (testLines[idx], &buffer[0], sizeof(buffer)-1);
        idx++;
    }

    exit (0);
#if 0
    // Test the INIRecords.
    bool status = false;

    RecordHandle handle = RecordInit ();

    if (NULL != handle)
    {
        // Write 10 lines...
        for (int idx = 1; idx <= 10; idx++)
        {
            char line[80];
            snprintf (line, sizeof(line), "This is line %d.", idx);

            status = RecordWrite (handle, line);

            if (false == status)
            {
                break;
            }
        } // end of for (int idx = 0

        if (true == status)
        {
            RecordShowAll (handle);
        }

        RecordTerm (handle);

        printf ("Done.\n");

    } // end of if (NULL != handle)

#endif

    // TEST CODE
    IniText iniText;

    iniText = Ini_New (0); // No automatic sorting.

    if (0 != iniText)
    {
        int             status = 0;
        unsigned int    httpPort = 0;
        char            httpUsername[80] = {0};

        unsigned int    httpsPort = 0;
        char            httpsUsername[80] = {0};

        unsigned int    ftpPort = 0;
        char            ftpUsername[80] = {0};


        status = Ini_ReadFromFile (iniText, INI_FILENAME);

        // TESTING:
        RecordShowAll (iniText);

        /*------------------------------------------------------------------*/
        // [http]
        /*------------------------------------------------------------------*/
        if (NO_ERROR == status)
        {
            status = Ini_GetUInt (iniText, "http", "port", &httpPort);
        }

        if (0 == status)
        {
            status = Ini_GetStringIntoBuffer (iniText, "http", "username",
                                              &httpUsername[0],
                                              sizeof(httpUsername)-1);
        }

        /*------------------------------------------------------------------*/
        // [https]
        /*------------------------------------------------------------------*/
        if (NO_ERROR == status)
        {
            status = Ini_GetUInt (iniText, "https", "port", &httpsPort);
        }

        if (NO_ERROR == status)
        {
            status = Ini_GetStringIntoBuffer (iniText, "https", "username",
                                              &httpsUsername[0],
                                              sizeof(httpsUsername)-1);
        }

        /*------------------------------------------------------------------*/
        // [ftp]
        /*------------------------------------------------------------------*/
        if (NO_ERROR == status)
        {
            status = Ini_GetUInt (iniText, "ftp", "port", &ftpPort);
        }

        if (NO_ERROR == status)
        {
            status = Ini_GetStringIntoBuffer (iniText, "ftp", "username",
                                              &ftpUsername[0],
                                              sizeof(ftpUsername)-1);
        }

        printf ("HTTP  %-5u - %s\n", httpPort, httpUsername);
        printf ("HTTPS %-5u - %s\n", httpPort, httpUsername);
        printf ("FTP   %-5u - %s\n", httpPort, httpUsername);

        Ini_Dispose (iniText);
    }

    return EXIT_SUCCESS;
}

// End of main.c
