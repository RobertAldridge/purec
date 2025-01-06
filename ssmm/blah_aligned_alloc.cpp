
// blah_aligned_alloc.cpp
// Robert Aldridge

#include <windows.h>
#include <ntsecapi.h>
//#include <ntstatus.h>
#include <Sddl.h>

#include <cstddef> // ptrdiff_t, size_t
#include <cstdint> // uint8_t
#include <cstdio> // printf
#include <cstdlib> // malloc
#include <cstring> // memset

#include <new> // bad_alloc
using std::bad_alloc;
using std::malloc;
using std::memset;
using std::printf;
using std::ptrdiff_t;
using std::size_t;
using std::uint8_t;

#include "blah_aligned_alloc.h"

// alignment is typically sizeof(void*)
// assumes size is already a multiple of alignment
// pass result of malloc_size_padded as size parameter to malloc to allow for post-malloc alignment
static size_t malloc_size_padded(size_t size)
{
  size_t result = size + (sizeof(void*) - 1);

  return result;
}

// alignment is typically sizeof(void*)
// assumes the parameter passed to malloc is sufficiently padded
// ptr is of type uint8_t*
// 'address' is of type ptrdiff_t, assigned to the value (uint8_t*)ptr - (uint8_t*)0
// pass return value of malloc to malloc_return_align (pass stored value not the literal malloc call)
static uint8_t* malloc_return_align(uint8_t* unaligned, ptrdiff_t ptrDiff)
{
  uint8_t* result = 0;

  if(ptrDiff % sizeof(void*) )
  {
    result = unaligned + (sizeof(void*) - ptrDiff % sizeof(void*) );
  }
  else
  {
    result = unaligned;
  }

  return result;
}

static size_t BlahPointerAlignedOfValue(size_t size)
  { return (size % sizeof(void*) ) ? size + (sizeof(void*) - size % sizeof(void*) ) : size; }

static size_t BlahLargePageAlignedOfValue(size_t size)
  { return (size % 2097152) ? size + (2097152 - size % 2097152) : size; }

//void* aligned_alloc(size_t alignment, size_t size)
//
//void free_aligned_sized(void* ptr, size_t alignment, size_t size)

int blah_get_number()
{
  return (int)GetLargePageMinimum();
}

// when you're forced to use a compiler/runtime that claims to conform yet
// doesn't implement aligned_alloc (*cough* microsoft)
//   void* aligned_alloc(size_t alignment, size_t size)
//
// in this case assume alignment is sizeof(void*)
uint8_t* blah_aligned_alloc(size_t size, uint8_t** reference, bool /*clear*/)
{
  uint8_t* aligned = 0;
  uint8_t* unaligned = 0;

//ptrdiff_t ptrDiff = 0;

  if( !size/* || !reference*/)
    goto error;

  // fail if size is not a multiple of alignment
  //if(size % sizeof(void*) )
  //  goto error;

  //size = malloc_size_padded(size);

  try
  {
    //unaligned = (uint8_t*)malloc(size);
    unaligned = (uint8_t*)VirtualAlloc(0, BlahLargePageAlignedOfValue(size), MEM_COMMIT | MEM_RESERVE | MEM_LARGE_PAGES, PAGE_READWRITE);
  }
  catch(bad_alloc& )
  {
    unaligned = 0;
  }

  if( !unaligned)
    goto error;

  if(reference)
    *reference = unaligned;

  aligned = unaligned;

  //ptrDiff = (uint8_t*)unaligned - (uint8_t*)0;

  //aligned = malloc_return_align(unaligned, ptrDiff);

  //if(clear)
  //  memset(aligned, 0, size);

error:
  return aligned;
}


void blah_free_aligned_sized(void* ptr, size_t /*alignment*/, size_t /*size*/)
{
  VirtualFree(ptr, 0, MEM_RELEASE);
}

void InitLsaString(PLSA_UNICODE_STRING LsaString, LPWSTR String)
{
    DWORD StringLength;

    if (String == NULL) {
        LsaString->Buffer = NULL;
        LsaString->Length = 0;
        LsaString->MaximumLength = 0;
        return;
    }

    StringLength = (DWORD)wcslen(String);
    LsaString->Buffer = String;
    LsaString->Length = (USHORT)StringLength * sizeof(WCHAR);
    LsaString->MaximumLength = (USHORT)(StringLength + 1) * sizeof(WCHAR);
}

