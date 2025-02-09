#ifndef INIPARSERGETTINGVALUESFROMTAGS_H_INCLUDED
#define INIPARSERGETTINGVALUESFROMTAGS_H_INCLUDED

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stddef.h>     // for size_t

#include "INIParser.h"

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef void *IniText; // TODO: Not sure what this will be yet.

/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
// Getting Values from Tags
int     Ini_GetPointerToString (IniText handle, const char sectionName[],
                                const char tagName[],
                                char **pointerToString);

int     Ini_GetStringCopy (IniText handle, const char sectionName[],
                           const char tagName[], char **copyOfString);

int     Ini_GetStringIntoBuffer (IniText handle, const char sectionName[],
                                 const char tagName[], char buffer[],
                                 size_t bufferSize);

int     Ini_GetPointerToRawString (IniText handle, const char sectionName[],
                                   const char tagName[],
                                   char **pointerToString);

int     Ini_GetRawStringCopy (IniText handle, const char sectionName[],
                              const char tagName[], char **copyOfString);

int     Ini_GetRawStringIntoBuffer (IniText handle, const char sectionName[],
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

int     Ini_GetData (IniText handle, const char sectionName[],
                     const char tagName[], unsigned char **data,
                     size_t *dataSize);

int     Ini_GetInt64 (IniText handle, const char sectionName[],
                      const char tagName[], long long *integerValue);

int     Ini_GetUInt64 (IniText handle, const char sectionName[],
                       const char tagName[],
                       unsigned long long *unsignedIntegerValue);

#endif // INIPARSERGETTINGVALUESFROMTAGS_H_INCLUDED

// End of INIParserGettingValuesFromTags.h
