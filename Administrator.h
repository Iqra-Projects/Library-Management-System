#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
class student
{
	char reg[15],name[30],isbno[15];
	int counter;
	public:
		void add_student(void)
		{
			cout<<"Enter Student Name "<<endl;
			cin>>name;
			cout<<"Enter Student Registeration Number "<<endl;
			cin>>reg;
			counter=0;
			isbno[0]='/0';
			cout<<"Successfully Student has Register "<<endl;
		}
		
		void show_sdata(void)
		{
			cout<<"Enter Student Name is "<<endl;
			cin>>name;
			cout<<"Registeration Number is "<<reg<<endl;
			cout<<"Number of issue book "<<counter<<endl;
		}
		
		void modify_sdata(void)
		{
			cout<<"Reisteration Number is  "<<reg<<endl;
			cout<<"Enter Name that you want to modify"<<endl;
			cin>>name;
		}
		
		char* resreg()
		{
			return reg; 
		}
		
		char* resisbno()
		{
			return isbno;
		}
		
		int rescounter()
		{
			return counter;
		}
		
		void addcounter()
		{
			counter=1;
		}
		
		void resetcounter()
		{
			counter=0;
		}
		
		void getisbno(char isu[15])
		{
			strcpy(isbno,isu);
		}
		
		void record()
		{
			cout<<"Student Name "<<name<<setw(25)<<"Registeration Number is "<<reg<<setw(25)<<"Number Of issue books "<<counter<<endl;
		}
 };
 
 
 class book
 {
 	char bserno[15],bname[40],arname[50];
 	public:
 		void add_book(void)
 		{
 			cout<<"Enter Book Name "<<endl;
 			cin>>bname;
 			cout<<"Enter The Name Of Author Of Book "<<endl;
 			cin>>arname;
 			cout<<"Enter the Serial Number Of Book "<<endl;
 			cin>>bserno;
 			cout<<"Book Enter Successfully in the record "<<endl;
		}
			 
		void show_bdata(void)
		{
			cout<<"Enter Name Of Book "<<endl;
			cin>>bname;
			cout<<"Enter Name of Authur "<<endl;
			cin>>arname;
			cout<<"Serial Number Of Book "<<bserno<<endl;
		}
		 
		void modify_book(void)
		{
			cout<<"Enter Name of Book that you want to Modify "<<endl;
			cin>>bname;
		    cout<<"Enter Name of Author of that Book that you want to Modify "<<endl;
		    cin>>arname;
		    cout<<"Serial Number Of Book "<<bserno<<endl;
		}
			 
		char* resbserno()
		{
		    return bserno;
		}
			 
		void record()
		{
		    cout<<"Book Name is "<<bname<<setw(25)<<"Author Name is "<<arname<<setw(25)<<"Serial Number of Book "<<bserno<<endl;
		}
		
 };
 
 
 fstream file1,file2;
 book bok;
 student stu;
 
 void write_student(void)
 {
 	char ch;
 	file1.open("student.dat",ios::app);
 	do
 	{
 		stu.add_student();
 		file1.write((char*)&stu,sizeof(student));
 		cout<<"You add Successfully Student in record "<<endl;
 		cout<<"If you Add More students in record Press 'Y' or 'y' "<<endl;
 		cin>>ch;
	}
	while(ch=='Y'||ch=='y');
	file1.close();
 }

void search_spstudent()
{
	int count=0;
	char s[15];
	cout<<"Student Record "<<endl;
	file1.open("student.dat",ios::in);
	while(file1.read((char*)&stu,sizeof(student)))
	{
		if(strcmp(stu.resreg(),s)==0)
		{
			stu.show_sdata();
			count=1;
		}
	}
	file1.close();
	if(count==0)
	{
		cout<<"Student Doesn't exist in Record "<<endl;
	}

}

void display_studentslist(void)
{
	file1.open("student.dat",ios::in);
	cout<<"*****STUDENTS LIST*****"<<endl;
	while(file1.read((char*)&stu,sizeof(student)))
	{
		stu.record();
	}
	file1.close();
}

void modify_student()
{
	char s[15];
	int found=0;
	cout<<"Enter Registeration Number of the student "<<endl;
	cin.get(s,15);
	file1.open("student.dat",ios::in|ios::out);
	while(file1.read((char*)&stu,sizeof(student)) && found==0)
	{
		if(strcmp(stu.resreg(),s)==0)
		{
			stu.show_sdata();
			cout<<"Enter New data Of student "<<endl;
			stu.modify_sdata();
			int pos=-1*sizeof(stu);
			file1.seekp(pos,ios::cur);
			file1.write((char*)&stu,sizeof(student));
			cout<<"Record Are updated"<<endl;
			found=1;
		}
	}
	file1.close();
	if(found==0)
	{
		cout<<"Record Doesn't exist"<<endl;
	}
}

void delete_student()
{
	char s[15];
	int count=0;
	cout<<"Enter the registeration Number of student "<<endl;
	cin.get(s,15);
	file1.open("student.dat",ios::in|ios::out);
	fstream file3;
	file3.open("temporary.dat",ios::app);
	file1.seekg(0,ios::beg);
	while(file1.read((char*)&stu,sizeof(student)))
	{
		if(strcmp(stu.resreg(),s)!=0)
		{
			file3.write((char*)&stu,sizeof(student));
		}
		else
		{
			count=1;
		}
	}
	
	file3.close();
	file1.close();
	remove("student.dat");
	rename("temporary.dat","student.dat");
	if(count==1)
	{
		cout<<"Record Deleted"<<endl;
	}
	else
	{
		cout<<"Record aren't found"<<endl;
	}
}

