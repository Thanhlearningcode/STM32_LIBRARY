/* Platform_Types.h */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/* AUTOSAR standard fixed-width integer types */
typedef unsigned char       uint8;   /* 0 to 255 */
typedef unsigned short      uint16;  /* 0 to 65535 */
typedef unsigned long       uint32;  /* 0 to 4294967295 */
typedef unsigned long long  uint64;  /* 0 to 18446744073709551615 */

typedef signed char         sint8;   /* -128 to 127 */
typedef signed short        sint16;  /* -32768 to 32767 */
typedef signed long         sint32;  /* -2147483648 to 2147483647 */
typedef signed long long    sint64;  /* -9223372036854775808 to 9223372036854775807 */

/* Boolean type */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#endif /* PLATFORM_TYPES_H */
