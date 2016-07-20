/*
 * cognitionClass.cpp
 *
 *  Created on: May 31, 2016
 *      Author: Kourosh Darvish
 */
#include "cognitionClass.hpp"

cognitionClass::cognitionClass(int no_hmp_out1){
	NO_OUTPUT_HMP=no_hmp_out1;

/*	array_test=NULL;
	cout<<&array_test<<endl;
	if ( !(array_test=new float[no_hmp_out1*10]))
	{
		cout<<"error of memory!";
		exit(1);
	}
	else
		{
			cout<<"memory works!"<<endl;
			for (int i=0;i<10*no_hmp_out1;i++)
				array_test[i]=i;

			for (int i=0;i<10*no_hmp_out1;i++){
				cout<<array_test[i]<<"\t";
				cout<<&array_test[i]<<"\t";
			}
			cout<<endl;
			exit(1);
		}
*/

	HMP_posib_max=NULL;
	HMP_posib_max_time=NULL;
	max_flag=NULL;
	hmpOutput=NULL;

	HMP_posib_max=new float[NO_OUTPUT_HMP];
	HMP_posib_max_time=new long int[NO_OUTPUT_HMP];
	max_flag=new bool[NO_OUTPUT_HMP];
	hmpOutput=new float[NO_OUTPUT_HMP];		// is it necessary to delete these arrays and having a destructor?
	hmp_ActionsName=new string[NO_OUTPUT_HMP+1];
	percentage_check_max=new float [NO_OUTPUT_HMP];
	HMP_max_element=0;

	for(int i=0; i<NO_OUTPUT_HMP;i++)
	{
		HMP_posib_max[i]=0.0;
		HMP_posib_max_time[i]=0;
		max_flag[i]=true;
		percentage_check_max[i]=0.9;
		hmp_ActionsName[i]="0";
	}
	percentage_check_max[2]=0.95;// put down needs less max_check point!
	hmp_ActionsName[NO_OUTPUT_HMP]="NonOfTheActions";

	last_check_point=-10;// maybe when the program start the first possibily be the highest one!
	prev_max_element=NO_OUTPUT_HMP+10;
	prev_max_value=0;
	min_flag=true;



	percentage_check_min=0.1;

	zero_threshold=1.0e-10;

	HMP_moment_zero_no=0;
	zero_counter=0;
	time_counter=0;


	cognitionHMP_flag=true;
	reasoningHMP_flag=true;
	cog_hmp_ActionNumber=0;
	reas_hmp_ActionNumber=0;
	reas_hmp_previous_ActionNumber=3;// initialization is in resting mode.
	firstAction_flag=true;



///	f = 0.0;
///	kouri1 = NULL;
///	kouri1 = new int(0);
///	cout << "pkouri1 (inside const):" << kouri1 << endl;
///	cout << "kouri1 (inside const):" << *kouri1 << endl;

}

//void cognitionClass::get(float hmpOutput[])
//{

///	cout << "kouri1 (inside get_k):" << kouri1 << endl;
///	cout << "f (inside get_k):" << f << endl;
///	int k = *kouri1;
///	cout << "kouri1 (dopo assegnamento):" << k << endl;
//	return 0;

//}

