/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>

// This project's header
#include "INIParser.h"

// This file's header
#include "INIParserGettingValuesFromTags.h"

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
        status = -1; // TODO
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
        status = -1; // TODO
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
        status = -1; // TODO
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
        (NULL == booleanValue))
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
        status = -1; // TODO
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
        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

// End of INIParserGettingValuesFromTags.c
