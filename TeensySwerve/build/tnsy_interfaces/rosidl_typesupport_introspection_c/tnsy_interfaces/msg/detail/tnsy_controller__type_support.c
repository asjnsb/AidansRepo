// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "tnsy_interfaces/msg/detail/tnsy_controller__rosidl_typesupport_introspection_c.h"
#include "tnsy_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "tnsy_interfaces/msg/detail/tnsy_controller__functions.h"
#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tnsy_interfaces__msg__TnsyController__init(message_memory);
}

void tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_fini_function(void * message_memory)
{
  tnsy_interfaces__msg__TnsyController__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_member_array[6] = {
  {
    "translation_magnitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, translation_magnitude),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "translation_angle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, translation_angle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pointing_magnitude",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, pointing_magnitude),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pointing_angle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, pointing_angle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rotation_speed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, rotation_speed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "enable_switch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tnsy_interfaces__msg__TnsyController, enable_switch),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_members = {
  "tnsy_interfaces__msg",  // message namespace
  "TnsyController",  // message name
  6,  // number of fields
  sizeof(tnsy_interfaces__msg__TnsyController),
  tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_member_array,  // message members
  tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_init_function,  // function to initialize message memory (memory has to be allocated)
  tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_type_support_handle = {
  0,
  &tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tnsy_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tnsy_interfaces, msg, TnsyController)() {
  if (!tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_type_support_handle.typesupport_identifier) {
    tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &tnsy_interfaces__msg__TnsyController__rosidl_typesupport_introspection_c__TnsyController_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
