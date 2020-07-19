/*********************************************************************************************************

This project is the demonstration of bank management system.
It creates a bank account for user, display the account details, modify the details of existing account,
deposite money for user, withdraw money for user, gives a record of existing bank accounts

It accepts the unique entry of account number from user so that each account holder will have unique 
account number for safety purpose.

The binary file created for this project is attached with this source code in folder
Also the UML diagram(ppt) for this project is attached with this source code.

**********************************************************************************************************/


//Header files required for a project

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//Defining a class to make a bank management system

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;

	public:
		void create_account();		//function to get data from user
		void show_account() const;	//function to show account information
		void modify();				//function to add new data, modify existing one
		void dep(int);				//function to accept amount and add to balance amount (deposite money)
		void draw(int);				//function to accept amount and subtract from balance amount (withdraw money)
		void report() const;		//function to show data in tabular format	
		int retacno() const;		//function to return account number
		int retdeposit() const;		//function to return balance amount
		char rettype() const;		//function to return type of account
} ac1;      	  

//defining functions declared in class

//function to create account
void account::create_account()
{
	int found = 0, temp=1;
	fstream fio;
	long pos;
	//open original binary file in read and write mode
	fio.open("Account_details.dat", ios::binary | ios::in |ios::out);
	cout<<"\nEnter Account Number :"<<endl;
	cin>>acno;
	
	//To check if the entered account number already exists. 
	//If it already exists ask user to enter another account number
	
	while(1){
		temp = 1;
		fio.seekg(0);
		while(!fio.eof()){
			pos = fio.tellg();
			fio.read((char *)(&ac1), sizeof(ac1));
			if(ac1.retacno() == acno){
				cout<< "This ac no already exist" << endl;
				temp = 0;
				break;
			}
					
		}
				
		if(!temp){
			cout<<"\nEnter Account Number :"<<endl;
			cin>>acno;
		}			
		else
			break;
	}

	cout<<"\n\nEnter The Name of The Account Holder : "<<endl;
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account: C for current, S for saving: ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : "<<endl;
	cin>>deposit;
	while(!found){
		int flag = 1;
		if((type == 'C' && deposit < 1000) || (type == 'S' && deposit < 500)){
			cout << "Deposited amount is not sufficient for the type of account chosen" << "\n" << endl;
			cout << "Please deposite sufficient amount to create account" << "\n" << endl;
			cout<<"\nEnter The Initial amount(>=1000 for Saving and >=1500 for current ) : "<<endl;
			cin>>deposit;
			flag = 0;
		}
		if(flag)
			break;
	
	
	}
	cout<<"\n\nAccount Created..";
}

//function to show account details
void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : "<< name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


//function to modify the details of existing account
void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	
}

//function to deposite money in bank account	
void account::dep(int x)
{
	deposit+=x;
}
	
//function to withdraw money from bank account	
void account::draw(int x)
{
	deposit-=x;
}
	
//function to print account summary	
void account::report() const
{
	cout << acno << setw(30) << name << setw(40) << type << setw(20) << deposit << endl;
}

//function to return account number	
int account::retacno() const
{
	return acno;
}

//function to return amount deposited
int account::retdeposit() const
{
	return deposit;
}

//function to return type of account
char account::rettype() const
{
	return type;
}


//function declarations to process data


void write_account();				//function to write record in binary file
void display_sp(int);				//function to display account details given by user
void modify_account(int);			//function to modify existing record of file
void delete_account(int);			//function to delete record of file
void display_all();					//function to display all account details
void deposit_withdraw(int, int); 	//function to desposit/withdraw amount for given account
void intro();						//to print introduction on screen

//main function begins here

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

//main function ends here


//function to write in file


void write_account()
{
	account ac;
	ofstream outFile;
	//open original binary file in app mode to append new record
	outFile.open("Account_details.dat",ios::binary|ios::app);
	ac.create_account();	
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


//function to read specific record from file


void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	//open original binary file in read mode
	inFile.open("Account_details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



//function to modify record of file


void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	//open original binary file in read and write mode
	File.open("Account_details.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//function to delete record of file


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	//open original binary file in read mode
	inFile.open("Account_details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	
	//copy all the record from original binary file to new temporary binary file created except the record 
	//which is to be deleted. Then remove the original binary file and rename the temporary file with the 
	//name of original file
	
	remove("Account_details.dat");
	rename("Temp.dat","Account_details.dat");
	cout<<"\n\n\tRecord Deleted ..";
}


//function to display all accounts deposit list


void display_all()
{
	account ac;
	ifstream inFile;
	//open original binary file in read mode
	inFile.open("Account_details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"******************************************************************************************************\n";
	cout<<"A/c no." << setw(30) << "NAME" << setw(40) << "Type" << setw(20) << "Balance" << "\n";
	cout<<"******************************************************************************************************\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


//function to deposit and withdraw amounts


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	//open original binary file in read and write mode
	File.open("Account_details.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


//Introduction Function


void intro()
{
	cout<<"Object Oriented Programming and Design Project";
	cout<<"\n\n\n\t  BANK MANAGEMENT SYSTEM";
	cout<<"\n\n\n\n\tMade By : Vaishnavi Agrawal";
	cout<<"\n\n\tMIS : 111707071";
	cout<<"\n\n\tBranch: ENTC";
	cout<<"\n\n\tCollege of Engineering Pune";
	cin.get();
}


//End of project

