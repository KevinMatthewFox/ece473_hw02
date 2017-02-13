#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include "turtlesim/Pose.h"

#include <sstream>
#include <math.h>
/*void cmdCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    ROS_INFO_STREAM("I heard x:" << msg->linear.x << " theta:" << msg->angular.z;
}
void colorCallback(const turtlesim::Color::ConstPtr& msg)
{
    ROS_INFO_STREAM("I heard R:" << (int)msg->r);
}*/

double turtlePose_x;
double turtlePose_y;
double turtlePose_theta;

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
	turtlePose_x = (double)msg->x;
	turtlePose_y = (double)msg->y;    
	turtlePose_theta = (double)msg->theta;
    //std::cout << "in callback"  << std::endl; 
}
int main(int argc, char **argv)
{


	//INITIALIZATION
    ros::init(argc, argv, "sprial");
    ros::NodeHandle n;
    ros::NodeHandle pn("~");
    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    //ros::Subscriber sub = n.subscribe("/turtle1/cmd_vel", 1000, cmdCallback);
    //ros::Subscriber subcolor = n.subscribe("/turtle1/color_sensor", 1000, colorCallback);

    //DECLARATIONS
    double theta;
    double speed;
    double rate;
    const double CENTER = 5.5444; //initial location = 5.5444
	geometry_msgs::Twist cmdvel_msg;

    //PARAMETERS
    //std::string someString;
    //n.param<std::string>("my_param", someString, "DEFAULT"); //template
    pn.param<double>("theta", theta, 2); //theta parameter
    pn.param<double>("speed", speed, 5); //speed parameter
    pn.param<double>("rate", rate, 100); //rate parameter
    /*std::cout << "speed " << speed << std::endl;
    std::cout << "theta " << theta << std::endl;
    std::cout << "rate " << rate << std::endl;*/
    //ros::Rate loop_rate(10)
    ros::Rate loop_rate(rate);
    cmdvel_msg.linear.x = speed;
    
    //PUBLISHERS
    ros::Publisher cmdvel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
     //SUBSCRIBERS
    ros::Subscriber pose_sub = n.subscribe("turtle1/pose", 1000,poseCallback);
    
    while (ros::ok())
    {    
     	loop_rate.sleep();
        ros::spinOnce();
        cmdvel_msg.linear.x = speed; 
        //std::cout << "linear.x " << speed << std::endl;
        //std::cout << "angular.z " << theta << std::endl;
        cmdvel_msg.angular.z = pow((turtlePose_x - CENTER), 2.0);
        cmdvel_msg.angular.z += pow((turtlePose_y - CENTER), 2.0);
        cmdvel_msg.angular.z = sqrt(cmdvel_msg.angular.z);
        cmdvel_msg.angular.z *= theta;
        //cmdvel_msg.angular.z -= turtlePose_theta;
        //cmdvel_msg.angular.z *= rate;
        /*std::cout <<  "cmdvel.linear " << cmdvel_msg.linear.x << std::endl;
        std::cout << "cmdvel.angular " << cmdvel_msg.angular.z << std::endl;
        std::cout << "turtlePose_x " << turtlePose_x << std::endl;
        std::cout << "turtlePose_y " << turtlePose_y << std::endl;*/
        //cmdvel_msg.angular.z -= turtlePose_theta;
        //cmdvel_msg.angular.z = (sqrt(pow(turtlePose_x - CENTER,2) + pow(turtlePose_y - CENTER, 2))*theta - turtlePose_theta)*rate;
	    cmdvel_pub.publish(cmdvel_msg);
        //loop_rate.sleep();
        //ros::spinOnce();
    }

    return 0;


}

