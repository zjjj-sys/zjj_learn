#ifndef __CONFIG_ARRAY_SIZE_HH__
#define __CONFIG_ARRAY_SIZE_HH__


// need gnu++11 support . 
// see with linux kernel "ARRAY_SIZE" define.
// lifan @2021.08.20

// DON'T include this header in extern "C"


#ifdef __cplusplus
#if __cplusplus

// g++ version - ARRAY_SIZE - <C++ ARRAY_SIZE() - why you still need a macro>
// at http://www.cplusplus.com/forum/general/103284/
// lifan @2021.10.26

template< typename T, size_t N >
size_t countof_A( const T (&)[N] ) { return N; }

template <typename T, size_t N>
char ( &_ArraySizeHelper( T (&array)[N] ))[N];
#define countof_B( array ) (sizeof( _ArraySizeHelper( array ) ))




#define ARRAY_SIZE countof_B
//#define ARRAY_SIZE countof_A
#endif

#else

// gcc version - ARRAY_SIZE - copy from linux kernel source code...
// lifan @2021.10.26

#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:-!!(e); }))
#define __must_be_array(a)     BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))

#endif /* End of #ifdef __cplusplus */




#endif //__CONFIG_ARRAY_SIZE_HH__

