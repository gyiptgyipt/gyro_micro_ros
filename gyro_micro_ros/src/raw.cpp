#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

class IMU_TF : public rclcpp::Node {
public:
    IMU_TF() : Node("imu_tf") {
        
       std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
       
        
        imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu", 10, std::bind(&IMU_TF::imuCallback, this, std::placeholders::_1));
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    }

private:
    void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        // Extract orientation from the IMU message
        tf2::Quaternion tf_orientation;
        tf2::fromMsg(msg->orientation, tf_orientation);

        // Create a transformation message
        geometry_msgs::msg::TransformStamped transform_stamped;
        transform_stamped.header.stamp = msg->header.stamp;
        transform_stamped.header.frame_id = "imu_frame";  // Parent frame
        transform_stamped.child_frame_id = "base_link";   // Child frame
        transform_stamped.transform.translation.x = msg->angular_velocity.x;  // Assuming no translation
        transform_stamped.transform.translation.y = msg->angular_velocity.y;
        transform_stamped.transform.translation.z = msg->angular_velocity.z;
        transform_stamped.transform.rotation = tf2::toMsg(tf_orientation);

        // Broadcast the transformation
        tf_broadcaster_->sendTransform(transform_stamped);
    }

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IMU_TF>());
    rclcpp::shutdown();
    return 0;
}
