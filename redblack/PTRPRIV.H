
// File Name: ptrpriv.h

#if !defined( PTRPRIV )
#define PTRPRIV

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

   void * Object;

} BINTREE_NODE;

typedef struct __BINTREE_HEAD
{
   PBINTREE_NODE Root;

   PBINTREE_NODE Nil;

   INDEX_TYPE MaxNumberOfNodes;

   INDEX_TYPE NumberOfNodes;


   ////////////////////////////////////
   INDEX_TYPE MemoryTotalSize;
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