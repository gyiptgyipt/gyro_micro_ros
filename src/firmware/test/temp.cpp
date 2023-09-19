#include "rclcpp/rclcpp.hpp"
#include "your_message_package/msg/YourMessageType.hpp"  // Replace with your message type
#include "your_message_package/msg/YourMessageTypeStamped.hpp"  // Replace with your message type

class MySubscriberNode : public rclcpp::Node
{
public:
    MySubscriberNode() : Node("my_subscriber_node")
    {
        subscription_ = this->create_subscription<your_message_package::msg::YourMessageType>(
            "source_topic", 10, std::bind(&MySubscriberNode::sourceCallback, this, std::placeholders::_1));
        publisher_ = this->create_publisher<your_message_package::msg::YourMessageTypeStamped>("target_topic", 10);
    }

private:
    void sourceCallback(const your_message_package::msg::YourMessageType::SharedPtr msg)
    {
        // Process the received message (msg) if needed
        // Then, publish it to the target topic
        auto stamped_msg = std::make_shared<your_message_package::msg::YourMessageTypeStamped>();
        stamped_msg->header = msg->header;  // Copy the header if your message has one
        stamped_msg->data = msg->data;  // Copy the data or modify it if needed
        publisher_->publish(stamped_msg);
    }

    rclcpp::Subscription<your_message_package::msg::YourMessageType>::SharedPtr subscription_;
    rclcpp::Publisher<your_message_package::msg::YourMessageTypeStamped>::SharedPtr publisher_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MySubscriberNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}