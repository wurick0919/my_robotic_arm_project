#include <cstdio>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
// #include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
// #include <tf2/LinearMath/Quaternion.hpp>


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<rclcpp::Node>(
    "hello_moveit",
    rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)
  );

  auto const logger = rclcpp::get_logger("hello_moveit");

  // main code goes here
  // Create the MoveIt MoveGroup Interface
  using moveit::planning_interface::MoveGroupInterface;
  auto move_group_interface = MoveGroupInterface(node, "arm"); // "" is the name of the group of joints we are controlling
  

  std::vector<double> joint_group_positions = {0.1, -0.8, -0.8}; 
  move_group_interface.setJointValueTarget(joint_group_positions);


  // // Set a target Pose
  // auto const target_pose = []{
  //   geometry_msgs::msg::Pose msg;
  //   msg.orientation.w = 1.0;
  //   msg.position.x = 0.1;
  //   msg.position.y = 0.1;
  //   msg.position.z = 0.1;
  //   return msg;
  // }();
  // move_group_interface.setPoseTarget(target_pose);
  // move_group_interface.setPositionTarget(-0.28, -0.3, 0.39);


  // Create a plan to that target pose
  auto const [success, plan] = [&move_group_interface]{
    moveit::planning_interface::MoveGroupInterface::Plan msg;
    auto const ok = static_cast<bool>(move_group_interface.plan(msg));
    return std::make_pair(ok, msg);
  }();

  // Execute the plan
  if(success) {
    move_group_interface.execute(plan);
  } else {
    RCLCPP_ERROR(logger, "Planning failed!");
  }

  rclcpp::shutdown();
  return 0;
}
