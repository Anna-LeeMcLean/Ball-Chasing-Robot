#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
	ROS_INFO_STREAM("Driving the robot");
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;

	if (!client.call(srv))
		ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    // left is the first third of the step size. forward is the middle third and right is the last third.
    int third_step = img.step/3; //266*3
    int row_counter = 0;
    int row_index = 0;
    int column_index = 0;
    float linear_x_vel = 0.0;
    float angular_z_vel = 0.0;

    for (int i=0; i<img.height*img.step; i=i+3) {

	if ((img.data[i] == white_pixel) && (img.data[i+1] == white_pixel) && (img.data[i+2] == white_pixel)){
	    row_index = i%img.step;
	    column_index = row_index/third_step;
	    if (column_index <= 1){
		//call drive_bot to drive left
		linear_x_vel = 0.5;
		angular_z_vel = 0.5;
	    }
	    else if ((row_index == 0) || (column_index >= 2)){
		//call drive_bot to drive right
		linear_x_vel = 0.5;
		angular_z_vel = -0.5;
	    }
	    else if ((column_index > 1) && (column_index < 2)){
		//call drive_bot to drive forward
		linear_x_vel = 0.5;
		angular_z_vel = 0.0;
	    }
	    break;
	}
	else {
	    // request stop
	    linear_x_vel = 0.0;
	    angular_z_vel = 0.0;
	}
    }

    drive_robot(linear_x_vel, angular_z_vel);
					
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
