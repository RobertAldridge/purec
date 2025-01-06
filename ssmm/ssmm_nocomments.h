
// ssmm.h
// single size memory manager

struct ssmm;

ssmm* SsmmConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsmmDestruct(ssmm** _this/*reference*/);

int SsmmNum(ssmm* _this);

int SsmmReset(ssmm* _this);

void* SsmmAlloc(ssmm* _this);

bool SsmmFree(ssmm* _this, void** client);
