
/*
 * 
 * (c) Copyright RIFT.io, 2013-2016, All Rights Reserved
 *
 */


/**
 * @file rwlib.h
 * @author Anil Gunturu (anil.gunturu@riftio.com)
 * @author Matt Harper (matt.harper@riftio.com)
 * @date 07/20/2013
 * @brief Top level include for RIFT utilities library. 
 * @details RIFT top-level include file that is used by everything RIFT
 */
#ifndef __RWLIB_H__
#define __RWLIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <glib.h>
#include <rw_object.h>
#include <pthread.h>

#include <glib.h>
#include <libpeas/peas.h>
#include "rwtypes.h"

__BEGIN_DECLS

/*
 * NOTE: rw_status_t is defined in autogenerated rwtypes.h
 */

#ifndef likely
#define likely(x)  __builtin_expect((x),1)
#endif /* likely */

/**
 * Provide the compiler a static hint that a branch is likely to be taken.
 *
 * Example:
 *
 *   if (RW_LIKELY(val != 0)) { fn_typically_called();}
 *
 */
#define RW_LIKELY(_bv) likely(_bv)

#ifndef unlikely
#define unlikely(x)  __builtin_expect((x),0)
#endif /* unlikely */
/**
 * Provide the compiler a static hint that a branch is unlikely to be taken.
 *
 * Example:
 *   if (RW_UNLIKELY(val != 0)) { fn_typically_NOT_called();} *
 *
 */
#define RW_UNLIKELY(_bv) unlikely(_bv)

#define RW_MAX_LOCATION_FILENAME_SIZE 16
#define RW_MAX_CODE_LOCATIONS 4

/**
 * Holds the file name and line number of the macro.
 * The macros would typically be trace, log or assert 
 * macros. 
 *
 * This structure is used for slectively enabling/disabling
 * specific macros. The user can disable all the
 * traces, and selectively enable some traces.
 * Note: The user can specify upto RW_MAX_CODE_LOCATIONS.
 * For performance reasons the value of RW_MAX_CODE_LOCATIONS
 * should be kept small.
 */
typedef struct _rw_code_location {
  uint32_t lineno; /*!< line number of the macro */
  char filename[RW_MAX_LOCATION_FILENAME_SIZE]; /*!< name of the file invoking the macro */
} rw_code_location_t;


/**
 * Contains information about various locations configured
 * for special handling.
 */
typedef struct _rw_code_location_info {
  uint32_t location_hash; /*!< aids at runtime to quickly check if currrent
                            location is configured for special handling */
  uint32_t location_count; /*!< Number of locations configured for special
                             handling */
  rw_code_location_t location[RW_MAX_CODE_LOCATIONS]; /*!< array of locations configured */
} rw_code_location_info_t;

/**
 * This global variable tracks if any of the RW_ASSERT macros are disabled
 */
extern rw_code_location_info_t g_assert_code_info;

/**
 * This function updates the rw_location_info_t with new location
 *
 *  @param[in] info     - pointer to the code location info
 *  @param[in] location - pointer to the new code location
 */
rw_status_t rw_set_code_location(rw_code_location_info_t *info,
                                   rw_code_location_t *location);

/**
 * This function gets the code location cnt 
 *
 *  @param[in] info     - pointer to the code location info
 */
int rw_get_code_location_count(rw_code_location_info_t *info);

/**
 * This function unsets the code location that we set by
 * rw_set_code_location
 *
 *  @param[in] info     - pointer to the code location info
 *  @param[in] location - pointer to the new code location
 */
rw_status_t rw_unset_code_location(rw_code_location_info_t *info,
                                     rw_code_location_t *location);
/**
 * rw_set_assert_location
 *
 *  @param[in] location - pointer to the new code location
 */
rw_status_t rw_set_assert_ignore_location(rw_code_location_t *location);

/**
 * rw_unset_assert_location
 *
 *  @param[in] location - pointer to the new code location
 */
rw_status_t rw_unset_assert_ignore_location(rw_code_location_t *location);

/**
 * rw_get_trace_location_count
 */
int rw_get_assert_ignore_location_count(void);

/**
 * rw_init_assert_ignore_location_info
 */
rw_status_t rw_init_assert_ignore_location_info(void);

