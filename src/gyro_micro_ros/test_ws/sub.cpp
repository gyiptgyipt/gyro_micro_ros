#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include "tf2_ros/transform_broadcaster.h"

using std::placeholders::_1;

class Imu_Subscriber : public rclcpp::Node
{
  public:
    Imu_Subscriber() : Node("minimal_subscriber")
    {

        subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
        "/imu", 10, std::bind(&Imu_Subscriber::topic_callback, this, std::placeholders::_1));
      tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);

    }

  private:
    void topic_callback(const sensor_msgs::msg::Imu::SharedPtr imu_msg){
    
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", imu_msg->angular_velocity.y);
    }
    
    void publishImuData() {
        auto imu_msg = sensor_msgs::msg::Imu();

    rclcpp::Time now = this->get_clock()->now();
    geometry_msgs::msg::TransformStamped t;

    t.header.stamp = now;
    t.header.frame_id = "base_link";
    t.child_frame_id = "imu";

    t.transform.translation.x = imu_msg.angular_velocity.x;
    t.transform.translation.y = imu_msg.angular_velocity.y;
    t.transform.translation.z = imu_msg.angular_velocity.z;

    // For the same reason, turtle can only rotate around one axis
    // and this why we set rotation in x and y to 0 and obtain
    // rotation in z axis from the message
    tf2::Quaternion q;
    q.setRPY(0, 0, 0);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    tf_broadcaster_->sendTransform(t);


    }
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Imu_Subscriber>());
  rclcpp::shutdown();
  return 0;
}