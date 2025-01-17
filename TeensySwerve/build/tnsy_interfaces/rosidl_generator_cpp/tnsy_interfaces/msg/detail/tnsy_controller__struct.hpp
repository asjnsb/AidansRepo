// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#ifndef TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_HPP_
#define TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__tnsy_interfaces__msg__TnsyController __attribute__((deprecated))
#else
# define DEPRECATED__tnsy_interfaces__msg__TnsyController __declspec(deprecated)
#endif

namespace tnsy_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TnsyController_
{
  using Type = TnsyController_<ContainerAllocator>;

  explicit TnsyController_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->translation_magnitude = 0.0f;
      this->translation_angle = 0.0f;
      this->rotation_speed = 0.0f;
      this->enable_switch = false;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->translation_magnitude = 0.0f;
      this->translation_angle = 0.0f;
      this->rotation_speed = 0.0f;
      this->pointing_magnitude = 0.0f;
      this->pointing_angle = 0.0f;
      this->enable_switch = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pointing_magnitude = 0.0f;
      this->pointing_angle = 0.0f;
    }
  }

  explicit TnsyController_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->translation_magnitude = 0.0f;
      this->translation_angle = 0.0f;
      this->rotation_speed = 0.0f;
      this->enable_switch = false;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->translation_magnitude = 0.0f;
      this->translation_angle = 0.0f;
      this->rotation_speed = 0.0f;
      this->pointing_magnitude = 0.0f;
      this->pointing_angle = 0.0f;
      this->enable_switch = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pointing_magnitude = 0.0f;
      this->pointing_angle = 0.0f;
    }
  }

  // field types and members
  using _translation_magnitude_type =
    float;
  _translation_magnitude_type translation_magnitude;
  using _translation_angle_type =
    float;
  _translation_angle_type translation_angle;
  using _rotation_speed_type =
    float;
  _rotation_speed_type rotation_speed;
  using _pointing_magnitude_type =
    float;
  _pointing_magnitude_type pointing_magnitude;
  using _pointing_angle_type =
    float;
  _pointing_angle_type pointing_angle;
  using _enable_switch_type =
    bool;
  _enable_switch_type enable_switch;

  // setters for named parameter idiom
  Type & set__translation_magnitude(
    const float & _arg)
  {
    this->translation_magnitude = _arg;
    return *this;
  }
  Type & set__translation_angle(
    const float & _arg)
  {
    this->translation_angle = _arg;
    return *this;
  }
  Type & set__rotation_speed(
    const float & _arg)
  {
    this->rotation_speed = _arg;
    return *this;
  }
  Type & set__pointing_magnitude(
    const float & _arg)
  {
    this->pointing_magnitude = _arg;
    return *this;
  }
  Type & set__pointing_angle(
    const float & _arg)
  {
    this->pointing_angle = _arg;
    return *this;
  }
  Type & set__enable_switch(
    const bool & _arg)
  {
    this->enable_switch = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    tnsy_interfaces::msg::TnsyController_<ContainerAllocator> *;
  using ConstRawPtr =
    const tnsy_interfaces::msg::TnsyController_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      tnsy_interfaces::msg::TnsyController_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      tnsy_interfaces::msg::TnsyController_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__tnsy_interfaces__msg__TnsyController
    std::shared_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__tnsy_interfaces__msg__TnsyController
    std::shared_ptr<tnsy_interfaces::msg::TnsyController_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TnsyController_ & other) const
  {
    if (this->translation_magnitude != other.translation_magnitude) {
      return false;
    }
    if (this->translation_angle != other.translation_angle) {
      return false;
    }
    if (this->rotation_speed != other.rotation_speed) {
      return false;
    }
    if (this->pointing_magnitude != other.pointing_magnitude) {
      return false;
    }
    if (this->pointing_angle != other.pointing_angle) {
      return false;
    }
    if (this->enable_switch != other.enable_switch) {
      return false;
    }
    return true;
  }
  bool operator!=(const TnsyController_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TnsyController_

// alias to use template instance with default allocator
using TnsyController =
  tnsy_interfaces::msg::TnsyController_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace tnsy_interfaces

#endif  // TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__STRUCT_HPP_
