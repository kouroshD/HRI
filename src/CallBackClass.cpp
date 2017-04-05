/*
 * CallBackClass.cpp
 *
 *  Created on: May 02, 2016
 *      Author: Kourosh Darvish
 */

#include "CallBackClass.hpp"

CallBackClass::CallBackClass(int NoParameterHMP1,int NoOutputHMP1) {

	HMP_cognition_flag			=true;
	HMP_ack_flag				=true;
	HMP_initial_command_flag	=true;
	control_ack_flag[0]			=true;
	control_ack_flag[1]			=true;
	control_ack_flag[2]			=true;

	rec_human_action_flag		=true;

	control_initial_command_flag=true;
	HMP_parameter_cognition_flag=true;
	hri_control_goal_flag[0]	=true;
	hri_control_goal_flag[1]	=true;
	hri_control_goal_flag[2]	=true;
	rob_goal_reach_flag[0]		=true;
	rob_goal_reach_flag[1]		=true;
	rob_goal_reach_flag[2]		=true;

	sub_HMPAck	=nh.subscribe("HMPAck",80, &CallBackClass::HMPAckCallBack, this);
	sub_HMPOut	=nh.subscribe("HMPOutput",1, &CallBackClass::HMPOutputCallBack, this);
	sub_HRecAction	=nh.subscribe("HRecAction",1, &CallBackClass::HRecActionCallBack, this);

	sub_CtrlAck	=nh.subscribe("hri_robot_ack",80, &CallBackClass::RobotAckCallBack, this);
	sub_CtrlOut	=nh.subscribe("controlOutput",1, &CallBackClass::ControlOutputCallBack, this);
//	sub_JntSt	=nh.subscribe("robot/joint_states",1, &CallBackClass::RobotJointStatesCallBack, this);
//	sub_LGrip	=nh.subscribe("robot/end_effector/left_gripper/state",1,&CallBackClass::RobotLeftGripperStatesCallBack, this);
//	sub_RGrip	=nh.subscribe("robot/end_effector/right_gripper/state",1,&CallBackClass::RobotRightGripperStatesCallBack, this);
	NoParameterHMP=NoParameterHMP1;
	parameterHMP=new string [NoParameterHMP];

	for (int ii=0;ii<NoParameterHMP;ii++)
	{	parameterHMP[ii]="0";
	}
	recognized_action_human="0";

	NoOutputHMP=NoOutputHMP1;
	HMPOutput=new float[NoOutputHMP];

	for (int ii=0;ii<NoOutputHMP;ii++)
	{	HMPOutput[ii]=0.0;
	}

}

//	HMP
void CallBackClass::HMPAckCallBack(const std_msgs::String::ConstPtr& msg) {
	ROS_INFO("I heard HMP Ack: [%s]", msg->data.c_str());

	if(HMP_initial_command_flag==false) {
//		cout<< "---------->>>>HMP Initial Flag is: "<<HMP_initial_command_flag<<endl;
		HMP_initial_command_flag=true;
//		cout<< "---------->>>>I changed HMP Initial Flag to: "<<HMP_initial_command_flag<<endl;
	}
	else {

		string MSG=msg-> data.c_str();
		//string parameterHMP[NoParameterHMP];
		istringstream ss (MSG);
		copy(
				istream_iterator <string>(ss),
				istream_iterator <string> (),
				parameterHMP);
//		cout<<"I heard this msg:\t";
//		for (int jj=0; jj<NoParameterHMP;jj++)
//			cout<<"parameterHMP["<<jj<<"]: "<<parameterHMP[jj]<<" \t";
//		cout<<endl;
		// if successful having data change to true, otherwise still be false.
//		cout<< "---------->>>>HMP Ack Flag is: "<<HMP_ack_flag<<endl;
		HMP_ack_flag=true;
		HMP_parameter_cognition_flag=false;// related to HMP-cognition flag;
//		cout<< "---------->>>>I changed the HMP Ack Flag to: "<<HMP_ack_flag<<endl;

	}
}