/**
 * Quotes a string using the preprocessor
 *
 * @param token Name to "stringize"
 *
 * Example Usage:
 * @code
 * quoted_string = RW_QUOTE(foo_t)
 * @endcode
 */

#define RW_QUOTE(name) #name

/**
 * Hashes a string using the preprocessor
 * Hash is optimized away by gcc or g++with -O, -O1 or -Os
 *
 * @param token Name to hash
 *
 * Example Usage:
 * @code
 * quoted_string = RW_HASH_STRING_CONST(foo_t)
 * @endcode
 */

//#define RW_H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define RW_H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<(sizeof(s)-1)?sizeof(s)-2-(i):(sizeof(s)-1)])
#define RW_H4(s,i,x)   RW_H1(s,i,RW_H1(s,i+1,RW_H1(s,i+2,RW_H1(s,i+3,x))))
#define RW_H16(s,i,x)  RW_H4(s,i,RW_H4(s,i+4,RW_H4(s,i+8,RW_H4(s,i+12,x))))
#define RW_H64(s,i,x)  RW_H16(s,i,RW_H16(s,i+16,RW_H16(s,i+32,RW_H16(s,i+48,x))))
#define RW_H256(s,i,x) RW_H64(s,i,RW_H64(s,i+64,RW_H64(s,i+128,RW_H64(s,i+192,x))))

#define RW_HASH_STRING_CONST(s) ((uint32_t)(RW_H256(s,0,0)^(RW_H256(s,0,0)>>16)))

// CLANG blows up on this macro so redo it for now until we can #ifdef around CLANG
//#undef RW_HASH_STRING_CONST
//#define RW_HASH_STRING_CONST(s) (1)

#define RW_HASH_TYPE(type) RW_HASH_STRING_CONST(RW_QUOTE(type))

#define RW_MAGIC 0xFFFFFFFFFFFFFFC5 //largest 64 bit prime

typedef uint64_t rw_magic_pad_t;

#define RW_RESOURCE_TRACK_MAX_CALLERS 50

struct rw_mem_res_track_s {
  void *addr;
  void *parent;
  unsigned int size;
  rw_object_type_t obj_type;
};
typedef struct rw_mem_res_track_s rw_mem_res_track_t;

//#define _THREAD_ __thread
#define _RW_THREAD_ 

typedef void *RW_RESOURCE_TRACK_HANDLE;
extern _RW_THREAD_ RW_RESOURCE_TRACK_HANDLE g_rwresource_track_handle;

#define RW_MAGIC_PAD ((sizeof(rw_magic_pad_t)+sizeof(rw_mem_res_track_t)+15)/16)*16 //padding alligned to 16bytes

#define RW_RESOURCE_TRACK 
#ifdef RW_RESOURCE_TRACK
static inline void *RW_MALLOC_MAGIC(gsize size, 
                                    rw_magic_pad_t hash, 
                                    const char* type, 
                                    rw_object_type_t obj_type, 
                                    const char* loc);

static inline void *RW_MALLOC0_MAGIC(gsize size, 
                                     rw_magic_pad_t hash, 
                                     const char* type, 
                                     rw_object_type_t obj_type, 
                                     const char* loc);

static inline void *RW_REALLOC_MAGIC(void *ptr, 
                                     gsize size, 
                                     rw_magic_pad_t hash, 
                                     const char* type, 
                                     rw_object_type_t obj_type, 
                                     const char* loc);

#define RW_MALLOC_TYPE(size, type)                  \
  ((type *) RW_MALLOC_MAGIC(size,                   \
                            RW_HASH_TYPE(type),     \
                            RW_QUOTE(type),         \
                            RW_RAW_OBJECT,          \
                            G_STRLOC))

#define RW_MALLOC0_TYPE(size, type)                 \
  ((type *) RW_MALLOC0_MAGIC(size,                  \
                             RW_HASH_TYPE(type),    \
                             RW_QUOTE(type),        \
                             RW_RAW_OBJECT,         \
                             G_STRLOC))

#define RW_REALLOC_TYPE(ptr, size, type)            \
  ((type *) RW_REALLOC_MAGIC(ptr,                   \
                             size,                  \
                             RW_HASH_TYPE(type),    \
                             RW_QUOTE(type),        \
                             RW_RAW_OBJECT,         \
                             G_STRLOC))

