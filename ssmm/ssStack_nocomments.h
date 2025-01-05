
// ssStack.h
// single size stack blah

struct ssStack;

ssStack* SsStackConstruct(int sizeOf, int minimumCapacity, int maximumCapacity, int resize);

int SsStackDestruct(ssStack** _this);

int SsStackNum(ssStack* _this);

int SsStackReset(ssStack* _this);

bool SsStackPush(ssStack* _this, void* chunk);

bool SsStackPop(ssStack* _this, void* chunk);
