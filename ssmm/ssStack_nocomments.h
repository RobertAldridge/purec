
// ssStack.h
// single size stack blah

struct ssStack;

ssStack* SsStackConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize);

int64_t SsStackDestruct(ssStack** _this);

int64_t SsStackNum(ssStack* _this);

int64_t SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* client);
bool SsStackPop(ssStack* _this, void* client);

bool SsStackGet(ssStack* _this, void* client);
bool SsStackSet(ssStack* _this, void* client);

bool SsStackGetAt(ssStack* _this, uint32_t index, void* client);
bool SsStackSetAt(ssStack* _this, uint32_t index, void* client);
