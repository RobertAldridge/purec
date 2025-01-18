
// BlahPlatformAlloc.cpp
// Robert Aldridge

// _MSC_VER

//#include <cstddef> // size_t, wchar_t
#include <cstdint> // uint32_t
#include <cstdlib> // free, malloc
//#include <cstring>
#include <cwchar> // wcslen

//using std::size_t;
using std::uint32_t;
//using std::wchar_t;

#include "BlahLog.h"

#include "BlahPlatformAlloc.h"

#if 0/*defined(_MSC_VER)*/

#include <windows.h>
#include <ntsecapi.h>
#include <sddl.h>

#else

extern "C"
{

#define ERROR_INSUFFICIENT_BUFFER 122L
#define ERROR_SUCCESS 0L

#define MEM_COMMIT 0x00001000
#define MEM_LARGE_PAGES 0x20000000
#define MEM_RELEASE 0x00008000
#define MEM_RESERVE 0x00002000

#define PAGE_READWRITE 0x04

#define POLICY_CREATE_ACCOUNT 0x00000010L
#define POLICY_LOOKUP_NAMES 0x00000800L

#define SE_LOCK_MEMORY_NAME L"SeLockMemoryPrivilege"

#define SE_PRIVILEGE_ENABLED 0x00000002L

#define TOKEN_ADJUST_PRIVILEGES 0x0020
#define TOKEN_QUERY 0x0008

enum _TOKEN_INFORMATION_CLASS
{
  TokenUser = 1
};

typedef enum _TOKEN_INFORMATION_CLASS TOKEN_INFORMATION_CLASS;
typedef enum _TOKEN_INFORMATION_CLASS* PTOKEN_INFORMATION_CLASS;

struct _LSA_UNICODE_STRING
{
  unsigned short Length;
  unsigned short MaximumLength;
  unsigned char padding1[4];
  wchar_t* Buffer;
};

typedef struct _LSA_UNICODE_STRING LSA_UNICODE_STRING;
typedef struct _LSA_UNICODE_STRING* PLSA_UNICODE_STRING;

typedef void* LSA_HANDLE;
typedef void** PLSA_HANDLE;

typedef unsigned long ACCESS_MASK;

typedef void* HANDLE;

struct _LSA_OBJECT_ATTRIBUTES
{
  unsigned long Length;
  unsigned char padding1[4];
  HANDLE RootDirectory;
  LSA_UNICODE_STRING* ObjectName;
  unsigned long Attributes;
  unsigned char padding2[4];
  void* SecurityDescriptor;
  void* SecurityQualityOfService;
};

typedef struct _LSA_OBJECT_ATTRIBUTES LSA_OBJECT_ATTRIBUTES;
typedef struct _LSA_OBJECT_ATTRIBUTES* PLSA_OBJECT_ATTRIBUTES;

typedef void* PSID;

struct _SID_AND_ATTRIBUTES
{
  PSID Sid;
  unsigned long Attributes;
  unsigned char padding1[4];
};

typedef struct _SID_AND_ATTRIBUTES SID_AND_ATTRIBUTES;
typedef struct _SID_AND_ATTRIBUTES* PSID_AND_ATTRIBUTES;

struct _TOKEN_USER
{
  SID_AND_ATTRIBUTES User;
};

typedef struct _TOKEN_USER TOKEN_USER;
typedef struct _TOKEN_USER* PTOKEN_USER;

struct _LUID
{
  unsigned long LowPart;
  long HighPart;
};

typedef struct _LUID LUID;
typedef struct _LUID* PLUID;

struct _LUID_AND_ATTRIBUTES
{
  LUID Luid;
  unsigned long Attributes;
};

typedef struct _LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES;
typedef struct _LUID_AND_ATTRIBUTES* PLUID_AND_ATTRIBUTES;

struct _TOKEN_PRIVILEGES
{
  unsigned long PrivilegeCount;
  LUID_AND_ATTRIBUTES Privileges[1];
};

typedef struct _TOKEN_PRIVILEGES TOKEN_PRIVILEGES;
typedef struct _TOKEN_PRIVILEGES* PTOKEN_PRIVILEGES;

long __stdcall LsaOpenPolicy(LSA_UNICODE_STRING* SystemName, LSA_OBJECT_ATTRIBUTES* ObjectAttributes, ACCESS_MASK DesiredAccess, LSA_HANDLE* PolicyHandle);

__declspec(dllimport) int __stdcall AdjustTokenPrivileges(HANDLE TokenHandle, int DisableAllPrivileges, TOKEN_PRIVILEGES* NewState, unsigned long BufferLength, PTOKEN_PRIVILEGES PreviousState, unsigned long* ReturnLength);

__declspec(dllimport) int __stdcall CloseHandle(HANDLE hObject);

int __stdcall ConvertSidToStringSidW(PSID Sid, wchar_t** StringSid);

__declspec(dllimport) HANDLE __stdcall GetCurrentProcess();

__declspec(dllimport) unsigned long long __stdcall GetLargePageMinimum();

__declspec(dllimport) unsigned long __stdcall GetLastError();

__declspec(dllimport) int __stdcall GetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, void* TokenInformation, unsigned long TokenInformationLength, unsigned long* ReturnLength);

