#pragma once

#ifdef __cplusplus
#include <cstdint>
#include <cstring>
#else
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#endif // __cplusplus

// GCC complains about the COM interfaces
// not having virtual destructors

// and class conversion for C...DESC helper types
#if defined(__GNUC__) && defined(__cplusplus)
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wclass-conversion"
#endif // __GNUC__ && __cplusplus

struct SDL_Window;

typedef int32_t INT;
typedef uint32_t UINT;

typedef int32_t LONG;
typedef uint32_t ULONG;

typedef int32_t HRESULT;

typedef wchar_t WCHAR;

typedef INT BOOL;
typedef BOOL WINBOOL;

typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef void VOID;
typedef void* LPVOID;
typedef const void* LPCVOID;

// warning: in Windows `typedef __int64 LONG_PTR` on 64 bit systems
// and `typedef long LONG_PTR` on 32 bit systems.
// This was taken from vkd3d, so let's leave it as it was in vkd3d
typedef long LONG_PTR;

typedef size_t SIZE_T;

typedef int8_t  INT8;
typedef uint8_t UINT8;
typedef uint8_t BYTE;

typedef int16_t SHORT;
typedef uint16_t USHORT;

typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;

typedef float FLOAT;

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct GUID {
  uint32_t Data1;
  uint16_t Data2;
  uint16_t Data3;
  uint8_t  Data4[8];
} GUID;
#endif // GUID_DEFINED

typedef GUID UUID;
typedef GUID IID;
#ifdef __cplusplus
#define REFIID const IID&
#define REFGUID const GUID&
#else
#define REFIID const IID*
#define REFGUID const GUID*
#endif // __cplusplus

#ifdef __cplusplus

template <typename T>
constexpr GUID __uuidof_helper();

#define __uuidof(T) __uuidof_helper<T>()
#define __uuidof_var(T) __uuidof_helper<decltype(T)>()

inline bool operator==(const GUID& a, const GUID& b) { return std::memcmp(&a, &b, sizeof(GUID)) == 0; }
inline bool operator!=(const GUID& a, const GUID& b) { return std::memcmp(&a, &b, sizeof(GUID)) != 0; }

#endif // __cplusplus

typedef uint32_t DWORD;
typedef uint16_t WORD;

typedef void* HANDLE;
typedef HANDLE HMONITOR;
typedef HANDLE HDC;
typedef HANDLE HMODULE;
typedef HANDLE HWND;
typedef HANDLE HKEY;
typedef DWORD COLORREF;

typedef char* LPSTR;
typedef const char* LPCSTR;
typedef const wchar_t* LPCWSTR;

typedef struct LUID {
  DWORD LowPart;
  LONG  HighPart;
} LUID;

typedef struct POINT {
  LONG x;
  LONG y;
} POINT;

typedef POINT* LPPOINT;

typedef struct RECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
} RECT;

typedef struct SIZE {
  LONG cx;
  LONG cy;
} SIZE;

typedef union {
  struct {
    DWORD LowPart;
    LONG HighPart;
  };

  struct {
    DWORD LowPart;
    LONG HighPart;
  } u;

  LONGLONG QuadPart;
} LARGE_INTEGER;

typedef struct MEMORYSTATUS {
  DWORD  dwLength;
  SIZE_T dwTotalPhys;
} MEMORYSTATUS;

typedef struct SECURITY_ATTRIBUTES {
  DWORD nLength;
  void* lpSecurityDescriptor;
  BOOL  bInheritHandle;
} SECURITY_ATTRIBUTES;

typedef struct PALETTEENTRY {
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
} PALETTEENTRY;

typedef struct RGNDATAHEADER {
  DWORD dwSize;
  DWORD iType;
  DWORD nCount;
  DWORD nRgnSize;
  RECT  rcBound;
} RGNDATAHEADER;

typedef struct RGNDATA {
  RGNDATAHEADER rdh;
  char          Buffer[1];
} RGNDATA;

// Ignore these.
#define STDMETHODCALLTYPE
#define __stdcall

#define CONST const
#define CONST_VTBL const

#define TRUE 1
#define FALSE 0

#define interface struct
#define MIDL_INTERFACE(x) struct

