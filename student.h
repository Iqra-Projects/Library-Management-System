#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
class students
{
	char reg[15],name[30],isbno[15];
	int counter;
	public:

		void show_sdata(void)
		{
			cout<<"Student Name is "<<name<<endl;
			cout<<"Registeration Number is "<<reg<<endl;
			cout<<"Number of issue book "<<counter<<endl;
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
			cout<<reg<<setw(33)<<name<<setw(22)<<counter<<endl;
		}
 };
 
 //END Of Student Class
 
 class books
 {
 	char bserno[15],bname[40],arname[50];
 	public:

		void show_bdata(void)
		{
			cout<<"Book Name is  "<<bname<<endl;
			cout<<"Author Name of Book is  "<<arname<<endl;
			cout<<"Serial Number Of Book is  "<<bserno<<endl;
		}
		 

		char* resbserno()
		{
		    return bserno;
		}
			 
		void record()
		{
		     cout<<bserno<<setw(44)<<bname<<setw(34)<<arname<<endl;
		}
		
 };
 //END Of Book Class
 
 
 // Global Declaration Of Objects.
 
 
 fstream fil1,fil2;
 books book;
 students stud;
 
 
 void show_studentslist(void)
{
	fil1.open("student.txt",ios::in);
	cout<<"*****STUDENTS LIST*****"<<endl;
	cout<<"Registeration No."<<setw(30)<<"Student Name"<<setw(25)<<"Book Issue\n";
	while(fil1.read((char*)&stud,sizeof(students)))
	{
		stud.record();
	}
	fil1.close();
}


void show_booklist(void)
{
	fil1.open("book.txt",ios::in);
	cout<<"***** BooK LIST *****"<<endl;
	cout<<"Book Number"<<setw(33)<<"Book Name"<<setw(41)<<"Author Name\n";
	while(fil1.read((char*)&book,sizeof(books)))
	{
		book.record();
	}
	fil1.close();
}



void issue_book()
{
	char reg[15],bserno[15];
	int found=0,count=0;
	cout<<"Enter The registration Number of student "<<endl;
	cin>>reg;
	fil1.open("student.txt",ios::in|ios::out);
	fil2.open("book.txt",ios::in|ios::out);
	while(fil1.read((char*)&stud,sizeof(students))&& found==0)
	
	{
		if(strcmp(stud.resreg(),reg)==0)
		{
			found=1;
			if(stud.rescounter()==0)
			{
			
			cout<<"Enter Serial number Of Book "<<endl;
			cin>>bserno;
			while(fil2.read((char*)&book,sizeof(books))&& count==0)
			{
				if(strcmp(book.resbserno(),bserno)==0)
				{
					book.show_bdata();
					count=1;
					stud.addcounter();
					stud.getisbno(book.resbserno());
					int pos=-1*sizeof(stud);
					fil1.seekp(pos,ios::cur);
					fil1.write((char*)&stud,sizeof(students));
					cout<<"book Issue Successfully For 25 Days After 25 Days the fine has been charge rupees 100 Per day"<<endl;
				}
			}
			if (count==0)
			{
				cout<<"Book doesn't Exist"<<endl;
			}
		}
			else
				cout<<"You have not returned the last book "<<endl;
		}
	}

	if(found==0)
	{
		cout<<"Student Record doesn't exist "<<endl;
	}
	fil1.close();
	fil2.close();
}

void book_return()
{
	char reg[15],bserno[15];
	int found=0,count=0,day,fine;
	cout<<"Enter the registration Number of the Student "<<endl;
	cin>>reg;
	fil1.open("student.txt",ios::in|ios::out);
	fil2.open("book.txt",ios::in|ios::out);
	while(fil1.read((char*)&stud,sizeof(students)) && found==0)
       {
	    if(strcmp(stud.resreg(),reg)==0)
	    {
		    found=1;
		    if(stud.rescounter()==1)
		    {
			while(fil2.read((char*)&book,sizeof(book))&& count==0)
			{
			   if(strcmp(book.resbserno(),stud.resisbno())==0)
			{
				book.show_bdata();
				count=1;
				cout<<"Enter The number of days that you have the book"<<endl;
				cin>>day;
				if(day>25)
				{
				   fine=(day-25)*100;
				   cout<<"You have Paid fine Rupees "<<fine<<endl;
				}
					stud.resetcounter();
					int pos=-1*sizeof(stud);
					fil1.seekp(pos,ios::cur);
					fil1.write((char*)&stud,sizeof(students));
					cout<<"You returned the Book successfully "<<endl;
			}
		    }
		  if(count==0)
		    cout<<"Book no does not exist"<<endl;
		      }
		 else
			cout<<"No book is issued..please check"<<endl;
		}
	   }
      if(found==0)
	cout<<"Student record not exist"<<endl;
  fil1.close();
  fil2.close();
}


void Smenu(void);
void Smenu(void)
{
	int ch;
	cout<<" ***** Welcome To Student Menu *****"<<endl;
	cout<<"Press 1 For Issue Book "<<endl;
	cout<<"Press 2 For Return Book "<<endl;
	cout<<"Press 3 For See All Books "<<endl;
	cout<<"Press 4 For See All Students "<<endl;
	cout<<"Press 5 For Exit From Student menu "<<endl;
	cin>>ch;
	switch(ch)
	{
		case 1:
			issue_book();
			break;
		case 2:
			book_return();
			break;
		case 3:
			show_booklist();
			break;
		case 4:
		    show_studentslist();
			break;
		case 5:
			return;
		default:
		    cout<<"You Enter Wrong Option "<<endl;
			break;	
	}
	Smenu();
}
