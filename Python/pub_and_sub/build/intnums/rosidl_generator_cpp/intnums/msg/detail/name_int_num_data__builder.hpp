// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from intnums:msg/NameIntNumData.idl
// generated code does not contain a copyright notice

#ifndef INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__BUILDER_HPP_
#define INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "intnums/msg/detail/name_int_num_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace intnums
{

namespace msg
{

namespace builder
{

class Init_NameIntNumData_int_num_data
{
public:
  explicit Init_NameIntNumData_int_num_data(::intnums::msg::NameIntNumData & msg)
  : msg_(msg)
  {}
  ::intnums::msg::NameIntNumData int_num_data(::intnums::msg::NameIntNumData::_int_num_data_type arg)
  {
    msg_.int_num_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::intnums::msg::NameIntNumData msg_;
};

class Init_NameIntNumData_name
{
public:
  Init_NameIntNumData_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NameIntNumData_int_num_data name(::intnums::msg::NameIntNumData::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_NameIntNumData_int_num_data(msg_);
  }

private:
  ::intnums::msg::NameIntNumData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::intnums::msg::NameIntNumData>()
{
  return intnums::msg::builder::Init_NameIntNumData_name();
}

}  // namespace intnums

#endif  // INTNUMS__MSG__DETAIL__NAME_INT_NUM_DATA__BUILDER_HPP_