#else //RW_RESOURCE_TRACK

#define RW_MALLOC_TYPE(size, type)                  \
  ((type *) rw_malloc_magic(size,                   \
                            RW_HASH_TYPE(type),     \
                            RW_RAW_OBJECT))

#define RW_MALLOC0_TYPE(size, type)                 \
  ((type *) rw_malloc0_magic(size,                  \
                             RW_HASH_TYPE(type),    \
                             RW_RAW_OBJECT))

#define RW_REALLOC_TYPE(ptr, size, type)            \
  ((type *) rw_realloc_magic(ptr,                   \
                             size,                  \
                             RW_HASH_TYPE(type),    \
                             RW_RAW_OBJECT))

#endif //RW_RESOURCE_TRACK

#define RW_FREE_TYPE(addr, type) rw_free_magic(addr, RW_HASH_TYPE(type))

#define _RW_ASSERT_TYPE_INT(addr, hash, addr_s, type_s)                  \
{                                                                             \
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);                             \
  rw_magic_pad_t *head = (rw_magic_pad_t *) ((char *) addr - RW_MAGIC_PAD);   \
  if(*((rw_magic_pad_t *) head) != (hash ^ (rw_magic_pad_t) head)) {          \
    uint32_t _suppressed;                                                     \
    char msg[999];                                                            \
    _RW_ASSERT_SUPPRESSED_((*((rw_magic_pad_t *) head) ==                     \
			    (hash ^ (rw_magic_pad_t) head)), _suppressed);    \
    if (!_suppressed) {                                                       \
      sprintf(msg, "Bad Heap Magic for value %s %s=%p", type_s, addr_s, addr);\
      g_assertion_message_expr (G_LOG_DOMAIN, __FILE__, __LINE__, G_STRFUNC,  \
			       	msg);                                         \
    }                                                                         \
  }                                                                           \
}

#define RW_ASSERT_TYPE(addr, type)                  \
  RW_ASSERT(addr);                                  \
  _RW_ASSERT_TYPE_INT(addr, RW_HASH_TYPE(type), RW_QUOTE(addr), RW_QUOTE(type))

/**
 * Allocates an array of __count__ elements of __type__.
 * An  array of pointers of size __count__ is alloated and each array element is pointed to an 
 * allocated  structure of type __type__. 
 *
 * @param __type__  The type of each indvidual element in the array
 * @param __count__ The number of elements in the array
 *
 * @return  The alloced array of size __count__ as a pointer to pointer to __type__
 *           
 * Example Usage:
 * @code
 * typedef struct example_s {
 *   int index;
 *   // ...
 * }  example_t;
 *  
 * example_t **array = RW_MALLOC_ARRAY_TYPE(example_t, 10);
 * int i;
 * for (i = 10; i < 10; i++) {
 *   array[i].index = i;
 * }
 * @endcode
 */
#define RW_MALLOC_ARRAY_TYPE(__type__, __count__) \
(G_GNUC_EXTENSION ({                                 \
   int __array_index; \
  __type__ ** __type_array = RW_MALLOC_TYPE(((__count__) * sizeof(__type__ *)), __type__*);  \
  for (__array_index = 0;  __array_index < (__count__); __array_index++) { \
    __type_array[__array_index]  = RW_MALLOC_TYPE(sizeof(__type__), __type__);\
  } \
  __type_array; \
 }))


/**
 * Allocates an array of __count__ elements of __type__ and initializes them to zero.
 * An  array of pointers of size __count__ is alloated and each array element is pointed to an 
 * allocated  structure of type __type__. Returns  pointer to pointer to __type__
 *
 * @param __type__  The type of each indvidual element in the array
 * @param __count__ The number of elements in the array
 *
 * @return  The alloced array of size __count__ as a pointer to pointer to __type__
 *           
 * Example Usage:
 * @code
 * typedef struct example_s {
 *   int index;
 *   // ...
 * }  example_t;
 *  
 * example_t **array = RW_MALLOC_ARRAY_TYPE(example_t, 10);
 * int i;
 * for (i = 10; i < 10; i++) {
 *   array[i].index = i;
 * }
 * @endcode
 */

