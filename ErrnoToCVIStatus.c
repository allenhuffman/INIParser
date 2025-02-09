/*--------------------------------------------------------------------------*/
// Includes
/*--------------------------------------------------------------------------*/
// Compiler headers
#include <errno.h>

// This projects's header
#include "INIParser.h"

// This file's header
#include "ErrnoToCVIStatus.h"

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
// Convert a C errno value to a LabWindows status value.
int ErrnoToCVIStatus (int err) // cannot use "errno" since it is a global
{
    int status = NO_ERROR;

    switch (err)
    {
        // 0 - No Error
        case 0:
            status = NO_ERROR;
            break;

        // 2 - No Such File or Directory
        case ENOENT:
            status = FILE_NOT_FOUND;
            break;

        // 6 - Input/Output Error
        case EIO:
            status = INPUT_OUTPUT_ERROR;
            break;

        // 10 - Bad File Descriptor
        case EBADF:
            status = -1; // TODO
            break;

        // 12 - Out of Memory
        case ENOMEM:
            status = OUT_OF_MEMORY;
            break;

        // 13 - Permission Denied
        case EACCES:
            status = FILE_ACCESS_PERMISSION_DENIED;
            break;

        // 16 - Device or Resource Busy
        case EBUSY:
            status = -1; // TODO
            break;

        // 17 - File Exists
        case EEXIST:
            status = -1; // TODO
            break;

        //21 - Is a Directory
        case EISDIR:
            status = -1; // TODO
            break;

        // 23 - Too Many Files are Open in the System
        case ENFILE:
            status = -1; // TODO
            break;

        // 24 - Too Many Files are Open by the Process
        case EMFILE:
            status = -1; // TODO
            break;

        // 27 - File Too Large
        case EFBIG:
            status = -1; // TODO
            break;

        // 28 - No Space Left on Device
        case ENOSPC:
            status = -1; // TODO
            break;

        // 30 - Read Only File System
        case EROFS:
            status = -1; // TODO
            break;

        // 28 - Filename Too Long
        case ENAMETOOLONG:
            status = -1; // TODO
            break;

        default:
            status = -1; // TODO
            break;
    }

    return status;
}

/*--------------------------------------------------------------------------*/
// Private Functions
/*--------------------------------------------------------------------------*/


// End of ErrnoToCVIStatus.c
