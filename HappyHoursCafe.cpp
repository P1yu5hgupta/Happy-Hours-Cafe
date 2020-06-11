#include<iostream>
#include<string>
#include <conio.h>
#include<windows.h>
#include<cstdio>
#include<ctype.h>
#include<fstream>
#include<time.h>
#include <process.h>
#define V 14
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#include "game.h"
#include "snake.h"
using namespace  std;

void gotoxy( int x, int y )
{
    COORD p = { x, y };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}
int tno;
string pname;
string pid;
void games();
void enter();
void extra();
void bookcab();
void games();
void layout();
void fltree();
void food();
void bookcab();
void login();
void signup();
void deletecart();
void confirmorder();
void addtoorders(string , float);
void additem(string ,string ,float);
void confirmord(float );
class records;
class usertree;

class orditem{
	public:
	string it_name;
	float price;
	orditem *left;
	orditem(string n,float p){
		this->it_name=n;
		this->price=p;
		this->left=NULL;
	}
};
class order{
	public:
	orditem *oroot;
	float total;
	order(){
		oroot=NULL;
		total=0;
	}
	int getstatus(){
		if(oroot==NULL)
			return 0;
		else
			return 1;
	}
	void additem(string name,float price){
		orditem *newnode=new orditem(name,price);
		if(oroot==NULL){
			oroot=newnode;
		}
		else{
			orditem *temp=oroot;
			while(temp->left!=NULL){
				temp=temp->left;	
			}
			temp->left=newnode;
		}
		total+=price;
	}
	void displayord(){
		int i=0;
		orditem *temp=oroot;
		gotoxy(85,8);
			cout<<"|Items|         |Price|";
			
		while(temp!=NULL){
			gotoxy(86,10+i);
			cout<<i+1<<". "<<temp->it_name;
			gotoxy(100,10+i);
			cout<<temp->price;
			temp=temp->left;
			i++;
		}
		i++;
		gotoxy(98,10+i);
		cout<<"|Total: "<<total<<" |";
	}
	void confdisplay(){
		int i=0;
		orditem *temp=oroot;
		gotoxy(30,11);
			cout<<"|Items|         |Price|";
			
		while(temp!=NULL){
			gotoxy(30,12+i);
			cout<<i+1<<". "<<temp->it_name;
			gotoxy(46,12+i);
			cout<<temp->price;
			temp=temp->left;
			i++;
		}
		i++;
		gotoxy(44,12+i);
		float tax,discount=0;
		cout<<"|Total: "<<total<<" |";
		if(pid!="0"){
			discount=total*(0.20);
			tax=(total*(0.80))*(0.05);
		}
		else{
			tax=total*0.05;
		}
		i++;
		gotoxy(44,12+i);
		cout<<"|Discount|: "<<discount;
		i++;	
		gotoxy(44,12+i);
		cout<<"|Tax Charged|: "<<tax;
		i++;	
		gotoxy(44,12+i);
		cout<<"|Net Total|: "<<total+tax-discount;
		gotoxy(32,15+i);
		cout<<"|Confirm Your Order|    ";
		system("pause");
		this->oroot=NULL;
		this->total=0;
		confirmord(total+tax-discount);
	}

	void deleteitem(string name){
		
		orditem *temp=oroot->left;
		orditem *prev=oroot;
		if(oroot->it_name==name){
			total=total-oroot->price;
			oroot=oroot->left;
		}
		else{
			while(temp!=NULL){
				if(temp->it_name==name){
					total=total-temp->price;
					prev->left=temp->left;
					temp->left=NULL;
						
				}
				temp=temp->left;
			}
		}
	}
	void clearcart(){
		this->oroot=NULL;
		this->total=0;
	}
	void getarray(string arr[]){
		orditem *temp=oroot;
		int i=0;
		while(temp!=NULL){
			arr[i]=temp->it_name;
			temp=temp->left;
			i++;
		}
	}
};
order ord;
class card{
	public:
		float amt;
		card(){
			this->amt=0;
		}
		void add(float a){
			this->amt+=a;
		}
		void cut(float c){
			this->amt-=c;
		}
};
class user{
	public:
	string name;
	string id;
	string password;
	card c;
	user *next;
	public:
		user(string n,string i,string p,float amt){
			this->name=n;
			this->id=i;
			this->password=p;
			this->c.amt=amt;
		}
		void addbal(float amt){
			this->c.add(amt);
		}
		void bill(float amt){
			this->c.cut(amt);
		}
		
};
user *u;
class node{
	public:
	char alphbt;
	user *next;
	node *left;
	node *right;
		node(char x){
			this->alphbt=x;
			this->next=NULL;
			this->left=NULL;
			this->right=NULL;
		}
};

