
// File Name: mmpriv.h
// Robert Aldridge

#ifdef __cplusplus
   extern "C" {
#endif

class dMemoryManagement
{

private:

   friend class mm;
   friend class dInitGlobalData;

   static bool enter;

   static
   void
   dMemoryManagementInit
   (
   );

   static
   void
   dMemoryManagementTerm
   (
   );
};

#ifdef __cplusplus
   }
#endif