/*
 * endorCognition.hpp
 *
 *  Created on: Jun 16, 2016
 *      Author: Kourosh Darvish
 */

#include <iostream>
#include <stdio.h>
#include <std_msgs/Char.h>
#include <std_msgs/String.h>
//#include "/opt/ros/indigo/include/sensor_msgs/JointState.h"
#include <string>
#include <iterator>
#include <sstream>
#include "aograph.h"
#include "aonode.h"

#define RST  "\x1B[0m"
#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define FBLU(x) KBLU x RST
#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define BOLD(x) "\x1B[1m" x RST

using namespace std;

//class AOgraph;

class endorActionClass {
	public:
//variables:
		const int nodeActionList_width;
		const int Number_of_Nodes;
		const int Number_of_Actions;
		const int Number_of_Arms_State;

		string suggested_Node;// the node is suggested should be done by human
		//string sug_Node_Human;// the node is suggested should be done by Robot

		string	solved_Node;			// the node is solved

		string	**node_action_list;
		int		**node_action_flag; // if the action is in a node and (solved:1), (Not Solved: 0), (pending:-1)
		string	**action_list;
		string 	**node_list;
		int 	*node_level; // this should be integer to check which has higher priority.
		string *actionCommand;// size: no of arms


	/*	string	**node_action_list;
		string	**action_list;
		string 	**node_list;
		int 	*node_level; // this should be integer to check which has higher priority.
		int		**node_action_flag; // if the action is in a node and (solved:1), (Not Solved: 0), (pending:-1)
		string *actionCommand;// size: no of arms
*/

		//string solved_Node_Human;	// the node is solved by human
		string solved_action;
		string suggested_action;
		int  actionNumber;
		int node_number;
		bool actionFlag;
		bool nodeFlag;
		string responsible;
		int ambiguity_Number;
		//class functions:

		endorActionClass(int,int,int,int);						//constructor
		void nodeActionListFunction (void);				//the list actions should be done by each node
		void ActionListFunction(void);					// each action should do what and who should do that.
		void nodeListFunction(void);
		void humanActionSearch(string,AOgraph&);
		void robStopFunction(void);
		~endorActionClass();
		//string graphName2="screwing_task";
		//AOgraph mygraph_EA;

	private:
		int cc;
		int suggested_node_number, suggested_action_number;

};

