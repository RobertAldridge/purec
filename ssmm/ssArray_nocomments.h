
// ssArray.h
// single size array blah

struct ssArray;

ssArray* SsArrayConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize/*, bool lookup*/);

int64_t SsArrayDestruct(ssArray** _this);

int64_t SsArrayNum(ssArray* _this);

int64_t SsArrayReset(ssArray* _this);

bool SsArrayPush(ssArray* _this, void* client);

bool SsArrayGet(ssArray* _this, void* client);
bool SsArraySet(ssArray* _this, void* client);

bool SsArrayGetAt(ssArray* _this, uint32_t index, void* client);
bool SsArraySetAt(ssArray* _this, uint32_t index, void* client);
