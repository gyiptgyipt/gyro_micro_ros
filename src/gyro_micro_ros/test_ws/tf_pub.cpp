#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "tf2_ros/transform_broadcaster.h"

class ImuPublisherNode : public rclcpp::Node
{
public:
    ImuPublisherNode() : Node("imu_receiver_node")
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("imu_data", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&ImuPublisherNode::publishImuData, this));
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    }

private:
    void publishImuData()
    {
        auto imu_msg = sensor_msgs::msg::Imu();

        // Fill in imu_msg with your IMU data
        imu_msg.header.stamp = this->now();
        imu_msg.linear_acceleration.x = 0.0;
        imu_msg.linear_acceleration.y = 0.0;
        imu_msg.linear_acceleration.z = 0.0;
        imu_msg.angular_velocity.x = 0.0;
        imu_msg.angular_velocity.y = 0.0;
        imu_msg.angular_velocity.z = 0.0;

        // Publish the IMU data
        publisher_->publish(imu_msg);

        // Publish a TF2 transform
        geometry_msgs::msg::TransformStamped transform_stamped;
        transform_stamped.header.stamp = imu_msg.header.stamp;
        transform_stamped.header.frame_id = "base_link";
        transform_stamped.child_frame_id = "imu_link";
        transform_stamped.transform.translation.x = 0.0;
        transform_stamped.transform.translation.y = 0.0;
        transform_stamped.transform.translation.z = 0.0;
        transform_stamped.transform.rotation.x = 0.0;
        transform_stamped.transform.rotation.y = 0.0;
        transform_stamped.transform.rotation.z = 0.0;
        transform_stamped.transform.rotation.w = 1.0;
        tf_broadcaster_->sendTransform(transform_stamped);
    }

    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImuPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
