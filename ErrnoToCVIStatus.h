#ifndef ERRNOTOCVISTATUS_H_INCLUDED
#define ERRNOTOCVISTATUS_H_INCLUDED

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
#define NO_ERROR                                (0)
#define OUT_OF_MEMORY                           (-12)
#define NULL_POINTER_PASSED                     (-65)
#define TOO_MANY_FILES_OPEN                     (-91)
#define UNEXPECTEDLY_REACHED_END_OF_FILE        (-92)
#define INPUT_OUTPUT_ERROR                      (-93)
#define FILE_NOT_FOUND                          (-94)
#define FILE_ACCESS_PERMISSION_DENIED           (-95)
#define DISK_IS_FULL                            (-97)
#define FILE_ALREADY_OPEN                       (-99)
#define BADLY_FORMED_PATHNAME                   (-100)
#define OPERATION_FAILED                        (-184)
#define COULD_NOT_OPEN_FILE_FOR_READING         (-5001)
#define ERROR_READING_FILE                      (-5002)
#define COULD_NOT_GENERATE_UNUSED_TEMP_FILENAME (-5003)
#define COULT_NOT_CREATE_TEMP_FILE              (-5004)
#define INVALID_INTEGER                         (-5021)
#define INVALID_UNSIGNED_INTEGER                (-5022)
#define INVALID_DOUBLE_VALUE                    (-5023)
#define INVALID_BOOLEAN                         (-5024)

/*--------------------------------------------------------------------------*/
// Prototypes
/*--------------------------------------------------------------------------*/
int ErrnoToCVIStatus (int err);

#endif // ERRNOTOCVISTATUS_H_INCLUDED

// End of ErrnoToCVIStatus.h
