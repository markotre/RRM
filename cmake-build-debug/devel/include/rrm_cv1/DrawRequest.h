// Generated by gencpp from file rrm_cv1/DrawRequest.msg
// DO NOT EDIT!


#ifndef RRM_CV1_MESSAGE_DRAWREQUEST_H
#define RRM_CV1_MESSAGE_DRAWREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rrm_cv1
{
template <class ContainerAllocator>
struct DrawRequest_
{
  typedef DrawRequest_<ContainerAllocator> Type;

  DrawRequest_()
    : speed(0)
    , radius(0)  {
    }
  DrawRequest_(const ContainerAllocator& _alloc)
    : speed(0)
    , radius(0)  {
  (void)_alloc;
    }



   typedef int64_t _speed_type;
  _speed_type speed;

   typedef int64_t _radius_type;
  _radius_type radius;





  typedef boost::shared_ptr< ::rrm_cv1::DrawRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rrm_cv1::DrawRequest_<ContainerAllocator> const> ConstPtr;

}; // struct DrawRequest_

typedef ::rrm_cv1::DrawRequest_<std::allocator<void> > DrawRequest;

typedef boost::shared_ptr< ::rrm_cv1::DrawRequest > DrawRequestPtr;
typedef boost::shared_ptr< ::rrm_cv1::DrawRequest const> DrawRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rrm_cv1::DrawRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rrm_cv1::DrawRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::rrm_cv1::DrawRequest_<ContainerAllocator1> & lhs, const ::rrm_cv1::DrawRequest_<ContainerAllocator2> & rhs)
{
  return lhs.speed == rhs.speed &&
    lhs.radius == rhs.radius;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::rrm_cv1::DrawRequest_<ContainerAllocator1> & lhs, const ::rrm_cv1::DrawRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace rrm_cv1

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rrm_cv1::DrawRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rrm_cv1::DrawRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rrm_cv1::DrawRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "0df3d2abbf3db4de1a8cc3054dc46c99";
  }

  static const char* value(const ::rrm_cv1::DrawRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0df3d2abbf3db4deULL;
  static const uint64_t static_value2 = 0x1a8cc3054dc46c99ULL;
};

template<class ContainerAllocator>
struct DataType< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rrm_cv1/DrawRequest";
  }

  static const char* value(const ::rrm_cv1::DrawRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 speed\n"
"int64 radius\n"
;
  }

  static const char* value(const ::rrm_cv1::DrawRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.speed);
      stream.next(m.radius);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DrawRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rrm_cv1::DrawRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rrm_cv1::DrawRequest_<ContainerAllocator>& v)
  {
    s << indent << "speed: ";
    Printer<int64_t>::stream(s, indent + "  ", v.speed);
    s << indent << "radius: ";
    Printer<int64_t>::stream(s, indent + "  ", v.radius);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RRM_CV1_MESSAGE_DRAWREQUEST_H
