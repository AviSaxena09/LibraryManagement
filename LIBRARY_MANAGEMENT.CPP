#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

char password[30],npass[30];
fstream fp,fp1;
int cpass=0;

void display();                 //to display relevant info
void write_book();              //to write data in book.dat
void write_book();              //to write data in student.dat
void display_spb(char n[]);     //display particular data in book.dat
void display_sps(char n[]);     //display particular data in student.dat
void modify_book();             //edit in book.dat
void modify_student();          //edit in student.dat
void delete_student();		//delete in student.dat
void delete_book();		//delete in book.dat
void display_alls();		//display all data of student.dat
void display_allb();		//display all data of book.dat
void book_issue();		//issue book to a student
void book_deposit();    	//to return back book and calculate fine if any
void admin_menu();		//display menu of modifying records option
void get_pass();		//read password from password.dat and copy to ch
void getpass();			//takes ch i.e. password and check if password correct or not
void changepass();		//change password i.e. overwrite file password.dat
void deleteallrecords();        //To delete all the files and create new files i.e. book.dat and student.dat and again create them


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
public:
	void create_book()
	{
	cout<<"\n New Book Entry \n";
	cout<<"\n Enter the book number \n";
	cin>>bno;
	cout<<"\n Enter the name of book \n";
	gets(bname);
	cout<<"\n Enter the Author's Name \n";
	gets(aname);
	cout<<"\n Book created \n";
	}
	void show_book()
	{
	cout<<"\n Book number :"<<bno;
	cout<<"\n Book Name : ";
	puts(bname)  ;
	cout<<"\n Author Name : ";
	puts(aname);
	}
	void modify_book()
	{
	cout<<"\n Book Number :"<<bno;
	cout<<"\n Book Name to Modify : ";
	gets(bname);
	cout<<"Modify Author's Name of Book ";
	gets(aname) ;
	}
	char* retbno()
	{
	return bno;
	}
	void report()
	{
	cout<<"  \t"<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
}bk;
class student
{
char admno[6];
char name[20];
char stbno[6];
int token;
public:
	void create_student()
	{
	clrscr();
	cout<<"\n New Student Entry \n";
	cout<<"\n Enter The Admission Number = ";
	cin>>admno;
	cout<<"\n Enter Name of the Student = ";
	gets(name);
	token=0;
	stbno[0]='/0';
	cout<<"\n Student Record Created \n";
	}
	void show_student()
	{
	cout<<"\n Admission Number : "<<admno;
	cout<<"\n Student name : ";
	puts(name);
	cout<<"\n Number of Books issued : "<<token;
	if(token==1)
	cout<<"\n Book Number "<<stbno;
	}
	void modify_student()
	{
	cout<<"\n Admission Number :"<<admno;
	cout<<"\n Modify Student Name :";
	gets(name);
	}
	char* retadmno()
	{
	return admno;
	}
	char* retstbno()
	{
	return stbno;
	}
	int rettoken()
	{
	return token;
	}
	void addtoken()
	{
	token=1;
	}
	void resettoken()
	{
	token=0;
	}
	void getstbno(char t[])
	{
	strcpy(stbno,t) ;
	}
	void report()
	{
	cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
	}
}st;

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app | ios::binary);
	do
	{
	clrscr();
	bk.create_book();
	fp.write((char*)&bk,sizeof(book));
	cout<<"\n Do you want to add more record ...?";
	cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
}
void write_student()
{
char ch;
fp.open("student.dat",ios::out|ios::app  | ios::binary);
do
{
	st.create_student();
	fp.write((char*)&st,sizeof(student));
	cout<<"\n Do you want to add more record ?";
	cin>>ch;
	}
	while(ch=='y'||ch=='Y');
	fp.close();
}
void display_spb(char n[])
{
	cout<<"\n Book Details \n";
	int flag=0;
	fp.open("book.dat",ios::in | ios::binary);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmp(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
		cout<<"\n Book Does Not Exist \n";
	getche();
}
void display_sps(char n[])
{
	cout <<"\n Student Details \n";
	int flag=0;
	fp.open("student.dat",ios::in | ios::binary);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmp(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n Student does not exist \n";
	getche();
}
void modify_book()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n Modify Book Records \n ";
	cout<<"Enter the Book No. of the book ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out | ios::binary );
	while(fp.read((char*)&bk,sizeof(book))&&found==0)
	{
		if(strcmp(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\n Enter the New Details of the book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n Record Updated \n";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n Record not found \n";
		getche();
}
void modify_student()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n Modify Student Records \n ";
	cout<<"Enter the Admission No. of the Student ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out  | ios::binary);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
		if(strcmp(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\n Enter the New Details of the Student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(student));
			cout<<"\n Record Updated \n";
			found=1;
		}
	}
	fp.close();
	if(found==0)
		cout<<"\n Record not found \n";
		getche();
}
void delete_student()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n Delete Student \n";
	cout<<"\n Enter the Admission No. of the student ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out | ios::binary);
	fstream fp2;
	fp2.open("Temp.dat",ios::out | ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmp(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}
	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n Record Deleted \n ";
	else
		cout<<"\n Record Not found \n";
	getche();
}
void delete_book()
{
	char n[6];
	clrscr();
	cout<<"\n Enter the Book No. of the Book ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out | ios::binary);
	fstream fp2;
	fp2.open("Temp.dat",ios::out | ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmp(bk.retbno(),n)!=0)
	       {	fp2.write((char*)&bk,sizeof(book));
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
		cout<<"\n Record Deleted ";
	getche();
}
void display_alls()
{
	clrscr();
	 fp.open("student.dat",ios::in | ios::binary);
	 if(!fp)
	 {
		cout<<"ERROR!!! File could not be opened ";
		getche();
		return;
	 }
	 cout<<"\n \t Student List \n ";
	 cout<<"\t Admission No."<<setw(10)<<"Name"<<setw(20)<<"Book issued \n";
	 while(fp.read((char*)&st,sizeof(student)))
	 {
	 st.report();
	 }
	 fp.close();
	 getche();
}
void display_allb()
{
	clrscr();
	 fp.open("book.dat",ios::in | ios::binary);
	 if(!fp)
	 {
		cout<<"ERROR!!! File could not be opened ";
		getche();
		return;
	 }
	 cout<<"\n \t\t\t\t Book List \n ";
	 cout<<"\tBook No."<<setw(30)<<"Book Name"<<setw(30)<<"Author\n";
	 while(fp.read((char*)&bk,sizeof(book)))
	 {
	 bk.report();
	 }
	 fp.close();
	 getche();
}
void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n Book Issue \n";
	cout<<"\n Enter Student Admission No. \n";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out | ios::binary);
	fp1.open("book.dat",ios::in|ios::out | ios::binary);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
	if(strcmp(st.retadmno(),sn)==0)
	{
	found=1;
		if(st.rettoken()==0)
		{
			cout<<"\n Enter The Book No.";
			cin>>bn;
			while(fp1.read((char*)&bk,sizeof(book))&&flag==0)
			{
				if(strcmp(bk.retbno(),bn)==0)
				{
					bk.show_book();
					flag=1;
					st.addtoken();
					st.getstbno(bk.retbno());
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
			cout<<"\n Book Issued successfully \n Please note: Write Current date in backside of \n book and submit within 15 days.\n Fine of Rs.5 for each day after 15 days period";
				}
			}
			if(flag==0)
			cout<<"Book does not exist ";
		}
		else
		cout<<"You have not returned the last book ";
		}
	}
	if(found==0)
	cout<<"student Record not exist....";
	getche();
	fp.close();
	fp1.close();
}
void book_deposit()
{
	char sn[6],bn[6];
	int found=0,flag=0,day,fine;
	clrscr();
	cout<<"\n Book Deposit \n";
	cout<<"\n Enter student Admission Number ";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out | ios::binary);
	fp1.open("book.dat",ios::in|ios::out | ios::binary);
	while(fp.read((char*)&st,sizeof(student))&&found==0)
	{
		if(strcmp(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==1)
			{
			while(fp1.read((char*)&bk,sizeof(book))&&flag==0)
			{
			if(strcmp(bk.retbno(),st.retstbno())==0)
			{
			bk.show_book();
			flag=1;
			cout<<"\n Enter Book deposited in no. of days :";
			cin>>day;
			if(day>15)
			{
			fine=(day-15)*5;
			cout<<"\n Fine to be deposited is : Rs."<<fine;
			}
			st.resettoken();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n \n \t Book Deposited successfully";
			}
		}
		if(flag==0)
		cout<<"Book no. does not exist ";
		}
		else
		cout<<"No book is issues ...please check again!!!";
		}
	}
	if(found==0)
	cout<<"Student Record Does Not Exist...";
	getche();
	fp.close();
	fp1.close();
}
void admin_menu()
{
clrscr();
int ch2;
cout<<"\n                 MODIFY  RECORDS";
cout<<"\n\n\n 1.Create Student Record";
cout<<"           2.Modify Student Record";
cout<<"\n 3.Delete Student Record";
cout<<"           4.Create Book";
cout<<"\n 5.Modify Book";
cout<<"                     6.Delete Book";

cout<<"\n 7.Delete All RECORDS";
cout<<"              8.Back to Main Menu";
cout<<"\n________________________________________________________________________________";
cin>>ch2;
switch(ch2)
{
	case 1:clrscr()  ;
	write_student();
	break;
	case 2:clrscr()     ;
	modify_student();
	break;
	case 3:clrscr()      ;
	delete_student();
	break;
	case 4:clrscr()       ;
	write_book();
	break;
	case 5:clrscr()          ;
	modify_book();
	break;
	case 6:clrscr()          ;
	delete_book();
	break;
	case 7:        clrscr();
	deleteallrecords()  ;
	case 8:return;
	default:cout<<"\a";
	}
	admin_menu();
}

