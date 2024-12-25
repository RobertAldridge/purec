
// ssmm.h
// single size memory manager

// n is total number of elements
// p is total number of pools

// memory overhead O(lg(n) ) when resize is -1 otherwise O(p)

#if 0
// memory overhead is per chuck when debug is enabled; O(n)
enum class ssmm_debug
{
  off = 0,
  constant = 1, // O(1)
  logarithmic = 2, // O(lg(n) )
  linear = 2 // O(n)
};

using enum ssmm_debug;
#endif

// O(malloc)
// sizeOf >= sizeof(void*)
//
// returns null on failure, otherwise returns non-null
//
// initial capacity must be larger than zero
//
// you can delay the overhead of creating a pool by setting isTentative to true.  in that case, the first pool will be
// created upon first call to SsmmAlloc.  note that in this case calls to SsmmSetResize will fail until after the first
// call to SsmmAlloc
ssmm* SsmmConstruct(int sizeOf, int initialCapacity, bool isTentative, ssmm_debug debug);

// O(free) * O(lg(n) ) when resize is -1 otherwise O(free) * O(p)
// client reference to ssmm instance will be cleared
//
// returns -1 on failure, otherwise returns the number of chunks that were in
// use before the call
int SsmmDestruct(ssmm** _this);

// O(1)
//
// returns -1 on failure, otherwise returns the number of chunks currently in
// use
int SsmmNum(ssmm* _this);

// O(1)
// ssmm instance doubles capacity each time it runs out of space
// initialCapacity 1000 -> 2000 -> 4000 etc
//
// call SsmmSetResize to override default behavior
// for example SsmmSetResize(100)
// initialCapacity 1000 -> 1100 -> 1200 etc
//
// call SsmmSetResize(-1) to revert to default behavior
//
// returns false on failure, otherwise returns true
bool SsmmSetResize(ssmm* _this, int resize);

// O(1)
// reclaims all chunks without freeing pool memory (ie retains current capacity)
// pointers returned by SsmmAlloc prior to calling SsmmReset will be invalid
//
// returns -1 on failure, otherwise returns the number of chunks that were in
// use before the call
int SsmmReset(ssmm* _this);

// O(free) * O(lg(n) ) when resize is -1 otherwise O(free) * O(p)
// reclaims all chunks, frees all appended pools (ie reverts to initialCapacity)
// pointers returned by SsmmAlloc prior to calling SsmmClear will be invalid
//
// returns -1 on failure, otherwise returns the number of chunks that were in
// use before the call
int SsmmClear(ssmm* _this);

// if resize is -1
// amortized cost over n calls is O(n) + O(malloc) * O(lg(n) )
// or O(malloc) * O(lg(n) / n) per call - effectively O(1)
//
// if resize is not -1
// amortized cost over n calls is O(n) + O(malloc) * O(p)
// or O(malloc) * O(p / n) per call
//
// returns null on failure, otherwise returns non-null
void* SsmmAlloc(ssmm* _this);

// O(1)
// if call is successful, client reference to chunk will be cleared
//
// returns false on failure, otherwise returns true
bool SsmmFree(ssmm* _this, void** chunk);
