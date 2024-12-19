
// File Name: fmpriv.h
// Robert Aldridge

#ifdef __cplusplus
   extern "C" {
#endif

class dFileManagement
{

private:

   friend class fileManagement;
   friend class dInitGlobalData;

   static bool enter;

   static
   void
   dFileManagementInit
   (
   );

   static
   void
   dFileManagementTerm
   (
   );
};

#ifdef __cplusplus
   }
#endif