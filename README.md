# Ball-Chasing-Robot
This project implements a custom robot which chases a white ball in a Gazebo world. This project was done as a part of the Go Chase It! Project in the Udacity Robotics Software Engineering Nanodegree Program.

The my_robot package implements a cusotm robot which is equipped with a camera and a Hokuyo lidar sensor for object detection.
The ball_chaser package gives the robot the ability to chase a white ball as it is moved by the user through the Gazebo world. 

To try out the application, clone and build the package and run the following commands:

Clone the workspace:
`git clone `
`catkin_make`
`source devel/setup.bash`

Launch the Gazebo world with the custom robot and white ball:
`roslaunch my_robot world.launch`

Launch the ball_chaser node which allows the robot to follow the white ball:
`roslaunch ball_chaser ball_chaser.launch`

Visualize the images from the robot's camera:
`rosrun rqt_image_view rqt_image_view`

Now place the white ball at different positions in front of the robot and watch the robot chase the ball!
