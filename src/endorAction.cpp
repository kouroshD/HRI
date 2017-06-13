/*

 * endorAction.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: Kourosh Darvish
 */
#include "endorAction.hpp"

endorActionClass::endorActionClass(int nodeActionList_width1,int Number_of_Arms1, string action_definition_path, string hyperArc_action_path):
nodeActionList_width(nodeActionList_width1),Number_of_Arms_State(Number_of_Arms1){

	string delim_type=" ";
    Read_2D_TXT_FILE(hyperArc_action_path,delim_type,Node_action_list);
    Read_2D_TXT_FILE(action_definition_path,delim_type,Action_DEF_list);

    Number_of_Actions=Action_DEF_list.size();
    Number_of_Nodes=Node_action_list.size();

    int size=0;
    for (int r=0;r<Number_of_Nodes;r++){
    	size=Node_action_list[r].size()-2; // First column is node names, second column is seq/nonseq, from third row the actions are written.
    	std::vector<int> Node_action(size,0);
    	Node_action_flag.push_back(Node_action);
    	Number_of_Action_For_Each_Node.push_back(size);
    }

    for (int m=0;m<Number_of_Nodes;m++){
    	if (Node_action_flag[m].size()>0){
    		for(int n=0;n<Node_action_flag[m].size();n++){
    			cout<<Node_action_flag[m][n]<<" ";
    		}
    		cout<<endl;
    	}
    	else
    		cout<<"EMPTY"<<endl;
    }



	actionCommand=new string [Number_of_Arms_State];
//	node_level=new int [Number_of_Nodes];
//	node_list=new string* [Number_of_Nodes];
//	for (int i1=0;i1<Number_of_Nodes;i1++)
//		node_list[i1]=new string [2];

	node_action_list=new string* [Number_of_Nodes];
	node_action_flag=new int* [Number_of_Nodes];

	for (int i1=0;i1<Number_of_Nodes;i1++)
	{
		node_action_list[i1]=new string [ nodeActionList_width];
		node_action_flag[i1]=new int[nodeActionList_width];
	}

//	Action_DEF_list=new string* [Number_of_Actions];
//	for (int i1=0;i1<Number_of_Actions;i1++)
//		Action_DEF_list[i1]=new string [Number_of_Arms_State+2];// first column: action name, 2nd: resposible, other columns, each arm command.

	for (int i1=0;i1<Number_of_Arms_State;i1++)
		actionCommand[i1]	="0";

	suggested_Node	="0";
	solved_Node		="0";
	solved_action	="0";
	suggested_action="0";
	responsible		="0";
	actionNumber	=-1;
	node_number		=0;
	actionFlag		=true;
	nodeFlag		=true;

	suggested_node_number=0;
	suggested_action_number=0;
	ambiguity_Number=0;

	// S: Sequential, F:Flexible
//	node_list[0][0]	="screwedPlate_finalPos";			node_list[0][1]="S";
//	node_list[1][0]	="driver_finalPos";					node_list[1][1]="S";
//	node_list[2][0]	="plate_screw_driver_screwPos";		node_list[2][1]="S";
//	node_list[3][0]	="plate_screw_screwPos1";			node_list[3][1]="S";
//	node_list[4][0]	="plate_screwPos";					node_list[4][1]="S";
//	node_list[5][0]	="plate_screw_initialPos";			node_list[5][1]="S";
//	node_list[6][0]	="plate_initialPos";				node_list[6][1]="S";
//	node_list[7][0]	="screw_initialPos";				node_list[7][1]="S";
//	node_list[8][0]	="driver_initialPos";				node_list[8][1]="S";
//	node_list[9][0]	="plate_screw_screwPos2";			node_list[9][1]="S";

//	node_level[0]=6;
//	node_level[1]=5;
//	node_level[2]=4;
//	node_level[3]=3;
//	node_level[4]=2;
//	node_level[5]=1;
//	node_level[6]=0;
//	node_level[7]=0;
//	node_level[8]=0;
//	node_level[9]=3;

//	node_action_list[0][0]="UnGraspRight";		node_action_list[0][1]="HandOverRightPoint6";	node_action_list[0][2]="HandOverLeftPoint7";		node_action_list[0][3]="UnGraspLeft";			node_action_list[0][4]="HandOver2InitialPos";		node_action_list[0][5]="0";						node_action_list[0][6]="0";					node_action_list[0][7]="0";						node_action_list[0][8]="0";
//	node_action_list[0][0]="UnGraspRight";		node_action_list[0][1]="HandOverRightPoint6";	node_action_list[0][2]="HandOverLeftPoint7";		node_action_list[0][3]="HandOverLeftPoint8";	node_action_list[0][4]="UnGraspLeft";				node_action_list[0][5]="HandOver2InitialPos";	node_action_list[0][6]="0";					node_action_list[0][7]="0";						node_action_list[0][8]="0";
	node_action_list[0][0]="UnGraspRight";		node_action_list[0][1]="HandOverLeftPoint7";	node_action_list[0][2]="HandOverLeftPoint8";		node_action_list[0][3]="UnGraspLeft";			node_action_list[0][4]="HandOver2InitialPos";		node_action_list[0][5]="0";						node_action_list[0][6]="0";					node_action_list[0][7]="0";						node_action_list[0][8]="0";
	node_action_list[1][0]="PutDown";			node_action_list[1][1]="StopRobot";				node_action_list[1][2]="0";							node_action_list[1][3]="0";						node_action_list[1][4]="0";							node_action_list[1][5]="0";						node_action_list[1][6]="0";					node_action_list[1][7]="0";						node_action_list[1][8]="0";
	node_action_list[2][0]="PickUp";			node_action_list[2][1]="Screwing";				node_action_list[2][2]="0";							node_action_list[2][3]="0";						node_action_list[2][4]="0";							node_action_list[2][5]="0";						node_action_list[2][6]="0";					node_action_list[2][7]="0";						node_action_list[2][8]="0";
	node_action_list[3][0]="PickUp";			node_action_list[3][1]="PutDown";				node_action_list[3][2]="0"; 						node_action_list[3][3]="0";						node_action_list[3][4]="0";							node_action_list[3][5]="0";						node_action_list[3][6]="0";					node_action_list[3][7]="0";						node_action_list[3][8]="0";
//	node_action_list[4][0]="UnGrasp";			node_action_list[4][1]="HandOver2InitialPos";	node_action_list[4][2]="HandOverRightPoint1";		node_action_list[4][3]="HandOverRightPoint2";	node_action_list[4][4]="GraspRight"; 				node_action_list[4][5]="HandOverRightPoint3";	node_action_list[4][6]="HandOverPoint4";	node_action_list[4][7]="HandOverLeftPoint5"; 	node_action_list[4][8]="GraspLeft";
	node_action_list[4][0]="UnGrasp";			node_action_list[4][1]="HandOverRightPoint1";	node_action_list[4][2]="HandOverRightPoint2";		node_action_list[4][3]="GraspRight"; 			node_action_list[4][4]="HandOverRightPoint3";		node_action_list[4][5]="HandOverPoint4";		node_action_list[4][6]="HandOverLeftPoint5";node_action_list[4][7]="GraspLeft";				node_action_list[4][8]="BimanKeepPlate";
	node_action_list[5][0]="PickUp";			node_action_list[5][1]="ScrewingInitial";		node_action_list[5][2]="PutDown";					node_action_list[5][3]="0";						node_action_list[5][4]="0";							node_action_list[5][5]="0";						node_action_list[5][6]="0";					node_action_list[5][7]="0";						node_action_list[5][8]="0";
	node_action_list[6][0]="0";					node_action_list[6][1]="0";						node_action_list[6][2]="0";							node_action_list[6][3]="0";						node_action_list[6][4]="0";							node_action_list[6][5]="0";						node_action_list[6][6]="0";					node_action_list[6][7]="0";						node_action_list[6][8]="0";
	node_action_list[7][0]="HoldOn";			node_action_list[7][1]="ObstacleAvoidanceTask";	node_action_list[7][2]="0";							node_action_list[7][3]="0";						node_action_list[7][4]="0";							node_action_list[7][5]="0";						node_action_list[7][6]="0";					node_action_list[7][7]="0";						node_action_list[7][8]="0";
	node_action_list[8][0]="0";					node_action_list[8][1]="0";						node_action_list[8][2]="0";							node_action_list[8][3]="0";						node_action_list[8][4]="0";							node_action_list[8][5]="0";						node_action_list[8][6]="0";					node_action_list[8][7]="0";						node_action_list[8][8]="0";
	node_action_list[9][0]="UnGrasp";			node_action_list[9][1]="HandOver2InitialPos";	node_action_list[9][2]="HandOverRightPoint1";		node_action_list[9][3]="HandOverRightPoint2";	node_action_list[9][4]="GraspRight"; 				node_action_list[9][5]="HandOverRightPoint3";	node_action_list[9][6]="HandOverPoint4";	node_action_list[9][7]="HandOverLeftPoint5"; 	node_action_list[9][8]="GraspLeft";

	//node_action_list[5][0]	="plate_screw_initialPos";			node_action_list[5][1]="S";				node_action_list[5][2]="PickUp";							node_action_list[5][3]="PutDown";				node_action_list[5][4]="0";							node_action_list[5][5]="0";						node_action_list[5][6]="0";							node_action_list[5][7]="0";						node_action_list[5][8]="0";
	// each of node, has a flag, done=true or not Done=false:
	for (int g1=0;g1<Number_of_Nodes;g1++)
		for (int g2=0; g2<nodeActionList_width;g2++)
			node_action_flag[g1][g2]=0;


	//	action_list[:][2]: Left Arm (arm_index=0)  ; action_list[:][3]: Right Arm (arm_index=1)
	// now H: just have first command because of one watch, later can increase.
//	action_list[0][0]	="PickUp";						action_list[0][1]	="H";	action_list[0][2]	="PickUp";														action_list[0][3]	="0";
//	action_list[1][0]	="Screwing";					action_list[1][1]	="H";	action_list[1][2]	="Screwing";													action_list[1][3]	="0";
//	action_list[2][0]	="PutDown";						action_list[2][1]	="H";	action_list[2][2]	="PutDown";														action_list[2][3]	="0";
//	action_list[3][0]	="GraspLeft";					action_list[3][1]	="R";	action_list[3][2]	="closeGrip left";												action_list[3][3]	="0";
//	action_list[4][0]	="GraspRight";					action_list[4][1]	="R";	action_list[4][2]	="0";															action_list[4][3]	="closeGrip right";
//	action_list[5][0]	="UnGraspLeft";					action_list[5][1]	="R";	action_list[5][2]	="openGrip left";												action_list[5][3]	="0";
//	action_list[6][0]	="UnGraspRight";				action_list[6][1]	="R";	action_list[6][2]	="0";															action_list[6][3]	="openGrip right";
//	action_list[7][0]	="HoldOnLeft";					action_list[7][1]	="R";	action_list[7][2]	="holdOn left";													action_list[7][3]	="0";
//	action_list[8][0]	="HoldOnRight";					action_list[8][1]	="R";	action_list[8][2]	="0";															action_list[8][3]	="holdOn right";
//	action_list[9][0]	="HoldOffLeft";					action_list[9][1]	="R";	action_list[9][2]	="stopArm left";												action_list[9][3]	="0";
//	action_list[10][0]	="HoldOffRight";				action_list[10][1]	="R";	action_list[10][2]	="0";															action_list[10][3]	="stopArm right";
//	action_list[11][0]	="HandOverRightPoint1";			action_list[11][1]	="R";	action_list[11][2]	="0";															action_list[11][3]	="jointPos right  0.756 -0.341 -0.280 0.753 0.251 1.163 0.686";
//	action_list[12][0]	="HandOverRightPoint2";			action_list[12][1]	="R";	action_list[12][2]	="0";															action_list[12][3]	="jointPos right 0.620 -0.018 -0.069 0.267 0.115 1.328 0.749";
//	action_list[13][0]	="HandOverRightPoint3";			action_list[13][1]	="R";	action_list[13][2]	="0";															action_list[13][3]	="jointPos right  0.725 -0.391 -0.280 0.753 0.251 1.163 0.686";
//	action_list[14][0]	="HandOverPoint4";				action_list[14][1]	="R";	action_list[14][2]	="jointPos left -0.517 -0.137 -0.020 0.133 -1.414 1.672 -1.628";action_list[14][3]	="jointPos right +0.611 0 0 0 1.571 1.658 1.571";
//	action_list[15][0]	="HandOverLeftPoint5";			action_list[15][1]	="R";	action_list[15][2]	="jointPos left -0.611 0 0 0.05 -1.571 1.658 -1.571";				action_list[15][3]	="0";
//	action_list[16][0]	="HandOverRightPoint6";			action_list[16][1]	="R";	action_list[16][2]	="0";															action_list[16][3]	="jointPos right 0.419 -0.074 -0.016 0.080 1.521 1.649 1.477";
//	action_list[17][0]	="PickUp_2_Plate_Init_Pos";		action_list[17][1]	="H";	action_list[17][2]	="PickUp Screw To plate Initial Position";						action_list[17][3]	="0";
//	action_list[18][0]	="ScrewingInitial";				action_list[18][1]	="H";	action_list[18][2]	="ScrewingInitial";												action_list[18][3]	="0";
//	action_list[19][0]	="PutDown_hand_2_Resting";		action_list[19][1]	="H";	action_list[19][2]	="Put Down Your Hand In Resting Position";						action_list[19][3]	="0";
//	action_list[20][0]	="HandOver2InitialPos";			action_list[20][1]	="R";	action_list[20][2]	="jointPos left -0.084 -1.006 -1.188 1.947 0.668 1.028 -0.502";	action_list[20][3]	="jointPos right 0.093 -0.983 1.142 1.885 -0.591 1.042 0.53";
//	action_list[21][0]	="HandOverLeftPoint7";			action_list[21][1]	="R";	action_list[21][2]	="jointPos left -0.706 0.360 0.054 0.166 -1.490 -0.225 -1.806";	action_list[21][3]	="0";
//	action_list[22][0]	="Grasp";						action_list[22][1]	="R";	action_list[22][2]	="grasp 0"; 													action_list[22][3]	="grasp 1";
//	action_list[23][0]	="UnGrasp";						action_list[23][1]	="R";	action_list[23][2]	="unGrasp 0"; 													action_list[23][3]	="unGrasp 1";
//	action_list[24][0]	="HoldOn";						action_list[24][1]	="R";	action_list[24][2]	="holdOn 0";													action_list[24][3]	="holdOn 1";
//	action_list[25][0]	="StopRobot";						action_list[25][1]	="R";	action_list[25][2]	="stop 0";														action_list[25][3]	="stop 1";
//	Action_DEF_list[0][0]	="PickUp";						Action_DEF_list[0][1]	="H";	Action_DEF_list[0][2]	="PickUp";									Action_DEF_list[0][3]	="0"; 							Action_DEF_list[0][4]	="0";
//	Action_DEF_list[1][0]	="Screwing";					Action_DEF_list[1][1]	="H";	Action_DEF_list[1][2]	="Screwing";								Action_DEF_list[1][3]	="0"; 							Action_DEF_list[1][4]	="0";
//	Action_DEF_list[2][0]	="PutDown";						Action_DEF_list[2][1]	="H";	Action_DEF_list[2][2]	="PutDown";									Action_DEF_list[2][3]	="0"; 							Action_DEF_list[2][4]	="0";
//	Action_DEF_list[3][0]	="GraspLeft";					Action_DEF_list[3][1]	="R";	Action_DEF_list[3][2]	="grasp left";								Action_DEF_list[3][3]	="0"; 							Action_DEF_list[3][4]	="0";
//	Action_DEF_list[4][0]	="GraspRight";					Action_DEF_list[4][1]	="R";	Action_DEF_list[4][2]	="0";										Action_DEF_list[4][3]	="grasp right"; 				Action_DEF_list[4][4]	="0";
//	Action_DEF_list[5][0]	="UnGraspLeft";					Action_DEF_list[5][1]	="R";	Action_DEF_list[5][2]	="unGrasp left";							Action_DEF_list[5][3]	="0"; 							Action_DEF_list[5][4]	="0";
//	Action_DEF_list[6][0]	="UnGraspRight";				Action_DEF_list[6][1]	="R";	Action_DEF_list[6][2]	="0";										Action_DEF_list[6][3]	="unGrasp right"; 				Action_DEF_list[6][4]	="0";
//	Action_DEF_list[7][0]	="HandOverLeftPoint8";			Action_DEF_list[7][1]	="R";	Action_DEF_list[7][2]	="pointReach left 8";						Action_DEF_list[7][3]	="0"; 							Action_DEF_list[7][4]	="0";
//	Action_DEF_list[8][0]	="HoldOnRight";					Action_DEF_list[8][1]	="R";	Action_DEF_list[8][2]	="0";										Action_DEF_list[8][3]	="holdOn right"; 				Action_DEF_list[8][4]	="0";
//	Action_DEF_list[9][0]	="StopLeft";					Action_DEF_list[9][1]	="R";	Action_DEF_list[9][2]	="stop left";								Action_DEF_list[9][3]	="0"; 							Action_DEF_list[9][4]	="0";
//	Action_DEF_list[10][0]	="StopRight";					Action_DEF_list[10][1]	="R";	Action_DEF_list[10][2]	="0";										Action_DEF_list[10][3]	="stop right"; 					Action_DEF_list[10][4]	="0";
//	Action_DEF_list[11][0]	="HandOverRightPoint1";			Action_DEF_list[11][1]	="R";	Action_DEF_list[11][2]	="0";										Action_DEF_list[11][3]	="pointReach right 0"; 			Action_DEF_list[11][4]	="0";
//	Action_DEF_list[12][0]	="HandOverRightPoint2";			Action_DEF_list[12][1]	="R";	Action_DEF_list[12][2]	="0";										Action_DEF_list[12][3]	="pointReach right 1"; 			Action_DEF_list[12][4]	="0";
//	Action_DEF_list[13][0]	="HandOverRightPoint3";			Action_DEF_list[13][1]	="R";	Action_DEF_list[13][2]	="0";										Action_DEF_list[13][3]	="pointReach right 2"; 			Action_DEF_list[13][4]	="0";
//	Action_DEF_list[14][0]	="HandOverPoint4";				Action_DEF_list[14][1]	="R";	Action_DEF_list[14][2]	="pointReach left 3";						Action_DEF_list[14][3]	="pointReach right 4"; 			Action_DEF_list[14][4]	="0";
//	Action_DEF_list[15][0]	="HandOverLeftPoint5";			Action_DEF_list[15][1]	="R";	Action_DEF_list[15][2]	="pointReach left 5";						Action_DEF_list[15][3]	="0"; 							Action_DEF_list[15][4]	="0";
//	Action_DEF_list[16][0]	="HandOverRightPoint6";			Action_DEF_list[16][1]	="R";	Action_DEF_list[16][2]	="0";										Action_DEF_list[16][3]	="pointReach right 6"; 			Action_DEF_list[16][4]	="0";
//	Action_DEF_list[17][0]	="PickUp_2_Plate_Init_Pos";		Action_DEF_list[17][1]	="H";	Action_DEF_list[17][2]	="PickUp Screw To plate Initial Position";	Action_DEF_list[17][3]	="0"; 							Action_DEF_list[17][4]	="0";
//	Action_DEF_list[18][0]	="ScrewingInitial";				Action_DEF_list[18][1]	="H";	Action_DEF_list[18][2]	="ScrewingInitial";							Action_DEF_list[18][3]	="0"; 							Action_DEF_list[18][4]	="0";
//	Action_DEF_list[19][0]	="PutDown_hand_2_Resting";		Action_DEF_list[19][1]	="H";	Action_DEF_list[19][2]	="Put Down Your Hand In Resting Position";	Action_DEF_list[19][3]	="0"; 							Action_DEF_list[19][4]	="0";
//	Action_DEF_list[20][0]	="HandOver2InitialPos";			Action_DEF_list[20][1]	="R";	Action_DEF_list[20][2]	="pointReach left 10";						Action_DEF_list[20][3]	="pointReach right 9"; 			Action_DEF_list[20][4]	="0";
//	Action_DEF_list[21][0]	="HandOverLeftPoint7";			Action_DEF_list[21][1]	="R";	Action_DEF_list[21][2]	="pointReach left 7";						Action_DEF_list[21][3]	="0"; 							Action_DEF_list[21][4]	="0";
//	Action_DEF_list[22][0]	="Grasp";						Action_DEF_list[22][1]	="R";	Action_DEF_list[22][2]	="grasp left"; 								Action_DEF_list[22][3]	="grasp right"; 				Action_DEF_list[22][4]	="0";
//	Action_DEF_list[23][0]	="UnGrasp";						Action_DEF_list[23][1]	="R";	Action_DEF_list[23][2]	="unGrasp left"; 							Action_DEF_list[23][3]	="unGrasp right"; 				Action_DEF_list[23][4]	="0";
//	Action_DEF_list[24][0]	="HoldOn";						Action_DEF_list[24][1]	="R";	Action_DEF_list[24][2]	="holdOn left";								Action_DEF_list[24][3]	="holdOn right"; 				Action_DEF_list[24][4]	="0";
//	Action_DEF_list[25][0]	="StopRobot";					Action_DEF_list[25][1]	="R";	Action_DEF_list[25][2]	="stop left";								Action_DEF_list[25][3]	="stop right"; 					Action_DEF_list[25][4]	="0";
//	Action_DEF_list[26][0]	="ObstacleAvoidanceTask";		Action_DEF_list[26][1]	="R";	Action_DEF_list[26][2]	="0";										Action_DEF_list[26][3]	="0"; 							Action_DEF_list[26][4]	="obstacleAvoidanceTask biMan";
//	Action_DEF_list[27][0]	="BimanKeepPlate";				Action_DEF_list[27][1]	="R";	Action_DEF_list[27][2]	="0";										Action_DEF_list[27][3]	="0"; 							Action_DEF_list[27][4]	="pointReach biMan 11";

//	obstacleAvoidanceTask
}
void endorActionClass::nodeListFunction(void){
	// search for the node number we should solve: (endorClass-endorAction)
	if (solved_Node=="plate_screwPos" && suggested_Node=="plate_screw_screwPos")
		suggested_Node="plate_screw_screwPos1";
	else if (solved_Node=="plate_screw_initialPos" && suggested_Node=="plate_screw_screwPos")
		suggested_Node="plate_screw_screwPos2";

	for(int i=0;i<Number_of_Nodes;i++)
			if (Node_action_list[i][0]==suggested_Node)
				node_number=i;
		nodeFlag=true;
		actionFlag=false;
}

