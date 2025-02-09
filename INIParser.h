#ifndef INIPARSER_H_INCLUDED
#define INIPARSER_H_INCLUDED

// https://www.ni.com/docs/en-US/bundle/labwindows-cvi/page/toolslib/toolslibreadingwriting_inistyle_files_co.htm

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stddef.h>     // for size_t

#include "INIParser.h"

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef void* IniText;


/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/
typedef enum
{
    AUTO,
    ANSI,
    UTF8BOM,
    UTF8NOBOM,
    RAWBYTES
} IniFileEncodingType;

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/
#define OUT_OF_MEMORY                           -12
#define NULL_POINTER_PASSED                     –65
#define TOO_MANY_FILES_OPEN                     –91
#define UNEXPECTEDLY_REACHED_END_OF_FILE        –92
#define INPUT_OUTPUT_ERROR                      –93
#define FILE_NOT_FOUND                          –94
#define FILE_ACCESS_PERMISSION_DENIED           –95
#define DISK_IS_FULL                            –97
#define FILE_ALREADY_OPEN                       –99
#define BADLY_FORMED_PATHNAME                   –100
#define OPERATION_FAILED                        –184

#define COULD_NOT_OPEN_FILE_FOR_READING         –5001
#define ERROR_READING_FILE                      –5002
#define COULD_NOT_GENERATE_UNUSED_TEMP_FILENAME –5003
#define COULT_NOT_CREATE_TEMP_FILE              –5004
#define INVALID_INTEGER                         –5021
#define INVALID_UNSIGNED_INTEGER                –5022
#define INVALID_DOUBLE_VALUE                    –5023
#define INVALID_BOOLEAN                         –5024

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
// Management
IniText Ini_New (int automaticSorting);
void    Ini_Dispose (IniText handle);
//int     Ini_SetEncoding (IniText handle, IniFileEncodingType iniFileEncoding);
//int     Ini_GetEncoding (IniText handle, IniFileEncodingType *iniFileEnding);
//void    Ini_Sort (IniText handle);
//void    Ini_DisableSorting (IniText handle);
//int     Ini_SortInternally (IniText handle);
//void    Ini_DisableInternalSorting (IniText handle);
int     Ini_WriteToFile (IniText handle, const char pathname[]);
int     Ini_ReadFromFile (IniText handle, const char pathname[]);
//int     Ini_WriteToRegistry (IniText handle, int rootKey, const char subkeyName[]);
//int     Ini_ReadFromRegistry (IniText handle,  int rootKey, const char subkeyName[]);
//int     Ini_WriteGeneric (IniText handle, Ini_OutputFunc outputFunction, void *outputDestination);
//int     Ini_ReadGeneric (IniText handle, Ini_InputFunc inputFunction, void *inputSource);
//int     Ini_CopySection (IniText handle, const char sectionToCopy[], IniText destination, int overwriteDuplicateSections);
//int     Ini_CopySectionEx (IniText source, const char sectionToCopy[], IniText destination, const char destinationSectionToCopyTo[], int overwriteDuplicateSections);
//int     Ini_SetTokens (IniText handle, char sectionNameStartCharacter, char sectionNameEndCharacter, const char valueSeparator[], const char commentMarker[]);
//int     Ini_SetSectionFilter (IniText handle, Ini_SectionFilterFunc sectionFilterFunction, void *callbackData);
//int     Ini_SetDuplicateChecking (IniText handle, int checkForDuplicates);
//int     Ini_SetAddQuotesToStrings (IniText handle, int addQuotesToStrings);
//int     Ini_SetMaxValueLineLength (IniText handle, int maxValueLineLength);

// Putting Tag/Value Pairs
int     Ini_PutString (IniText handle, const char sectionName[], const char tagName[], const char stringValue[]);
int     Ini_PutRawString (IniText handle, const char sectionName[], const char tagName[], const char stringValue[]);
int     Ini_PutInt (IniText handle, const char sectionName[], const char tagName[], int integerValue);
int     Ini_PutUInt (IniText handle, const char sectionName[], const char tagName[], unsigned int unsignedIntegerValue);
int     Ini_PutDouble (IniText handle, const char sectionName[], const char tagName[], double doubleValue);
int     Ini_PutBoolean (IniText handle, const char sectionName[], const char tagName[], int booleanValue);
int     Ini_PutData (IniText handle, const char sectionName[], const char tagName[], const unsigned char data[], long dataSize);

// Getting Values from Tags
int     Ini_GetPointerToString (IniText handle, const char sectionName[], const char tagName[], char **pointerToString);
int     Ini_GetStringCopy (IniText handle, const char sectionName[], const char tagName[], char **copyOfString);
int     Ini_GetStringIntoBuffer (IniText handle, const char sectionName[], const char tagName[], char buffer[], size_t bufferSize);
int     Ini_GetPointerToRawString (IniText handle, const char sectionName[], const char tagName[], char **pointerToString);
int     Ini_GetRawStringCopy (IniText handle, const char sectionName[], const char tagName[], char **copyOfString);
int     Ini_GetRawStringIntoBuffer (IniText handle, const char sectionName[], const char tagName[], char buffer[], size_t bufferSize);
int     Ini_GetInt (IniText handle, const char sectionName[], const char tagName[], int *integerValue);
int     Ini_GetUInt (IniText handle, const char sectionName[], const char tagName[], unsigned int *unsignedIntegerValue);
int     Ini_GetDouble (IniText handle, const char sectionName[], const char tagName[], double *doubleValue);
int     Ini_GetBoolean (IniText handle, const char sectionName[], const char tagName[], int *booleanValue);
int     Ini_GetData (IniText handle, const char sectionName[], const char tagName[], unsigned char **data, size_t *dataSize);
int     Ini_GetInt64 (IniText handle, const char sectionName[], const char tagName[], long long *integerValue);
int     Ini_GetUInt64 (IniText handle, const char sectionName[], const char tagName[], unsigned long long *unsignedIntegerValue);

// Informational
//int     Ini_SectionExists (IniText handle, const char sectionName[]);
//int     Ini_NumberOfSections (IniText handle);
//int     Ini_NthSectionName (IniText handle, int sectionIndex, char **sectionNamePointer);
//int     Ini_ItemExists (IniText handle, const char sectionName[], const char tagName[]);
//int     Ini_NumberOfItems (IniText handle, const char sectionName[]);
//int     Ini_NthItemName (IniText handle, const char sectionName[], int itemIndex, char **itemTagNamePointer);
//int     Ini_LineOfLastAccess (IniText handle);

// Removing Sections and Items
//int     Ini_RemoveSection (IniText handle, const char sectionName[]);
//int     Ini_RemoveItem (IniText handle, const char sectionName[], const char tagName[]);

#endif // INIPARSER_H_INCLUDED

// End of INIParser.h

