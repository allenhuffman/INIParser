#ifndef MYMALLOC_H_INCLUDED
#define MYMALLOC_H_INCLUDED

// MyMalloc.h
size_t GetSizeAllocated (void);
void *MyMalloc (size_t size);
void MyFree (void *ptr);

#endif // MYMALLOC_H