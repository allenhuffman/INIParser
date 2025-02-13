/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <stdio.h>

// This projects's header
#include "INIParser.h"

// This file's header
#include "INIParserInformational.h"

// Other headers

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
// Informational
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// If the section exists, a 1 is returned.
// If the section does not exist, a 0 is returned.
int Ini_SectionExists (IniText handle, const char sectionName[])
{
    return RecordSectionExists (handle, sectionName);
}

/*--------------------------------------------------------------------------*/
//int Ini_NumberOfSections (IniText handle)

/*--------------------------------------------------------------------------*/
//int Ini_NthSectionName (IniText handle, int sectionIndex, char **sectionNamePointer)

/*--------------------------------------------------------------------------*/
//int Ini_ItemExists (IniText handle, const char sectionName[], const char tagName[])

/*--------------------------------------------------------------------------*/
//int Ini_NumberOfItems (IniText handle, const char sectionName[])

/*--------------------------------------------------------------------------*/
//int Ini_NthItemName (IniText handle, const char sectionName[], int itemIndex, char **itemTagNamePointer)

/*--------------------------------------------------------------------------*/
//int Ini_LineOfLastAccess (IniText handle)

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/

// End of INIParserInformational.c