__declspec(dllimport) int __stdcall LookupPrivilegeValueW(const wchar_t* lpSystemName, const wchar_t* lpName, LUID* lpLuid);

long __stdcall LsaAddAccountRights(LSA_HANDLE PolicyHandle, PSID AccountSid, LSA_UNICODE_STRING* UserRights, unsigned long CountOfRights);

long __stdcall LsaRemoveAccountRights(LSA_HANDLE PolicyHandle, PSID AccountSid, unsigned char AllRights, LSA_UNICODE_STRING* UserRights, unsigned long CountOfRights);

__declspec(dllimport) int __stdcall OpenProcessToken(HANDLE ProcessHandle, unsigned long DesiredAccess, HANDLE* TokenHandle);

__declspec(dllimport) void* __stdcall VirtualAlloc(void* BaseAddress, unsigned long long Size, unsigned long AllocationType, unsigned long Protection);

__declspec(dllimport) int __stdcall VirtualFree(void* lpAddress, unsigned long long dwSize, unsigned long dwFreeType);

}

#endif

#if defined(_MSC_VER)
//static bool gBlahLargePageSupportEnabled
//static bool gBlahLargePageSupportFailed
//static uint32_t gLargePageMinimum
static void InitLsaString(LSA_UNICODE_STRING* lhsString, wchar_t* rhsString);
static long OpenPolicy(wchar_t* serverName, unsigned long desiredAccess, void** policyHandle);
static long SetPrivilegeOnAccount(void* policyHandle, void* accountSid, wchar_t* privilegeName, int bEnable);
static bool EnableLargePageSupport();
static uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf);
#endif

#if defined(_MSC_VER)
static bool gBlahLargePageSupportEnabled = false;

static bool gBlahLargePageSupportFailed = false;

static uint32_t gLargePageMinimum = 0;

void InitLsaString(LSA_UNICODE_STRING* lhsString, wchar_t* rhsString)
{
  size_t stringLength = 0;

  if( !rhsString)
  {
    lhsString->Buffer = 0;
    lhsString->Length = 0;
    lhsString->MaximumLength = 0;
  }
  else
  {
    stringLength = wcslen(rhsString);

    lhsString->Buffer = rhsString;
    lhsString->Length = (unsigned short)(sizeof(wchar_t) * stringLength);
    lhsString->MaximumLength = (unsigned short)(sizeof(wchar_t) * (stringLength + 1) );
  }
}

long OpenPolicy(wchar_t* serverName, unsigned long desiredAccess, void** policyHandle)
{
  long result = 0;

  LSA_OBJECT_ATTRIBUTES objectAttributes = {0};
  LSA_UNICODE_STRING serverString = {0};
  LSA_UNICODE_STRING* server = 0;

  if(serverName)
  {
    InitLsaString( &serverString, serverName);

    server = &serverString;
  }

  result = LsaOpenPolicy(server, &objectAttributes, desiredAccess, policyHandle);

  return result;
}

long SetPrivilegeOnAccount(void* policyHandle, void* accountSid, wchar_t* privilegeName, int bEnable)
{
  long result = 0;

  LSA_UNICODE_STRING privilegeString = {0};

  InitLsaString( &privilegeString, privilegeName);

  if(bEnable)
    result = LsaAddAccountRights(policyHandle, accountSid, &privilegeString, 1);
  else
    result = LsaRemoveAccountRights(policyHandle, accountSid, false, &privilegeString, 1);

  return result;
}

