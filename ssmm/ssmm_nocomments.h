
// ssmm.h
// single size memory manager

struct ssmm;

ssmm* SsmmConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize);

bool SsmmDestruct(ssmm** _this, uint32_t* num);

bool SsmmNum(ssmm* _this, uint32_t* num);

bool SsmmReset(ssmm* _this, uint32_t* num);

void* SsmmAlloc(ssmm* _this);

bool SsmmFree(ssmm* _this, void** client);
