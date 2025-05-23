// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from nav_msgs:msg/Goals.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "nav_msgs/msg/detail/goals__rosidl_typesupport_introspection_c.h"
#include "nav_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "nav_msgs/msg/detail/goals__functions.h"
#include "nav_msgs/msg/detail/goals__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `goals`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `goals`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  nav_msgs__msg__Goals__init(message_memory);
}

void nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_fini_function(void * message_memory)
{
  nav_msgs__msg__Goals__fini(message_memory);
}

size_t nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__size_function__Goals__goals(
  const void * untyped_member)
{
  const geometry_msgs__msg__PoseStamped__Sequence * member =
    (const geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return member->size;
}

const void * nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_const_function__Goals__goals(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__PoseStamped__Sequence * member =
    (const geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void * nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_function__Goals__goals(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__PoseStamped__Sequence * member =
    (geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  return &member->data[index];
}

void nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__fetch_function__Goals__goals(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__PoseStamped * item =
    ((const geometry_msgs__msg__PoseStamped *)
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_const_function__Goals__goals(untyped_member, index));
  geometry_msgs__msg__PoseStamped * value =
    (geometry_msgs__msg__PoseStamped *)(untyped_value);
  *value = *item;
}

void nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__assign_function__Goals__goals(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__PoseStamped * item =
    ((geometry_msgs__msg__PoseStamped *)
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_function__Goals__goals(untyped_member, index));
  const geometry_msgs__msg__PoseStamped * value =
    (const geometry_msgs__msg__PoseStamped *)(untyped_value);
  *item = *value;
}

bool nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__resize_function__Goals__goals(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__PoseStamped__Sequence * member =
    (geometry_msgs__msg__PoseStamped__Sequence *)(untyped_member);
  geometry_msgs__msg__PoseStamped__Sequence__fini(member);
  return geometry_msgs__msg__PoseStamped__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_msgs__msg__Goals, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goals",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(nav_msgs__msg__Goals, goals),  // bytes offset in struct
    NULL,  // default value
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__size_function__Goals__goals,  // size() function pointer
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_const_function__Goals__goals,  // get_const(index) function pointer
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__get_function__Goals__goals,  // get(index) function pointer
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__fetch_function__Goals__goals,  // fetch(index, &value) function pointer
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__assign_function__Goals__goals,  // assign(index, value) function pointer
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__resize_function__Goals__goals  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_members = {
  "nav_msgs__msg",  // message namespace
  "Goals",  // message name
  2,  // number of fields
  sizeof(nav_msgs__msg__Goals),
  nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_member_array,  // message members
  nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_init_function,  // function to initialize message memory (memory has to be allocated)
  nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_type_support_handle = {
  0,
  &nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_nav_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, Goals)() {
  nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  if (!nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_type_support_handle.typesupport_identifier) {
    nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &nav_msgs__msg__Goals__rosidl_typesupport_introspection_c__Goals_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
