
// blah_alloc.cpp
// Robert Aldridge

#if defined(_MSC_VER)
#pragma warning (disable : 4668)
#pragma warning (disable : 5039)
#include <windows.h>
#include <ntsecapi.h>
#include <Sddl.h>
#endif

// _MSC_VER
// ERROR_INSUFFICIENT_BUFFER
// ERROR_SUCCESS
// MEM_COMMIT
// MEM_LARGE_PAGES
// MEM_RELEASE
// MEM_RESERVE
// PAGE_READWRITE
// POLICY_CREATE_ACCOUNT
// POLICY_LOOKUP_NAMES
// SE_LOCK_MEMORY_NAME
// SE_PRIVILEGE_ENABLED
// TOKEN_ADJUST_PRIVILEGES
// TOKEN_QUERY

// LSA_OBJECT_ATTRIBUTES
// LSA_UNICODE_STRING
// TOKEN_PRIVILEGES
// TOKEN_USER

// AdjustTokenPrivileges
// CloseHandle
// ConvertSidToStringSid
// GetCurrentProcess
// GetLargePageMinimum
// GetLastError
// GetTokenInformation
// LookupPrivilegeValue
// LsaAddAccountRights
// LsaOpenPolicy
// LsaRemoveAccountRights
// OpenProcessToken
// VirtualAlloc
// VirtualFree

#include <cstddef> // size_t
#include <cstdint> // uint32_t
#include <cstdio> // printf
#include <cstdlib> // free, malloc
#include <cstring> // memset

using std::free;
using std::malloc;
using std::memset;
using std::printf;
using std::size_t;
using std::uint32_t;
using std::wchar_t;

#include "blah_alloc.h"

#if defined(_MSC_VER)
//static bool gBlahLargePageSupportEnabled;
//static uint32_t gLargePageMinimum;
static void InitLsaString(LSA_UNICODE_STRING* lhsString, wchar_t* rhsString);
static long OpenPolicy(wchar_t* serverName, unsigned long desiredAccess, void** policyHandle);
static long SetPrivilegeOnAccount(void* policyHandle, void* accountSid, wchar_t* privilegeName, int bEnable);
static bool EnableLargePageSupport();
#endif

static uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf);

#if defined(_MSC_VER)
static bool gBlahLargePageSupportEnabled = false;

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

  memset( &objectAttributes, 0, sizeof(LSA_OBJECT_ATTRIBUTES) );

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
    printf("OpenProcessToken failed %lu\n", GetLastError() );
    goto label_return;
  }

  if( !GetTokenInformation(hToken, TokenUser, 0, 0, &dwBufferSize) )
  {
    error = GetLastError();
    if(error != ERROR_INSUFFICIENT_BUFFER)
    {
      printf("GetTokenInformation failed %lu\n", error);

      CloseHandle(hToken);
      hToken = 0;

      goto label_return;
    }
  }

  tokenUser = (TOKEN_USER*)malloc(dwBufferSize);

  if( !GetTokenInformation(hToken, TokenUser, tokenUser, dwBufferSize, &dwBufferSize) )
  {
    printf("GetTokenInformation failed %lu\n", GetLastError() );

    CloseHandle(hToken);
    hToken = 0;

    goto label_return;
  }

  ConvertSidToStringSid(tokenUser->User.Sid, &strsid);
  printf("User SID: %S\n", strsid);

  CloseHandle(hToken);
  hToken = 0;

  status = OpenPolicy(0, POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES, &policyHandle);
  if(status)
    printf("OpenPolicy %li\n", status);

  status = SetPrivilegeOnAccount(policyHandle, tokenUser->User.Sid, (wchar_t*)SE_LOCK_MEMORY_NAME, true);
  if(status)
    printf("OpenPSetPrivilegeOnAccountolicy %li\n", status);

  if( !OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken) )
  {
    printf("OpenProcessToken #2 failed %lu\n", GetLastError() );
    goto label_return;
  }

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if( !LookupPrivilegeValue(0, SE_LOCK_MEMORY_NAME, &tp.Privileges[0].Luid) )
  {
    printf("LookupPrivilegeValue failed %lu\n", GetLastError() );
    goto label_return;
  }

  privileged = AdjustTokenPrivileges(hToken, false, &tp, 0, 0, 0);
  error = GetLastError();

  if( !privileged || error != ERROR_SUCCESS)
  {
      printf("AdjustTokenPrivileges failed %lu\n", error);
      goto label_return;
  }

  CloseHandle(hToken);
  hToken = 0;

  pointer = VirtualAlloc(0, GetLargePageMinimum(), MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
  if( !pointer)
    printf("VirtualAlloc failed %lu\n", GetLastError() );

  VirtualFree(pointer, 0, MEM_RELEASE);
  pointer = 0;

  result = true;

label_return:
  return result;
}
#endif

uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf)
{
  return (sizeOf % alignmentOf) ? sizeOf + (alignmentOf - sizeOf % alignmentOf) : sizeOf;
}

void BlahEnableAlloc()
{
#if defined(_MSC_VER)
  if(gBlahLargePageSupportEnabled)
    goto label_return;

  gBlahLargePageSupportEnabled = EnableLargePageSupport();

  if(gBlahLargePageSupportEnabled)
    gLargePageMinimum = (uint32_t)GetLargePageMinimum();

label_return:
  return;
#endif
}

void* BlahAlloc(uint32_t sizeOf, bool zero)
{
  void* pointer = 0;

  if( !sizeOf)
    goto label_return;

#if defined(_MSC_VER)
  if(gBlahLargePageSupportEnabled && sizeOf >= gLargePageMinimum)
  {
    sizeOf = BlahAlignedOfValue(gLargePageMinimum, sizeOf);
    pointer = VirtualAlloc(0, sizeOf, MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES, PAGE_READWRITE);
  }
  else
#endif
  {
    sizeOf = BlahAlignedOfValue(sizeof(void*), sizeOf);
    pointer = malloc(sizeOf);
    if( !pointer)
      goto label_return;
    
    if(zero)
      memset(pointer, 0, sizeOf);
  }

label_return:
  return pointer;
}

void BlahFree(void* pointer, uint32_t sizeOf, bool zero)
{
  if( !pointer || !sizeOf)
    goto label_return;

#if defined(_MSC_VER)
  if(gBlahLargePageSupportEnabled && sizeOf >= gLargePageMinimum)
  {
    if(zero)
    {
      sizeOf = BlahAlignedOfValue(gLargePageMinimum, sizeOf);
      memset(pointer, 0, sizeOf);
    }

    VirtualFree(pointer, 0, MEM_RELEASE);
  }
  else
#endif
  {
    if(zero)
    {
      sizeOf = BlahAlignedOfValue(sizeof(void*), sizeOf);
      memset(pointer, 0, sizeOf);
    }

    free(pointer);
  }

label_return:
  return;
}
