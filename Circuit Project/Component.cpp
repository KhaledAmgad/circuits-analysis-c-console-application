#include "Component.h"


Component::Component(int N1,int N2,int T)
{
	type=T;
	Node1 = N1;
	Node2 = N2;
	objectCount++;
	
}

void Component::SetComponent(int N1,int N2,int T)
{
	type=T;
	Node1 = N1;
	Node2 = N2;
	if (Node1==0||Node2==0)
	{
		parallelorseries=1;
		
		
		HasZeroNode=true;

	}
	else
	{
		parallelorseries=0;
		HasZeroNode=false;

	}
	
	
}
int Component::getNode1()
{
	return Node1;

}
int Component::getNode2()
{
	return Node2;

}

void Component::SetVoltage(double mag,double deg)
{
	voltage=polar(mag,deg*3.141592/180);

}
	void Component::Setcurrent(double mag,double deg)
	{
		current=polar(mag,deg*3.14159265359/180);
	
	
	}
		void Component::SetZ(double mag,double deg)
	{
		Z=polar(mag,deg*3.14159265359/180);
		


	
	
	}
	void Component:: PrintInfo()
	{
		if (type==0)
		{
			cout<<"V"<<"  Voltage=  "<<voltage<<" Currunt=  "<<current<<endl;

		}
		if (type==1)
		{
			cout<<"I"<<"  Voltage=  "<<voltage<<" Currunt=  "<<current<<endl;

		}
		if (type==2)
		{
			cout<<"Z"<<"  Voltage=  "<<voltage<<" Currunt=  "<<current<<" Z= "<<Z<<endl;

		}

	
	
	
	}

Component::~Component(void)
{
}