void deleteallrecords()
{
remove("student.dat");
remove("book.dat");
fstream f1("student.dat", ios :: in | ios :: out | ios:: binary);
fstream f2("book.dat", ios :: in | ios:: out | ios :: binary);
}
void get_pass()
{
fstream pass("password.dat",ios ::in |ios::out | ios::binary) ;
char ch[30];

pass.read((char*)&ch,sizeof(ch));
strcpy(password,ch);
pass.close()    ;
}
void changepass()
{
clrscr();
//char npass[30];
cout<<"Enter new password";
gets(npass);
fstream pass("password.dat",ios ::in |ios::out | ios::trunc | ios::binary) ;

pass.write((char*)&npass,sizeof(npass));
pass.close();

cout<<"\n\n\n\n\n\t\tPassword Changed Sucessfully!!!!";
cout<<"\n\t\tPassword is   :  "<<npass;
}

void getpass()
{

char pass[30];
int i=0;
do{
clrscr();
if(i!=0)
cout<<"\nleft with  "<<4-i<<"attempts";
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                        ENTER PASSWORD  = ";
cin>>pass;
get_pass();
if(strcmp(pass,password)==0)
cpass=1;
else
{
cpass=0;
i++;
}

}while(cpass==0 && i<4)  ;


}

void display()
{
clrscr();
cout<<"This software is based on library management system ";
cout<<"\n\nPLEASE NOTE:-";
cout<<"\n\t1. The file used in the software are :" ;
cout<<"\n\t   (i)Book.dat (ii)student.dat (iii)password.dat" ;
cout<<"\n\t2. There should be no file named as temp.dat, so as to avoid damage of";
cout<<"\n\t   data";
cout<<"\n\t3. Incase of password forget,please refer to program resetpass.cpp, to";
cout<<"\n\t   reset password  ; Password by default is : default";
cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\tPrograming done by:-Avi Saxena";
cout<<"\n\t\t\t                    XII A";
cout<<"\n\t\t\t                    The Asian School, Dehradun";
getch();
}

