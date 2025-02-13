/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <ctype.h>  // for iswhite()
#include <stdio.h>
#include <stdlib.h> // for malloc()/free()
#include <string.h> // for strchr()

// This project's header

// This file's header
#include "INI.h"

// Other headers
// Include the special malloc/free routines and override places in this
// code where it uses "malloc" and "free" to use those new routines.
#include "MyMalloc.h"
#define malloc MyMalloc
#define free MyFree

/*--------------------------------------------------------------------------*/
// Private Constants
/*--------------------------------------------------------------------------*/
#define DEBUG_RECORDS 1

/*--------------------------------------------------------------------------*/
// Private Typedefs
/*--------------------------------------------------------------------------*/
typedef struct record_t
{
    struct record_t *next;  // Next record
    struct record_t *prev;  // Previous record
    RecordTypeEnum  type;   // Record type
    union
    {
        char *unknown;      // Contains unknown data
        char *comment;      // Contains a Comment
        char *section;      // Contains a Section
        struct
        {
            char *tag;      // Contains a Tag
            char *value;    // ...and a Value
        }; // Anonymous structure.
    }; // Anonymous union.
} RecordStruct;

typedef struct
{
    RecordStruct    *first;     // First record.
    RecordStruct    *last;      // Last record.
    RecordStruct    *nextOut;   // Next record to read.
    unsigned int    count;
} RecordIndexStruct;

/*--------------------------------------------------------------------------*/
// Public Global Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Static Variables
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
// Private Prototypes
/*--------------------------------------------------------------------------*/
// Records
static RecordStruct *RecordAllocUnknown (const char *unknown);
static RecordStruct *RecordAllocComment (const char *comment);
static RecordStruct *RecordAllocSection (const char *section);
static RecordStruct *RecordAllocTagValue (const char *tag, const char *value);

static bool RecordFree (RecordStruct *handle);

// Read / Write
//static RecordStruct *RecordRead (RecordHandle *handle);
static bool RecordWrite (RecordHandle *handle, RecordStruct *record);
static RecordStruct *RecordGetSection (RecordHandle *handle,
                                       const char *section);
static RecordStruct *RecordGetTag (RecordHandle *handle, RecordStruct *record,
                                   const char *tag);

// Insert / Delete / Replace
static bool RecordDelete (RecordHandle *handle, RecordStruct *record);
static bool RecordInsertAfter (RecordHandle *handle, RecordStruct *record,
                               RecordStruct *newRecord);
static bool RecordReplace (RecordHandle *handle, RecordStruct *record,
                           RecordStruct *newRecord);

// Debug
static bool RecordShow (RecordStruct *record);

/*--------------------------------------------------------------------------*/
// Public Functions
/*--------------------------------------------------------------------------*/

// Init / Term
/*--------------------------------------------------------------------------*/
RecordHandle RecordInit (void)
{
    RecordIndexStruct *handle = NULL;

    handle = malloc (sizeof (RecordIndexStruct));

    if (NULL != handle)
    {
        handle->first = NULL;
        handle->last = NULL;
        handle->nextOut = NULL;
        handle->count = 0;
    }

    return handle;
}

/*--------------------------------------------------------------------------*/
bool RecordTerm (RecordHandle *handle)
{
    bool status = false;

    if (NULL != handle)
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        while (NULL != records->first)
        {
            RecordDelete (handle, records->first);
        }

        free (handle);

        status = true;
    }

    return status;
}

// Read / Write
/*--------------------------------------------------------------------------*/
bool RecordReadTagValue (RecordHandle *handle, const char *section,
                         const char *tag, char *buffer, size_t bufferSize)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordReadTagValue (0x%p, '%s', '%s', 0x%p, %u", handle, section,
            tag, buffer, bufferSize);