NTSTATUS OpenPolicy(LPWSTR ServerName, DWORD DesiredAccess, PLSA_HANDLE PolicyHandle)
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    LSA_UNICODE_STRING ServerString;
    PLSA_UNICODE_STRING Server = NULL;

    // 
    // Always initialize the object attributes to all zeroes.
    // 
    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

    if (ServerName != NULL) {
        // 
        // Make a LSA_UNICODE_STRING out of the LPWSTR passed in
        // 
        InitLsaString(&ServerString, ServerName);
        Server = &ServerString;
    }

    // 
    // Attempt to open the policy.
    // 
    return LsaOpenPolicy(
        Server,
        &ObjectAttributes,
        DesiredAccess,
        PolicyHandle
    );
}

NTSTATUS SetPrivilegeOnAccount(LSA_HANDLE PolicyHandle, PSID AccountSid, LPWSTR PrivilegeName, BOOL bEnable)
{
    LSA_UNICODE_STRING PrivilegeString;

    // 
    // Create a LSA_UNICODE_STRING for the privilege name.
    // 
    InitLsaString(&PrivilegeString, PrivilegeName);

    // 
    // grant or revoke the privilege, accordingly
    // 
    if (bEnable) {
        return LsaAddAccountRights(
            PolicyHandle,       // open policy handle
            AccountSid,         // target SID
            &PrivilegeString,   // privileges
            1                   // privilege count
        );
    }
    else {
        return LsaRemoveAccountRights(
            PolicyHandle,       // open policy handle
            AccountSid,         // target SID
            FALSE,              // do not disable all rights
            &PrivilegeString,   // privileges
            1                   // privilege count
        );
    }
}

int EnableLargePageSupport()
{
    HANDLE hToken = NULL;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        printf("OpenProcessToken failed. GetLastError returned: %i\n", (int)GetLastError() );
        return -1;
    }

    DWORD dwBufferSize = 0;

    // Probe the buffer size reqired for PTOKEN_USER structure
    if (!GetTokenInformation(hToken, TokenUser, NULL, 0, &dwBufferSize) &&
        (GetLastError() != ERROR_INSUFFICIENT_BUFFER))
    {
        printf("GetTokenInformation failed. GetLastError returned: %i\n", (int)GetLastError() );

        // Cleanup
        CloseHandle(hToken);
        hToken = NULL;

        return -1;
    }

    PTOKEN_USER pTokenUser = (PTOKEN_USER) malloc(dwBufferSize);

    // Retrieve the token information in a TOKEN_USER structure
    if (!GetTokenInformation(
        hToken,
        TokenUser,
        pTokenUser,
        dwBufferSize,
        &dwBufferSize))
    {
        printf("GetTokenInformation failed. GetLastError returned: %i\n", (int)GetLastError() );

        // Cleanup
        CloseHandle(hToken);
        hToken = NULL;

        return -1;
    }

    // Print SID string
    LPWSTR strsid;
    ConvertSidToStringSid(pTokenUser->User.Sid, &strsid);
    printf("User SID: %S\n", strsid);

    // Cleanup
    CloseHandle(hToken);
    hToken = NULL;

    NTSTATUS status;
    LSA_HANDLE policyHandle;

    if (status = OpenPolicy(NULL, POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES, &policyHandle))
    {
        printf("OpenPolicy %i", (int)status);
    }

    // Add new privelege to the account
    if (status = SetPrivilegeOnAccount(policyHandle, pTokenUser->User.Sid, (wchar_t*)SE_LOCK_MEMORY_NAME, TRUE))
    {
        printf("OpenPSetPrivilegeOnAccountolicy %i", (int)status);
    }

    // Enable this priveledge for the current process
    hToken = NULL;
    TOKEN_PRIVILEGES tp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        printf("OpenProcessToken #2 failed. GetLastError returned: %i\n", (int)GetLastError() );
        return -1;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!LookupPrivilegeValue(NULL, SE_LOCK_MEMORY_NAME, &tp.Privileges[0].Luid))
    {
        printf("LookupPrivilegeValue failed. GetLastError returned: %i\n", (int)GetLastError() );
        return -1;
    }

    BOOL result = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    DWORD error = GetLastError();

    if (!result || (error != ERROR_SUCCESS))
    {
        printf("AdjustTokenPrivileges failed. GetLastError returned: %i\n", (int)error);
        return -1;
    }

    // Cleanup
    CloseHandle(hToken);
    hToken = NULL;

    SIZE_T pageSize = GetLargePageMinimum();

    // Finally allocate the memory
    char *largeBuffer = (char*)VirtualAlloc(0, pageSize * 1, MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES, PAGE_READWRITE);
    //char* largeBuffer = (char*)blah_aligned_alloc(1, 0, false);

    if( !largeBuffer)
    {
        printf("VirtualAlloc failed, error 0x%x", (int)GetLastError() );
    }

    VirtualFree(largeBuffer, 0, MEM_RELEASE);
}
