// generated from rosidl_generator_c/resource/rosidl_generator_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define INTNUMS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_intnums __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_intnums __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_intnums __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_intnums __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_intnums
    #define ROSIDL_GENERATOR_C_PUBLIC_intnums ROSIDL_GENERATOR_C_EXPORT_intnums
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_intnums ROSIDL_GENERATOR_C_IMPORT_intnums
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_intnums __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_intnums
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_intnums __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_intnums
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // INTNUMS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
