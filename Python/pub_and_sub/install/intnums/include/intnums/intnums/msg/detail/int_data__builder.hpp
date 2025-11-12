// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from intnums:msg/IntData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__INT_DATA__BUILDER_HPP_
#define INTNUMS__MSG__DETAIL__INT_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "intnums/msg/detail/int_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace intnums
{

namespace msg
{

namespace builder
{

class Init_IntData_num_b
{
public:
  explicit Init_IntData_num_b(::intnums::msg::IntData & msg)
  : msg_(msg)
  {}
  ::intnums::msg::IntData num_b(::intnums::msg::IntData::_num_b_type arg)
  {
    msg_.num_b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::intnums::msg::IntData msg_;
};

class Init_IntData_num_a
{
public:
  Init_IntData_num_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IntData_num_b num_a(::intnums::msg::IntData::_num_a_type arg)
  {
    msg_.num_a = std::move(arg);
    return Init_IntData_num_b(msg_);
  }

private:
  ::intnums::msg::IntData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::intnums::msg::IntData>()
{
  return intnums::msg::builder::Init_IntData_num_a();
}

}  // namespace intnums

#endif  // INTNUMS__MSG__DETAIL__INT_DATA__BUILDER_HPP_
