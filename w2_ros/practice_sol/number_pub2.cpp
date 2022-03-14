
#include "ros/ros.h"
#include "std_msgs/Int32.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << "initialize publish number" << endl;

  ros::init(argc, argv, "number_pub2");
  ros::NodeHandle n;

  ros::Publisher chatter_pub2 = n.advertise<std_msgs::Int32>("/number_2", 1000);


  ros::Rate loop_rate(10);
  int count = 0;

  while (ros::ok())
  {

    std_msgs::Int32 msg;
    // number data


    msg.data = 1;
    chatter_pub2.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
