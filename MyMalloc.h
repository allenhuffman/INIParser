#ifndef MYMALLOC_H_INCLUDED
#define MYMALLOC_H_INCLUDED

#include <stddef.h> // for size_t

// MyMalloc.h
size_t GetSizeAllocated (void);
void *MyMalloc (size_t size);
void MyFree (void *ptr);

#endif // MYMALLOC_H_INCLUDED
