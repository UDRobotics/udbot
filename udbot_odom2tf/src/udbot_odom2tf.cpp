#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
//#include <tf/transform_broadcaster.h>
#include "nav_msgs/msg/odometry.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include <rclcpp/qos.hpp>
#include <rmw/qos_profiles.h>
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
    : Node("minimal_subscriber")
  {
     // Initialize the transform broadcaster
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    
    auto sensor_qos = rclcpp::QoS(rclcpp::KeepLast(10), 
				  rmw_qos_profile_sensor_data);
    
    //    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>("/sonic/odom", sensor_qos, std::bind(&MinimalSubscriber::odom_callback, this, _1));
    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>("/yoshi/odom", sensor_qos, std::bind(&MinimalSubscriber::odom_callback, this, _1));
  }
  
private:
  void odom_callback(const nav_msgs::msg::Odometry & odm) const
  {
    geometry_msgs::msg::TransformStamped t;

    // Read message content and assign it to corresponding tf variables
    t.header = odm.header; 
    t.child_frame_id = odm.child_frame_id;

    t.transform.translation.x = odm.pose.pose.position.x;
    t.transform.translation.y = odm.pose.pose.position.y;
    t.transform.translation.z = odm.pose.pose.position.z;
    
    t.transform.rotation = odm.pose.pose.orientation;
    
    // Send the transformation
    tf_broadcaster_->sendTransform(t);
  }
  
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