bool EnableLargePageSupport()
{
  bool result = false;

  void* hToken = 0;
  unsigned long dwBufferSize = 0;
  unsigned long error = 0;
  TOKEN_USER* tokenUser = 0;
  wchar_t* strsid = 0;
  void* policyHandle = 0;
  long status = 0;
  TOKEN_PRIVILEGES tp = {0};
  int privileged = 0;
  void* pointer = 0;

  if( !OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) )
  {
    BlahLog("OpenProcessToken failed %lu\n", GetLastError() );
    goto label_return;
  }

  if( !GetTokenInformation(hToken, TokenUser, 0, 0, &dwBufferSize) )
  {
    error = GetLastError();
    if(error != ERROR_INSUFFICIENT_BUFFER)
    {
      BlahLog("GetTokenInformation failed %lu\n", error);

      CloseHandle(hToken);
      hToken = 0;

      goto label_return;
    }
  }

  tokenUser = (TOKEN_USER*)malloc( (size_t)dwBufferSize);

  if( !GetTokenInformation(hToken, TokenUser, tokenUser, dwBufferSize, &dwBufferSize) )
  {
    BlahLog("GetTokenInformation failed %lu\n", GetLastError() );

    CloseHandle(hToken);
    hToken = 0;

    goto label_return;
  }

  ConvertSidToStringSidW(tokenUser->User.Sid, &strsid);
  BlahLog("User SID: %S\n", strsid);

  CloseHandle(hToken);
  hToken = 0;

  status = OpenPolicy(0, POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES, &policyHandle);
  if(status)
  {
    BlahLog("OpenPolicy %li\n", status);

    //free(tokenUser);
    //tokenUser = 0;

    goto label_return;
  }

  status = SetPrivilegeOnAccount(policyHandle, tokenUser->User.Sid, (wchar_t*)SE_LOCK_MEMORY_NAME, true);
  if(status)
  {
    BlahLog("OpenPSetPrivilegeOnAccountolicy %li\n", status);
    goto label_return;
  }

  if( !OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken) )
  {
    BlahLog("OpenProcessToken #2 failed %lu\n", GetLastError() );
    goto label_return;
  }

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if( !LookupPrivilegeValueW(0, SE_LOCK_MEMORY_NAME, &tp.Privileges[0].Luid) )
  {
    BlahLog("LookupPrivilegeValue failed %lu\n", GetLastError() );
    goto label_return;
  }

  privileged = AdjustTokenPrivileges(hToken, false, &tp, 0, 0, 0);
  error = GetLastError();

  if( !privileged || error != ERROR_SUCCESS)
  {
      BlahLog("AdjustTokenPrivileges failed %lu\n", error);
      goto label_return;
  }

  CloseHandle(hToken);
  hToken = 0;

  pointer = VirtualAlloc(0, GetLargePageMinimum(), MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
  if( !pointer)
    BlahLog("VirtualAlloc failed %lu\n", GetLastError() );

  VirtualFree(pointer, 0, MEM_RELEASE);
  pointer = 0;

  result = true;

label_return:
  if(tokenUser)
  {
    free(tokenUser);
    tokenUser = 0;
  }

  return result;
}

uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf)
{
  return (sizeOf % alignmentOf) ? sizeOf + (alignmentOf - sizeOf % alignmentOf) : sizeOf;
}
#endif

bool BlahPlatformAllocIsEnabled()
{
  bool result = false;

#if defined(_MSC_VER)
  if(gBlahLargePageSupportEnabled)
  {
    result = true;
    goto label_return;
  }

  if(gBlahLargePageSupportFailed)
    goto label_return;

  result = EnableLargePageSupport();

  if(result)
  {
    gBlahLargePageSupportEnabled = true;

    gLargePageMinimum = (uint32_t)GetLargePageMinimum();
  }
  else
    gBlahLargePageSupportFailed = true;
#endif

label_return:
  return result;
}

bool BlahPlatformAllocIsAcceptable(uint32_t sizeOf)
{
  bool result = false;

#if defined(_MSC_VER)
  if( !BlahPlatformAllocIsEnabled() )
    goto label_return;

  if(sizeOf >= gLargePageMinimum)
    result = true;
#endif

label_return:
  return result;
}

// guarantees that when the caller later initially accesses the memory, the contents will be zero.
// actual physical pages are not allocated unless/until the virtual addresses are actually accessed.
void* BlahPlatformAlloc(uint32_t sizeOf, bool /*zero*/)
{
  void* pointer = 0;

#if defined(_MSC_VER)
  if( !sizeOf)
    goto label_return;

  if( !BlahPlatformAllocIsEnabled() || !BlahPlatformAllocIsAcceptable(sizeOf) )
    goto label_return;

  sizeOf = BlahAlignedOfValue(gLargePageMinimum, sizeOf);

  pointer = VirtualAlloc(0, sizeOf, MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES, PAGE_READWRITE);
#endif

label_return:
  return pointer;
}

bool BlahPlatformFree(void* pointer, uint32_t sizeOf)
{
  bool result = false;

#if defined(_MSC_VER)
  if( !pointer || !sizeOf)
    goto label_return;

  if( !BlahPlatformAllocIsEnabled() || !BlahPlatformAllocIsAcceptable(sizeOf) )
    goto label_return;

  // if the function succeeds, the return value is nonzero
  //
  // if the function fails, the return value is 0 (zero). to get extended error information, call GetLastError
  result = (VirtualFree(pointer, 0, MEM_RELEASE) != 0);
#endif

label_return:
  return result;
}