#ifdef __cplusplus

#define DEFINE_GUID(iid, a, b, c, d, e, f, g, h, i, j, k) \
  constexpr GUID iid = {a,b,c,{d,e,f,g,h,i,j,k}};

#define DECLARE_UUIDOF_HELPER(type, a, b, c, d, e, f, g, h, i, j, k) \
  extern "C++" { template <> constexpr GUID __uuidof_helper<type>() { return GUID{a,b,c,{d,e,f,g,h,i,j,k}}; } } \
  extern "C++" { template <> constexpr GUID __uuidof_helper<type*>() { return __uuidof_helper<type>(); } } \
  extern "C++" { template <> constexpr GUID __uuidof_helper<const type*>() { return __uuidof_helper<type>(); } } \
  extern "C++" { template <> constexpr GUID __uuidof_helper<type&>() { return __uuidof_helper<type>(); } } \
  extern "C++" { template <> constexpr GUID __uuidof_helper<const type&>() { return __uuidof_helper<type>(); } }

#else
#define DEFINE_GUID(iid, a, b, c, d, e, f, g, h, i, j, k) \
  static const GUID iid = {a,b,c,{d,e,f,g,h,i,j,k}};
#define DECLARE_UUIDOF_HELPER(type, a, b, c, d, e, f, g, h, i, j, k)
#endif // __cplusplus

#define __CRT_UUID_DECL(type, a, b, c, d, e, f, g, h, i, j, k) DECLARE_UUIDOF_HELPER(type, a, b, c, d, e, f, g, h, i, j, k)

#define S_OK     0
#define S_FALSE  1

#define E_INVALIDARG  ((HRESULT)0x80070057)
#define E_FAIL        ((HRESULT)0x80004005)
#define E_NOINTERFACE ((HRESULT)0x80004002)
#define E_NOTIMPL     ((HRESULT)0x80004001)
#define E_OUTOFMEMORY ((HRESULT)0x8007000E)
#define E_POINTER     ((HRESULT)0x80004003)

#define DXGI_STATUS_OCCLUDED                     ((HRESULT)0x087a0001)
#define DXGI_STATUS_CLIPPED                      ((HRESULT)0x087a0002)
#define DXGI_STATUS_NO_REDIRECTION               ((HRESULT)0x087a0004)
#define DXGI_STATUS_NO_DESKTOP_ACCESS            ((HRESULT)0x087a0005)
#define DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE ((HRESULT)0x087a0006)
#define DXGI_STATUS_MODE_CHANGED                 ((HRESULT)0x087a0007)
#define DXGI_STATUS_MODE_CHANGE_IN_PROGRESS      ((HRESULT)0x087a0008)
#define DXGI_STATUS_UNOCCLUDED                   ((HRESULT)0x087a0009)
#define DXGI_STATUS_DDA_WAS_STILL_DRAWING        ((HRESULT)0x087a000a)
#define DXGI_STATUS_PRESENT_REQUIRED             ((HRESULT)0x087a002f)

#define DXGI_ERROR_INVALID_CALL                  ((HRESULT)0x887A0001)
#define DXGI_ERROR_NOT_FOUND                     ((HRESULT)0x887A0002)
#define DXGI_ERROR_MORE_DATA                     ((HRESULT)0x887A0003)
#define DXGI_ERROR_UNSUPPORTED                   ((HRESULT)0x887A0004)
#define DXGI_ERROR_DEVICE_REMOVED                ((HRESULT)0x887A0005)
#define DXGI_ERROR_DEVICE_HUNG                   ((HRESULT)0x887A0006)
#define DXGI_ERROR_DEVICE_RESET                  ((HRESULT)0x887A0007)
#define DXGI_ERROR_WAS_STILL_DRAWING             ((HRESULT)0x887A000A)
#define DXGI_ERROR_FRAME_STATISTICS_DISJOINT     ((HRESULT)0x887A000B)
#define DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE  ((HRESULT)0x887A000C)
#define DXGI_ERROR_DRIVER_INTERNAL_ERROR         ((HRESULT)0x887A0020)
#define DXGI_ERROR_NONEXCLUSIVE                  ((HRESULT)0x887A0021)
#define DXGI_ERROR_NOT_CURRENTLY_AVAILABLE       ((HRESULT)0x887A0022)
#define DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED    ((HRESULT)0x887A0023)
#define DXGI_ERROR_REMOTE_OUTOFMEMORY            ((HRESULT)0x887A0024)
#define DXGI_ERROR_ACCESS_LOST                   ((HRESULT)0x887A0026)
#define DXGI_ERROR_WAIT_TIMEOUT                  ((HRESULT)0x887A0027)
#define DXGI_ERROR_SESSION_DISCONNECTED          ((HRESULT)0x887A0028)
#define DXGI_ERROR_RESTRICT_TO_OUTPUT_STALE      ((HRESULT)0x887A0029)
#define DXGI_ERROR_CANNOT_PROTECT_CONTENT        ((HRESULT)0x887A002A)
#define DXGI_ERROR_ACCESS_DENIED                 ((HRESULT)0x887A002B)
#define DXGI_ERROR_NAME_ALREADY_EXISTS           ((HRESULT)0x887A002C)
#define DXGI_ERROR_SDK_COMPONENT_MISSING         ((HRESULT)0x887A002D)

