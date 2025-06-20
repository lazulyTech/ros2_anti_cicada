#ifndef OAK_DETECTION__VISIBILITY_CONTROL_H_
#define OAK_DETECTION__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define OAK_DETECTION_EXPORT __attribute__ ((dllexport))
    #define OAK_DETECTION_IMPORT __attribute__ ((dllimport))
  #else
    #define OAK_DETECTION_EXPORT __declspec(dllexport)
    #define OAK_DETECTION_IMPORT __declspec(dllimport)
  #endif
  #ifdef OAK_DETECTION_BUILDING_LIBRARY
    #define OAK_DETECTION_PUBLIC OAK_DETECTION_EXPORT
  #else
    #define OAK_DETECTION_PUBLIC OAK_DETECTION_IMPORT
  #endif
  #define OAK_DETECTION_PUBLIC_TYPE OAK_DETECTION_PUBLIC
  #define OAK_DETECTION_LOCAL
#else
  #define OAK_DETECTION_EXPORT __attribute__ ((visibility("default")))
  #define OAK_DETECTION_IMPORT
  #if __GNUC__ >= 4
    #define OAK_DETECTION_PUBLIC __attribute__ ((visibility("default")))
    #define OAK_DETECTION_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define OAK_DETECTION_PUBLIC
    #define OAK_DETECTION_LOCAL
  #endif
  #define OAK_DETECTION_PUBLIC_TYPE
#endif

#endif  // OAK_DETECTION__VISIBILITY_CONTROL_H_
