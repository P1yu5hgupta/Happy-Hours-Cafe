
#include<iostream>
#include<string>
#include <conio.h>
#include<windows.h>
#include<cstdio>
#include<ctype.h>
#include<fstream>
using namespace std;
void recharge();
void list();
void gotoxy( int x, int y )
{
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}
void layout(){
	cout<<"\n\n";
	cout<<"          ****************************************************************************************************          "<<endl;
	cout<<"                                             'You're Welcome to your own Cafe'                                          "<<endl;
	cout<<"          ****************************************************************************************************          "<<endl;
	for(int i=0;i<30;i++){
	gotoxy(10,2+i);
	cout<<"*";
	}
	for(int i=0;i<30;i++){
	gotoxy(110,2+i);
	cout<<"*";
	}
}
home(){
	system("cls");
		layout();
	gotoxy(20,8);
	cout<<"Tasks which can be done...";
	gotoxy(24,11);
	cout<<"1. Recharge the card of Customer";
	gotoxy(24,13);
	cout<<"2. List of all registered users";
	int ch;
	cin>>ch;
	switch(ch){
		case 1: {
			recharge();
			break;
		}
		case 2: {
			list();
			break;
		}
	}
}
int main(){
home();
return 0;
}
int go(int amt){
	system("cls");
	layout();
	gotoxy(20,8);
	cout<<"Enter the Recharge amount: ";
	int amnt;
	cin>>amnt;
	return amt+amnt;
}
void recharge(){
	system("cls");
	layout();
	string pid;
	gotoxy(20,8);
	cout<<"Enter the Unique Id of the Customer:";
	gotoxy(20,10);
	cin>>pid;
	string name,id,pass;
	float amt,amnt;
	int f=0;
	ifstream fp;
	fp.open("user.txt");
	while(!fp.eof()){
		fp>>name;
		fp>>id;
		fp>>pass;
		fp>>amt;
		if(id==pid){
			amt=go(amt);
			f=1;
			break;
		}
	}
	if(f!=1){
		gotoxy(20,14);
		cout<<"Invalid Id";
		gotoxy(20,16);
		system("pause");
		recharge();
	}
	else{
		system("cls");
		layout();
		ifstream fp;
	fp.open("user.txt");
	while(!fp.eof()){
		fp>>name;
		fp>>id;
		fp>>pass;
		if(id==pid){
			ofstream fp;
			fp.open("user.txt",std::ios_base::app);
			fp<<amt;
			break;
		}
		fp>>amnt;
	}
	}
	home();
}
void list(){
	system("cls");
	layout();
	gotoxy(20,8);
	cout<<"All registered Users";
	int i=0;
	string name,id,amt,pass;
	ifstream fp;
	fp.open("user.txt");
	while(!fp.eof()){
		fp>>name>>id>>pass>>amt;
		gotoxy(24,10+i*2);
		cout<<i+1<<". Name: "<<name<<"     ID: "<<id<<"    Card Balance: "<<amt;
		i++;
	}
	i++;
	gotoxy(20,11+2*i);
	system("pause");
	home();
}
