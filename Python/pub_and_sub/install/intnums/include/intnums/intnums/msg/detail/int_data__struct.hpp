// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_HPP_
#define INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__intnums__msg__IntData __attribute__((deprecated))
#else
# define DEPRECATED__intnums__msg__IntData __declspec(deprecated)
#endif

namespace intnums
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IntData_
{
  using Type = IntData_<ContainerAllocator>;

  explicit IntData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_a = 0ll;
      this->num_b = 0ll;
    }
  }

  explicit IntData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_a = 0ll;
      this->num_b = 0ll;
    }
  }

  // field types and members
  using _num_a_type =
    int64_t;
  _num_a_type num_a;
  using _num_b_type =
    int64_t;
  _num_b_type num_b;

  // setters for named parameter idiom
  Type & set__num_a(
    const int64_t & _arg)
  {
    this->num_a = _arg;
    return *this;
  }
  Type & set__num_b(
    const int64_t & _arg)
  {
    this->num_b = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    intnums::msg::IntData_<ContainerAllocator> *;
  using ConstRawPtr =
    const intnums::msg::IntData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<intnums::msg::IntData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<intnums::msg::IntData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      intnums::msg::IntData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<intnums::msg::IntData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      intnums::msg::IntData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<intnums::msg::IntData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<intnums::msg::IntData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<intnums::msg::IntData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__intnums__msg__IntData
    std::shared_ptr<intnums::msg::IntData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__intnums__msg__IntData
    std::shared_ptr<intnums::msg::IntData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IntData_ & other) const
  {
    if (this->num_a != other.num_a) {
      return false;
    }
    if (this->num_b != other.num_b) {
      return false;
    }
    return true;
  }
  bool operator!=(const IntData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IntData_

// alias to use template instance with default allocator
using IntData =
  intnums::msg::IntData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace intnums

#endif  // INTNUMS__MSG__DETAIL__INT_DATA__STRUCT_HPP_
