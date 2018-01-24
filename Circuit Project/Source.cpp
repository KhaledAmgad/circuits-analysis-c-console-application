#include <iostream>
#include <fstream>
#include <iomanip> 
#include "Component.h"
#include <Eigen/Eigen>
using namespace Eigen;

int Component::objectCount = 0;



int main()
{
	//////////////////////////////////////////////      ((Input))
	/*cout << "EnterNumberOfComponent\n";
	int NumberOfComponent;
	cin >> NumberOfComponent;
	Component *Components = new Component[NumberOfComponent];
	string input;
	int N1, N2;
	float mag, deg;

	for (int i = 0; i < NumberOfComponent; i++)
	{
		cin >> input;
		stringstream ss;
		ss << i;
		string str = ss.str();

		if (input == "Vs")//maag and Deg
		{
			cin >> N1 >> N2 >> mag >> deg;
			Components[i].SetComponent(N1, N2, 0);
			Components[i].SetVoltage(mag, deg);
		}
		if (input == "Cs")
		{
			cin >> N1 >> N2 >> mag >> deg;//maag and Deg
			Components[i].SetComponent(N1, N2, 1);
			Components[i].Setcurrent(mag, deg);
		}
		if (input == ("Z" + str))//Real and imaggg
		{
			cin >> N1 >> N2 >> mag >> deg;
			Components[i].SetComponent(N1, N2, 2);
			Components[i].SetZ(mag, deg);
		}
	}*/
	///////////////////////////////////////////////////////


	///////////////////////////////////////////////////////   ((File))
	Component Components[200];
	ifstream Input("Input_File.txt");
	string Type;
	int N1, N2,Count=0;
	float j, w, mag, deg;

	if (Input.is_open())
	{
		int ssrr, ssrl, ssrc;
		ssrr = 1;
		ssrc = 1;
		ssrl = 1;
		Input >> w;
		bool Flag = true;
		for (int i = 0; Flag == true; i++)
		{
			std::string strr = to_string(ssrr);
			std::string strc = to_string(ssrc);
			std::string strl = to_string(ssrl);

			Input >> Type;
			if (Type == "Vs")
			{
				Count++;
				Input >> N1 >> N2 >> mag >> deg;
				Components[i].SetComponent(N1, N2, 0);
				Components[i].SetVoltage(mag, deg);
			}
			if (Type == "Cs")
			{
				Count++;
				Input >> N1 >> N2 >> mag >> deg;//maag and Deg
				Components[i].SetComponent(N1, N2, 1);
				Components[i].Setcurrent(mag, deg);
			}
			if (Type == ("R" + strr))//Real and imaggg
			{
				Count++;
				ssrr++;
				Input >> N1 >> N2 >> mag;
				Components[i].SetComponent(N1, N2, 2);
				Components[i].SetZ(mag, 0);
			}
			if (Type == ("C" + strc))//Real and imaggg
			{
				Count++;
				ssrc ++;
				Input >> N1 >> N2 >> mag;
				Components[i].SetComponent(N1, N2, 2);
				Components[i].SetZ(1/(w*mag), -90);
			}
			if (Type == ("L" + strl))//Real and imaggg
			{
				Count++;
				ssrl ++;
				Input >> N1 >> N2 >> mag;
				Components[i].SetComponent(N1, N2, 2);
				Components[i].SetZ(w*mag, 90);
			}
			if (Type == "F")
				Flag = false;
		}
	}
	int NumberOfComponent;
	NumberOfComponent = Count;

	///////////////////////////////////////////////////////

	int NumberOfUnknowns = 0;
	int NumberOfVs = 0;

	for (int i = 0; i < NumberOfComponent; i++)
	{
		if (Components[i].Node1>Components[i].Node2)
		{
			if (NumberOfUnknowns<Components[i].Node1)
			{
				NumberOfUnknowns = Components[i].Node1;
			}
		}
		else
		{
			if (NumberOfUnknowns<Components[i].Node2)
			{
				NumberOfUnknowns = Components[i].Node2;
			}
		}
	}
	NumberOfVs = NumberOfUnknowns;
	for (int i = 0; i < NumberOfComponent; i++)
	{
		if (Components[i].type == 0)
		{
			NumberOfVs++;
			Components[i].NumberVs = NumberOfVs;
		}
	}
	Eigen::MatrixXcd A(NumberOfVs, NumberOfVs);
	Eigen::MatrixXcd B(NumberOfVs, 1);
	Eigen::MatrixXcd X(NumberOfVs, 1);

	for (int i = 0; i < NumberOfVs; i++)
	{
		for (int K = 0; K < NumberOfVs; K++)
		{
			A(i, K).imag(0);
			A(i, K).real(0);
		}
	}
	for (int i = 0; i < NumberOfVs; i++)
	{
		B(i, 0).imag(0);
		B(i, 0).real(0);
		X(i, 0).imag(0);
		X(i, 0).real(0);
	}

	for (int i = 0; i < NumberOfComponent; i++)
	{

		if (Components[i].HasZeroNode&&Components[i].type == 0)
		{
			if (Components[i].Node2 == 0)
			{
				A(Components[i].Node1 - 1, Components[i].NumberVs - 1) += complex<double>(1, 0);
				A(Components[i].NumberVs - 1, Components[i].Node1 - 1) += complex<double>(1, 0);
				B(Components[i].NumberVs - 1, 0) += Components[i].voltage;
			}
			else
			{
				A(Components[i].Node2 - 1, Components[i].NumberVs - 1) += complex<double>(-1, 0);
				A(Components[i].NumberVs - 1, Components[i].Node2 - 1) += complex<double>(-1, 0);
				B(Components[i].NumberVs - 1, 0) += Components[i].voltage;
			}
		}
		else if (Components[i].HasZeroNode == false && Components[i].type == 0)
		{
			A(Components[i].Node1 - 1, Components[i].NumberVs - 1) += complex<double>(1, 0);
			A(Components[i].Node2 - 1, Components[i].NumberVs - 1) += complex<double>(-1, 0);
			A(Components[i].NumberVs - 1, Components[i].Node1 - 1) += complex<double>(1, 0);
			A(Components[i].NumberVs - 1, Components[i].Node2 - 1) += complex<double>(-1, 0);
			B(Components[i].NumberVs - 1, 0) += Components[i].voltage;
		}
		else if (Components[i].HasZeroNode&&Components[i].type == 2)
		{
			if (Components[i].Node1 == 0)
			{
				A(Components[i].Node2 - 1, Components[i].Node2 - 1) += pow(Components[i].Z, -1);
			}
			else
			{
				A(Components[i].Node1 - 1, Components[i].Node1 - 1) += pow(Components[i].Z, -1);
			}
		}
		else if (Components[i].HasZeroNode == false && Components[i].type == 2)
		{
			A(Components[i].Node1 - 1, Components[i].Node1 - 1) += pow(Components[i].Z, -1);
			A(Components[i].Node2 - 1, Components[i].Node1 - 1) -= pow(Components[i].Z, -1);
			A(Components[i].Node1 - 1, Components[i].Node2 - 1) -= pow(Components[i].Z, -1);
			A(Components[i].Node2 - 1, Components[i].Node2 - 1) += pow(Components[i].Z, -1);
		}
		else if (Components[i].HasZeroNode&&Components[i].type == 1)
		{
			if (Components[i].Node2 == 0)
			{
				B(Components[i].Node1 - 1, 0) += Components[i].current;
			}
			else
			{
				B(Components[i].Node2 - 1, 0) -= Components[i].current;////////////////
			}

		}
		else if (Components[i].HasZeroNode == false && Components[i].type == 1)
		{
			B(Components[i].Node1 - 1, 0) += Components[i].current;
			B(Components[i].Node2 - 1, 0) -= Components[i].current;
		}
	}


	cout<<A;
	cout<<"======================\n";
	cout<<B;
	cout<<"======================\n";
	


	X += A.jacobiSvd(ComputeThinU | ComputeThinV).solve(B);
	cout<<X;
	cout<<"======================\n";

	ofstream Output("Output_file.txt");

	for (int i = 0; i < NumberOfVs; i++)////////////////////////////////////////////////////////////
		{
			
			X(i,0).real(int(X(i,0).real()*1000)/1000.0);
			X(i,0).imag(int(X(i,0).imag()*1000)/1000.0);


		}
	int i = 0;
	for (; i < NumberOfUnknowns; i++)
	{
		cout << "V(" << i + 1 << ")" << " " << abs(X(i, 0)) << " " << (arg(X(i, 0))*(180 / 3.141592654));
		cout << endl;
		Output << "V(" << i + 1 << ")" << " " << abs(X(i, 0)) << " " << (arg(X(i, 0))*(180 / 3.141592654));  //
		Output << endl;                                                                                      //
	}
	for (int j = 0; j < NumberOfComponent; j++)
	{
		if (Components[j].type == 0)
		{
			cout << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(X(i, 0)) << " " << (arg(X(i, 0))*(180 / 3.141592654));
			Output << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(X(i, 0)) << " " << (arg(X(i, 0))*(180 / 3.141592654));
			i++;
			cout << endl;
			Output << endl;
		}
		if (Components[j].type == 1)
		{
			cout << "I(" << Components[j].Node2 << " " << Components[j].Node1 << ")" << " " << abs(Components[j].current) << " " << (arg(Components[j].current)*(180 / 3.141592654));
			Output << "I(" << Components[j].Node2 << " " << Components[j].Node1 << ")" << " " << abs(Components[j].current) << " " << (arg(Components[j].current)*(180 / 3.141592654));
			cout << endl;
			Output << endl;
		}
		if (Components[j].type == 2)
		{
			if (Components[j].HasZeroNode == false)
			{
				complex<double> I = ((X(Components[j].Node1 - 1, 0) - X(Components[j].Node2 - 1, 0)) / Components[j].Z);
				cout << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
				Output << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
				cout << endl;
				Output << endl;
			}
			else
			{
				if (Components[j].Node1 == 0)
				{
					complex<double> I = ((complex<double>(0, 0) - X(Components[j].Node2 - 1, 0)) / Components[j].Z);
					cout << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
					Output << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
					cout << endl;
					Output << endl;
				}
				else if (Components[j].Node2 == 0)
				{
					complex<double> I = ((X(Components[j].Node1 - 1, 0)) / Components[j].Z);/////////ikhhhhhhhhh/////////////////////
					cout << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
					Output << "I(" << Components[j].Node1 << " " << Components[j].Node2 << ")" << " " << abs(I) << " " << (arg(I)*(180 / 3.141592654));
					cout << endl;
					Output << endl;
				}
			}
		}
	}
	cout << endl;
	system("PAUSE");
}