void CallBackClass::HMPOutputCallBack(const std_msgs::String::ConstPtr& msg) {
	//cout<<"====================================================================="<<endl;
	//ROS_INFO("I heard HMP Output: [%s]", msg->data.c_str());
	string MSG=msg-> data.c_str();
	//float
	for (int ii=0;ii<NoOutputHMP;ii++)
	{
		HMPOutput[ii]=0.0;
	}
	istringstream ss (MSG);
	copy(
			istream_iterator <float>(ss),
			istream_iterator <float> (),
			HMPOutput);
	//cout<<"I heard this msg in callback HMP Output:\t";
	//for (int jj=0; jj<NoOutputHMP;jj++)
		//cout<<HMPOutput[jj]<<"\t";
	//cout<<endl;
	HMP_cognition_flag=false;
}

void CallBackClass::HRecActionCallBack(const std_msgs::String::ConstPtr& msg) {
	recognized_action_human=msg-> data.c_str();
	rec_human_action_flag=false;
}
// Control
void CallBackClass::RobotAckCallBack(const std_msgs::String::ConstPtr& msg) {
	ROS_INFO("I heard Control Ack: [%s]", msg->data.c_str());
	string hri_control_ack_msg;
	hri_control_ack_msg=msg->data.c_str();

//	if(control_initial_command_flag==false) {
//		cout<< "---------->>>>Control Initial Flag is: "<<control_initial_command_flag<<endl;
//		cout<< "---------->>>>Control Initial msg: "<<hri_control_ack_msg<<endl;
//		control_initial_command_flag=true;
//		cout<< "---------->>>>I changed Control Initial Flag to: "<<control_initial_command_flag<<endl;

//	}
//	else {
//		cout<< "---------->>>>Control Ack Flag 0 is: "<<control_ack_flag[0]<<endl;
//		cout<< "---------->>>>Control Ack Flag 1 is: "<<control_ack_flag[1]<<endl;
		//hri_control_goal_flag=false;

//		if (hri_control_ack_msg=="hri_control_command_recieved_left"){// maybe can be commented!
//			hri_control_goal_flag[0]=false;
//			control_ack_flag[0]=true;
////			cout<<"control_ack_flag[0]: "<<control_ack_flag[0]<<endl;
////			cout<<"hri_control_goal_flag[0]: "<<hri_control_goal_flag[0]<<endl;
////			cout<<"hri_control_goal_flag[1]: "<<hri_control_goal_flag[1]<<endl;
//
//		}
//		else if (hri_control_ack_msg=="hri_control_command_recieved_right"){// maybe can be commented!
//			hri_control_goal_flag[1]=false;
//			control_ack_flag[1]=true;
//
//		}
		if (hri_control_ack_msg=="GoalReachedLeft")
		{
			rob_goal_reach_flag[0]=false;
			hri_control_goal_flag[0]=true;
		}
		else if (hri_control_ack_msg=="GoalReachedRight")
		{
			rob_goal_reach_flag[1]=false;
			hri_control_goal_flag[1]=true;
		}
		else if (hri_control_ack_msg=="GoalReachedBiManual")
		{
			rob_goal_reach_flag[2]=false;
			hri_control_goal_flag[2]=true;
		}
		else if (hri_control_ack_msg=="RobotTaskReached"){// maybe can be commented!
			control_ack_flag[0]=true;
		}
//	}
}

void CallBackClass::ControlOutputCallBack(const std_msgs::String::ConstPtr& msg) {
//	ROS_INFO("I heard Control Output: [%s]", msg->data.c_str());
}
/*
//	BAXTER
void CallBackClass::RobotJointStatesCallBack(sensor_msgs::JointState stateMsg) {
	///ROS_INFO("I heard Robot Joint States:");
	float jointPositionVectror=stateMsg.position[1];
	///cout<<jointPositionVectror<<endl;
}

void CallBackClass::RobotLeftGripperStatesCallBack(const baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg) {
	///ROS_INFO("I heard Robot Left Gripper States:");
}

void CallBackClass::RobotRightGripperStatesCallBack(const baxter_core_msgs::EndEffectorState::ConstPtr& stateMsg) {
	///ROS_INFO("I heard Robot Right Gripper States:");
}
*/