#define WINAPI
#define WINUSERAPI

#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )

#ifdef __cplusplus
#define STDMETHOD(name) virtual HRESULT name
#define STDMETHOD_(type, name) virtual type name
#else
#define STDMETHOD(name) HRESULT (STDMETHODCALLTYPE *name)
#define STDMETHOD_(type, name) type (STDMETHODCALLTYPE *name)
#endif // __cplusplus

#define THIS_
#define THIS

#define __C89_NAMELESSUNIONNAME
#define __C89_NAMELESSUNIONNAME1
#define __C89_NAMELESSUNIONNAME2
#define __C89_NAMELESSUNIONNAME3
#define __C89_NAMELESSUNIONNAME4
#define __C89_NAMELESSUNIONNAME5
#define __C89_NAMELESSUNIONNAME6
#define __C89_NAMELESSUNIONNAME7
#define __C89_NAMELESSUNIONNAME8
#define __C89_NAMELESS
#define DUMMYUNIONNAME
#define DUMMYSTRUCTNAME

#ifdef __cplusplus
#define DECLARE_INTERFACE(x)     struct x
#define DECLARE_INTERFACE_(x, y) struct x : public y
#else
#define DECLARE_INTERFACE(x) \
    typedef interface x { \
        const struct x##Vtbl *lpVtbl; \
    } x; \
    typedef const struct x##Vtbl x##Vtbl; \
    const struct x##Vtbl
#define DECLARE_INTERFACE_(x, y) DECLARE_INTERFACE(x)
#endif // __cplusplus

#define BEGIN_INTERFACE
#define END_INTERFACE

#ifdef __cplusplus
#define PURE = 0
#else
#define PURE
#endif // __cplusplus

#define DECLSPEC_SELECTANY

#define __MSABI_LONG(x) x

#define ENUM_CURRENT_SETTINGS ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS ((DWORD)-2)

#define FAILED(hr) ((HRESULT)(hr) < 0)
#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)

/* compatibility macros */
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))
#define ZeroMemory RtlZeroMemory

#ifndef DEFINE_ENUM_FLAG_OPERATORS
#ifdef __cplusplus
# define DEFINE_ENUM_FLAG_OPERATORS(type) \
extern "C++" \
{ \
    inline type operator &(type x, type y) { return (type)((int)x & (int)y); } \
    inline type operator &=(type &x, type y) { return (type &)((int &)x &= (int)y); } \
    inline type operator ~(type x) { return (type)~(int)x; } \
    inline type operator |(type x, type y) { return (type)((int)x | (int)y); } \
    inline type operator |=(type &x, type y) { return (type &)((int &)x |= (int)y); } \
    inline type operator ^(type x, type y) { return (type)((int)x ^ (int)y); } \
    inline type operator ^=(type &x, type y) { return (type &)((int &)x ^= (int)y); } \
}
#else
# define DEFINE_ENUM_FLAG_OPERATORS(type)
#endif
#endif /* DEFINE_ENUM_FLAG_OPERATORS */


//
////////////////////////////// basetyps.h //////////////////////////////
//

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

