#include<fstream.h>
#include<stdio.h>
//#include<cstdio>
#include<conio.h>
char npass[30];

void changepass()
{
clrscr();
remove("password.dat");
//passold.close();
cout<<"Enter new password	:	";
gets(npass);
fstream pass("password.dat",ios ::in |ios::out | ios::trunc | ios::binary) ;

pass.write((char*)&npass,sizeof(npass));
pass.close();

cout<<"\n\n\n\n\n\t\tPassword Changed Sucessfully!!!!";
cout<<"\n\t\tPassword is   :  "<<npass;
}

void main()
{
clrscr();
changepass();

getch();
}