void endorActionClass::nodeActionListFunction(void){

	/* when the last action of a node is done OR number of actions in a node list is zero ->
		The node is solved, so do not check for next action*/
	if (actionNumber==(Number_of_Action_For_Each_Node[node_number]-1) || Number_of_Action_For_Each_Node[node_number]==0 )
	{
		solved_Node=Node_action_list[node_number][0];

		if (solved_Node=="plate_screw_screwPos1" || solved_Node=="plate_screw_screwPos2")
			solved_Node="plate_screw_screwPos";

		actionFlag=true; /* we should have this action change here otherwise it
							will go	inside next if condition which it should not go */
		nodeFlag=false;
		actionNumber=-1;
	}
	/* 	Check for the action Human/Robot should perform:
		also here we should have the if cond, because in case prev if is correct,
			then we should not check for next element*/
	if (actionFlag==false)
	{
		actionNumber=actionNumber+1;
		suggested_action=Node_action_list[node_number][actionNumber+2];

		if (actionNumber>0 && Node_action_flag[node_number][actionNumber-1]==0)
			cout<<FRED("Previous action in this node is not solved")<<endl;
		///		actionFlag=true;
		// when we reach "0" actions, it means we reach the requested node.
		///DEL
		if (suggested_action=="0")
		{
			solved_Node=Node_action_list[node_number][0];
			if (solved_Node=="plate_screw_screwPos1" || solved_Node=="plate_screw_screwPos2")
				solved_Node="plate_screw_screwPos";

			//cout<<"***************** solved_Node2: "<<solved_Node<<endl;
///			actionFlag=true;
			nodeFlag=false;
			actionNumber=-1;
		}
	}
	actionFlag=true;

}
void endorActionClass::ActionListFunction(void){

	// check for the action in action list and who should do that:
		for(int i=0;i<Number_of_Actions;i++)
			if (Action_DEF_list[i][0]==suggested_action)
			{
				responsible=Action_DEF_list[i][1];
				for (int j=0;j<Number_of_Arms_State;j++){
				actionCommand[j]=Action_DEF_list[i][2+j];
				}
			}
}


