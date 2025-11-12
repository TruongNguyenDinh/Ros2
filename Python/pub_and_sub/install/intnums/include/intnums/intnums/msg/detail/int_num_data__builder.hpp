// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from intnums:msg/IntNumData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__INT_NUM_DATA__BUILDER_HPP_
#define INTNUMS__MSG__DETAIL__INT_NUM_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "intnums/msg/detail/int_num_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace intnums
{

namespace msg
{

namespace builder
{

class Init_IntNumData_num_b
{
public:
  explicit Init_IntNumData_num_b(::intnums::msg::IntNumData & msg)
  : msg_(msg)
  {}
  ::intnums::msg::IntNumData num_b(::intnums::msg::IntNumData::_num_b_type arg)
  {
    msg_.num_b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::intnums::msg::IntNumData msg_;
};

class Init_IntNumData_num_a
{
public:
  Init_IntNumData_num_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IntNumData_num_b num_a(::intnums::msg::IntNumData::_num_a_type arg)
  {
    msg_.num_a = std::move(arg);
    return Init_IntNumData_num_b(msg_);
  }

private:
  ::intnums::msg::IntNumData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::intnums::msg::IntNumData>()
{
  return intnums::msg::builder::Init_IntNumData_num_a();
}

}  // namespace intnums

#endif  // INTNUMS__MSG__DETAIL__INT_NUM_DATA__BUILDER_HPP_
