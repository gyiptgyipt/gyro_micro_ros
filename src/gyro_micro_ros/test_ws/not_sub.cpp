#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include "tf2_ros/transform_broadcaster.h"


using std::placeholders::_1;

class Imu_Publisher : public rclcpp::Node{
    
  public:
    double _poll;
    std::string _topicImu;
    std::string _frameId;

    Imu_Publisher() : Node("IMU_TF"){

    // double _poll;
    std::string _topicImu;
    std::string _frameId;

      get_parameter_or<std::string>("frame_id", _frameId, "imu_tf"); 
 
      // get_parameter_or<double>("poll", _poll, 15.0);


      subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "/imu", 10, std::bind(&Imu_Publisher::topic_callback, this, _1));

      _publisherImu = this->create_publisher<sensor_msgs::msg::Imu>("imu_tf", 10);
      
      tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

      // _timer = this->create_wall_timer(
      //   std::chrono::duration<double, std::milli>(_poll), 
      //   std::bind(&Imu_Publisher::publishImuData, this));

        //tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);

    }
 

  private:

    void topic_callback(const sensor_msgs::msg::Imu::SharedPtr imu_msg){
      
       geometry_msgs::msg::TransformStamped messageImu; //geometry_tf

        messageImu.header.frame_id = _frameId;
        messageImu.header.stamp = messageImu.header.stamp;


        // messageImu.linear_acceleration.x = imu_msg->linear_acceleration.x;
        // messageImu.linear_acceleration.y = imu_msg->linear_acceleration.y;
        // messageImu.linear_acceleration.z = imu_msg->linear_acceleration.z;

        messageImu.transform.translation.x = imu_msg->angular_velocity.x;
        messageImu.transform.translation.y = imu_msg->angular_velocity.y;
        messageImu.transform.translation.z = imu_msg->angular_velocity.z;

           tf2::Quaternion q;
           q.setRPY(0, 0, 0);
           messageImu.transform.rotation.x = q.x();
            messageImu.transform.rotation.y = q.y();
            messageImu.transform.rotation.z = q.z();
            messageImu.transform.rotation.w = q.w();

        // messageImu.linear_acceleration.x = imu_msg->linear_acceleration.x;
        // messageImu.linear_acceleration.y = imu_msg->linear_acceleration.y;
        // messageImu.linear_acceleration.z = imu_msg->linear_acceleration.z;

        // messageImu.angular_velocity.x = imu_msg->angular_velocity.x;
        // messageImu.angular_velocity.y = imu_msg->angular_velocity.y;
        // messageImu.angular_velocity.z = imu_msg->angular_velocity.z;
          tf_broadcaster_->sendTransform(messageImu);
      // _publisherImu->publish(messageImu);
      RCLCPP_INFO(this->get_logger(),"Publishing : ");

    }
    void publishImuData() {
  
    // rclcpp::Time now = this->get_clock()->now();       
     
         auto messageImu = sensor_msgs::msg::Imu();
        messageImu.header.frame_id = _frameId;
        messageImu.header.stamp = messageImu.header.stamp;

        // messageImu.linear_acceleration.x = imu_msg->linear_acceleration.x;
        // messageImu.linear_acceleration.y = imu_msg->linear_acceleration.y;
        // messageImu.linear_acceleration.z = imu_msg->linear_acceleration.z;

        // messageImu.angular_velocity.x = imu_msg->angular_velocity.x;
        // messageImu.angular_velocity.y = imu_msg->angular_velocity.y;
        // messageImu.angular_velocity.z = imu_msg->angular_velocity.z;
        RCLCPP_INFO(this->get_logger(),"Value Y : '%f'", messageImu.angular_velocity.y);

    _publisherImu->publish(messageImu);
    // tf_broadcaster_->sendTransform(messageImu);
    // Send the transformation

    }
 
    
    // rclcpp::TimerBase::SharedPtr _timer;
     rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr _publisherImu;
    //std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Imu_Publisher>());
  rclcpp::shutdown();
  return 0;
}