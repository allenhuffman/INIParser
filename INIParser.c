#include <stdio.h>

#include "INIParser.h"

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/
#define MAX_PATHNAME_LEN    256 // TODO

/*--------------------------------------------------------------------------*/
// Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Static Variables
/*--------------------------------------------------------------------------*/
int S_automaticSorting = 0;


/*--------------------------------------------------------------------------*/
// Management
/*--------------------------------------------------------------------------*/
IniText Ini_New (int automaticSorting)
{
    IniText iniText = NULL;

    S_automaticSorting = automaticSorting;

    return iniText;
}

/*--------------------------------------------------------------------------*/
void Ini_Dispose (IniText handle)
{
    if (NULL != handle)
    {

    }
}

//int Ini_SetEncoding (IniText handle, IniFileEncodingType iniFileEncoding)
//int Ini_GetEncoding (IniText handle, IniFileEncodingType *iniFileEnding)
//void    Ini_Sort (IniText handle)
//void    Ini_DisableSorting (IniText handle)
//int Ini_SortInternally (IniText handle)
//void    Ini_DisableInternalSorting (IniText handle)

/*--------------------------------------------------------------------------*/
int Ini_WriteToFile (IniText handle, const char pathname[])
{
    int status = 0;

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
            fp = fopen (pathname, "w");

            fclose (fp);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_ReadFromFile (IniText handle, const char pathname[])
{
    int status = 0;

    if (NULL != handle)
    {
        FILE *fp;

        if (NULL == pathname)
        {
            fp = stdout;
        }
        else
        {
            // Open file for reading.
            fp = fopen (pathname, "r");

            fclose (fp);
        }
    }

    return status;
}

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

/*--------------------------------------------------------------------------*/
// Putting Tag/Value Pairs
/*--------------------------------------------------------------------------*/
int Ini_PutString (IniText handle, const char sectionName[],
                   const char tagName[], const char stringValue[])
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != stringValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutRawString (IniText handle, const char sectionName[],
                      const char tagName[], const char stringValue[])
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != stringValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutInt (IniText handle, const char sectionName[],
                const char tagName[], int integerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)integerValue;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutUInt (IniText handle, const char sectionName[],
                 const char tagName[], unsigned int unsignedIntegerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)unsignedIntegerValue;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutDouble (IniText handle, const char sectionName[],
                   const char tagName[], double doubleValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)doubleValue;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutBoolean (IniText handle, const char sectionName[],
                    const char tagName[], int booleanValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName))
    {
        (void)booleanValue;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_PutData (IniText handle, const char sectionName[],
                 const char tagName[], const unsigned char data[], long dataSize)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != data))
    {
        (void)dataSize;
    }

    return status;
}


/*--------------------------------------------------------------------------*/
// Getting Values from Tags
/*--------------------------------------------------------------------------*/
int Ini_GetPointerToString (IniText handle, const char sectionName[],
                            const char tagName[], char **pointerToString)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != pointerToString) && (NULL != *pointerToString))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetStringCopy (IniText handle, const char sectionName[],
                       const char tagName[], char **copyOfString)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != copyOfString) && (NULL != *copyOfString))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetStringIntoBuffer (IniText handle, const char sectionName[],
                             const char tagName[], char buffer[],
                             size_t bufferSize)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != buffer))
    {
        (void)bufferSize;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetPointerToRawString (IniText handle, const char sectionName[],
                               const char tagName[], char **pointerToString)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != pointerToString) && (NULL != *pointerToString))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetRawStringCopy (IniText handle, const char sectionName[],
                          const char tagName[], char **copyOfString)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != copyOfString) && (NULL != *copyOfString))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetRawStringIntoBuffer (IniText handle, const char sectionName[],
                                const char tagName[], char buffer[],
                                size_t bufferSize)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != buffer))
    {
        (void)bufferSize;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetInt (IniText handle, const char sectionName[],
                const char tagName[], int *integerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != integerValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetUInt (IniText handle, const char sectionName[],
                 const char tagName[], unsigned int *unsignedIntegerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != unsignedIntegerValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetDouble (IniText handle, const char sectionName[],
                   const char tagName[], double *doubleValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != doubleValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetBoolean (IniText handle, const char sectionName[],
                    const char tagName[], int *booleanValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL == booleanValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetData (IniText handle, const char sectionName[],
                 const char tagName[], unsigned char **data, size_t *dataSize)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != data) && (NULL != *data) && (NULL != dataSize))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetInt64 (IniText handle, const char sectionName[],
                  const char tagName[], long long *integerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != integerValue))
    {

    }

    return status;
}

/*--------------------------------------------------------------------------*/
int Ini_GetUInt64 (IniText handle, const char sectionName[],
                   const char tagName[],
                   unsigned long long *unsignedIntegerValue)
{
    int status = 0;

    if ((NULL != handle) && (NULL != sectionName) && (NULL != tagName) &&
        (NULL != unsignedIntegerValue))
    {

    }

    return status;
}


/*--------------------------------------------------------------------------*/
// Informational
/*--------------------------------------------------------------------------*/
//int Ini_SectionExists (IniText handle, const char sectionName[])
//int Ini_NumberOfSections (IniText handle)
//int Ini_NthSectionName (IniText handle, int sectionIndex, char **sectionNamePointer)
//int Ini_ItemExists (IniText handle, const char sectionName[], const char tagName[])
//int Ini_NumberOfItems (IniText handle, const char sectionName[])
//int Ini_NthItemName (IniText handle, const char sectionName[], int itemIndex, char **itemTagNamePointer)
//int Ini_LineOfLastAccess (IniText handle)

/*--------------------------------------------------------------------------*/
// Removing Sections and Items
/*--------------------------------------------------------------------------*/
//int Ini_RemoveSection (IniText handle, const char sectionName[])
//int Ini_RemoveItem (IniText handle, const char sectionName[], const char tagName[])

// End of INIParser.c
