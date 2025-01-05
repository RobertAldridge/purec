
// ssStack.h
// single size stack blah

struct ssStack;

ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsStackDestruct(ssStack** _this/*reference*/);

int SsStackNum(ssStack* _this);

int SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* client);
bool SsStackPop(ssStack* _this, void* client);

bool SsStackGet(ssStack* _this, void* client);
bool SsStackSet(ssStack* _this, void* client);

bool SsStackGetAt(ssStack* _this, int index, void* client);
bool SsStackSetAt(ssStack* _this, int index, void* client);
