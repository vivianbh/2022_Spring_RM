#include "ros/ros.h"
#include <turtlesim/Spawn.h>
#include <turtlesim/Kill.h>
#include <string>
#include <iostream>

using namespace std;


int main(int argc, char **argv)
{
    ros::init(argc, argv, "spawnturtles");
    ros::NodeHandle n;

    // Check if the service is on
    ros::service::waitForService("/turtlesim/spawn");

    // initialize kill turtle service
    ros::ServiceClient client_kill=n.serviceClient<turtlesim::Kill>("/turtlesim/kill");
    turtlesim::Kill kill_name;
    // define parameters in service
    kill_name.request.name = "turtle1";
    // call the service
    client_kill.call(kill_name); 


    // initialize spawn turtle service
    ros::ServiceClient client_spawn = n.serviceClient<turtlesim::Spawn>("turtlesim/spawn");
    turtlesim::Spawn turtle;
 
    // Finish your code, you will need to spawn turtles
	string turtle_name[] = {"Karl", "Abel", "Byron", "Magee"}; 
	// sizeof: get memory size 
	// --> sizeof(turle_name)=4 bits*4 strings
	// --> sizeof(turtle_name[0])=4 bits*1 string
	size_t turtle_num = sizeof(turtle_name) / sizeof(turtle_name[0]);

    for (int i = 0; i < turtle_num; i++){
    	turtle.request.x = 2*(i+1);
    	turtle.request.y = 2*(i+1);
    	turtle.request.theta = 0;
    	turtle.request.name = turtle_name[i];

		client_spawn.call(turtle);
    }

}