#define RW_MALLOC0_ARRAY_TYPE(__type__, __count__) \
(G_GNUC_EXTENSION ({ \
  int __array_index; \
  __type__ ** __type_array = RW_MALLOC_TYPE(((sizeof(__type__*)) * (__count__)), __type__*); \
  for (__array_index = 0;  __array_index < (__count__); __array_index++) { \
    __type_array[__array_index]  = RW_MALLOC0_TYPE(sizeof(__type__), __type__);\
  } \
  __type_array; \
 }))

/**
 * Frees an array of __count__ elements  allocated through RW_MALLOC_ARRAY_TYPE/RW_MALLOC0_ARRAY_TYPE
 *
 * @param __addr__  The begining of the array
 * @param __type__  The type of each indvidual element in the array
 * @param __count__ The number of elements in the array
 *
 * @return  The alloced array of size __count__ as a pointer to pointer to __type__
 *           
 * Example Usage:
 * @code
 * typedef struct example_s {
 *   int index;
 *   // ...
 * }  example_t;
 *  
 * example_t **array = RW_MALLOC0_ARRAY_TYPE(example_t, 10);
 * int i;
 * for (i = 10; i < 10; i++) {
 *   array[i].index = i;
 * }
 * // ... Do stuff with array
   RW_FREE_ARRAY_TYPE(array, example_t, 10);
 * @endcode
 */
#define RW_FREE_ARRAY_TYPE(__addr__, __type__, __count__) \
({ \
  int __array_index; \
  for (__array_index = 0; __array_index < (__count__); __array_index++) { \
    rw_free_magic((__addr__)[__array_index], RW_HASH_TYPE(__type__)); \
    (__addr__)[__array_index] = NULL; \
  } \
  rw_free_magic((__addr__), RW_HASH_TYPE(__type__*)); \
})

/**
 * Allocates n_bytes of memory. Returns NULL if n_bytes is zero.
 * Asserts if the memory allocation fails.
 *
 * @param n_bytes Number of bytes to be allocated.
 *
 * Example Usage:
 * @code
 * foo = (foo_t *)RW_MALLOC(sizeof(foo_t)
 * @endcode
 */
#define RW_MALLOC         g_malloc

/**
 * Allocates n_bytes of memory and zeroes the memory.
 * Returns NULL if n_bytes is zero.
 * Asserts if the memory allocation fails.
 *
 * @param n_bytes Number of bytes to be allocated.
 *
 * Example Usage:
 * @code
 * foo = (foo_t *)RW_MALLOC0(sizeof(foo_t)
 * @endcode
 */
#define RW_MALLOC0        g_malloc0

/**
 * Reallocates n_bytes of memory. 
 * Asserts if the memory allocation fails.
 *
 * @param mem Memory to be freed.
 * @param n_bytes Number of bytes to be allocated.
 *
 * Example Usage:
 * @code
 * foo = (foo_t *)RW_REALLOC(mem, sizeof(foo_t)
 * @endcode
 */
#define RW_REALLOC       g_realloc

/**
 * Frees the memory location
 *
 * @param mem Memory to be freed.
 *
 * Example Usage:
 * @code
 * RW_FREE(mem)
 * @endcode
 */
#define RW_FREE         g_free

/**
 * Creates duplicate of the string, its the responsibility of the caller
 * to free the memory.
 *
 * @param str String to be duplicated.
 *
 * Example Usage:
 * @code
 * RW_STRDUP(str)
 * @endcode
 */
#define RW_STRDUP       g_strdup

/**
 * Creates duplicate of the string, its the responsibility of the caller
 * to free the memory.
 *
 * @param format format string
 *
 * Example Usage:
 * @code
 * RW_STRDUP_PRINTF("Test %s\n", str)
 * @endcode
 */
#define RW_STRDUP_PRINTF g_strdup_printf

/**
 * Zeroes a variable
 *
 * @param[in] _v Pointer to the variable to memset()
 *
 * Example Usage:
 * @code
 * RW_ZERO_VARIABLE(foo)
 * @endcode
 */
#define RW_ZERO_VARIABLE(_v) memset((void *)(_v), 0, sizeof(*(_v)))

#define RW_MAGIC 0xFFFFFFFFFFFFFFC5 //largest 64 bit prime

/**
 * Allocates the memory with a padding for magic at the head
 */
