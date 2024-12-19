
// FileName: init.cpp
// Robert Aldridge

#include "../../general.h"

#if defined( _MSC_VER )
   #pragma warning ( push, 4 )
#endif

#include "../debugutils/memleakpriv.h"
#include "../mm/mmpriv.h"
#include "../fm/fmpriv.h"

#ifdef __cplusplus
   extern "C" {
#endif

class dInitGlobalData
{

private:

   static bool enter;

public:

   dInitGlobalData::dInitGlobalData
   (
   );

   dInitGlobalData::~dInitGlobalData
   (
   );
};

bool dInitGlobalData::enter = false;

static dInitGlobalData dInitGlobalDataInstance;

dInitGlobalData::dInitGlobalData
(
)
{
   #if defined( _DEBUG ) && !defined( NDEBUG ) && !defined( _MSC_VER )
      dMemoryLeak::dMemoryLeakInit();
   #endif
   dMemoryManagement::dMemoryManagementInit();
   dFileManagement::dFileManagementInit();
   dInitGlobalData::enter = true;
}

dInitGlobalData::~dInitGlobalData
(
)
{
   dFileManagement::dFileManagementTerm();
   dMemoryManagement::dMemoryManagementTerm();
   #if defined( _DEBUG ) && !defined( NDEBUG ) && !defined( _MSC_VER )
      dMemoryLeak::dMemoryLeakTerm();
   #endif
   dInitGlobalData::enter = false;
}

#ifdef __cplusplus
   }
#endif