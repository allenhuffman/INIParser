#ifndef INI_H_INCLUDED
#define INI_H_INCLUDED

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stddef.h>     // for size_t

// Include all the other header files.

/*--------------------------------------------------------------------------*/
// Enums
/*--------------------------------------------------------------------------*/
typedef enum
{
    RECORD_TYPE_UNKNOWN = 0,    // Blank lines (anything else is an error)
    RECORD_TYPE_COMMENT,        // "; A comment in the file"
    RECORD_TYPE_SECTION,        // "[Section]"
    RECORD_TYPE_TAGVALUE        // "Tag=Value"
} RecordTypeEnum;

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef void *RecordHandle;

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
// Init / Term
RecordHandle RecordInit (void);
bool RecordTerm (RecordHandle *handle);

// Read / Write
bool RecordReadTagValue (RecordHandle *handle, const char *section,
                         const char *tag, char *buffer, size_t bufferSize);

bool RecordWriteUnknown (RecordHandle *handle, const char *unknown);
bool RecordWriteComment (RecordHandle *handle, const char *comment);
bool RecordWriteSection (RecordHandle *handle, const char *section);
bool RecordWriteSectionTagValue (RecordHandle *handle, const char *section,
                                 const char *tag, const char *value);
bool RecordWriteTagValue (RecordHandle *handle, const char *tag, const char *value);

// Record to line (for writing to a file)
bool RecordGetNext (RecordHandle *handle, char *buffer, size_t bufferSize);
bool RecordSeekToStart (RecordHandle *handle);

// Debug
bool RecordShowAll (RecordHandle *handle);

#endif // INI_H_INCLUDED

// End of Template.h

