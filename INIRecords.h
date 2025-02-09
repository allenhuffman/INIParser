#ifndef INIRECORDS_H_INCLUDED
#define INIRECORDS_H_INCLUDED

/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/
#define DEBUG_RECORDS 0

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef void *RecordHandle;

typedef struct rec_t
{
    struct rec_t    *next;      // Pointer to next record structure.
    struct rec_t    *prev;      // Pointer to previous record structure.
    const char      line[];     //
} RecordStruct;

/*--------------------------------------------------------------------------*/
// Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Static Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Public Prototypes
/*--------------------------------------------------------------------------*/
// Init/Term

RecordHandle *RecordInit (void);

bool RecordTerm (RecordHandle *handle);

// Read/Write

RecordStruct *RecordRead (RecordHandle *handle);

bool RecordWrite (RecordHandle *handle, const char *line);

unsigned int RecordGetCount (RecordHandle *handle);

// Delete/Seek

bool RecordDelete (RecordHandle *handle, RecordStruct *record);

bool RecordSeek (RecordHandle *handle, unsigned int recordNumber);

// Debug Functions

bool RecordShow (RecordStruct *record);

bool RecordShowAll (RecordHandle *handle);

#endif // INIRECORDS_H_INCLUDED

// End of INIRecords.h
