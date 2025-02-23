#ifndef INIFILEPARSER_H_INCLUDED
#define INIFILEPARSER_H_INCLUDED

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>     // for size_t
#include <stdio.h.>     // for FILE*

// Include all the other header files.
#include "INI.h"


/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Externs for Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
bool FindFirstAndLastNonWhitespace (const char *line, unsigned int *startPos, unsigned int *endPos, bool removeComments);

bool ParseSection (const char *line, char *section, size_t sectionSize);

bool ParseTagValue (const char *line, char *tag, size_t tagSize, char *value, size_t valueSize);


#endif // INIFILEPARSER_H_INCLUDED

// End of Template.h