#endif

    if ((NULL != handle) && (NULL != section) && (NULL != tag) &&
        (NULL != buffer) && (0 != bufferSize))
    {
        //RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *sectionRecord = RecordGetSection (handle, section);

        if (NULL != sectionRecord) // If section was found...
        {
            RecordStruct *tagRecord = RecordGetTag (handle, sectionRecord, tag);

            if (NULL != tagRecord) // If tag was found...
            {
                if (NULL != tagRecord->value)
                {
                    strncpy (buffer, tagRecord->value, bufferSize);

                    status = true;
                }
            }
        }
    } // end of NULL checks

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordWriteUnknown (RecordHandle *handle, const char *unknown)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWriteUnknown (0x%p, 0x%p)\n", handle, unknown);
#endif

    if ((NULL != handle) && (NULL != unknown))
    {
        RecordStruct *record = RecordAllocUnknown (unknown);

        if (NULL != record)
        {
            status = RecordWrite (handle, record);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordWriteComment (RecordHandle *handle, const char *comment)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWriteComment (0x%p, 0x%p)\n", handle, comment);
#endif

    if ((NULL != handle) && (NULL != comment))
    {
        RecordStruct *record = RecordAllocComment (comment);

        if (NULL != record)
        {
            status = RecordWrite (handle, record);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordWriteSection (RecordHandle *handle, const char *section)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWriteSection (0x%p, 0x%p)\n", handle, section);
#endif

    if ((NULL != handle) && (NULL != section))
    {
        RecordStruct *record = RecordAllocSection (section);

        if (NULL != record)
        {
            status = RecordWrite (handle, record);
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordWriteSectionTagValue (RecordHandle *handle, const char *section,
                                 const char *tag, const char *value)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWriteSectionTagValue (0x%p, 0x%p, 0x%p, 0x%p)\n",
            handle, section, tag, value);
#endif

    // TODO: If no section is given, it could just write it out direct.

    if ((NULL != handle) && (NULL != section) && (NULL != tag) && (NULL != value))
    {
        //RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *sectionRecord = RecordGetSection (handle, section);

        if (NULL == sectionRecord) // Section was not found.
        {
#if (DEBUG_RECORDS > 0)
            printf ("[%s] NOT found.\n", section);
#endif
            // Add it at the end.
            status = RecordWriteSection (handle, section);

            if (true == status)
            {
                status = RecordWriteTagValue (handle, tag, value);
            }
        }
        else // Section was found
        {
#if (DEBUG_RECORDS > 0)
            printf ("Existing [%s] found.\n", section);
#endif
            // Look to see if this tag already exists.
            RecordStruct *tagRecord = RecordGetTag (handle, sectionRecord, tag);

            if (NULL != tagRecord)
            {
#if (DEBUG_RECORDS > 0)
                printf ("Existing '%s=%s' found.\n", tagRecord->tag, tagRecord->value);
#endif
                RecordStruct *newRecord = RecordAllocTagValue (tag, value);

                if (NULL != newRecord)
                {
                    status = RecordReplace (handle, tagRecord, newRecord);
                }
            }
            else // Not found. Add a new one.
            {
#if (DEBUG_RECORDS > 0)
                printf ("'%s=' not found.\n", tag);
#endif
                RecordStruct *newRecord = RecordAllocTagValue (tag, value);

                if (NULL != newRecord)
                {
                    status = RecordInsertAfter (handle, sectionRecord, newRecord);
                }
            }
        }
    }

    return status;
}

/*--------------------------------------------------------------------------*/
bool RecordWriteTagValue (RecordHandle *handle, const char *tag,
                          const char *value)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWriteTagValue (0x%p, 0x%p, 0x%p)\n", handle, tag, value);
#endif

    if ((NULL != handle) && (NULL != tag) && (NULL != value))
    {
        RecordStruct *record = RecordAllocTagValue (tag, value);

        if (NULL != record)
        {
            status = RecordWrite (handle, record);
        }
    }

    return status;
}

// ...

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/
static RecordStruct *RecordAlloc (RecordTypeEnum type)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordAlloc (%u)\n", type);
#endif

    record = malloc (sizeof(RecordStruct));

    if (record != NULL)
    {
        record->next = NULL;
        record->prev = NULL;

        switch (type)
        {
            default:
            case RECORD_TYPE_UNKNOWN:
                record->type = RECORD_TYPE_UNKNOWN;
                record->unknown = NULL;
                break;

            case RECORD_TYPE_COMMENT:
                record->type = RECORD_TYPE_COMMENT;
                record->comment = NULL;
                break;

            case RECORD_TYPE_SECTION:
                record->type = RECORD_TYPE_SECTION;
                record->section = NULL;
                break;

            case RECORD_TYPE_TAGVALUE:
                record->type = RECORD_TYPE_TAGVALUE;
                record->tag = NULL;
                record->value = NULL;
                break;
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
static RecordStruct *RecordAllocUnknown (const char *unknown)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordAllocUnknown (0x%p)\n", unknown);
#endif

    if (NULL != unknown)
    {
        record = RecordAlloc (RECORD_TYPE_UNKNOWN);

        if (record != NULL)
        {
            size_t len = strlen (unknown) + 1;

            record->comment = malloc (len);

            if (NULL != record->unknown)
            {
                strncpy (record->unknown, unknown, len);
            }
            else
            {
                RecordFree (record);
                record = NULL;
            }
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
static RecordStruct *RecordAllocComment (const char *comment)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordAllocComment (0x%p)\n", comment);
#endif

    if (NULL != comment)
    {
        record = RecordAlloc (RECORD_TYPE_COMMENT);

        if (record != NULL)
        {
            size_t len = strlen (comment) + 1;

            record->comment = malloc (len);

            if (NULL != record->comment)
            {
                strncpy (record->comment, comment, len);
            }
            else
            {
                RecordFree (record);
                record = NULL;
            }
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
static RecordStruct *RecordAllocSection (const char *section)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordAllocSection (0x%p)\n", section);
#endif

    if (NULL != section)
    {
        record = RecordAlloc (RECORD_TYPE_SECTION);

        if (record != NULL)
        {
            size_t len = strlen (section) + 1;

            record->section = malloc (len);

            if (NULL != record->section)
            {
                strncpy (record->section, section, len);
            }
            else
            {
                RecordFree (record);
                record = NULL;
            }
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
static RecordStruct *RecordAllocTagValue (const char *tag, const char *value)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordAllocTagValue (0x%p, 0x%p)\n", tag, value);
#endif

    if ((NULL != tag) && (NULL != value)) // Must have both.
    {
        record = RecordAlloc (RECORD_TYPE_TAGVALUE);

        if (record != NULL)
        {
            size_t len = strlen (tag) + 1;

            record->tag = malloc (len);

            if (NULL != record->tag)
            {
                strncpy (record->tag, tag, len);
            }
            else
            {
                RecordFree (record);
                record = NULL;
            }

            len = strlen (value) + 1;

            record->value = malloc (len);

            if (NULL != record->value)
            {
                strncpy (record->value, value, len);
            }
            else
            {
                RecordFree (record);
                record = NULL;
            }
        }
    }

    return record;
}

/*--------------------------------------------------------------------------*/
static bool RecordFree (RecordStruct *record)
{
    bool status = true;

#if (DEBUG_RECORDS > 1)
    printf ("RecordFree (0x%p)\n", record);
#endif

    if (NULL != record)
    {
        switch (record->type)
        {
            default:
            case RECORD_TYPE_UNKNOWN:
                free (record->unknown);
                break;

            case RECORD_TYPE_COMMENT:
                free (record->comment);
                break;

            case RECORD_TYPE_SECTION:
                free (record->section);
                break;

            case RECORD_TYPE_TAGVALUE:
                free (record->value);
                free (record->tag);
                break;
        }

        free (record);
    }

    return status;
}

/*--------------------------------------------------------------------------*/
/*
static RecordStruct *RecordRead (RecordHandle *handle)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordRead (0x%p)\n", handle);
#endif

    if (NULL != handle)
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
*/

/*--------------------------------------------------------------------------*/
static bool RecordWrite (RecordHandle *handle, RecordStruct *record)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordWrite (0x%p, 0x%p)\n", handle, record);
#endif

    if ((NULL != handle) && (NULL != record))
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *lastRecord = records->last;

        record->next = NULL;
        record->prev = lastRecord;

        // Is this the first record?
        if (NULL == records->first)
        {
#if (DEBUG_RECORDS > 0)
            printf ("Adding first record.\n");
#endif
            records->first = record;
            records->last = record;
            records->nextOut = record;
        }
        else
        {
#if (DEBUG_RECORDS > 0)
            printf ("Adding record to end.\n");
#endif
            lastRecord->next = record;
            records->last = record;
        }

        records->count++;

        status = true;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
static bool RecordDelete (RecordHandle *handle, RecordStruct *record)
{
    bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordDelete (0x%p, 0x%p)\n", handle, record);
#endif

    if ((NULL != handle) || (NULL != record))
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *prevRecord = record->prev;
        RecordStruct *nextRecord = record->next;

        if (NULL != prevRecord)
        {
            // Connect previous record to next record.
            prevRecord->next = nextRecord;
        }
        else
        {
            // This was the first record.
            records->first = nextRecord;
        }

        if (NULL != nextRecord)
        {
            // Connect next record to previous record.
            nextRecord->prev = prevRecord;
        }
        else
        {
            // This was the last record.
            records->last = prevRecord;
        }

        // De-allocate this record.
        RecordFree (record);

        records->count--;

        status = true;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
static bool RecordInsertAfter (RecordHandle *handle, RecordStruct *record,
                               RecordStruct *newRecord)
{
   bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordInsertAfter (0x%p, 0x%p, 0x%p)\n", handle, record, newRecord);
#endif

    if ((NULL != handle) && (NULL != record) && (NULL != newRecord))
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *nextRecord = record->next;

        // Is there a record after this one?
        if (NULL != nextRecord)
        {
            nextRecord->prev = newRecord;
        }

        record->next = newRecord;

        newRecord->next = nextRecord; // Could be NULL
        newRecord->prev = record;

        records->count++;

        // If record was the last record, adjust.
        if (records->last == record)
        {
            records->last = newRecord;
        }

        status = true;

#if (DEBUG_RECORDS > 0)
        printf ("Inserting:\n");
        RecordShow (newRecord);
        printf ("After:\n");
        RecordShow (record);
#endif
    }

    return status;
}

static bool RecordReplace (RecordHandle *handle, RecordStruct *record,
                           RecordStruct *newRecord)
{
   bool status = false;

#if (DEBUG_RECORDS > 1)
    printf ("RecordReplace (0x%p, 0x%p)\n", handle, record);
#endif

    if ((NULL != handle) && (NULL != record) && (NULL != newRecord))
    {
#if (DEBUG_RECORDS > 0)
        printf ("Replacing:\n");
        RecordShow (record);
        printf ("With:\n");
        RecordShow (newRecord);
#endif

        //RecordIndexStruct *records = (RecordIndexStruct*)handle;
        RecordStruct *nextRecord = record->next;
        RecordStruct *prevRecord = record->prev;

        // Is there a record before this one?
        if (NULL != prevRecord)
        {
            prevRecord->next = newRecord;
        }

        // Is there a record after this one?
        if (NULL != nextRecord)
        {
            nextRecord->prev = newRecord;
        }

        newRecord->next = nextRecord; // Could be NULL
        newRecord->prev = prevRecord; // Could be NULL

        RecordFree (record);

        status = true;
    }

    return status;
}


/*--------------------------------------------------------------------------*/
static RecordStruct *RecordGetSection (RecordHandle *handle, const char *section)
{
    RecordStruct *record = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordGetSection (0x%p, 0x%p)\n", handle, section);
#endif

    if ((NULL != handle) && (NULL != section))
    {
        RecordIndexStruct *records = (RecordIndexStruct*)handle;

        record = records->first; // Start with the first record.

        while (NULL != record)
        {
            if (RECORD_TYPE_SECTION == record->type)
            {
                if (NULL != record->section)
                {
                    // TODO: Protect against buffer overrun!
                    if (0 == strcmp (section, record->section))
                    {
                        // Found it!
#if (DEBUG_RECORDS > 1)
                        printf ("[%s] found.\n", section);
#endif
                        break;
                    }
                }
            }

            record = record->next;
        } // end of while
    } // end of NULL checks

    return record;
}


/*--------------------------------------------------------------------------*/
// Scan forward from current record looking for a matching tag. Return it
// if found, or return NULL if another [Section] is reached.
static RecordStruct *RecordGetTag (RecordHandle *handle, RecordStruct *record,
                                   const char *tag)
{
    RecordStruct *tagRecord = NULL;

#if (DEBUG_RECORDS > 1)
    printf ("RecordGetTag (0x%p, 0x%p, 0x%p)\n", handle, record, tag);
#endif

    if ((NULL != handle) && (NULL != record) && (NULL != tag))
    {
        //RecordIndexStruct *records = (RecordIndexStruct*)handle;

        // If user passed in the section, move past it.
        if (RECORD_TYPE_SECTION == record->type)
        {
            record = record->next;
        }

        while (NULL != record)
        {
            if (RECORD_TYPE_SECTION == record->type)
            {
                // Found another section. Done.
                break;
            }
            else if (RECORD_TYPE_TAGVALUE == record->type)
            {
                if (NULL != record->tag)
                {
                    // TODO: Protect against buffer overrun!
                    if (0 == strcmp (tag, record->tag))
                    {
                        // Found it!
#if (DEBUG_RECORDS > 1)
                        printf ("'%s=%s' found.\n", record->tag, record->value);
#endif
                        tagRecord = record;
                        break;
                    }
                }
            }

            record = record->next;
        } // end of while()
    } // end of NULL checks

    return tagRecord;
}

// Debug


/*--------------------------------------------------------------------------*/
bool RecordShowAll (RecordHandle *handle)
{
    bool status = false;

    if (NULL != handle)
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

// Debug
/*--------------------------------------------------------------------------*/
bool RecordShow (RecordStruct *record)
{
    bool status = false;

    if (NULL != record)
    {
#if (DEBUG_RECORDS > 1)
        // Really verbose output.
        printf ("0x%p  "
                "prev: 0x%p "
                "next: 0x%p ",
                (void*)record,
                (void*)record->prev,
                (void*)record->next);
#endif
        switch (record->type)
        {
            default:
            case RECORD_TYPE_UNKNOWN:
                if (NULL != record->unknown)
                {
                    printf ("%s\n", record->unknown);
                }
                break;

            case RECORD_TYPE_COMMENT:
                if (NULL != record->comment)
                {
                    printf (";%s\n", record->comment);
                }
                break;

            case RECORD_TYPE_SECTION:
                if (NULL != record->section)
                {
                    printf ("[%s]\n", record->section);
                }
                break;

            case RECORD_TYPE_TAGVALUE:
                if ((NULL != record->tag) && (NULL != record->value))
                {
                    printf ("%s=%s\n", record->tag, record->value);
                }
                break;
        }

        status = true;
    }

    return status;
}

// End of Template.c
