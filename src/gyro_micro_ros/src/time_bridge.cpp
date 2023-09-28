#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "sensor_msgs/msg/imu.hpp"


class IMU_bridge : public rclcpp::Node {
public:
    IMU_bridge() : Node("IMU_bridge") {
        
        publisher_ = this->create_publisher<sensor_msgs::msg::Imu>("/imu/data_raw", 10);


        imu_subscriber_ = this->create_subscription<sensor_msgs::msg::Imu>(
            "/imu/micro", 10, std::bind(&IMU_bridge::imuCallback, this, std::placeholders::_1));

        // tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
        // timer_ = this->create_wall_timer(
        // 100ms, std::bind(&IMU_bridge::imuCallback, this));


    }

private:
    // void rec_data(const sensor_msgs::msg::Imu::SharedPtr msg) {
    
    // }

    void imuCallback( const std::shared_ptr<sensor_msgs::msg::Imu> msg) {
       
        auto pub_msg = sensor_msgs::msg::Imu();
        
        pub_msg.header.stamp = this->get_clock()->now();
        pub_msg.header.frame_id = "imu_frame_bridge";

        pub_msg.linear_acceleration.x = msg->linear_acceleration.x;
        pub_msg.linear_acceleration.y = msg->linear_acceleration.y;
        pub_msg.linear_acceleration.z = msg->linear_acceleration.z;

        pub_msg.angular_velocity.x = msg->angular_velocity.x;
        pub_msg.angular_velocity.y = msg->angular_velocity.y;
        pub_msg.angular_velocity.z = msg->angular_velocity.z;

        publisher_->publish(pub_msg);

    }
    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr publisher_;
    
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IMU_bridge>());
    rclcpp::shutdown();
    return 0;
}