static inline void *rw_magic_malloc(gsize size)
{
  void *_ret = RW_MALLOC0(size + RW_MAGIC_PAD);
  *(uint64_t *)_ret = (RW_MAGIC ^ (uint64_t)_ret);
  ((rw_mem_res_track_t*)((char*)_ret + sizeof(rw_magic_pad_t)))->obj_type = RW_RAW_OBJECT;
  return (void *)((char *)_ret + RW_MAGIC_PAD);
}

#define RW_MAGIC_MALLOC rw_magic_malloc

static inline void
rw_free_magic(void *addr, rw_magic_pad_t hash);

/**
 * Free the memory with rift magic
 */
static inline void rw_magic_free(void *addr)
{
  rw_free_magic(addr, 0);
}

#define RW_MAGIC_FREE rw_magic_free

/**
 * Check the rift magic
 */
static inline rw_status_t rw_magic_check(void *addr)
{
  void *head = ((char *)addr - RW_MAGIC_PAD);
  if ((RW_MAGIC ^ (uint64_t)head) == *(uint64_t *)head) {
    return RW_STATUS_SUCCESS;
  } else {
    return RW_STATUS_FAILURE;
  }
}

#define RW_MAGIC_CHECK rw_magic_check

/**
 * Function to get backtrace using linunwind library
 */
void rw_show_unw_backtrace(FILE *out);
void rw_show_gdb_trace(void);

int rw_btrace_backtrace(void **array, int depth);
char* rw_unw_get_proc_name(void *addr);
char* rw_btrace_get_proc_name(void *addr);
/**
 * Macro to generate stacktrace.
 *
 * Example Usage:
 * @code
 * RW_SHOW_BACKTRACE()
 * @endcode
 */
#define RW_SHOW_BACKTRACE rw_show_unw_backtrace(stdout)

/**
 * Macro to catch compile time issues
 * @param[in] expr - expression
 *
 * Example Usage:
 * @code
 * RW_STATIC_ASSERT((sizeof(struct foo) == 4)) 
 * @endcode
 * If the sizeof foo is not 4, the above macro will generate 
 * a message like the following <BR>
 * * error: size of array '__RW_STATIC_ASSERT_FAILED_<linenumber>' negative
 */
#ifdef __cplusplus
#define RW_STATIC_ASSERT(expr)  static_assert((expr), #expr)
#else
#define RW_STATIC_ASSERT(expr)  _Static_assert((expr), #expr)
#endif


/**
 * Macro to catch compile time issues
 * @param[in] expr - expression
 * @param[in] msg - a message that will appear in the error.
 *       must be an identifer fragment, will be token-pasted.
 *
 * Example Usage:
 * @code
 * RW_STATIC_ASSERT_MSG((sizeof(struct foo) == 4), WRONG_SIZE) 
 * @endcode
 * If the sizeof foo is not 4, the above macro will generate 
 * a message like the following <BR>
 * * error: size of array '__RW_STATIC_ASSERT_FAILED_<linenumber>_WRONG_SIZE' negative
 */
#ifdef __cplusplus
#define RW_STATIC_ASSERT_MSG(expr,msg)  static_assert((expr), msg)
#else
#define RW_STATIC_ASSERT_MSG(expr,msg)  _Static_assert((expr), #expr)
#endif


#define _RW_ASSERT_SUPPRESSED_(_expr, _suppressed)                        \
{                                                                         \
    _suppressed = 1;                                                      \
    if (g_assert_code_info.location_hash & (1 << (__LINE__ & 0x1F))) {    \
      /* This assert may have been supressed */                           \
      uint32_t _i;                                                        \
      for (_i = 0; _i < g_assert_code_info.location_count; ++_i) {        \
        rw_code_location_t *_loc = &g_assert_code_info.location[_i];      \
        if ((_loc->lineno == __LINE__) &&                                 \
            (strstr(__FILE__, _loc->filename))) {                         \
          break;                                                          \
        }                                                                 \
      }                                                                   \
                                                                          \
      if (_i == g_assert_code_info.location_count) {                      \
        /* no match found, so assert */                                   \
        _suppressed = 0;                                                  \
      }                                                                   \
    } else {                                                              \
      _suppressed = 0;                                                    \
    }                                                                     \
}