void main()
{
clrscr();
display();
clrscr();
char ch;
getpass();

if (cpass==1)
{
   do
   { 	clrscr();
	cout<<"\n                        LIBRARY MANAGEMENT SYSTEM ";
	cout<<"\n________________________________________________________________________________";
	cout<<"\n\n\n\n 1.Issue Book ";
	cout<<"                      2.Deposit Book ";
	cout<<"\n 3.Show All Student Records ";
	cout<<"        4.Show Particular student record";
	cout<<"\n 5.Show All Books";
	cout<<"                   6.Show Particular Book";
	cout<<"\n 7.Modify Record ";
	cout<<"                   8.Change Password" ;
	cout<<"\n\n\n\n\n\n\n\n\n ";
	cout<<"\n-------------------------TO QUIT PRESS (.Q.)------------------------------------";

	cout<<"\n\t\t\t\t\tProgramed by  :- Avi Saxena";
	cout<<"\n\t\t\t\t\t		    XII-A\n";
	cout<<"Enter Your Choice        :    ";
	cin>>ch;
	switch(ch)
	{
	case '1':clrscr();
	book_issue();
	break;
	case '2':clrscr();
	book_deposit();
	break;
	case '7':clrscr();
	getpass();
	if(cpass==1)
	{
	cpass=0;
	admin_menu();
	}
	else
	cout<<"wrong password";getch();
	break;
	case '6':clrscr()         ;
	char gum[6];
	cout<<"Enter the Book No.";
	cin>>gum;
	display_spb(gum);
	break;
	case '3':clrscr()    ;
	display_alls();
	break;
	case '5':clrscr() ;
	display_allb();
	break;
	case '4':clrscr();
	char num[6];
	cout<<"\n \t Enter The Admission No.=  ";
	cin>>num;
	display_sps(num);
	break;
	case '8' :
	getpass();
	if(cpass==1)
	{
	cpass=0;
	changepass();
	}
	else
	cout<<"wrong password";getch();
	break;
	case 'q':exit(0); break;
	case 'Q':exit(0); break;
	default:cout<<"\nwrong input";
	}
}
	while(ch!='Q');
}        else{exit(0);
}
	getche();

}