
// ssMm.h
// single size memory manager

struct ssMm;

ssMm* SsMmConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize);

bool SsMmDestruct(ssMm** _this);

bool SsMmNum(ssMm* _this, uint32_t* num);

bool SsMmReset(ssMm* _this);

void* SsMmAlloc(ssMm* _this);

bool SsMmFree(ssMm* _this, void** client);