// Function Of Books

void write_book(void)
{
	char ch;
	file1.open("book.dat",ios::app);
	do
	{
		bok.add_book();
		file1.write((char*)&bok,sizeof(book));
		cout<<"Book Add Successfully in the record"<<endl;
		cout<<"If you Add More Books in record Press 'Y' or 'y' "<<endl;
		cin>>ch;
	}
	while(ch=='Y'||ch=='y');
	file1.close();
}

void search_spbook()
{
	int count=0;
	char n[15];
	file1.open("book.dat",ios::in);
	while(file1.read((char*)&bok,sizeof(book)))
	{
		if(strcmp(bok.resbserno(),n)==0)
		{
			bok.show_bdata();
			count=1;
		}
	}
	file1.close();
	if(count==0)
	{
		cout<<"Book Doesn't Exist in Record "<<endl;
	}
}

void modify_book()
{
	char b[15];
	int found=0;
	cout<<"Enter Serial Number of the book "<<endl;
	cin>>b;
	file1.open("book.dat",ios::in|ios::out);
	while(file1.read((char*)&bok,sizeof(book)) && found==0)
	{
		if(strcmp(bok.resbserno(),b)==0)
		{
			bok.show_bdata();
			cout<<"Enter New data Of Book "<<endl;
			bok.modify_book();
			int pos=-1*sizeof(bok);
			file1.seekp(pos,ios::cur);
			file1.write((char*)&bok,sizeof(book));
			cout<<"Record Are updated"<<endl;
			found=1;
		}
	}
	file1.close();
	if(found==0)
	{
		cout<<"Record Doesn't exist"<<endl;
	}
}

void delete_book()
{
	char b[15];
	int count=0;
	cout<<"Enter the Serial Number Of Book "<<endl;
	cin>>b;
	file1.open("book.dat",ios::in|ios::out);
	fstream file3;
	file3.open("temporary.dat",ios::app);
	file1.seekg(0,ios::beg);
	while(file1.read((char*)&bok,sizeof(book)))
	{
		if(strcmp(bok.resbserno(),b)!=0)
		{
			file3.write((char*)&bok,sizeof(book));
		}
		else
		{
			count=1;
		}
	}
	
	file3.close();
	file1.close();
	remove("book.dat");
	rename("temporary.dat","book.dat");
	if(count==1)
	{
		cout<<"Record Deleted"<<endl;
	}
	else
	{
		cout<<"Record aren't found"<<endl;
	}
}


void display_booklist(void)
{
	file1.open("book.dat",ios::in);
	cout<<"***** BooK LIST *****"<<endl;
	while(file1.read((char*)&bok,sizeof(book)))
	{
		bok.record();
	}
	file1.close();
}

// ADMINISTRATOR MENU 
void Amenu(void);
void Amenu(void)
{
	int ch;
	char ch2;
	cout<<"****** Administrator Menu ******"<<endl;
	cout<<"**** Press B or b for books  and Press S or s for Stduents and Press n or N for exit  ****"<<endl;
	cin>>ch2;
	if (ch2=='B'||ch2=='b')
	{
		cout<<"**** Press 1 For Add New Book ****"<<endl;
		cout<<"**** Press 2 For Display All Books ****"<<endl;
		cout<<"**** Press 3 For Display Specific book ****"<<endl;
		cout<<"**** Press 4 For Modify Books Record ****"<<endl;
		cout<<"**** Press 5 For Delete Book From Record ****"<<endl;
		cout<<"**** Press 6 For Back To Administrator Menu ****"<<endl;
		cout<<"**** Enter Your Choice From (1-6) ****"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:
				write_book();
				break;
			case 2:
				display_booklist();
				break;
			case 3:
				search_spbook();
				break;
			case 4:
				modify_book();
				break;
			case 5:
				delete_book();
				break;
			case 6:
				return;
			default:
				cout<<"You Wrong Option"<<endl;
		}
	}
	else if (ch2=='S'||ch2=='s')
	{
		cout<<"**** Press 1 For Add New Student ****"<<endl;
		cout<<"**** Press 2 For Display All Students ****"<<endl;
		cout<<"**** Press 3 For Display Specific Student ****"<<endl;
		cout<<"**** Press 4 For Modify students Record ****"<<endl;
		cout<<"**** Press 5 For Delete student From Record ****"<<endl;
		cout<<"**** Press 6 For Back To Administrator Menu ****"<<endl;
		cout<<"**** Enter Your Choice From (1-6) ****"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1:
				write_student();
				break;
			case 2:
				display_studentslist();
				break;
			case 3:
				search_spstudent();
				break;
			case 4:
				modify_student();
				break;
			case 5:
				delete_student();
				break;
			case 6:
				return;
			default:
				cout<<"You Wrong Option"<<endl;
		}
	}
	else if(ch2=='N'||ch2=='n')
	{
		return;
	}
	else
	cout<<"**** You Enter Wrong choice ****"<<endl;
	Amenu();
}

