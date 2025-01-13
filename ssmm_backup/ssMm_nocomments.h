
// ssMm.h
// single size memory manager

struct ssMm;

ssMm* SsMmConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize);

int64_t SsMmDestruct(ssMm** _this);

int64_t SsMmNum(ssMm* _this);

int64_t SsMmReset(ssMm* _this);

void* SsMmAlloc(ssMm* _this);

bool SsMmFree(ssMm* _this, void** client);
