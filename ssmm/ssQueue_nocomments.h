
// ssQueue.h
// single size queue blah

struct ssQueue;

ssQueue* SsQueueConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize);

bool SsQueueDestruct(ssQueue** _this);

bool SsQueueNum(ssQueue* _this, uint32_t* num);

bool SsQueueReset(ssQueue* _this);

bool SsQueuePushBack(ssQueue* _this, void* client);
bool SsQueuePopBack(ssQueue* _this, void* client);

bool SsQueuePushFront(ssQueue* _this, void* client);
bool SsQueuePopFront(ssQueue* _this, void* client);

bool SsQueueGetBack(ssQueue* _this, void* client);
bool SsQueueSetBack(ssQueue* _this, void* client);

bool SsQueueGetFront(ssQueue* _this, void* client);
bool SsQueueSetFront(ssQueue* _this, void* client);

bool SsQueueGetAt(ssQueue* _this, uint32_t index, void* client);
bool SsQueueSetAt(ssQueue* _this, uint32_t index, void* client);
