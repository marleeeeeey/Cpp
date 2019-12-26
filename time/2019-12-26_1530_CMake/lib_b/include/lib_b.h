#pragma once
#include <string>

#if defined (LIBB_BUILT_AS_DYNAMIC_LIB)

  #if defined (LIBB_EXPORTS)  /* Compiling the MXA DLL/Dylib */
    #if defined (_MSC_VER)  /* MSVC Compiler Case */
      #define  LIBB_EXPORT __declspec(dllexport)
    #elif (__GNUC__ >= 4)  /* GCC 4.x has support for visibility options */
      #define LIBB_EXPORT __attribute__ ((visibility("default")))
    #endif
  #else  /* Importing the DLL into another project */
    #if defined (_MSC_VER)  /* MSVC Compiler Case */
      #define  LIBB_EXPORT __declspec(dllimport)
    #elif (__GNUC__ >= 4)  /* GCC 4.x has support for visibility options */
      #define LIBB_EXPORT __attribute__ ((visibility("default")))
    #endif
  #endif
#endif

/* If LIBB_EXPORT was never defined, define it here */
#ifndef LIBB_EXPORT
  #define LIBB_EXPORT
#endif

LIBB_EXPORT std::string getLibBName();