#ifndef INIPARSER_H_INCLUDED
#define INIPARSER_H_INCLUDED

// https://www.ni.com/docs/en-US/bundle/labwindows-cvi/page/toolslib/toolslibreadingwriting_inistyle_files_co.htm

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stddef.h>     // for size_t

// Include all the other header files.
#include "INIParserGettingValuesFromTags.h"
#include "INIParserInformational.h"
#include "INIParserManagement.h"
#include "INIParserPuttingTagValuePairs.h"
#include "INIParserRemovingSectionsAndItems.h"

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef void *IniText; // TODO: Not sure what this will be yet.

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
#define LINE_MAX_LEN    256

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/

#endif // INIPARSER_H_INCLUDED

// End of INIParser.h

