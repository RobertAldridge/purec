
// File Name: memory.h

#ifdef __cplusplus
   extern "C" {
#endif

extern
void *
Allocate(
          size_t Size
        );

extern
void
DeAllocate(
            void * Memory
          );

extern
void
TermAllocate();

#ifdef __cplusplus
   }
#endif