#include<iostream>
using namespace std;
#include"Administrator.h"
#include"student.h"
int main()
{
	int op;
	cout<<"\t\tMAIN MENU"<<endl;
	cout<<"\t\tPress 1 For Administrator Menu "<<endl;
	cout<<"\t\tPress 2 For Student Menu "<<endl;
	cout<<"\t\tPress 3 For Exit "<<endl;
	cin>>op;
	while(op!=3)
	{
	switch(op)
	{
		case 1:
			Amenu();
			break;
		case 2:
			Smenu();
			break;
		case 3:
			exit;
		default:
			cout<<"You Enter Wrong option"<<endl;
			break;
	}
	cout<<"\t\tMAIN MENU"<<endl;
	cout<<"\t\tPress 1 For Administrator Menu "<<endl;
	cout<<"\t\tPress 2 For Student Menu "<<endl;
	cout<<"\t\tPress 3 For Exit "<<endl;
	cin>>op;
	}
	 	
}