void endorActionClass::humanActionSearch(string human_action_name, AOgraph& mygraph_EA ){
	ambiguity_Number=0;
	int j;
				// check feasible and not solved nodes  --> vector of node names,
				// last node-action cannot happen because all actions related to Robot.
	for (int i=0;i<Number_of_Nodes-1;i++) // -1 Because the number of nodes in the file are one more than the number of nodes in the AO Graph.
	{
		// 1- check for all the feasible and not-solved nodes:
		if (mygraph_EA.NodeFeasibiltyInfo(i)==1 && mygraph_EA.NodeSolveInfo(i)==0)
		{
//			cout<<"z: "<<i<<endl;
			if (Node_action_list[i][1]=="Seq" && Number_of_Action_For_Each_Node[i]>0)
			{
				j=0;
				do
				{
					if (Node_action_list[i][j+2]==human_action_name && Node_action_flag[i][j]==0)
					{
						ambiguity_Number++;
						suggested_node_number=i;
						suggested_action_number=j;//+2
						Node_action_flag[i][j]=-1;
//						cout<<"***** "<<mygraph_EA.NodeNameInfo(zz)<<" *****"<<endl;
//						cout<<"obj_nodeAction.node_action_list[zz][cc]"<<node_action_list[zz][cc]<<endl;
//						cout<<"obj_cognition.cognitionHMP_get()"<<human_action_name<<endl;
//						cout<<"obj_nodeAction.node_action_flag[zz][cc]"<<node_action_flag[zz][cc]<<endl;
//						cout<<"ambiguity_Number"<<ambiguity_Number<<endl;
						break;
					}
//					cout<<"*** "<<mygraph_EA.NodeNameInfo(zz)<<" ***"<<endl;
//					cout<<"obj_nodeAction.node_action_list[zz][cc]"<<node_action_list[zz][cc]<<endl;
//					cout<<"obj_cognition.cognitionHMP_get()"<<human_action_name<<endl;
//					cout<<"obj_nodeAction.node_action_flag[zz][cc]"<<node_action_flag[zz][cc]<<endl;
//					cout<<"ambiguity_Number"<<ambiguity_Number<<endl;
					j++;
				}
				while( ( Node_action_flag[i][j-1]==1 || Node_action_flag[i][j-1]==-1) && j <Number_of_Action_For_Each_Node[i]); //node_action_list[i][j]!="0" &&
							// next action not be "0", and this action flag be 1 to go forward.
			}

			else if (Node_action_list[i][1]=="nonSeq" && Number_of_Action_For_Each_Node[i]>0)
			{
//				cout<<mygraph_EA.NodeNameInfo(i)<<"\t";
//				j=0;
//				do
//				{
//					if (node_action_list[i][j]==human_action_name)
//					{	ambiguity_Number++;
//						break;
//					}
//					j++;
//				}
//				while( node_action_list[i][j]!="0" && j <Number_of_Action_For_Each_Node[i]);
			}
		}
	}

//=============================================================================================
	if (ambiguity_Number==1)
	{
		//&& obj_cognition.cognitionHMP_get()==obj_nodeAction.actionCommand[0]
		if (node_number==suggested_node_number )
		{
			cout<<"ambiguity_Number: "<<ambiguity_Number<<endl;
			cout<<FGRN("Human Is Following the Path")<<endl;
			//** these should be the same & action check has been done before, not necessary again!
			// it is suppossed that each action name is unique in each row of node_action_list.
			//obj_nodeAction.node_number=suggested_node_number;
			//obj_nodeAction.actionNumber=suggested_action_number;
			///Human_Gesture_Flag=true;
			Node_action_flag[suggested_node_number][suggested_action_number]=1;
			actionFlag=false;
		}
		else if (node_number!=suggested_node_number)
		{
			/* make zero all the actions flag done on node_number now before changing the value of node_number,
			because we are changing the path here */
			for (int i=0;i<Number_of_Action_For_Each_Node[node_number];i++)
				Node_action_flag[node_number][i]=0;

			cout<<FBLU("Human Is Not Following Optimal Path")<<endl;
			///Human_Gesture_Flag=true;
			node_number=suggested_node_number;
			actionNumber=suggested_action_number;
			Node_action_flag[suggested_node_number][suggested_action_number]=1;
			actionFlag=false;
		}
		// send stop robot command.
		// * make the all the "-1" elements of the "node_action_flag" matrix to zero, just the ones in the "node_number" line equal to one
		
		for (int i=0;i<(Number_of_Nodes);i++)// No of hyper arcs again, not the nodes?
			if (Number_of_Action_For_Each_Node[i]>0)
				for (int j=0;j<Number_of_Action_For_Each_Node[i];j++)
					if (Node_action_flag[i][j]==-1 && i!=node_number)
						Node_action_flag[i][j]=0;
					else if (Node_action_flag[i][j]==-1 && i==node_number)
						Node_action_flag[i][j]=1;

	}
	else if (ambiguity_Number==0 && human_action_name!="ScrewingInitial")
	{
		// it means we moved at first (first putDown)
		cout<<FRED("Human Is Moved, No Path, Continue Your Actions Human")<<endl;
		///Human_Gesture_Flag=true;
		///obj_nodeAction.actionFlag=false;???
	}

	else if (ambiguity_Number>1)
	{
		cout<<">>> ambiguity_Number: "<<ambiguity_Number<<endl;
		cout<<FBLU("******************* Ambiguity in Endor  ***********************")<<endl;
		cout<<FBLU("*** Human Continue your Actions Until Ambiguity is Solved!  ***")<<endl;
		if (responsible=="H")
			actionFlag=false;
		// suggest an action from optimal path between the possible ones

	}

}

void endorActionClass::robStopFunction(){
//	responsible		=Action_DEF_list[25][1];
//	for (int j=0;j<Number_of_Arms_State;j++){
//	actionCommand[j]=Action_DEF_list[25][2+j];
//	}
//	actionCommand[0]=action_list[25][2];
//	actionCommand[1]=action_list[25][3];
	for(int i=0;i<Number_of_Actions;i++)
		if (Action_DEF_list[i][0]=="StopRobot"){
			responsible=Action_DEF_list[i][1];
			for (int j=0;j<Number_of_Arms_State;j++){
				actionCommand[j]=Action_DEF_list[i][2+j];
//				actionCommand[1]=action_list[i][3];
			}
		}
}

endorActionClass::~endorActionClass(){

	delete [] actionCommand;
//	delete [] node_level;

	for(int i1=0;i1<Number_of_Nodes;i1++)
	{
//		delete [] node_list[i1];
		delete [] node_action_flag[i1];
		delete [] node_action_list[i1];
	}
//	delete [] node_list;
	delete [] node_action_flag;
	delete [] node_action_list;

//	for(int i1=0;i1<Number_of_Actions;i1++)
//		delete [] Action_DEF_list[i1];
//	delete [] Action_DEF_list;
}


