
// ssStack.h
// single size stack blah

struct ssStack;

ssStack* SsStackConstruct(uint32_t sizeOf, uint32_t minimumCapacity, uint32_t maximumCapacity, uint32_t resize);

bool SsStackDestruct(ssStack** _this);

bool SsStackNum(ssStack* _this, uint32_t* num);

bool SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* client);
bool SsStackPop(ssStack* _this, void* client);

bool SsStackGet(ssStack* _this, void* client);
bool SsStackSet(ssStack* _this, void* client);

bool SsStackGetAt(ssStack* _this, uint32_t index, void* client);
bool SsStackSetAt(ssStack* _this, uint32_t index, void* client);
