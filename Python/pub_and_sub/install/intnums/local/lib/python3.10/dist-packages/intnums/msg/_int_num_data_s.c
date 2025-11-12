// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from intnums:msg/IntNumData.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "intnums/msg/detail/int_num_data__struct.h"
#include "intnums/msg/detail/int_num_data__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool intnums__msg__int_num_data__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[37];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("intnums.msg._int_num_data.IntNumData", full_classname_dest, 36) == 0);
  }
  intnums__msg__IntNumData * ros_message = _ros_message;
  {  // num_a
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_a");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_a = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // num_b
    PyObject * field = PyObject_GetAttrString(_pymsg, "num_b");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->num_b = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * intnums__msg__int_num_data__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of IntNumData */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("intnums.msg._int_num_data");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "IntNumData");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  intnums__msg__IntNumData * ros_message = (intnums__msg__IntNumData *)raw_ros_message;
  {  // num_a
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->num_a);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_a", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // num_b
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->num_b);
    {
      int rc = PyObject_SetAttrString(_pymessage, "num_b", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
