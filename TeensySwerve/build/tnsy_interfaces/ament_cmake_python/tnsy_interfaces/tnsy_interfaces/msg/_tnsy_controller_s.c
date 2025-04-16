// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from tnsy_interfaces:msg/TnsyController.idl
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
#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.h"
#include "tnsy_interfaces/msg/detail/tnsy_controller__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool tnsy_interfaces__msg__tnsy_controller__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[52];
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
    assert(strncmp("tnsy_interfaces.msg._tnsy_controller.TnsyController", full_classname_dest, 51) == 0);
  }
  tnsy_interfaces__msg__TnsyController * ros_message = _ros_message;
  {  // translation_magnitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "translation_magnitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->translation_magnitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // translation_angle
    PyObject * field = PyObject_GetAttrString(_pymsg, "translation_angle");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->translation_angle = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pointing_magnitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "pointing_magnitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pointing_magnitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pointing_angle
    PyObject * field = PyObject_GetAttrString(_pymsg, "pointing_angle");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pointing_angle = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rotation_speed
    PyObject * field = PyObject_GetAttrString(_pymsg, "rotation_speed");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rotation_speed = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // enable_switch
    PyObject * field = PyObject_GetAttrString(_pymsg, "enable_switch");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->enable_switch = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * tnsy_interfaces__msg__tnsy_controller__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TnsyController */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("tnsy_interfaces.msg._tnsy_controller");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TnsyController");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  tnsy_interfaces__msg__TnsyController * ros_message = (tnsy_interfaces__msg__TnsyController *)raw_ros_message;
  {  // translation_magnitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->translation_magnitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "translation_magnitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // translation_angle
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->translation_angle);
    {
      int rc = PyObject_SetAttrString(_pymessage, "translation_angle", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pointing_magnitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pointing_magnitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pointing_magnitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pointing_angle
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pointing_angle);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pointing_angle", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rotation_speed
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rotation_speed);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rotation_speed", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // enable_switch
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->enable_switch ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "enable_switch", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
