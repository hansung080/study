#ifndef __TYPES_H__
#define __TYPES_H__

#define false 0
#define true  1

#define CHAR_MIN       ((char)0x80) // -128
#define CHAR_MAX       ((char)0x7f) //  127
#define CHAR_MAX_DIGIT 4

#define UCHAR_MIN       ((uchar)0x0)  // 0
#define UCHAR_MAX       ((uchar)0xff) // 255
#define UCHAR_MAX_DIGIT 3

#define SHORT_MIN       ((short)0x8000) // -32768
#define SHORT_MAX       ((short)0x7fff) //  32767
#define SHORT_MAX_DIGIT 6

#define USHORT_MIN       ((ushort)0x0)    // 0
#define USHORT_MAX       ((ushort)0xffff) // 65535
#define USHORT_MAX_DIGIT 5

#define INT_MIN       ((int)0x80000000) // -2147483648
#define INT_MAX       ((int)0x7fffffff) //  2147483647
#define INT_MAX_DIGIT 11

#define UINT_MIN       ((uint)0x0)        // 0
#define UINT_MAX       ((uint)0xffffffff) // 4294967295
#define UINT_MAX_DIGIT 10

#define LONG_MIN       ((long)0x8000000000000000) // -9223372036854775808
#define LONG_MAX       ((long)0x7fffffffffffffff) //  9223372036854775807
#define LONG_MAX_DIGIT 20

#define ULONG_MIN ((ulong)0x0)                // 0
#define ULONG_MAX ((ulong)0xffffffffffffffff) // 18446744073709551615
#define ULONG_MAX_DIGIT 20

typedef unsigned char  bool;
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

#endif // __TYPES_H__