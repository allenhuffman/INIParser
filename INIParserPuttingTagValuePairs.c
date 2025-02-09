/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>

// This project's header
#include "INIParser.h"

// This file's header
#include "INIParserPuttingTagValuePairs.h"

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
// Putting Tag/Value Pairs
/*--------------------------------------------------------------------------*/
int Ini_PutString (IniText handle, const char sectionName[],
                   const char tagName[], const char stringValue[])
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != stringValue))
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
int Ini_PutRawString (IniText handle, const char sectionName[],
                      const char tagName[], const char stringValue[])
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != stringValue))
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
int Ini_PutInt (IniText handle, const char sectionName[],
                const char tagName[], int integerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)integerValue;

        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutUInt (IniText handle, const char sectionName[],
                 const char tagName[], unsigned int unsignedIntegerValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)unsignedIntegerValue;

        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutDouble (IniText handle, const char sectionName[],
                   const char tagName[], double doubleValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)doubleValue;

        status = -1; // TODO
   }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutBoolean (IniText handle, const char sectionName[],
                    const char tagName[], int booleanValue)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)booleanValue;

        status = -1; // TODO
    }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutData (IniText handle, const char sectionName[],
                 const char tagName[], const unsigned char data[], long dataSize)
{
    int status = NO_ERROR;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != data))
    {
        (void)dataSize;

         status = -1; // TODO
   }
    else
    {
        status = NULL_POINTER_PASSED;
    }

    return status;
}

// End of INIParserPuttingTagValuePairs.c
