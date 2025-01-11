
// ssSet.h
// Robert Aldridge

struct ssSet;

typedef uint32_t(*SsSetCompare)(void*, void*);

typedef uint32_t(*SsSetEvaluate)(void*);

//typedef uint32_t(*SsSetEquivalence)(void* key, void*);

const int SsSetPreorder = 0; // preorder == 0; preorder == depth-first
const int SsSetInorder = 1; // inorder == 1
const int SsSetPostorder = 2; // postorder == 2
const int SsSetLevelorder = 3; // levelorder == 3; levelorder == breadth-first

ssSet* SsSetConstruct(uint32_t sizeOf, uint32_t minimum, int64_t maximum, uint32_t resize, SsSetCompare lessThan);

int64_t SsSetDestruct(ssSet* _this);

int64_t SsSetNum(ssSet* _this);

int64_t SsSetReset(ssSet* _this);

int64_t SsSetInsert(ssSet* _this, void* key, SsSetCompare lessThan, void* client);

int64_t SsSetRemove(ssSet* _this, void* key, SsSetCompare lessThan, void* client);

int64_t SsSetGetExtrema(ssSet* _this, bool maximum, void* client);

int64_t SsSetFind(ssSet* _this, void* key, SsSetCompare lessThan, void* client);

int64_t SsSetDump(ssSet* _this, SsSetEvaluate evaluate, int order);

// for debugging not production use
int64_t SsSetDepthTree(ssSet* _this);
int64_t SsSetMaxStack(ssSet* _this);
int64_t SsSetMaxQueue(ssSet* _this);

#if 0
bool SsSetPush(ssSet* _this, void* client);
bool SsSetPop(ssSet* _this, void* client);

bool SsSetGet(ssSet* _this, void* key, SsSetCompare lessThan, void* client);
bool SsSetSet(ssSet* _this, void* key, SsSetCompare lessThan, void* client);

bool SsSetGetAt(ssSet* _this, uint32_t index, void* client);
bool SsSetSetAt(ssSet* _this, uint32_t index, void* client);
#endif

// iterator begin()
// iterator end()

// iterator rbegin()
// iterator rend()

// bool empty()
// size_type size()
// size_type max_size()

// key_value& operator[key_value key]; unique
// key_value& at(key_value key); unique

// pair<iterator, bool> insert(key_value key, key_value client); unique
// iterator insert(key_value key, key_value client); non-unique

// iterator insert(iterator position, key_value)
// void insert(iterator first, iterator last)

// pair<iterator, bool> insert_or_assign(key_value key, key_value client); unique
// iterator insert_or_assign(iterator hint, key_value key, key_value client); unique

// node extract(iterator position)
// node extract(key_value key)
// pair<iterator position, bool inserted, node> insert(node); unique
// iterator insert(node); non-unique
// iterator insert(iterator hint, node)

// size_type erase(key_value key)
// iterator erase(iterator position)
// iterator erase(iterator first, iterator last)

// void clear()

// iterator find(key_value key)

// size_type count(key_value key)
// bool contains(key_value key)

// iterator lower_bound(key_value key)
// iterator upper_bound(key_value key)
// pair<iterator, iterator> equal_range(key_value key)
