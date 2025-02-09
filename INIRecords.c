/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
#include <stdbool.h>    // for true/false
#include <stdio.h>      // for printf()
#include <stdlib.h>     // for malloc()
#include <string.h>     // for memset()/memcpy()

#include "INIRecords.h"

/*--------------------------------------------------------------------------*/
// Constants
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Typedefs
/*--------------------------------------------------------------------------*/
typedef struct
{
    RecordStruct    *first;     // First record.
    RecordStruct    *last;      // Last record.
    RecordStruct    *nextOut;   // Next record to read.
    unsigned int    count;
} RecordIndexStruct;

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

// Init/Term

/*--------------------------------------------------------------------------*/
RecordHandle *RecordInit (void)
{
    RecordIndexStruct   *records;

    records = malloc (sizeof(RecordIndexStruct));

    if (records != NULL)
    {
        // Initialize empty record structure.
        records->first = NULL;
        records->last = NULL;
        records->nextOut = NULL;
        records->count = 0;
    }

    return (RecordHandle*)records; // NULL or this structure.
}

/*--------------------------------------------------------------------------*/
bool RecordTerm (RecordHandle *handle)
{
    bool status;

#if (DEBUG_RECORDS > 0)
    printf ("RecordTerm (0x%p)\n", (void*)handle);
#endif

    if (NULL == handle)
    {
        status = false;
    }
    else
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        while (NULL != records->first)
        {
            RecordDelete (handle, records->first);
        }

        status = true;
    }

    return status;
}

// Read/Write

/*--------------------------------------------------------------------------*/
RecordStruct *RecordRead (RecordHandle *handle)
{
    RecordStruct *record;

#if (DEBUG_RECORDS > 0)
    printf ("RecordRead (0x%p)\n", (void*)handle);
#endif

    if (NULL == handle)
    {
        record = NULL;
    }
    else
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        record = records->nextOut;

        if (NULL != record)
        {
            records->nextOut = record->next;
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
bool RecordWrite (RecordHandle *handle, const char line[])
{
    bool status;

#if (DEBUG_RECORDS > 0)
    printf ("RecordWrite (0x%p, 0x%p)\n", (void*)handle, line);
#endif

    if ((NULL == handle) || (NULL == line))
    {
        status = false;
    }
    else
    {
        // Allocate new record.

        // One byte is added so there is room for the string plus the
        // NIL '\0' terminator at the end of it.
        size_t lineLen = strlen (line) + 1; // Plus NIL

        RecordStruct *newRecord = malloc (sizeof(RecordStruct) + lineLen);

        if (NULL == newRecord)
        {
            status = false;
        }
        else
        {
            RecordIndexStruct *records = (RecordIndexStruct*)handle;
            RecordStruct *lastRecord = records->last;

            newRecord->next = NULL;
            newRecord->prev = lastRecord;

            // Is this the first record?
            if (NULL == records->first)
            {
#if (DEBUG_RECORDS > 0)
                printf ("Adding first record.\n");
#endif
                records->first = newRecord;
                records->last = newRecord;
                records->nextOut = newRecord;
            }
            else
            {
#if (DEBUG_RECORDS > 0)
                printf ("Adding record to end.\n");
#endif
                lastRecord->next = newRecord;
                records->last = newRecord;
            }

            // Copy data into new record data area.
            strncpy ((char*)newRecord->line, line, lineLen);

            records->count++;

            status = true;
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
unsigned int RecordGetCount (RecordHandle *handle)
{
    unsigned int recordCount = 0;

    if (NULL == handle)
    {
        recordCount = 0;
    }
    else
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        recordCount = records->count;
    }

    return recordCount;
}

// Delete/Seek

/*--------------------------------------------------------------------------*/
bool RecordDelete (RecordHandle *handle, RecordStruct *record)
{
    bool status;

#if (DEBUG_RECORDS > 0)
    printf ("RecordDelete (0x%p, 0x%p)\n", (void*)handle, (void*)record);
#endif

    if ((NULL == handle) || (NULL == record))
    {
        status = false;
    }
    else
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *prevRecord = record->prev;
        RecordStruct *nextRecord = record->next;

        // Connect previous record to next record.
        if (NULL != prevRecord)
        {
            prevRecord->next = nextRecord;
        }
        else
        {
            // This was the first record.
            records->first = nextRecord;
        }

        // Connect next record to previous record.
        if (NULL != nextRecord)
        {
            nextRecord->prev = prevRecord;
        }
        else
        {
            // This was the last record.
            records->last = prevRecord;
        }

        // De-allocate this record.
        free (record);

        records->count--;

        status = true;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordSeek (RecordHandle *handle, unsigned int recordNumber)
{
    bool                status;

#if (DEBUG_RECORDS > 0)
    printf ("RecordSeek ()\n");
#endif
    if (NULL == handle)
    {
        status = false;
    }
    else
    {
        // Linear search through records to find matching number.
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        // Start at first record, if any.
        RecordStruct *recordPtr = records->first;

        unsigned int number = 0;

        status = false; // Default to not finding a match.

        while (recordPtr != NULL)
        {
            // Stop at or after the desired record.
            if (number >= recordNumber)
            {
                records->nextOut = recordPtr;
                status = true;
                break;
            }

            recordPtr = recordPtr->next;
            number++;
        }
    }

    return status;
}

// Debug functions

/*--------------------------------------------------------------------------*/
bool RecordShow (RecordStruct *record)
{
    bool status = false;

    if (NULL != record)
    {
        // Really verbose output.
        printf ("0x%p  "
                "prev: 0x%p "
                "next: 0x%p "
                "line: '%s'\n",
                (void*)record,
                (void*)record->prev,
                (void*)record->next,
                record->line);

        status = true;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordShowAll (RecordHandle *handle)
{
    bool status = false;

    if (NULL == handle)
    {
        status = false;
    }
    else
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *tempRecord = records->first;

        printf ("%u Records:\n", records->count);

        while (NULL != tempRecord)
        {
            RecordShow (tempRecord);

            tempRecord = tempRecord->next;
        }

        status = true;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/

// End of INIRecords.c
