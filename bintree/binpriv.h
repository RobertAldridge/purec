
// File Name: binpriv.h

#if !defined( BINPRIV )
#define BINPRIV

#ifdef __cplusplus
   extern "C" {
#endif

typedef struct __BINTREE_NODE * PBINTREE_NODE;

#if defined( _MSC_VER )
   #pragma warning ( disable: 4200 )
   #pragma warning ( disable: 4201 )
#endif

typedef struct __BINTREE_NODE
{
   PBINTREE_NODE LeftChild;
   PBINTREE_NODE RightChild;
   PBINTREE_NODE Parent;

   INDEX_TYPE Color;

   char Object[];

} BINTREE_NODE;

typedef struct __BINTREE_HEAD
{
   PBINTREE_NODE Root;

   PBINTREE_NODE Nil;

   COMPARE LessThan;

   EQUIVALENCE EqualTo;

   EVALUATE ClientEvaluate;

   INDEX_TYPE MaxNumberOfNodes;

   INDEX_TYPE NumberOfNodes;


   ////////////////////////////////////
   INDEX_TYPE SizeOfClientAligned;

   INDEX_TYPE SizeOfClientExact;

   INDEX_TYPE MemoryTotalSize;
   ////////////////////////////////////


   ////////////////////////////////////
   union
   {
      PBINTREE_NODE * StackTraverseArrayStart;
      PBINTREE_NODE * QueueTraverseArrayStart;
   };
   ////////////////////////////////////


   ////////////////////////////////////
   char ** MemoryManagerArrayCurrent;

   char MemoryManagerNodePoolArrayStart[];
   ////////////////////////////////////


} BINTREE_HEAD;

#if defined( _MSC_VER )
   #pragma warning ( default: 4201 )
   #pragma warning ( default: 4200 )
#endif

#ifdef __cplusplus
   }
#endif

#endif