
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << "initialize publish number" << endl;

  ros::init(argc, argv, "number_pub3");
  ros::NodeHandle n;

  ros::Publisher chatter_pub3 = n.advertise<std_msgs::Int32>("/number_3", 1000);

  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {

    std_msgs::Int32 msg;
    // number data
    msg.data = 5;
    chatter_pub3.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
