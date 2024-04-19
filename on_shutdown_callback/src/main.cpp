#include <memory>
#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

class OnShutdownClass : public rclcpp::Node
{
public:
OnShutdownClass() : Node("minimal_publisher")
{
  rclcpp::Context::SharedPtr context = get_node_base_interface()->get_context();
  rcl_preshutdown_cb_handle_ = std::make_unique<rclcpp::PreShutdownCallbackHandle>(
      context->add_pre_shutdown_callback(
      std::bind(&OnShutdownClass::on_rcl_preshutdown, this))
  );
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
}

void on_rcl_preshutdown()
{

  auto message = std_msgs::msg::String();
  message.data = "Hello, world! " + std::to_string(1);
  this->publisher_->publish(message);

  RCLCPP_INFO(
    this->get_logger(), "Running rcl preshutdown");
}
  std::unique_ptr<rclcpp::PreShutdownCallbackHandle> rcl_preshutdown_cb_handle_{nullptr};
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OnShutdownClass>());
  rclcpp::shutdown();
  return 0;
}
