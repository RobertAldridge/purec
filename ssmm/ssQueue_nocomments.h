
// ssQueue.h
// single size queue blah

struct ssQueue;

ssQueue* SsQueueConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsQueueDestruct(ssQueue** _this/*reference*/);

int SsQueueNum(ssQueue* _this);

int SsQueueReset(ssQueue* _this);

bool SsQueuePushBack(ssQueue* _this, void* client);
bool SsQueuePopBack(ssQueue* _this, void* client);

bool SsQueuePushFront(ssQueue* _this, void* client);
bool SsQueuePopFront(ssQueue* _this, void* client);

bool SsQueueGetBack(ssQueue* _this, void* client);
bool SsQueueSetBack(ssQueue* _this, void* client);

bool SsQueueGetFront(ssQueue* _this, void* client);
bool SsQueueSetFront(ssQueue* _this, void* client);

bool SsQueueGetAt(ssQueue* _this, int index, void* client);
bool SsQueueSetAt(ssQueue* _this, int index, void* client);