//
////////////////////////////// rpcdce.h //////////////////////////////
//

typedef void *RPC_IF_HANDLE;

//
////////////////////////////// sal.h //////////////////////////////
//

/* Input parameters */
#define _In_
#define _In_opt_
#define _In_z_
#define _In_opt_z_
#define _In_reads_(s)
#define _In_reads_opt_(s)
#define _In_reads_bytes_(s)
#define _In_reads_bytes_opt_(s)
#define _In_reads_z_(s)
#define _In_reads_opt_z_(s)
#define _In_reads_or_z_(s)
#define _In_reads_or_z_opt_(s)
#define _In_reads_to_ptr_(p)
#define _In_reads_to_ptr_opt_(p)
#define _In_reads_to_ptr_z_(p)
#define _In_reads_to_ptr_opt_z_(p)

#define _In_count_(s)
#define _In_opt_count_(s)
#define _In_bytecount_(s)
#define _In_opt_bytecount_(s)
#define _In_count_c_(s)
#define _In_opt_count_c_(s)
#define _In_bytecount_c_(s)
#define _In_opt_bytecount_c_(s)
#define _In_z_count_(s)
#define _In_opt_z_count_(s)
#define _In_z_bytecount_(s)
#define _In_opt_z_bytecount_(s)
#define _In_z_count_c_(s)
#define _In_opt_z_count_c_(s)
#define _In_z_bytecount_c_(s)
#define _In_opt_z_bytecount_c_(s)
#define _In_ptrdiff_count_(s)
#define _In_opt_ptrdiff_count_(s)
#define _In_count_x_(s)
#define _In_opt_count_x_(s)
#define _In_bytecount_x_(s)
#define _In_opt_bytecount_x_(s)

/* Output parameters */
#define _Out_
#define _Out_opt_
#define _Out_writes_(s)
#define _Out_writes_opt_(s)
#define _Out_writes_bytes_(s)
#define _Out_writes_bytes_opt_(s)
#define _Out_writes_z_(s)
#define _Out_writes_opt_z_(s)
#define _Out_writes_to_(s, c)
#define _Out_writes_to_opt_(s, c)
#define _Out_writes_all_(s)
#define _Out_writes_all_opt_(s)
#define _Out_writes_bytes_to_(s, c)
#define _Out_writes_bytes_to_opt_(s, c)
#define _Out_writes_bytes_all_(s)
#define _Out_writes_bytes_all_opt_(s)
#define _Out_writes_to_ptr_(p)
#define _Out_writes_to_ptr_opt_(p)
#define _Out_writes_to_ptr_z_(p)
#define _Out_writes_to_ptr_opt_z_(p)

#define _Out_cap_(s)
#define _Out_opt_cap_(s)
#define _Out_bytecap_(s)
#define _Out_opt_bytecap_(s)
#define _Out_cap_c_(s)
#define _Out_opt_cap_c_(s)
#define _Out_bytecap_c_(s)
#define _Out_opt_bytecap_c_(s)
#define _Out_cap_m_(m, s)
#define _Out_opt_cap_m_(m, s)
#define _Out_z_cap_m_(m, s)
#define _Out_opt_z_cap_m_(m, s)
#define _Out_ptrdiff_cap_(s)
#define _Out_opt_ptrdiff_cap_(s)
#define _Out_cap_x_(s)
#define _Out_opt_cap_x_(s)
#define _Out_bytecap_x_(s)
#define _Out_opt_bytecap_x_(s)
#define _Out_z_cap_(s)
#define _Out_opt_z_cap_(s)
#define _Out_z_bytecap_(s)
#define _Out_opt_z_bytecap_(s)
#define _Out_z_cap_c_(s)
#define _Out_opt_z_cap_c_(s)
#define _Out_z_bytecap_c_(s)
#define _Out_opt_z_bytecap_c_(s)
#define _Out_z_cap_x_(s)
#define _Out_opt_z_cap_x_(s)
#define _Out_z_bytecap_x_(s)
#define _Out_opt_z_bytecap_x_(s)
#define _Out_cap_post_count_(a, o)
#define _Out_opt_cap_post_count_(a, o)
#define _Out_bytecap_post_bytecount_(a, o)
#define _Out_opt_bytecap_post_bytecount_(a, o)
#define _Out_z_cap_post_count_(a, o)
#define _Out_opt_z_cap_post_count_(a, o)
#define _Out_z_bytecap_post_bytecount_(a, o)
#define _Out_opt_z_bytecap_post_bytecount_(a, o)
#define _Out_capcount_(c)
#define _Out_opt_capcount_(c)
#define _Out_bytecapcount_(c)
#define _Out_opt_bytecapcount_(c)
#define _Out_capcount_x_(c)
#define _Out_opt_capcount_x_(c)
#define _Out_bytecapcount_x_(c)
#define _Out_opt_bytecapcount_x_(c)
#define _Out_z_capcount_(c)
#define _Out_opt_z_capcount_(c)
#define _Out_z_bytecapcount_(c)
#define _Out_opt_z_bytecapcount_(c)

