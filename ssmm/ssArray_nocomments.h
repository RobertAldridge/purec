
// ssArray.h
// single size array blah

struct ssArray;

ssArray* SsArrayConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsArrayDestruct(ssArray** _this/*reference*/);

int SsArrayNum(ssArray* _this);

int SsArrayReset(ssArray* _this);

bool SsArrayPush(ssArray* _this, void* client);

bool SsArrayGet(ssArray* _this, void* client);
bool SsArraySet(ssArray* _this, void* client);

bool SsArrayGetAt(ssArray* _this, int index, void* client);
bool SsArraySetAt(ssArray* _this, int index, void* client);
