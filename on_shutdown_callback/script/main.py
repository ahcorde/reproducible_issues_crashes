import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.executors import SingleThreadedExecutor
from std_msgs.msg import String
import time

def on_shutdown_alex():
    print("on_shutdown2")


def main(args=None):

  # context = rclpy.context.Context()
  rclpy.init()
  context = rclpy.get_default_context()
  node = rclpy.create_node('TestExecutor', context=context)

  executor = SingleThreadedExecutor(context=context)
  executor.add_node(node)

  try:
    while rclpy.ok():
      executor.spin_once()
      time.sleep(0.1)
  except KeyboardInterrupt:
     print('KeyboardInterrupt')
  except ExternalShutdownException:
     print('ExternalShutdownException')
  finally:
    node.destroy_node()
    context.on_shutdown(on_shutdown_alex)
    rclpy.try_shutdown(context=context)

if __name__ == '__main__':
  main()