/* Inout parameters */
#define _Inout_
#define _Inout_opt_
#define _Inout_z_
#define _Inout_opt_z_
#define _Inout_updates_(s)
#define _Inout_updates_opt_(s)
#define _Inout_updates_z_(s)
#define _Inout_updates_opt_z_(s)
#define _Inout_updates_to_(s, c)
#define _Inout_updates_to_opt_(s, c)
#define _Inout_updates_all_(s)
#define _Inout_updates_all_opt_(s)
#define _Inout_updates_bytes_(s)
#define _Inout_updates_bytes_opt_(s)
#define _Inout_updates_bytes_to_(s, c)
#define _Inout_updates_bytes_to_opt_(s, c)
#define _Inout_updates_bytes_all_(s)
#define _Inout_updates_bytes_all_opt_(s)

#define _Inout_count_(s)
#define _Inout_opt_count_(s)
#define _Inout_bytecount_(s)
#define _Inout_opt_bytecount_(s)
#define _Inout_count_c_(s)
#define _Inout_opt_count_c_(s)
#define _Inout_bytecount_c_(s)
#define _Inout_opt_bytecount_c_(s)
#define _Inout_z_count_(s)
#define _Inout_opt_z_count_(s)
#define _Inout_z_bytecount_(s)
#define _Inout_opt_z_bytecount_(s)
#define _Inout_z_count_c_(s)
#define _Inout_opt_z_count_c_(s)
#define _Inout_z_bytecount_c_(s)
#define _Inout_opt_z_bytecount_c_(s)
#define _Inout_ptrdiff_count_(s)
#define _Inout_opt_ptrdiff_count_(s)
#define _Inout_count_x_(s)
#define _Inout_opt_count_x_(s)
#define _Inout_bytecount_x_(s)
#define _Inout_opt_bytecount_x_(s)
#define _Inout_cap_(s)
#define _Inout_opt_cap_(s)
#define _Inout_bytecap_(s)
#define _Inout_opt_bytecap_(s)
#define _Inout_cap_c_(s)
#define _Inout_opt_cap_c_(s)
#define _Inout_bytecap_c_(s)
#define _Inout_opt_bytecap_c_(s)
#define _Inout_cap_x_(s)
#define _Inout_opt_cap_x_(s)
#define _Inout_bytecap_x_(s)
#define _Inout_opt_bytecap_x_(s)
#define _Inout_z_cap_(s)
#define _Inout_opt_z_cap_(s)
#define _Inout_z_bytecap_(s)
#define _Inout_opt_z_bytecap_(s)
#define _Inout_z_cap_c_(s)
#define _Inout_opt_z_cap_c_(s)
#define _Inout_z_bytecap_c_(s)
#define _Inout_opt_z_bytecap_c_(s)
#define _Inout_z_cap_x_(s)
#define _Inout_opt_z_cap_x_(s)
#define _Inout_z_bytecap_x_(s)
#define _Inout_opt_z_bytecap_x_(s)

