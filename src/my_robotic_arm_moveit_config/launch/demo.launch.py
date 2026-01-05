# from moveit_configs_utils import MoveItConfigsBuilder
# from moveit_configs_utils.launches import generate_demo_launch


# def generate_launch_description():
#     moveit_config = MoveItConfigsBuilder("my_robot", package_name="my_robotic_arm_moveit_config").to_moveit_configs()
#     return generate_demo_launch(moveit_config)


from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch
import os

def generate_launch_description():
    # Explicitly define where the controllers file is
    moveit_config = (
        MoveItConfigsBuilder("my_robot", package_name="my_robotic_arm_moveit_config")
        .robot_description(file_path="config/my_robot.urdf.xacro") # Or your .urdf
        .trajectory_execution(file_path="config/moveit_controllers.yaml") # FORCE THIS
        .to_moveit_configs()
    )
    
    return generate_demo_launch(moveit_config)
