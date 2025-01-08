
// blah_alloc.cpp
// Robert Aldridge

#if defined(_MSC_VER)
#pragma warning (disable : 4668)
#pragma warning (disable : 5039)
#include <windows.h>
#include <ntsecapi.h>
#include <Sddl.h>
#endif

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint32_t, uint8_t
#include <cstdio> // printf
#include <cstdlib> // free, malloc
#include <cstring> // memset

using std::free;
using std::malloc;
using std::memset;
using std::printf;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;
using std::uint32_t;

#include "blah_alloc.h"

#if defined(_MSC_VER)
static void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String)
{
  DWORD StringLength = 0;

  if( !String)
  {
    LsaString->Buffer = 0;
    LsaString->Length = 0;
    LsaString->MaximumLength = 0;
  }
  else
  {
    StringLength = (DWORD)wcslen(String);
    LsaString->Buffer = String;
    LsaString->Length = (USHORT)StringLength * sizeof(WCHAR);
    LsaString->MaximumLength = (USHORT)(StringLength + 1) * sizeof(WCHAR);
  }
}

static NTSTATUS OpenPolicy(LPWSTR ServerName, DWORD DesiredAccess, PLSA_HANDLE PolicyHandle)
{
  LSA_OBJECT_ATTRIBUTES ObjectAttributes = {0};
  LSA_UNICODE_STRING ServerString = {0};
  PLSA_UNICODE_STRING Server = 0;

  NTSTATUS result = 0;

  memset( &ObjectAttributes, 0, sizeof(ObjectAttributes) );

  if(ServerName)
  {
    InitLsaString( &ServerString, ServerName);

    Server = &ServerString;
  }

  result = LsaOpenPolicy(Server, &ObjectAttributes, DesiredAccess, PolicyHandle);

  return result;
}

static NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable)
{
  LSA_UNICODE_STRING PrivilegeString = {0};

  NTSTATUS result = 0;

  InitLsaString( &PrivilegeString, PrivilegeName);

  if(bEnable)
    result = LsaAddAccountRights(PolicyHandle, AccountSid, &PrivilegeString, 1);
  else
    result = LsaRemoveAccountRights(PolicyHandle, AccountSid, FALSE, &PrivilegeString, 1);

  return result;
}

static bool EnableLargePageSupport()
{
  bool result = false;

  HANDLE hToken = 0;
  DWORD dwBufferSize = 0;
  PTOKEN_USER pTokenUser = 0;

  LPWSTR strsid = {0};
  NTSTATUS status = {0};
  LSA_HANDLE policyHandle = {0};
  TOKEN_PRIVILEGES tp = {0};

  BOOL privileged = 0;
  DWORD error = 0;

  char* largeBuffer = 0;

  if( !OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken) )
  {
    printf("OpenProcessToken failed. GetLastError returned: %i\n", (uint32_t)GetLastError() );
    goto error;
  }

  if( !GetTokenInformation(hToken, TokenUser, 0, 0, &dwBufferSize) && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
  {
    printf("GetTokenInformation failed. GetLastError returned: %i\n", (uint32_t)GetLastError() );

    CloseHandle(hToken);
    hToken = 0;

    goto error;
  }

  pTokenUser = (PTOKEN_USER)malloc(dwBufferSize);

  if( !GetTokenInformation(hToken, TokenUser, pTokenUser, dwBufferSize, &dwBufferSize) )
  {
    printf("GetTokenInformation failed. GetLastError returned: %i\n", (uint32_t)GetLastError() );

    CloseHandle(hToken);
    hToken = 0;

    goto error;
  }

  ConvertSidToStringSid(pTokenUser->User.Sid, &strsid);
  printf("User SID: %S\n", strsid);

  CloseHandle(hToken);
  hToken = 0;

  status = OpenPolicy(0, POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES, &policyHandle);

  if(status)
    printf("OpenPolicy %i", (int)status);

  status = SetPrivilegeOnAccount(policyHandle, pTokenUser->User.Sid, (wchar_t*)SE_LOCK_MEMORY_NAME, TRUE);

  if(status)
    printf("OpenPSetPrivilegeOnAccountolicy %i", (int)status);

  hToken = 0;

  if( !OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken) )
  {
    printf("OpenProcessToken #2 failed. GetLastError returned: %i\n", (uint32_t)GetLastError() );
    goto error;
  }

  tp.PrivilegeCount = 1;
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if( !LookupPrivilegeValue(0, SE_LOCK_MEMORY_NAME, &tp.Privileges[0].Luid))
  {
    printf("LookupPrivilegeValue failed. GetLastError returned: %i\n", (uint32_t)GetLastError() );
    goto error;
  }

  privileged = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)0, 0);
  error = GetLastError();

  if( !privileged || error != ERROR_SUCCESS)
  {
      printf("AdjustTokenPrivileges failed. GetLastError returned: %i\n", (uint32_t)error);
      goto error;
  }

  CloseHandle(hToken);
  hToken = 0;

  largeBuffer = (char*)VirtualAlloc(0, GetLargePageMinimum(), MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);

  if( !largeBuffer)
    printf("VirtualAlloc failed, error 0x%x", (uint32_t)GetLastError() );

  VirtualFree(largeBuffer, 0, MEM_RELEASE);

  result = true;

error:
  return result;
}

static bool gBlahLargePageSupportEnabled = false;

static uint32_t gLargePageMinimum = 0;
#endif

static uint32_t BlahAlignedOfValue(uint32_t alignmentOf, uint32_t sizeOf)
{
  return (sizeOf % alignmentOf) ? sizeOf + (alignmentOf - sizeOf % alignmentOf) : sizeOf;
}

void BlahEnableAlloc()
{
#if defined(_MSC_VER)
  if(gBlahLargePageSupportEnabled)
    goto error;

  gBlahLargePageSupportEnabled = EnableLargePageSupport();

  if(gBlahLargePageSupportEnabled)
    gLargePageMinimum = (uint32_t)GetLargePageMinimum();

error:
  return;
#endif
}

void* BlahAlloc(uint32_t sizeOf, bool zero)
{
  void* pointer = 0;

  if( !sizeOf)
    goto error;

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

    if(pointer && zero)
      memset(pointer, 0, sizeOf);
  }

error:
  return pointer;
}

void BlahFree(void* pointer, uint32_t sizeOf, bool zero)
{
  if( !pointer || !sizeOf)
    goto error;

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

error:
  return;
}
