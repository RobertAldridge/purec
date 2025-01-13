
// BlahAlloc.h

void BlahEnableAlloc();

void* BlahAlloc(uint32_t sizeOf, bool zero);

void BlahFree(void* pointer, uint32_t sizeOf, bool zero);
