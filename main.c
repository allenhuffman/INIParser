#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "INIParser.h"
#include "Utilities.h"

#include "INIRecords.h" // for testing the records.

#define INI_FILENAME "Sample.ini"

int main()
{
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
#if 0
    // TEST CODE
    IniText iniText;

    iniText = Ini_New (0); // No automatic sorting.

    if (0 != iniText)
    {
        int             status = 0;
        unsigned int    httpPort = 0;
        char            httpUsername[80];

        unsigned int    httpsPort = 0;
        char            httpsUsername[80];

        unsigned int    ftpPort = 0;
        char            ftpUsername[80];

        status = Ini_ReadFromFile (iniText, INI_FILENAME);

        /*------------------------------------------------------------------*/
        // [http]
        /*------------------------------------------------------------------*/
        if (0 == status)
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
        if (0 == status)
        {
            status = Ini_GetUInt (iniText, "https", "port", &httpsPort);
        }

        if (0 == status)
        {
            status = Ini_GetStringIntoBuffer (iniText, "https", "username",
                                              &httpsUsername[0],
                                              sizeof(httpsUsername)-1);
        }

        /*------------------------------------------------------------------*/
        // [ftp]
        /*------------------------------------------------------------------*/
        if (0 == status)
        {
            status = Ini_GetUInt (iniText, "ftp", "port", &ftpPort);
        }

        if (0 == status)
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
#endif

    return EXIT_SUCCESS;
}

// End of main.c
