#ifndef INIPARSERPUTTINGTAGVALUEPAIRS_H_INCLUDED
#define INIPARSERPUTTINGTAGVALUEPAIRS_H_INCLUDED

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stddef.h>     // for size_t

#include "INIParser.h"

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
// Putting Tag/Value Pairs
int     Ini_PutString (IniText handle, const char sectionName[],
                       const char tagName[], const char stringValue[]);

int     Ini_PutRawString (IniText handle, const char sectionName[],
                          const char tagName[], const char stringValue[]);

int     Ini_PutInt (IniText handle, const char sectionName[],
                    const char tagName[], int integerValue);

int     Ini_PutUInt (IniText handle, const char sectionName[],
                     const char tagName[], unsigned int unsignedIntegerValue);

int     Ini_PutDouble (IniText handle, const char sectionName[],
                       const char tagName[], double doubleValue);

int     Ini_PutBoolean (IniText handle, const char sectionName[],
                        const char tagName[], int booleanValue);

int     Ini_PutData (IniText handle, const char sectionName[],
                     const char tagName[], const unsigned char data[],
                     long dataSize);

#endif // INIPARSERPUTTINGTAGVALUEPAIRS_H_INCLUDED

// End of INIParserPuttingTagValuePairs.h
