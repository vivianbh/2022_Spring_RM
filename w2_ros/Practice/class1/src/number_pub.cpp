
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;
std_msgs::Int32 msg;


int main(int argc, char **argv)
{
  cout << "initialize publish number" << endl;

  // you should rename your node and topic to avoid confliction
  ros::init(argc, argv, "number_pub_4");
  ros::NodeHandle n;
  ros::Publisher chatter_pub4 = n.advertise<std_msgs::Int32>("/number_4", 1000);
  ros::Rate loop_rate(10);


  while (ros::ok())
  {

    // Publish number data here

    msg.data = 5;
    ROS_INFO("msg: %d", msg.data);
    
    chatter_pub4.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
