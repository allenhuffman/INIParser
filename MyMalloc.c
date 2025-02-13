// MyMalloc.c
#include <stdlib.h> // for malloc()/free();
#include <string.h> // for memcpy()
#include <inttypes.h>

#define DEBUG_MYMALLOC 0

#if DEBUG_MYMALLOC > 0
    #include <stdio.h>
#endif

static size_t S_bytesAllocated = 0;

size_t GetSizeAllocated (void)
{
    return S_bytesAllocated;
}

void *MyMalloc (size_t size)
{
    // Allocate room for a "size_t" plus user's requested bytes.
    void *ptr = malloc (sizeof(size) + size);

    if (NULL != ptr)
    {
        // Add this amount.
        S_bytesAllocated = S_bytesAllocated + size;

        // Copy size into start of memory.
        memcpy (ptr, &size, sizeof (size));

        // Move pointer past the size.
        ptr = ((char*)ptr + sizeof (size));

#if DEBUG_MYMALLOC > 0
        printf ("MyMalloc (%zu)\n", size);
#endif
    }

    return ptr;
}

void MyFree (void *ptr)
{
    if (NULL != ptr)
    {
        size_t size = 0;

        // Move pointer back to the size.
        ptr = ((char*)ptr - sizeof (size));

        // Copy out size.
        memcpy (&size, ptr, sizeof(size));

        // Subtract this amount.
        S_bytesAllocated = S_bytesAllocated - size;

        // Release the memory.
        free (ptr);

#if DEBUG_MYMALLOC > 0
        printf ("MyFree (%zu)\n", size);
#endif
    }
}
