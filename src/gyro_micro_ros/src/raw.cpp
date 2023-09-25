#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "sensor_msgs/msg/imu.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

class IMU_TF : public rclcpp::Node {
public:
    IMU_TF() : Node("imu_tf") {
        
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);

        
        imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu/data", 10, std::bind(&IMU_TF::imuCallback, this, std::placeholders::_1));

        // tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
        // timer_ = this->create_wall_timer(
        // 100ms, std::bind(&IMU_TF::imuCallback, this));


    }

private:
    // void rec_data(const sensor_msgs::msg::Imu::SharedPtr msg) {
    
    // }

    void imuCallback( const std::shared_ptr<sensor_msgs::msg::Imu> msg) {
       
        // Extract orientation from the IMU message
        // tf2::Quaternion tf_orientation;
        // tf2::fromMsg(msg->orientation, tf_orientation);

        // Create a transformation message
        geometry_msgs::msg::TransformStamped transform_stamped;
        
        transform_stamped.header.stamp = this->get_clock()->now();
        transform_stamped.header.frame_id = "imu_link";  // Parent frame
        transform_stamped.child_frame_id = "base_link";   // Child frame
        transform_stamped.transform.translation.x = 0.0;  // Assuming no translation
        transform_stamped.transform.translation.y = 0.0;
        transform_stamped.transform.translation.z = 0.0;

        tf2::Quaternion q;
        q.setRPY(msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);
        transform_stamped.transform.rotation.x = q.x();
        transform_stamped.transform.rotation.y = q.y();
        transform_stamped.transform.rotation.z = q.z();
        transform_stamped.transform.rotation.w = q.w();
        // RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->angular_velocity.y);

        
        // transform_stamped.transform.rotation = tf2::toMsg(tf_orientation);

        // Broadcast the transformation
        tf_broadcaster_->sendTransform(transform_stamped);

    }
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IMU_TF>());
    rclcpp::shutdown();
    return 0;
}