/**
 * Macro to terminate the application if the expression fails.
 * The assertion may have been selectively disabled, this should
 * should check for that.
 *
 * @param[in] expr - expression to test
 *
 * Example usage:
 * @code
 * RW_ASSERT((sizeof(foo) == 4))
 * @endcode
 */
#define RW_ASSERT(_expr)                                                  \
{                                                                         \
  if (!(_expr)) {                                                         \
    uint32_t _suppressed;                                                 \
    _RW_ASSERT_SUPPRESSED_(_expr, _suppressed);                           \
    if(!_suppressed)                                                      \
    g_assert(_expr);                                                      \
  }                                                                       \
}

/**
 * Macro to terminate the application if the expression fails.
 * This macro becomes a no-op if RIFT_NDEBUG is defined.
 * @param[in] expr - expression
 *
 * Example usage:
 * @code
 * RW_ASSERT((sizeof(foo) == 4))
 * @endcode
 */      
#ifdef RIFT_NDEBUG
#define RW_DEBUG_ASSERT 
#else
#define RW_DEBUG_ASSERT RW_ASSERT
#endif

/**
 * Macro to enable the operation only  in debug builds.
 * This macro becomes a no-op if RIFT_NDEBUG is defined.
 * @param[in] operation - c statement active only for debug build 
 *
 * Example usage:
 * @code
 * RW_DEBUG_ONLY(debug_stats++);
 * @endcode
 */      
#ifdef RIFT_NDEBUG
#define RW_DEBUG_ONLY(x)
#else
#define RW_DEBUG_ONLY(x) x 
#endif

/**
 * Macro to terminate the application if it is ever reached
 *
 * Example usage:
 * @code
 * RW_ASSERT_NOT_REACHED()
 * @endcode
 */
#define RW_ASSERT_NOT_REACHED g_assert_not_reached

/**
 * Macro to log a message and abort
 * The assertion may have been selectively disabled, this should
 *
 * should check for that.
 * @param[in] expr - boolean expression
 * @param[in] format - format strings
 * @param[in] args ... - argument list
 *
 * Example usage:
 * @code
 * RW_ASSERT_MESSAGE((sizeof(foo) == 4), "Fatal error: %s\n", msg)
 * @endcode
 */
