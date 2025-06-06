// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from complex_msgs:msg/NestedMsgTest.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "complex_msgs/msg/detail/nested_msg_test__struct.h"
#include "complex_msgs/msg/detail/nested_msg_test__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace complex_msgs
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _NestedMsgTest_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _NestedMsgTest_type_support_ids_t;

static const _NestedMsgTest_type_support_ids_t _NestedMsgTest_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _NestedMsgTest_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _NestedMsgTest_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _NestedMsgTest_type_support_symbol_names_t _NestedMsgTest_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, complex_msgs, msg, NestedMsgTest)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, complex_msgs, msg, NestedMsgTest)),
  }
};

typedef struct _NestedMsgTest_type_support_data_t
{
  void * data[2];
} _NestedMsgTest_type_support_data_t;

static _NestedMsgTest_type_support_data_t _NestedMsgTest_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _NestedMsgTest_message_typesupport_map = {
  2,
  "complex_msgs",
  &_NestedMsgTest_message_typesupport_ids.typesupport_identifier[0],
  &_NestedMsgTest_message_typesupport_symbol_names.symbol_name[0],
  &_NestedMsgTest_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t NestedMsgTest_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_NestedMsgTest_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace complex_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, complex_msgs, msg, NestedMsgTest)() {
  return &::complex_msgs::msg::rosidl_typesupport_c::NestedMsgTest_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
