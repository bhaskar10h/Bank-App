#include<iostream>
#include<string>

using namespace std; 

//Bank Details of person 

class bankServer {
private: 
	int optn;
	string person;
	double amount;
	double balance;

public:

	void personBalance(double bal) {
		this->balance = bal;
	}

	void window(){
		cout << "Your Account type : " << endl;
		cout << "--------------------" << endl;
		cout << "1. Saving Account " << endl;
		cout << "2. Business Account " << endl;
		cout << "3. Industrial Account " << endl;
	}
	
	void accHolder(double amount, int option) {
	
		this->amount = amount;
		this->optn = option;
		
		cin >> option;
		switch (option) {
		case 1:
			cout << "From our Database, your account is of 'Saving Account' type " << endl;
			break;
		
		case 2:
			cout << "From our Database, your account is of 'Business Account' type " << endl;
			break;
		
		case 3:
			cout << "From our Database, your account is of 'Industrial Account' type " << endl;
			break;
		
		default:
			cout << "Invalid Option. Please choose from the list which is displayed on the window" << endl;
			break;
		}

		if (option == 1) {
			  double interest;
			  interest = 7.33 / 100;
			  balance = (balance + amount) * interest;
			  cout << "Your Balance in saving account is : ";
			  cout << balance << endl;
			  return;
			}
		else if(option==2){
			double interest;
			interest = 11.43 / 100;
			balance = (balance + amount) * interest;
			cout << "Your Balance in saving account is : ";
			cout << balance << endl;
			return;
		}

		else if (option == 3) {
			double interest;
			interest = 21.65 / 100;
			balance = (balance + amount) * interest;
			cout << "Your Balance in saving account is : ";
			cout << balance << endl;
			return;
		}

		else {
			cout << "Can't read from sever database." << endl;
		}

		
	  
	}

	void withdrawls(double amt, string name) {
		this->amount = amt;
		this->person = name;

		cout << "Dear Account-holder, " << name << ", you have chosen the withdrwal option: " << endl;
		
		if (balance >= amount) {
			balance -= amount;
			cout << "You have withdrawl an amount of " << amount << " from your account" << endl;
			cout << "Your Balance is : " << balance << endl;
			return;
		}

		else if (amount > balance) {
			cout << "You have an insufficient balance in your account" << endl;
			cout << "Your current balance of your account is : " << balance << endl;
			return;
		}

	}

};


int main() {

	bankServer my_Info;
	my_Info.personBalance(100000.00);
	my_Info.window();
	my_Info.accHolder(2500.00, 1);
	my_Info.withdrawls(1500.00, "Anonymous");


	
	cin.get();
	return 0;
}