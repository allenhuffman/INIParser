#ifndef INIPARSERMANAGEMENT_H_INCLUDED
#define INIPARSERMANAGEMENT_H_INCLUDED

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

#endif // INIPARSERMANAGEMENT_H_INCLUDED

// End of INIParserManagement.h