#define RW_ASSERT_MESSAGE(_expr, _fmt, _args...)                          \
{                                                                         \
  if (!(_expr)) {                                                         \
    if (g_assert_code_info.location_hash & (1 << (__LINE__ & 0x1F))) {    \
      /* This assert may have been supressed */                           \
      uint32_t _i;                                                        \
      for (_i = 0; _i < g_assert_code_info.location_count; ++_i) {        \
        rw_code_location_t *_loc = &g_assert_code_info.location[_i];      \
        if ((_loc->lineno == __LINE__) &&                                 \
            (strstr(__FILE__, _loc->filename))) {                         \
          break;                                                          \
        }                                                                 \
      }                                                                   \
                                                                          \
      if (_i == g_assert_code_info.location_count) {                      \
        /* no match found, so assert */                                   \
        g_error(_fmt, ##_args);                                           \
      }                                                                   \
    } else {                                                              \
      g_error(_fmt, ##_args);                                             \
    }                                                                     \
  }                                                                       \
}

#define RW_CRASH() RW_ASSERT(0)

#define RW_CRASH_MESSAGE(_fmt, _args...)                                  \
  RW_ASSERT_MESSAGE(0, _fmt, ##_args)

static inline void *rw_malloc0_magic(gsize size, 
                                     rw_magic_pad_t hash, 
                                     rw_object_type_t obj_type)
{
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  char *addr, *memblock;
  memblock = (char *) RW_MALLOC0(size + RW_MAGIC_PAD);
  *((uint64_t *) memblock) = (hash ^ (rw_magic_pad_t) memblock);
  ((rw_mem_res_track_t*)(memblock + sizeof(rw_magic_pad_t)))->obj_type = obj_type;
  addr = memblock + RW_MAGIC_PAD;
  return (void *) addr;
}

static inline void *rw_malloc_magic(gsize size, 
                                    rw_magic_pad_t hash, 
                                    rw_object_type_t obj_type)
{ 
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  char *addr, *memblock;
  memblock = (char *) RW_MALLOC(size + RW_MAGIC_PAD);
  memset(memblock, '\0', RW_MAGIC_PAD);
  *((uint64_t *) memblock) = (hash ^ (rw_magic_pad_t) memblock);
  ((rw_mem_res_track_t*)(memblock + sizeof(rw_magic_pad_t)))->obj_type = obj_type;
  addr = memblock + RW_MAGIC_PAD;
  return (void *) addr;
}

static inline void *rw_realloc_magic(void *addr_in, 
                                     gsize size, 
                                     rw_magic_pad_t hash)
{ 
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  char *addr, *memblock, *memblock_in = NULL;

  if (addr_in != NULL) {
    memblock_in = ((char *) addr_in - RW_MAGIC_PAD);
    RW_ASSERT(*((rw_magic_pad_t *) memblock_in) == 
              (hash ^ (rw_magic_pad_t) memblock_in));
  }

  memblock = (char *) RW_REALLOC(memblock_in, size + RW_MAGIC_PAD);

  *((uint64_t *) memblock) = (hash ^ (rw_magic_pad_t) memblock);
  addr = memblock + RW_MAGIC_PAD;

  return (void *) addr;
}


static inline void
rw_free_magic(void *addr, rw_magic_pad_t hash)
{
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  char *memblock;
  memblock = ((char *) addr - RW_MAGIC_PAD);
  if (hash) {
    RW_ASSERT(*((rw_magic_pad_t *) memblock) == 
              (hash ^ (rw_magic_pad_t) memblock));
  }
  RW_FREE(memblock);
}

#define MAX_ITERATIONS 4000000

/**
 * Seconds elapsed between start and end timers
 */
static inline double seconds_elapsed(struct timeval *start_tv,
                                     struct timeval *end_tv)
{
  struct timeval duration_tv;
  double seconds;
  
  timersub(end_tv, start_tv, &duration_tv);
  seconds = duration_tv.tv_sec + duration_tv.tv_usec / 1000000.0;

  return seconds;
}

/**
 * Macro to benchmark a function
 * This macro computes the average time this function takes
 * to execute over a large number of iterations
 * @param[in] _f - function pointer
 * @param[in] _args - argument list
 */
#define benchmark(_f, _args...)                                         \
  {                                                                     \
    struct timeval _start_tv;                                           \
    struct timeval _end_tv;                                             \
    double _seconds;                                                    \
    int _i;                                                             \
                                                                        \
    gettimeofday(&_start_tv, NULL);                                     \
                                                                        \
    for (_i = 0; _i < MAX_ITERATIONS; _i++) {                           \
      _f(_args);                                                        \
                                                                        \
      if (_i % 10000 == 0) {                                            \
        gettimeofday(&_end_tv, NULL);                                   \
        _seconds = seconds_elapsed(&_start_tv, &_end_tv);               \
        if (_seconds > 1.0) { break; }                                  \
      }                                                                 \
    }                                                                   \
                                                                        \
    gettimeofday(&_end_tv, NULL);                                       \
    _seconds = seconds_elapsed(&_start_tv, &_end_tv);                   \
                                                                        \
    printf("'%s' performance:\n", #_f);                                 \
    printf("function calls  = %d\n", _i);                               \
    printf("Seconds elapsed = %lf\n", _seconds);                        \
    printf("Rate            = %.2lf kTPS\n", _i/_seconds/1000);         \
  }



/**
 * Substract two timers of type struct timeval
 *
 * @param[in] a End timer
 * @param[in] b Start timer
 *
 * @param[out] result Result
 */
#if !defined(ctimersub)
#define ctimersub(a, b, result)                      \
  do {                                               \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;    \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec; \
    if ((result)->tv_usec < 0) {                     \
      --(result)->tv_sec;                            \
      (result)->tv_usec += 1000000;                  \
    }                                                \
  } while (0)
#endif /* !defined(ctimersub) */


/*
 * Jenkin's hash - lookup3.c plonked into rwlib
 */
uint64_t rw_hashlittle64(const void *key, size_t length);
void rw_hashlittle2( 
  const void *key,       /* the key to hash */
  size_t      length,    /* length of the key */
  uint32_t   *pc,        /* IN: primary initval, OUT: primary hash */
  uint32_t   *pb);       /* IN: secondary initval, OUT: secondary hash */
uint32_t rw_hashlittle( const void *key, size_t length, uint32_t initval);
int rw_lookup3_test();


/**
 * Macro to avoid compile warnings when a variable is not used
 *
 * @param[in] _x_ variable
 */
#if !defined(UNUSED)
#define UNUSED(_x_)  ((void)(_x_))
#endif /* !defined(UNUSED) */

#ifndef bool_t
#define bool_t int
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif


#include <rw_resource_track.h>

#ifdef RW_RESOURCE_TRACK
static inline void *RW_MALLOC_MAGIC(gsize size, 
                                    rw_magic_pad_t hash, 
                                    const char* type, 
                                    rw_object_type_t obj_type, 
                                    const char* loc)
{
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  void *addr = rw_malloc_magic(size, hash, obj_type);
  if (g_rwresource_track_handle) {
    RW_RESOURCE_TRACK_ATTACH_CHILD_W_LOC(g_rwresource_track_handle, 
                                         addr, size, type, loc);
  }
  return addr;
}

static inline void *RW_MALLOC0_MAGIC(gsize size, 
                                     rw_magic_pad_t hash, 
                                     const char* type, 
                                     rw_object_type_t obj_type, 
                                     const char* loc)
{
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  void *addr = rw_malloc0_magic(size, hash, obj_type);
  if (g_rwresource_track_handle) {
    RW_RESOURCE_TRACK_ATTACH_CHILD_W_LOC(g_rwresource_track_handle, 
                                         addr, size, type, loc);
  }
  return addr;
}

static inline void *RW_REALLOC_MAGIC(void *ptr, 
                                     gsize size, 
                                     rw_magic_pad_t hash, 
                                     const char* type, 
                                     rw_object_type_t obj_type, 
                                     const char* loc)
{
#if 0
  RW_STATIC_ASSERT(RW_MAGIC_PAD == RW_MAGIC_PAD);
  void *addr = rw_realloc_magic(ptr, size, hash, obj_type);
  if (g_rwresource_track_handle) {
    RW_RESOURCE_TRACK_ATTACH_CHILD_W_LOC(g_rwresource_track_handle, 
                                         addr, size, type, loc);
  }
  return addr;
#else
  UNUSED(ptr);
  UNUSED(size);
  UNUSED(hash);
  UNUSED(type);
  UNUSED(obj_type);
  UNUSED(loc);

  RW_CRASH();
#endif
}
#endif

/**
 * This function creates the directory path. If the
 * parent nodes don't exist, this function recursively creates the
 * parent nodes (similar to 'mkdir -p')
 *
 * @param[in] path The directory path.
 * @param[in] mode The directory permissions.
 */
rw_status_t rw_mkpath(const char *path, mode_t mode);

/**
 * This function deletes all files under the directory dir_path. 
 * Does not delete directories and subdirectories.
 *
 * @param[in] dir_path The directory path.
 */
rw_status_t rw_delfiles_in_dir(const char *dir_path);

/**
 * This function forks the current process, and replaces the
 * child process with user specified process.
 *
 * @param[in] filename Pointer to the file being executed.
 * @param[in] argv List of null terminated argument list.
 * @param[in] set_pid Set the process group id of that child
 * to the process group id of the parent.
 * @param[out] child_pid The process id of the child process.
 */
rw_status_t rw_spawn_process(const char *filename, 
                             char *const argv[], 
                             int set_pgid,
                             pid_t *child_pid);

/**
 * This function terminates the process based on pid.
 *
 * @param[in] pid Process id to terminate.
 */
rw_status_t rw_terminate_process(pid_t pid);

/**
 * Macro is used to overload the new/delete operator to 
 * use  RW_MALLOC_TYPE/RW_FREE_TYPE for allocations.
 */
#define RW_CLASS_DECLARE_NEW_AND_DELETE_OPERATORS(type) \
  void* operator new(size_t size) \
  { \
    void *storage = RW_MALLOC_TYPE(size, type); \
    if (storage == nullptr) { \
      RW_CRASH(); \
    } \
    return(storage); \
  } \
  void operator delete(void *ptr) \
  { \
    RW_FREE_TYPE(ptr, type); \
  }


__END_DECLS

#endif /* __RWLIB_H__ */

