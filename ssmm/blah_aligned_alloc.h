
// blah_aligned_alloc.h
// Robert Aldridge

int blah_get_number();

int EnableLargePageSupport();

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
uint8_t* blah_aligned_alloc(size_t size, uint8_t** reference, bool clear);

void blah_free_aligned_sized(void* ptr, size_t alignment, size_t size);