/* Pointer to pointer parameters */
#define _Outptr_
#define _Outptr_result_maybenull_
#define _Outptr_opt_
#define _Outptr_opt_result_maybenull_
#define _Outptr_result_z_
#define _Outptr_opt_result_z_
#define _Outptr_result_maybenull_z_
#define _Outptr_opt_result_maybenull_z_
#define _Outptr_result_nullonfailure_
#define _Outptr_opt_result_nullonfailure_
#define _COM_Outptr_
#define _COM_Outptr_result_maybenull_
#define _COM_Outptr_opt_
#define _COM_Outptr_opt_result_maybenull_
#define _Outptr_result_buffer_(s)
#define _Outptr_opt_result_buffer_(s)
#define _Outptr_result_buffer_to_(s, c)
#define _Outptr_opt_result_buffer_to_(s, c)
#define _Outptr_result_buffer_all_(s)
#define _Outptr_opt_result_buffer_all_(s)
#define _Outptr_result_buffer_maybenull_(s)
#define _Outptr_opt_result_buffer_maybenull_(s)
#define _Outptr_result_buffer_to_maybenull_(s, c)
#define _Outptr_opt_result_buffer_to_maybenull_(s, c)
#define _Outptr_result_buffer_all_maybenull_(s)
#define _Outptr_opt_result_buffer_all_maybenull_(s)
#define _Outptr_result_bytebuffer_(s)
#define _Outptr_opt_result_bytebuffer_(s)
#define _Outptr_result_bytebuffer_to_(s, c)
#define _Outptr_opt_result_bytebuffer_to_(s, c)
#define _Outptr_result_bytebuffer_all_(s)
#define _Outptr_opt_result_bytebuffer_all_(s)
#define _Outptr_result_bytebuffer_maybenull_(s)
#define _Outptr_opt_result_bytebuffer_maybenull_(s)
#define _Outptr_result_bytebuffer_to_maybenull_(s, c)
#define _Outptr_opt_result_bytebuffer_to_maybenull_(s, c)
#define _Outptr_result_bytebuffer_all_maybenull_(s)
#define _Outptr_opt_result_bytebuffer_all_maybenull_(s)

/* Output reference parameters */
#define _Outref_
#define _Outref_result_maybenull_
#define _Outref_result_buffer_(s)
#define _Outref_result_bytebuffer_(s)
#define _Outref_result_buffer_to_(s, c)
#define _Outref_result_bytebuffer_to_(s, c)
#define _Outref_result_buffer_all_(s)
#define _Outref_result_bytebuffer_all_(s)
#define _Outref_result_buffer_maybenull_(s)
#define _Outref_result_bytebuffer_maybenull_(s)
#define _Outref_result_buffer_to_maybenull_(s, c)
#define _Outref_result_bytebuffer_to_maybenull_(s, c)
#define _Outref_result_buffer_all_maybenull_(s)
#define _Outref_result_bytebuffer_all_maybenull_(s)
#define _Outref_result_nullonfailure_
#define _Result_nullonfailure_
#define _Result_zeroonfailure_

/* Return values */
#define _Ret_z_
#define _Ret_maybenull_z_
#define _Ret_notnull_
#define _Ret_maybenull_
#define _Ret_null_
#define _Ret_valid_
#define _Ret_writes_(s)
#define _Ret_writes_z_(s)
#define _Ret_writes_bytes_(s)
#define _Ret_writes_maybenull_(s)
#define _Ret_writes_maybenull_z_(s)
#define _Ret_writes_bytes_maybenull_(s)
#define _Ret_writes_to_(s, c)
#define _Ret_writes_bytes_to_(s, c)
#define _Ret_writes_to_maybenull_(s, c)
#define _Ret_writes_bytes_to_maybenull_(s, c)
#define _Points_to_data_
#define _Literal_
#define _Notliteral_
#define _Deref_ret_range_(l,u)
#define _Unchanged_(e)

/* Optional pointer parameters */
#define __in_opt
#define __out_opt
#define __inout_opt

/* Other common annotations */
#define _In_range_(low, hi)
#define _Out_range_(low, hi)
#define _Ret_range_(low, hi)
#define _Deref_in_range_(low, hi)
#define _Deref_out_range_(low, hi)
#define _Deref_inout_range_(low, hi)
#define _Struct_size_bytes_(size)
#define _Deref_out_
#define _Deref_out_opt_
#define _Deref_opt_out_
#define _Deref_opt_out_opt_

