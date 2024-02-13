#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

using namespace std::chrono_literals;

class Geometry2Issue1 : public rclcpp::Node
{
public:
  Geometry2Issue1()
  : Node("minimal_publisher")
  {
    this->declare_parameter("foo", 0);
    this->declare_parameter("bar", "");
    this->declare_parameter("baz", 0.);
    this->declare_parameter("foo.first", 0);
    this->declare_parameter("foo.second", 0);
    this->declare_parameter("foobar", false);


    auto on_set_parameters =
        [](const std::vector<rclcpp::Parameter> & parameters) {
            rcl_interfaces::msg::SetParametersResult result;
            result.successful = false;
            for (auto parameter : parameters) {
              std::cout << "param " << parameter.get_name() << std::endl;
            }
            return result;

        };

    callback_handler = this->add_on_set_parameters_callback(on_set_parameters);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    timer_ = this->create_wall_timer(
      8ms, std::bind(&Geometry2Issue1::timer_callback, this));
  }

private:
  void timer_callback()
  {
    std::vector<geometry_msgs::msg::TransformStamped> v_tf;

    for (int i = 0; i < 6; ++i)
    {
        geometry_msgs::msg::TransformStamped ts;
        ts.transform.rotation.w = 1;
        ts.header.frame_id = "c";
        ts.header.stamp = this->now();
        ts.child_frame_id = "d" + std::to_string(i);
        v_tf.push_back(ts);
    }

    tf_broadcaster_->sendTransform(v_tf);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Node::OnSetParametersCallbackHandle::SharedPtr callback_handler;
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Geometry2Issue1>());
  rclcpp::shutdown();
  return 0;
}