/*void cognitionClass::cognitionInit (int no_hmp_out1){

	NO_OUTPUT_HMP=no_hmp_out1;
	HMP_max_element=0;

	for(int i=0; i<NO_OUTPUT_HMP;i++)
	{
		HMP_posib_max[i]=0.0;
		HMP_posib_max_time[i]=0;
		max_flag[i]=true;
	}

	last_check_point=0;
	prev_max_element=NO_OUTPUT_HMP+10;
	prev_max_value=0;
	min_flag=true;


	percentage_check_max=0.9;
	percentage_check_min=0.1;

	zero_threshold=1.0e-10;

	HMP_moment_zero_no=0;
	zero_counter=0;
	time_counter=0;
}
*/
//input change to parameter: better computationally.
void cognitionClass::cognitionHMP_set(float hmpOutput1[]) {

	for (int i=0;i<NO_OUTPUT_HMP;i++)
	{
	hmpOutput[i]=hmpOutput1[i];
	}

}
void cognitionClass::cognitionHMP() {

	HMP_moment_zero_no=0;
	time_counter=time_counter+1;

	for ( int j=0; j<NO_OUTPUT_HMP;j++ ){

		// for checking Non of the actions option (all the possibilities are zero)
		if ( hmpOutput[j]< zero_threshold )// make less than 1e-10
			HMP_moment_zero_no=HMP_moment_zero_no+1;
		//--

		// flag for new max_possiblity if it is the same as previous one, in some conditions make the flag false!
		if (j==prev_max_element && hmpOutput[j]>zero_threshold && min_flag==true &&( hmpOutput[j]>=prev_max_value || hmpOutput[j]<=(percentage_check_min*prev_max_value) ) ){
			min_flag=false;
		}
		//--

		// Update the Max Possibilities matrix of HMP until now from previous one
		if (hmpOutput[j]>HMP_posib_max[j] && j!=prev_max_element )
		{
			HMP_posib_max[j]=hmpOutput[j]; 		//new max possibility of action j
			HMP_posib_max_time[j]=time_counter;	// time that the possibility happens.

			// here we check if the max value of new action is bigger than current value of previous action
			if (prev_max_element>NO_OUTPUT_HMP && j!=prev_max_element )
			{
				max_flag[j]=false;
			}
			else if (prev_max_element<NO_OUTPUT_HMP && j!=prev_max_element)
			{
				if (HMP_posib_max[j]>hmpOutput[prev_max_element])
				{
					max_flag[j]=false;
				}
			}
			//--
		}
		else if (  hmpOutput[j]>HMP_posib_max[j] && j==prev_max_element && min_flag==false )
		{
			HMP_posib_max[j]=hmpOutput[j];
			HMP_posib_max_time[j]=time_counter;
		}
		//--

		// find max element of "max possibility vector" in every "time moment and elements"
		if (HMP_posib_max[j]>HMP_posib_max[HMP_max_element])
		{
			HMP_max_element=j;
		}
		//--

		// hmpOutput[j]< (percentage_check*HMP_posib_max[j]:
		//			check for reaching "percentage_check" point after max:
		// hmpOutput[j]!=0:
		//			check if the output is not zero.
		//HMP_max_element!=prev_max_element:
		//			the change in action should happen if we want to publish or do sth
		// j==HMP_max_element:
		//
		//(HMP_max_element==prev_max_element && HMP_posib_max[j]>percentage_check_min*prev_max_value):
			// if we have new maximum like previous action, by saying it should be bigger than the "percentage_check_min*prev_max_value"
			// it is or a high max (more than previous) or new real max but before came less than 10%
			// max possibilty should be higher than 60%
		//cout<<HMP_posib_max[j]<<"\t";
		if (HMP_posib_max[j]>0.7 &&	hmpOutput[j]< (percentage_check_max[j]*HMP_posib_max[j]) && HMP_posib_max_time[j]> (last_check_point+1) &&
				hmpOutput[j]>zero_threshold && j==HMP_max_element &&
				((HMP_max_element!=prev_max_element && max_flag[j]==false)||
						(HMP_max_element==prev_max_element && HMP_posib_max[j]>percentage_check_min*prev_max_value) )  )
		{

			cout<<endl<<"**************************************************************************"<<endl;
			if (HMP_max_element==0)
				cout<<"\"Pick Up\" is Done!"<<endl;
			else if (HMP_max_element==1)
				cout<<"\"Screwing\" is Done!"<<endl;
			else if (HMP_max_element==2)
				cout<<"\"Put Down\" is Done!"<<endl;
			cout<<"j: "<<j<<endl;
			cout<<"prev_max_element: "<<prev_max_element<<endl;
			cout<<"prev_max_value: "<<prev_max_value<<endl;


			cout<<"HMP_posib_max_time:"<<endl;
			for (int k1=0;k1<NO_OUTPUT_HMP;k1++)
				cout<<HMP_posib_max_time[k1]<<endl;

			cout<<"HMP_poib_max:"<<endl;
			for (int k1=0;k1<NO_OUTPUT_HMP;k1++)
				cout<<HMP_posib_max[k1]<<endl;

			cout<<"time_counter: "<<time_counter<<endl;
			//cout<<"time_counter2: "<<time_counter2<<endl;
			cout<<"hmpOutput: "<<endl;
			for (int k1=0;k1<NO_OUTPUT_HMP;k1++)
				cout<<hmpOutput[k1]<<"\t";

			cout<<endl<<"max_flag"<<max_flag[j]<<endl;
			cout<<"min_flag"<<min_flag<<endl;
			cout<<	"last_check_point"<<last_check_point<<endl;
			cout<<"*************************************************************************"<<endl;

			cog_hmp_ActionNumber=HMP_max_element;
			cognitionHMP_flag=false;



			prev_max_element=HMP_max_element;// to not publish several times one action!
			prev_max_value=HMP_posib_max[j];
			last_check_point=time_counter; // next max be after this time(counter!)
			// update all the possibilities now, because later we should check with new max possibilities, not all the time
			//std::fill_n(HMP_posib_max,NoOutputHMP,0);
			for (int k1=0; k1<NO_OUTPUT_HMP;k1++)
			{
			HMP_posib_max[k1]=0.0;		// update these variables ??
			HMP_posib_max_time[k1]=0;	//updtae these variables ??
			max_flag[k1]=true;			// update max flag. it should be a vector, so that the value of another action do not affect the this action
			}
			HMP_max_element=0; //all the "max possibilities vector" are zero then no different!
			min_flag=true;

		}
	}

	// check if all actions possibilities are zero
		//first if is considered to check if the possibilities are continuously are zero, if not make zero_couter to zero!
	if ((HMP_moment_zero_no < NO_OUTPUT_HMP) )
	{
		zero_counter=0;
	}
	else if ((HMP_moment_zero_no==NO_OUTPUT_HMP) )
	{
		zero_counter=zero_counter+1;
	}
	if (zero_counter>5)
	{
		cog_hmp_ActionNumber=NO_OUTPUT_HMP;
		cognitionHMP_flag=false;


//		cout<<"Non of the Actions\n";


		zero_counter=0;

		prev_max_element=NO_OUTPUT_HMP+10;
		prev_max_value=0.0;

		// if we have high possibilities from before, we should make it zero for new coming possibilities:
		for (int k1=0; k1<NO_OUTPUT_HMP;k1++)
		{
			HMP_posib_max[k1]=0.0;
			HMP_posib_max_time[k1]=0;
			max_flag[k1]=true;
		}
		//--

		HMP_max_element=0; //all the "max possibilities vector" are zero then no different!
		min_flag=true;
		/* it is not necessary update, becuase if "non of the actions" happens 100%
		 * 	the time now is at least 5 more than the last_check_point!
		 */

	}

}
void cognitionClass::reasoningHMP(){
	// the sequence of action can not be any order, and some of the sequences are logically wrong.
	// action 0: PickUP;	action 1: Screwing;		action 2: PutDown;		action 3: resting;
	// we are not interested in NON of the actions option, for checking with previous actions.

	// pick up(0) can be done after PutDown(2), or at first:
	//cout<<"I am in reasoning function"<<endl;
	//cout<<"cog_hmp_ActionNumber"<<cog_hmp_ActionNumber<<endl;
	//cout<<"reas_hmp_previous_ActionNumber"<<reas_hmp_previous_ActionNumber<<endl;

	if (cog_hmp_ActionNumber==0 && ( reas_hmp_previous_ActionNumber==2 ||firstAction_flag==true))
	{
		reas_hmp_ActionNumber=cog_hmp_ActionNumber;
		reas_hmp_previous_ActionNumber=cog_hmp_ActionNumber;
		reasoningHMP_flag=false;
		firstAction_flag=false;

	}

	// Screwing can be done after  pickUp (Maybe also screwing but it makes problem in hri):
	if (cog_hmp_ActionNumber==1 && firstAction_flag==false && (reas_hmp_previous_ActionNumber==0 ))
	{
		reas_hmp_ActionNumber=cog_hmp_ActionNumber;
		reas_hmp_previous_ActionNumber=cog_hmp_ActionNumber;
		reasoningHMP_flag=false;

	}

	// PutDown can be done after Screwing,ScrewingInitial, pickUp:
	//&& firstAction_flag==false
	if (cog_hmp_ActionNumber==2 &&(reas_hmp_previous_ActionNumber==0 || reas_hmp_previous_ActionNumber==1 || reas_hmp_previous_ActionNumber==3))
	{
		reas_hmp_ActionNumber=cog_hmp_ActionNumber;
		reas_hmp_previous_ActionNumber=cog_hmp_ActionNumber;
		reasoningHMP_flag=false;

	}

	// ScrewingInitial Can be done after PickUp:
	if (cog_hmp_ActionNumber==3 && firstAction_flag==false && (reas_hmp_previous_ActionNumber==0 ))
	{
		reas_hmp_ActionNumber=cog_hmp_ActionNumber;
		reas_hmp_previous_ActionNumber=cog_hmp_ActionNumber;
		reasoningHMP_flag=false;

	}
	// NOn of the actions: i think this one should be commented now also do not make cognitionHMP_flag false there now!
	if (cog_hmp_ActionNumber==4)
	{
		reas_hmp_ActionNumber=cog_hmp_ActionNumber;
		cout<<hmp_ActionsName[reas_hmp_ActionNumber]<<endl;
		reasoningHMP_flag=true;
	}
	cognitionHMP_flag=true;

	if (reasoningHMP_flag==true && firstAction_flag==false && cog_hmp_ActionNumber!=4)
	{
		cout<<"Restart the Test!"<<endl;
	}

}
string cognitionClass::cognitionHMP_get() {
//	cout<<"I am in get function!"<<endl;
	reasoningHMP_flag=true;
	return hmp_ActionsName[reas_hmp_ActionNumber];
}



void cognitionClass::cognitionControl() {

}