int height(node *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
int diff(node *temp)
{
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
node* rr_rotation(node *parent)
{
    node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

node* ll_rotation(node *parent)
{
    node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 
node* lr_rotation(node *parent)
{
    node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
node *rl_rotation(node *parent)
{
    node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
node* balance(node *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

node* insert(node *root,char value)
{
   	if (root == NULL)
    {
       	root = new node(value);
        return root;
    }
   	else if (value < root->alphbt)
    {
       	root->left = insert(root->left, value);
       	root = balance (root);
    }
    else if (value >= root->alphbt)
    {
       	root->right = insert(root->right, value);
       	root = balance (root);
    }
	return root;
}
class usertree{
	public:
	node *root;
		usertree(){
			for(char i=97;i<123;i++){
				this->root=insert(this->root,i);
			}			
			fltree();
		}
		void adduser(string name,string id,string pass,float amt){
			char fl=name[0];
			if(fl>=65&&fl<=91){
				fl+=32;
				cout<<fl;
			}
			node *temp=this->root;
			while(temp->alphbt!=fl){
				if(fl>temp->alphbt)
					temp=temp->right;
				else
					temp=temp->left;
			}
			user *newnode=new user(name,id,pass,amt);
			if(temp->next==NULL){
				temp->next=newnode;
			}
			else{
			user *utemp=temp->next;
			while(utemp->next!=NULL){
				utemp=utemp->next;
			}
			utemp->next=newnode;
			}
		}
		bool existid(string id,string name){
			char fl=name[0];
			if(fl>=65&&fl<=91){
				fl+=32;
			}
			node *temp=root;
			while(temp->alphbt!=fl){
				if(fl>temp->alphbt)
					temp=temp->right;
				else
					temp=temp->left;
			}
			if(temp->next==NULL){
				return false;
			}
			user *utemp=temp->next;
			while(utemp!=NULL){
				if(utemp->id==id)
					return true;
				utemp=utemp->next;
			}
			return false;
		}
		bool existuser(string id,string name,string pass){
			char fl=name[0];
			if(fl>=65&&fl<=91){
				fl+=32;
			}
			node *temp=root;
			while(temp->alphbt!=fl){
				if(fl>temp->alphbt)
					temp=temp->right;
				else
					temp=temp->left;
			}
			if(temp->next==NULL){
				return false;
			}
			user *utemp=temp->next;
			while(utemp!=NULL){
				if(utemp->id==id&&utemp->password==pass)
					return true;
				utemp=utemp->next;
			}
			return false;
		}
		user *getinfo(string name,string id){
			char fl=name[0];
			if(fl>=65&&fl<=91){
				fl+=32;
			}
			node *temp=root;
			while(temp->alphbt!=fl){
				if(fl>temp->alphbt)
					temp=temp->right;
				else
					temp=temp->left;
			}
			user *utemp=temp->next;
			while(utemp->id!=id){
				utemp=utemp->next;
			}
			return utemp;
		}   
};
usertree ut;
void filltree(){
	ifstream fp;
		fp.open("user.txt");
		string name,id,pass,space;
		float amt;
		while(!fp.eof()){
				fp>>name;
				fp>>id;
				fp>>pass;
				fp>>amt;
			ut.adduser(name,id,pass,amt);
			}
}
class item{
	public:
	string it_name;
	float price;
	item *left;
	item(string n,float p){
		this->it_name=n;
		this->price=p;
		left=NULL;
	}
};
class category{
	public:
	string cname;
	category *down;
	item *left;
	category(string n){
		this->cname=n;
		this->down=NULL;
		this->left=NULL;
	}
	
	void getarrayitem(string nam[],float pr[]){
		item *temp=this->left;
		int i=0;
		while(temp!=NULL){
			nam[i]=temp->it_name;
			pr[i]=temp->price;
			temp=temp->left;
			i++;
		}
	}
	void display(){
		
		item *it=this->left;
		system("cls");
		layout();
		if(pid!="0"){
			gotoxy(50,5);
			cout<<"|NAME: "<<u->name<<" |";
			gotoxy(70,5);
			cout<<"ID: "<<u->id<<" |";
			gotoxy(85,5);
			cout<<"CARD BALANCE: "<<u->c.amt<<" |";
		}
		gotoxy(11,5);
		cout<<"|TABLE NUMBER: "<<tno<<" |";
		ord.displayord();
		gotoxy(20,8);
		cout<<"|Category: "<<this->cname<<" |";
		if(it==NULL){
			gotoxy(30,11);
			cout<<"|No Item available in this category|";
			gotoxy(30,17);
			system("pause");
		}
		else{
			int i=0;
			gotoxy(28,11);
			cout<<"|Item Name|          |Price(in Rs.)|";
			while(it!=NULL){
				gotoxy(30,13+i);
				cout<<i+1<<". "<<it->it_name;
				gotoxy(53,13+i);
				cout<<it->price;
				it=it->left;
				i++;
			}
			i++;
		gotoxy(30,13+i);
		cout<<"Add to Orders: ";
		int ch;
		cin>>ch;
		string nam[40];
		float pr[40];
		category *temp=this;
		temp->getarrayitem(nam,pr);
		cout<<nam[0]<<pr[0];
		addtoorders(nam[ch-1],pr[ch-1]);
		}
		
	}
};
class foodstore{
	public:
	category *froot;
	foodstore(){
		int items;
		string name,cname;
		float price;
		ifstream fp;
		fp.open("food.txt");
		while(!fp.eof()){
			fp>>cname;
			category *newnode=new category(cname);
			category *temp=froot;
			if(froot==NULL){
				froot=newnode;
			}
			else{
				while(temp->down!=NULL)
					temp=temp->down;
				temp->down=newnode;
				temp=temp->down;
			}
			fp>>items;
			while(items--){
				fp>>name;
				fp>>price;
				additem(cname,name,price);		
		 	}
		
	}
}
void additem(string cname,string name,float price){
	category *cat=froot;
	while(cat->cname!=cname){
		cat=cat->down;
	}
	item *temp=cat->left;
		item *newnode=new item(name,price);
		if(temp==NULL){
			cat->left=newnode;
		}
		else{
			while(temp->left!=NULL){
				temp=temp->left;
			}
			temp->left=newnode;
		}
}
	int displaycat(){
		int i=0;
		if(froot==NULL){
			gotoxy(30,13);
			cout<<"Sorry, Nothing is available this time...";
		}
		else{
			category  *temp=froot;
			
			while(temp!=NULL){
				gotoxy(30,12+i*2);
				cout<<i+1<<". "<<temp->cname;
				temp=temp->down;
				i++;
			}
		}
		return i;
	}
	void displayitem(string cname){
		category  *temp=froot;
			while(temp->cname!=cname){
				temp=temp->down;
			}
		temp->display();	
	}
	void getarray(string arr[]){
		int i=0;
		category  *temp=froot;
			while(temp!=NULL){
				arr[i]=temp->cname;
				temp=temp->down;
				i++;
			}
	}
};
foodstore ft;
void additem(string cname,string name,float price){
	ft.additem(cname,name,price);
}
bool check(string id,string pass,string name){
	if(!ut.existuser(id,name,pass)){
		return false;
	}
	return true;	
}
bool idcheck(string id,string name){
	if(!ut.existid(id,name)){
		return true;
	}
	return false;	
}
bool passcheck(string pass,string cpass){
	if(pass!=cpass)
		return false;
	return true;
}
void layout(){
	cout<<"\n\n";
	cout<<"          ****************************************************************************************************          "<<endl;
	cout<<"                                              WELCOME TO HAPPY HOURS CAFE                                          "<<endl;
	cout<<"          ****************************************************************************************************          "<<endl;
	for(int i=0;i<30;i++){
	gotoxy(10,2+i);
	cout<<"*";
	}
	gotoxy(10,40);
	cout<<"****************************************************************************************************           ";
	for(int i=0;i<30;i++){
	gotoxy(110,2+i);
	cout<<"*";
	}
}
void login(){
	system("cls");
	layout();
	gotoxy(11,5);
	string name,id,pass;
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(20,8);
	cout<<"Enter your Name: "<<name;
	gotoxy(20,10);
	cout<<"Enter your Login Id: "<<id;
	gotoxy(20,12);
	cout<<"Enter your Cafe Password: "<<pass;
	gotoxy(37,8);
	cin>>name;
	gotoxy(41,10);
	cin>>id;
	gotoxy(46,12);
	cin>>pass;
	pname=name;
	if(!check(id,pass,name)){
		gotoxy(20,16);
		cout<<"Invalid Id and Password.....";
		gotoxy(20,18);
		cout<<"|1. Login Again! | or |2. Register! |";
		int ch;
		cin>>ch;
		switch(ch){
			case 1: login();
				
			case 2: signup();
			
			default: login();
		}
	}
	else{
		u=ut.getinfo(name,id);
		pid=u->id;
		food();
	}
}
void noRgst(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	string name;
	gotoxy(20,8);
	cout<<"Enter your Name: "<<name;
	gotoxy(37,8);
	cin>>name;
	pname=name;
	pid="0";
	food();
}
void signup(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	string name,id,pass,cpass;
	gotoxy(40,8);
	cout<<"We're Thankful you're here...";
	gotoxy(20,11);
	cout<<"Enter your Name: "<<name;
	gotoxy(20,13);
	cout<<"Choose a unique Id: "<<id;
	gotoxy(20,15);
	cout<<"Create your Cafe Password: "<<pass;
	gotoxy(20,17);
	cout<<"Confirm your Password: "<<cpass;
	gotoxy(37,11);
	cin>>name;
	gotoxy(42,13);
	cin>>id;
	gotoxy(48,15);
	cin>>pass;
	gotoxy(44,17);
	cin>>cpass;
	if(id=="0"){
		gotoxy(20,20);
		cout<<"Invalid Id";
		gotoxy(20,22);
		cout<<"Press any key to Signup Again";
		system("pause");
		signup();
	}
	else if(!passcheck(pass,cpass)){
		gotoxy(20,20);
		cout<<"Your Password doesn't match....";
		gotoxy(20,22);
		cout<<"Please Signup Again....";
		gotoxy(20,24);
		system("pause");
		signup();
	}
	else if(!idcheck(id,name)){
		gotoxy(20,20);
		cout<<"Id already exists....Try a unique one...";
		gotoxy(20,22);
		cout<<"Please Signup Again";
		gotoxy(20,24);
		system("pause");
		signup();
	}
	else{
		float amt=0;
		ut.adduser(name,id,pass,amt);//user added in tree.
		ofstream fp;
		fp.open("user.txt",std::ios_base::app);
		fp<<name<<endl<<id<<endl<<pass<<endl<<amt<<endl;//user added in file
		fp.close();
		system("cls");
		layout();
		gotoxy(11,5);
		cout<<"TABLE NUMBER: "<<tno;
		gotoxy(20,8);
		cout<<"You are succesfully registered....";
		gotoxy(25,10);
		cout<<"You need to recharge your card from the reception....";
		gotoxy(25,12);
		cout<<"Press any key to go back to home page...";
		gotoxy(20,14);
		system("pause");
		enter();
	}
}
void enter(){
	int n;
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(20,8);
	cout<<"1. Login to your Registered Account(20% Discount on food Items)";
	gotoxy(20,10);
	cout<<"2. Continue without Registration(No Discount)";
	gotoxy(20,12);
	cout<<"3. Not registered?Get yourself Registered";
	gotoxy(20,15);
	cout<<"Choice is all yours: ";
	cin>>n;
	switch(n){
		case 1: {
			login();
			break;
		}
		
		case 2: {
			noRgst();
			break;
		}
		
		case 3: {
			signup();
			break;
		}
		
		default: enter();		
	}
}
void getTable(){
	cout<<"Let us know on which Table you're sitting on....";
	gotoxy(20,9);
	cout<<"Enter the Table number:";
	cin>>tno;
	enter();
}
void home(){
	layout();
	gotoxy(20,7);
	getTable();
}
void displayitem(string s){
	ft.displayitem(s);
	
}
void food(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(30,8);
	cout<<"HELLO "<<pname<<" Choose What u want to have....";
	ord.displayord();
	gotoxy(30,10);
	cout<<"| Food Categories |";
	int i=ft.displaycat();
	string arr[40];
	ft.getarray(arr);	//make array of category 
	if(pid!="0"){
		gotoxy(50,5);
		cout<<"|NAME: "<<u->name<<" |";
		gotoxy(70,5);
		cout<<"ID: "<<u->id<<" |";
		gotoxy(85,5);
		cout<<"CARD BALANCE: "<<u->c.amt<<" |";
	}
	if(i==0){
		gotoxy(35,18);
		cout<<"Please go back to Home Page";
		gotoxy(35,19);
		system("pause");
		enter();
	}
	else{
	int ch;
	gotoxy(30,14+2*i+2);
	cout<<"1. |Add in order Cart|";
	gotoxy(30,14+2*i+4);
	cout<<"2. |Delete from order Cart|";
	gotoxy(30,14+2*i+6);
	cout<<"3. |Proceed to Confirm Order|";
	if(pid!="0"){
	gotoxy(30,14+2*i+8);
	cout<<"4. |Log out|";
	}
	else{
		gotoxy(30,14+2*i+8);
		cout<<"4. |Back to Home Page|";
	}
	gotoxy(30,14+2*i+10);
	cin>>ch;
	gotoxy(30,14+2*i+10);
	cout<<" ";
	switch(ch){
		case 1:{
				gotoxy(30,10+2*i+2);
				cout<<"|Enter your Choice for Order| : ";
				cin>>ch;
				displayitem(arr[ch-1]);
				break;
		}
		case 2:{
			deletecart();
			break;
		}
		case 3:{
			confirmorder();
			break;
		}
		case 4:{
			ord.clearcart();
			enter();
			break;
		}
		default: food();
	}
}
}
void addtoorders(string nam,float pr){
	ord.additem(nam,pr);
	food();
}
void deletecart(){
	system("cls");
	layout();
	if(pid!="0"){
		gotoxy(50,5);
		cout<<"|NAME: "<<u->name<<" |";
		gotoxy(70,5);
		cout<<"ID: "<<u->id<<" |";
		gotoxy(85,5);
		cout<<"CARD BALANCE: "<<u->c.amt<<" |";
	}
	int st;
	st=ord.getstatus();
	if(st==0){
		gotoxy(20,8);
		cout<<"Firstly add something to the cart";
		gotoxy(24,10);
		system("pause");
		food();
	}
	else{
		ord.displayord();
		gotoxy(20,8);
		cout<<"Enter the item you want to delete:";
			gotoxy(20,10);
		int ch;
		cin>>ch;
		string arr[40];
		ord.getarray(arr);
		ord.deleteitem(arr[ch-1]);
		gotoxy(25,14);
		cout<<"Item deleted !";
		gotoxy(20,16);
		system("pause");
		food();
	}
}
void confirmorder(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(30,8);
	cout<<"|YOUR ORDER|";
	if(pid!="0"){
		gotoxy(50,5);
		cout<<"|NAME: "<<u->name<<" |";
		gotoxy(70,5);
		cout<<"ID: "<<u->id<<" |";
		gotoxy(85,5);
		cout<<"CARD BALANCE: "<<u->c.amt<<" |";
	}
	int st;
	st=ord.getstatus();
	if(pid!="0"){
		if(ord.total>u->c.amt){
		gotoxy(20,8);
		cout<<"Your total order is greater than your Card amount !";
		gotoxy(24,10);
		system("pause");
		food();
		}
	}
	if(st==0){
		gotoxy(20,8);
		cout<<"Firstly add something to the cart";
		gotoxy(24,10);
		system("pause");
		food();
	}
	else{
		ord.confdisplay();
	}
}
void confirmord(float bl){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	if(pid!="0"){
		gotoxy(50,5);
		cout<<"|NAME: "<<u->name<<" |";
		gotoxy(70,5);
		cout<<"ID: "<<u->id<<" |";
		gotoxy(85,5);
		cout<<"CARD BALANCE: "<<u->c.amt<<" |";
	}
		gotoxy(20,8);
		cout<<"Waiting for Confirmation from the Restaurent";
		int x=1;
		while(x){
			Sleep(1000);
			gotoxy(64,8);
			for(int i=0;i<5;i++){
				cout<<".";
				Sleep(1000);
			}
			gotoxy(64,8);
			for(int i=0;i<5;i++){
				cout<<" ";
			}
			x--;
		}
		if(pid!="0"){
		u->c.amt=(u->c.amt)-bl;
		}//amount  deduction
		gotoxy(30,10);
		cout<<"Ordered Confirmed....";
		gotoxy(20,13);
		system("pause");
		extra();
		
}
void extra(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	if(pid!="0"){
		gotoxy(50,5);
		cout<<"|NAME: "<<u->name<<" |";
		gotoxy(70,5);
		cout<<"ID: "<<u->id<<" |";
		gotoxy(85,5);
		cout<<"CARD BALANCE: "<<u->c.amt<<" |";
	}
	gotoxy(20,8);
	cout<<"You have all done with ordering.";
	gotoxy(20,10);
	cout<<"Here are some extra features";
	gotoxy(25,13);
	cout<<"1. Book your Cab";
	gotoxy(25,15);
	cout<<"2. Play Some Games";
	gotoxy(25,17);
	if(pid!="0")
	cout<<"3. Log Out";
	else
	cout<<"3. Back to Home Page";
	gotoxy(20,20);
	cout<<"|Enter Your Choice|: ";
	int ch;
	cin>>ch;
	switch(ch){
		case 1:{
			bookcab();
			break;
		}
		case 2:{
			games();
			break;
		}
		case 3:{
			enter();
			break;
		}
		default: extra();
	}
}
void fltree(){
string name,id,pass;
	float amt;
	ifstream fp;
    fp.open("user.txt", ios::in);
 	while(!fp.eof()){
		fp>>name;
		fp>>id;
		fp>>pass;
		fp>>amt;
		ut.adduser(name,id,pass,amt);
	}
}
//Main function
int main(){
	home();
return 0;
}


//Shortest path
int minDistance(int dist[], bool visited[])
{

   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (visited[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}


void printSolution(int dist[], int n, int src)
{
    int time,fare,destination,cabType, baseFare,hours[13], minutes[13] , totalFare[13];
    gotoxy(20,25);
	cout<<"|Where do you want to go?|: ";
	cin>>destination;
		system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
    gotoxy(20,8);
    cout<<"Select the type of ride you want: ";
	gotoxy(20,10);
    cout<<"1) Micro";
	gotoxy(20,11);
    cout<<"2) Mini";
	gotoxy(20,12);
    cout<<"3) Prime";
	gotoxy(20,13);
    cout<<"4) Luxury";
    gotoxy(54,8);
    cin>> cabType;
    if(cabType==1)
    {
        baseFare=20;
        fare=10;
    }
    else if(cabType==2)
    {
        baseFare=25;
        fare=15;
    }
    else if(cabType==3)
    {
        baseFare=40;
        fare=25;
    }
    else if(cabType==4)
    {
        baseFare= 100;
        fare= 40;
    }
    
   for (int i = 0; i < V; i++)
   { 
   		time= 15* dist[i];
		hours[i]= time/60;
        minutes[i]= time%60;
    	totalFare[i]= baseFare + fare* dist[i];
    }
    gotoxy(25,15);
    cout<<src<<"----->"<<destination;
    cout<<"       For smallest path..";
	gotoxy(15,17);
    cout<<"|Distance|: "<<dist[destination];
	gotoxy(35,17);
    cout<<"|Time Taken|: "<<hours[destination]<<":"<<minutes[destination];; 
	gotoxy(60,17);
    cout<<"|Fare|: "<<totalFare[destination];
    }


void dijkstra(int graph[V][V], int src)
{
     int dist[V];

     bool visited[V];

     for (int i = 0; i < V; i++){

    	dist[i] = INT_MAX, visited[i] = false;

     }
          dist[src] = 0;


     for (int count = 0; count < V-1; count++)
     {

       int u = minDistance(dist, visited);

       visited[u] = true;


       for (int v = 0; v < V; v++)
        {

         if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
         {
        dist[v] = dist[u] + graph[u][v];
        }
        }

     }
	printSolution(dist, V,src);
}
 
void bookcab()
{   
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	int c;
    int x;
	
    char number[10];
	char a;
   	gotoxy(20,8);
    cout<<"|Enter your phone number|: ";
    cin>>number;
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(20,8);
	cout<<"You are at JIIT Sector 62 !";
	gotoxy(24,11);
	cout<<"Choose your Destinaton.....";
	gotoxy(25,12);
    cout<<" 1) Sector 55 "<<endl;
    gotoxy(25,13);
    cout<<" 2) Sector 5 "<<endl;
    gotoxy(25,14);
    cout<<" 3) Sector 16 "<<endl;
    gotoxy(25,15);
    cout<<" 4) Sector 18 "<<endl;
    gotoxy(25,16);
    cout<<" 5) Sector 45 "<<endl;
    gotoxy(25,17);
    cout<<" 6) Sector 37 "<<endl;
    gotoxy(25,18);
    cout<<" 7) Sector 52 "<<endl;
    gotoxy(25,19);
    cout<<" 8) Sector 72 "<<endl;
    gotoxy(25,20);
    cout<<" 9) Sector 120"<<endl;
    gotoxy(25,21);
    cout<<"10) Sector 64 "<<endl;
    gotoxy(25,22);
    cout<<"11) Sector 115"<<endl;
    gotoxy(25,23);
    cout<<"12) Sector 75 "<<endl;
    gotoxy(25,24);
    cout<<"13) Sector 110 "<<endl;
    c=0;
    int graph[V][V] = {{0, 4, 0, 0, 0, 0, 7, 6, 0, 9, 4, 0, 0, 0},
                      {4, 0, 12, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 12, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 5, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 6, 0, 2, 0, 5, 3, 0, 0, 0, 0, 0, 0, 12},
                      {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 8, 7},
                      {7, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, 0, 0},
                      {6, 0, 0, 0, 0, 0, 5, 0, 2, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 3, 0},
                      {9, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 6, 0, 0},
                      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 5, 0},
                      {0, 0, 0, 0, 0, 12, 0, 0, 3, 0, 0, 5, 0, 8},
                      {0, 0, 0, 0, 12, 7, 0, 0, 0, 0, 0, 0, 8, 0}};

    dijkstra(graph,c);
        gotoxy(20,19);
		cout<<"Take the CAB to your doorstep!!!!";
		gotoxy(20,20);
		system("pause");
		extra();
}

void games(){
	system("cls");
	layout();
	gotoxy(11,5);
	cout<<"TABLE NUMBER: "<<tno;
	gotoxy(20,8);
	cout<<"|List of Games|";
	gotoxy(20,10);
	cout<<"1. Snake Game";
	gotoxy(20,11);
	cout<<"2. Tatrix";
	int ch;
	cin>>ch;
	switch(ch){
		case 1:{
			snake();
			break;
		}
		case 2: {
			stack();
			extra();
			break;
		}
		default: games();
	}
}
