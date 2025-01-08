
// ssArray.h
// single size array blah

struct ssArray;

ssArray* SsArrayConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize);

bool SsArrayDestruct(ssArray** _this);

bool SsArrayNum(ssArray* _this, uint32_t* num);

bool SsArrayReset(ssArray* _this);

bool SsArrayPush(ssArray* _this, void* client);

bool SsArrayGet(ssArray* _this, void* client);
bool SsArraySet(ssArray* _this, void* client);

bool SsArrayGetAt(ssArray* _this, uint32_t index, void* client);
bool SsArraySetAt(ssArray* _this, uint32_t index, void* client);