/* Function annotations */
#define _Called_from_function_class_(name)
#define _Check_return_ __checkReturn
#define _Function_class_(name)
#define _Raises_SEH_exception_
#define _Maybe_raises_SEH_exception_
#define _Must_inspect_result_
#define _Use_decl_annotations_

/* Success/failure annotations */
#define _Always_(anno_list)
#define _On_failure_(anno_list)
#define _Return_type_success_(expr)
#define _Success_(expr)

#define _Reserved_
#define _Const_

/* Buffer properties */
#define _Readable_bytes_(s)
#define _Readable_elements_(s)
#define _Writable_bytes_(s)
#define _Writable_elements_(s)
#define _Null_terminated_
#define _NullNull_terminated_

/* Field properties */
#define _Field_size_(s)
#define _Field_size_full_(s)
#define _Field_size_full_opt_(s)
#define _Field_size_opt_(s)
#define _Field_size_part_(s, c)
#define _Field_size_part_opt_(s, c)
#define _Field_size_bytes_(size)
#define _Field_size_bytes_full_(size)
#define _Field_size_bytes_full_opt_(s)
#define _Field_size_bytes_opt_(s)
#define _Field_size_bytes_part_(s, c)
#define _Field_size_bytes_part_opt_(s, c)
#define _Field_z_
#define _Field_range_(min, max)

/* Structural annotations */
#define _At_(e, a)
#define _At_buffer_(e, i, c, a)
#define _Group_(a)
#define _When_(e, a)

/* printf/scanf annotations */
#define _Printf_format_string_
#define _Scanf_format_string_
#define _Scanf_s_format_string_
#define _Format_string_impl_(kind,where)
#define _Printf_format_string_params_(x)
#define _Scanf_format_string_params_(x)
#define _Scanf_s_format_string_params_(x)

/* Analysis */
#define _Analysis_mode_(x)
#define _Analysis_assume_(expr)
#define _Analysis_assume_nullterminated_(expr)

#define _Post_
#define _Post_equal_to_(expr)
#define _Post_readable_byte_size_(s)
#define _Post_readable_size_(s)
#define _Post_satisfies_(c)
#define _Post_writable_byte_size_(s)
#define _Post_writable_size_(s)

#define _Pre_equal_to_(expr)
#define _Pre_notnull_
#define _Pre_readable_byte_size_(s)
#define _Pre_readable_size_(s)
#define _Pre_satisfies_(c)
#define _Pre_writable_byte_size_(s)
#define _Pre_writable_size_(s)

#define _Strict_type_match_

/* FIXME: __in macro conflicts with argument names in libstdc++. For this reason,
 * we disable it for C++. This should be fixed in libstdc++ so we can uncomment
 * it in fixed version here. */
#if !defined(__cplusplus) || !defined(__GNUC__)
#define __in
#define __out
#endif

#define __bcount(size)
#define __ecount(size)

#define __in_bcount(size)
#define __in_bcount_nz(size)
#define __in_bcount_z(size)
#define __in_ecount(size)
#define __in_ecount_nz(size)
#define __in_ecount_z(size)

#define __out_bcount(size)
#define __out_bcount_nz(size)
#define __out_bcount_z(size)
#define __out_bcount_full(size)
#define __out_bcount_full_z(size)
#define __out_bcount_part(size, length)
#define __out_bcount_part_z(size, length)
#define __out_ecount(size)
#define __out_ecount_nz(size)
#define __out_ecount_z(size)
#define __out_ecount_full(size)
#define __out_ecount_full_z(size)
#define __out_ecount_part(size, length)
#define __out_ecount_part_z(size, length)

#define __inout
#define __inout_bcount(size)
#define __inout_bcount_nz(size)
#define __inout_bcount_z(size)
#define __inout_bcount_full(size)
#define __inout_bcount_part(size, length)
#define __inout_ecount(size)
#define __inout_ecount_nz(size)
#define __inout_ecount_z(size)
#define __inout_ecount_full(size)
#define __inout_ecount_part(size, length)

#define __deref
#define __deref_opt_out
#define __deref_opt_out_bcount(x)
#define __deref_out
#define __deref_out_ecount(size)
#define __deref_out_opt

#define __range(x,y)
