// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from tnsy_interfaces:msg/TnsyController.idl
// generated code does not contain a copyright notice

#ifndef TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__FUNCTIONS_H_
#define TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "tnsy_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "tnsy_interfaces/msg/detail/tnsy_controller__struct.h"

/// Initialize msg/TnsyController message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * tnsy_interfaces__msg__TnsyController
 * )) before or use
 * tnsy_interfaces__msg__TnsyController__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__init(tnsy_interfaces__msg__TnsyController * msg);

/// Finalize msg/TnsyController message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
void
tnsy_interfaces__msg__TnsyController__fini(tnsy_interfaces__msg__TnsyController * msg);

/// Create msg/TnsyController message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * tnsy_interfaces__msg__TnsyController__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
tnsy_interfaces__msg__TnsyController *
tnsy_interfaces__msg__TnsyController__create();

/// Destroy msg/TnsyController message.
/**
 * It calls
 * tnsy_interfaces__msg__TnsyController__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
void
tnsy_interfaces__msg__TnsyController__destroy(tnsy_interfaces__msg__TnsyController * msg);

/// Check for msg/TnsyController message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__are_equal(const tnsy_interfaces__msg__TnsyController * lhs, const tnsy_interfaces__msg__TnsyController * rhs);

/// Copy a msg/TnsyController message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__copy(
  const tnsy_interfaces__msg__TnsyController * input,
  tnsy_interfaces__msg__TnsyController * output);

/// Initialize array of msg/TnsyController messages.
/**
 * It allocates the memory for the number of elements and calls
 * tnsy_interfaces__msg__TnsyController__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__Sequence__init(tnsy_interfaces__msg__TnsyController__Sequence * array, size_t size);

/// Finalize array of msg/TnsyController messages.
/**
 * It calls
 * tnsy_interfaces__msg__TnsyController__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
void
tnsy_interfaces__msg__TnsyController__Sequence__fini(tnsy_interfaces__msg__TnsyController__Sequence * array);

/// Create array of msg/TnsyController messages.
/**
 * It allocates the memory for the array and calls
 * tnsy_interfaces__msg__TnsyController__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
tnsy_interfaces__msg__TnsyController__Sequence *
tnsy_interfaces__msg__TnsyController__Sequence__create(size_t size);

/// Destroy array of msg/TnsyController messages.
/**
 * It calls
 * tnsy_interfaces__msg__TnsyController__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
void
tnsy_interfaces__msg__TnsyController__Sequence__destroy(tnsy_interfaces__msg__TnsyController__Sequence * array);

/// Check for msg/TnsyController message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__Sequence__are_equal(const tnsy_interfaces__msg__TnsyController__Sequence * lhs, const tnsy_interfaces__msg__TnsyController__Sequence * rhs);

/// Copy an array of msg/TnsyController messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_tnsy_interfaces
bool
tnsy_interfaces__msg__TnsyController__Sequence__copy(
  const tnsy_interfaces__msg__TnsyController__Sequence * input,
  tnsy_interfaces__msg__TnsyController__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TNSY_INTERFACES__MSG__DETAIL__TNSY_CONTROLLER__FUNCTIONS_H_
