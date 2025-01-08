
// blah_aligned_alloc.h

uint32_t blah_get_number();

void* blah_aligned_alloc(uint32_t size);

void blah_free_aligned_sized(void* ptr);

bool EnableLargePageSupport();
