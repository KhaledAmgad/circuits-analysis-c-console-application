#pragma once
#include<complex>
#include <iostream>
using namespace std;
class Component
{
public:
	  static int objectCount;
	  static int objectseriesCount;
	  int NumberVs;
	  

	 
	Component(int N1=0,int N2=0,int T=0);
	~Component(void);
	void SetComponent(int,int,int);
	void SetVoltage(double,double);
	void Setcurrent(double,double);
	void SetZ(double,double);
	int getNode1();
	int getNode2();
	int parallelorseries; //0-> parralee 1-> series
	int type; //0-> V source 1-> I source 2-> Z
	int Node1;
	int Node2;
	bool HasZeroNode;
	complex<double> voltage;
	complex<double> current;
	complex<double> Z;
	


	void PrintInfo();


private:
	
};
