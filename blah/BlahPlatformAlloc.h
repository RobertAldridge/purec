
// BlahPlatformAlloc.h

bool BlahPlatformAllocIsEnabled();

bool BlahPlatformAllocIsAcceptable(uint32_t sizeOf);

void* BlahPlatformAlloc(uint32_t sizeOf, bool zero);

bool BlahPlatformFree(void* pointer, uint32_t sizeOf);
