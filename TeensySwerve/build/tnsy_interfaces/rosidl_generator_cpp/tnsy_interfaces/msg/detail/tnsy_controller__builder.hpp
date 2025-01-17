// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#ifndef TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__BUILDER_HPP_
#define TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tnsy_interfaces
{

namespace msg
{

namespace builder
{

class Init_TnsyController_enable_switch
{
public:
  explicit Init_TnsyController_enable_switch(::tnsy_interfaces::msg::TnsyController & msg)
  : msg_(msg)
  {}
  ::tnsy_interfaces::msg::TnsyController enable_switch(::tnsy_interfaces::msg::TnsyController::_enable_switch_type arg)
  {
    msg_.enable_switch = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

class Init_TnsyController_pointing_angle
{
public:
  explicit Init_TnsyController_pointing_angle(::tnsy_interfaces::msg::TnsyController & msg)
  : msg_(msg)
  {}
  Init_TnsyController_enable_switch pointing_angle(::tnsy_interfaces::msg::TnsyController::_pointing_angle_type arg)
  {
    msg_.pointing_angle = std::move(arg);
    return Init_TnsyController_enable_switch(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

class Init_TnsyController_pointing_magnitude
{
public:
  explicit Init_TnsyController_pointing_magnitude(::tnsy_interfaces::msg::TnsyController & msg)
  : msg_(msg)
  {}
  Init_TnsyController_pointing_angle pointing_magnitude(::tnsy_interfaces::msg::TnsyController::_pointing_magnitude_type arg)
  {
    msg_.pointing_magnitude = std::move(arg);
    return Init_TnsyController_pointing_angle(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

class Init_TnsyController_rotation_speed
{
public:
  explicit Init_TnsyController_rotation_speed(::tnsy_interfaces::msg::TnsyController & msg)
  : msg_(msg)
  {}
  Init_TnsyController_pointing_magnitude rotation_speed(::tnsy_interfaces::msg::TnsyController::_rotation_speed_type arg)
  {
    msg_.rotation_speed = std::move(arg);
    return Init_TnsyController_pointing_magnitude(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

class Init_TnsyController_translation_angle
{
public:
  explicit Init_TnsyController_translation_angle(::tnsy_interfaces::msg::TnsyController & msg)
  : msg_(msg)
  {}
  Init_TnsyController_rotation_speed translation_angle(::tnsy_interfaces::msg::TnsyController::_translation_angle_type arg)
  {
    msg_.translation_angle = std::move(arg);
    return Init_TnsyController_rotation_speed(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

class Init_TnsyController_translation_magnitude
{
public:
  Init_TnsyController_translation_magnitude()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TnsyController_translation_angle translation_magnitude(::tnsy_interfaces::msg::TnsyController::_translation_magnitude_type arg)
  {
    msg_.translation_magnitude = std::move(arg);
    return Init_TnsyController_translation_angle(msg_);
  }

private:
  ::tnsy_interfaces::msg::TnsyController msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::tnsy_interfaces::msg::TnsyController>()
{
  return tnsy_interfaces::msg::builder::Init_TnsyController_translation_magnitude();
}

}  // namespace tnsy_interfaces

#endif  // TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__BUILDER_HPP_
