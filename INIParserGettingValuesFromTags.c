/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>
#include <stdlib.h> // for atoi()
#include <string.h> // for strcmp()

// This project's header
#include "INIParser.h"

// This file's header
#include "INIParserGettingValuesFromTags.h"

// Other headers
#include "ErrnoToCVIStatus.h"
#include "INIFileParser.h"

/*--------------------------------------------------------------------------*/
// Constants
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

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Getting Values from Tags
/*--------------------------------------------------------------------------*/
int Ini_GetPointerToString (IniText handle, const char sectionName[],
                            const char tagName[], char **pointerToString)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != pointerToString) && (NULL != *pointerToString))
    {
        status = -1; // TODO
        // Copy string into static buffer
        // Return pointer to that static buffer
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetStringCopy (IniText handle, const char sectionName[],
                       const char tagName[], char **copyOfString)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != copyOfString) && (NULL != *copyOfString))
    {
        status = -1; // TODO
        // Malloc buffer
        // Copy value into buffer
        // Return point to buffer. User must free.
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetStringIntoBuffer (IniText handle, const char sectionName[],
                             const char tagName[], char buffer[],
                             size_t bufferSize)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != buffer))
    {
        if (true == RecordReadTagValue (handle, sectionName, tagName, buffer, bufferSize))
        {
            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetPointerToRawString (IniText handle, const char sectionName[],
                               const char tagName[], char **pointerToString)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != pointerToString) && (NULL != *pointerToString))
    {
        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetRawStringCopy (IniText handle, const char sectionName[],
                          const char tagName[], char **copyOfString)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != copyOfString) && (NULL != *copyOfString))
    {
        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetRawStringIntoBuffer (IniText handle, const char sectionName[],
                                const char tagName[], char buffer[],
                                size_t bufferSize)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != buffer))
    {
        (void)bufferSize;

        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetInt (IniText handle, const char sectionName[],
                const char tagName[], int *integerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != integerValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            *integerValue = atoi (value);

            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetUInt (IniText handle, const char sectionName[],
                 const char tagName[], unsigned int *unsignedIntegerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != unsignedIntegerValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            *unsignedIntegerValue = (unsigned int)strtoul (value, NULL, 0);

            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetDouble (IniText handle, const char sectionName[],
                   const char tagName[], double *doubleValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != doubleValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            *doubleValue = strtod (value, NULL);

            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetBoolean (IniText handle, const char sectionName[],
                    const char tagName[], int *booleanValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != booleanValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            // TODO: Manual is unclear. Need to test on LabWdindows and verify.
            if (0 == strcmp ("True", value))
            {
                *booleanValue = 1;
                status = 1;
            }
            else if (0 == strcmp ("False", value))
            {
                *booleanValue = 0;
                status = 1;
            }
            else
            {
                status = -1;
            }
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// Obtains a copy of the data block associated with tagName in the section identified by sectionName.
// You are responsible for freeing the data.
int Ini_GetData (IniText handle, const char sectionName[],
                 const char tagName[], unsigned char **data, size_t *dataSize)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != data) && (NULL != *data) && (NULL != dataSize))
    {
        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetInt64 (IniText handle, const char sectionName[],
                  const char tagName[], long long *integerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != integerValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            *integerValue = strtoll (value, NULL, 0);

            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetUInt64 (IniText handle, const char sectionName[],
                   const char tagName[],
                   unsigned long long *unsignedIntegerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != unsignedIntegerValue))
    {
        char value[VALUE_MAX_LEN] = {0};

        if (true == RecordReadTagValue (handle, sectionName, tagName, value, sizeof(value)))
        {
            *unsignedIntegerValue = strtoull (value, NULL, 0);

            status = 1; // A positive return value indicates that a tag/string pair was found.
        }
        else
        {
            status = 0; // A zero indicates that no tag/string pair was found.
        }
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

// End of INIParserGettingValuesFromTags.c
