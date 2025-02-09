#ifndef INIPARSER_H_INCLUDED
#define INIPARSER_H_INCLUDED

// https://www.ni.com/docs/en-US/bundle/labwindows-cvi/page/toolslib/toolslibreadingwriting_inistyle_files_co.htm

#define DEBUG_INIPARSER 1

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stdbool.h>
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

typedef enum
{
    LINE_UNKNOWN,
    LINE_INVALID,
    LINE_EMPTY,
    LINE_COMMENT,
    LINE_SECTION,
    LINE_KEYVALUE,
} LineTypeEnum;

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/
#define LINE_MAX_LEN    256

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/

// SeekToSection

LineTypeEnum GetLineType (const char line[]);

bool GetCommentFromLine (const char line[], char *commentPtr, size_t commentSize);

bool GetSectionFromLine (const char line[], char *sectionPtr, size_t sectionSize);

bool GetTagFromLine (const char line[], char *tagPtr, size_t tagSize);

bool GetValueFromLine (const char line[], char *valuePtr, size_t valueSize);

const char *LineTypeToStringPtr (LineTypeEnum lineType);

bool RemoveComments (const char line[], char *newLinePtr, size_t newLineSize);

#endif // INIPARSER_H_INCLUDED

// End of INIParser.h

