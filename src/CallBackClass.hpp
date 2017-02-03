/*
 * HMPClass.hpp
 *
 *  Created on: May 2, 2016
 *      Author: Kourosh Darvish
 */

#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

class CallBackClass {
	public:
		bool HMP_ack_flag;
		bool HMP_cognition_flag;
		bool HMP_initial_command_flag;
		bool control_ack_flag[2];		// when we publish a control cmnd msg until receive a response this will be false.
		bool control_initial_command_flag;
		bool HMP_parameter_cognition_flag;
		bool hri_control_goal_flag [2];// 2 arms, flag is false when correct goal is received by controller and the robot is not recieved the goal
		bool rob_goal_reach_flag[2];//2 arms, flag is false when robot reaches goal, otherwise is true, then we check for the next action in endor-action
		bool rob_stop_reach_flag[2];
		bool rec_human_action_flag;
		string recognized_action_human;
		int NoParameterHMP;
		//int NoParameterCtrl;
		// int  parameterCtrl;
		int NoOutputHMP;// Number of outputs
		float* HMPOutput;
		string* parameterHMP;

		CallBackClass(int,int);
		void HMPAckCallBack(const std_msgs::String::ConstPtr& msg1); 	//(DEL)
		void HMPOutputCallBack(const std_msgs::String::ConstPtr& msg2); //(DEL)
		void HRecActionCallBack(const std_msgs::String::ConstPtr& msg3);


		void ControlAckCallBack(const std_msgs::String::ConstPtr& msg1);
		void ControlOutputCallBack(const std_msgs::String::ConstPtr& msg2);
/*
		void RobotJointStatesCallBack(sensor_msgs::JointState stateMsg);
		void RobotLeftGripperStatesCallBack(const baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg);
		void RobotRightGripperStatesCallBack(const baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg);
*/

	private:
		ros::NodeHandle nh;
		ros::Subscriber sub_HMPAck;
		ros::Subscriber sub_HMPOut;
		ros::Subscriber sub_HRecAction;
		ros::Subscriber sub_CtrlAck;
		ros::Subscriber sub_CtrlOut;
		ros::Subscriber sub_JntSt;
		ros::Subscriber sub_LGrip;
		ros::Subscriber sub_RGrip;



};
