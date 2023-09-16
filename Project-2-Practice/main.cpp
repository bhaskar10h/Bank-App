#include<iostream>
#include<string>
using namespace std;

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

    void window() {
        cout << "Your Account type : " << endl;
        cout << "--------------------" << endl;
        cout << "1. Saving Account " << endl;
        cout << "2. Business Account " << endl;
        cout << "3. Industrial Account " << endl;
    }

    void accHolder(double amount, int option) {
        this->amount = amount;
        this->optn = option;
        cout << "Enter your option : ";
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
        else if (option == 2) {
            double interest;
            interest = 11.43 / 100;
            balance = (balance + amount) * interest;
            cout << "Your Balance in business account is : ";
            cout << balance << endl;
            return;
        }
        else if (option == 3) {
            double interest;
            interest = 21.65 / 100;
            balance = (balance + amount) * interest;
            cout << "Your Balance in industrial account is : ";
            cout << balance << endl;
            return;
        }
        else {
            cout << "Can't read from server database." << endl;
        }
    }

    void withdrawls(double amt, string name) {
        this->amount = amt;
        this->person = name;

        cout << "Dear Account-holder, " << name << ", you have chosen the withdrawal option: " << endl;

        if (balance >= amount) {
            balance -= amount;
            cout << "You have withdrawn an amount of " << amount << " from your account" << endl;
            cout << "Your Balance is : " << balance << endl;
            return;
        }
        else if (amount > balance) {
            cout << "You have insufficient balance in your account" << endl;
            cout << "Your current balance of your account is : " << balance << endl;
            return;
        }
    }

    void deposit(double amt, string name) {
        this->amount = amt;
        this->person = name;

        balance += amount;
        cout << "Dear Account-holder, " << name << ", you have deposited an amount of " << amount << " into your account" << endl;
        cout << "Your Balance is : " << balance << endl;
    }

    void displayDetails(string name) {
        this->person = name;

        cout << "Account Holder Name: " << name << endl;
        cout << "Account Type: ";
        switch (optn) {
        case 1: cout << "Saving Account" << endl; break;
        case 2: cout << "Business Account" << endl; break;
        case 3: cout << "Industrial Account" << endl; break;
        default: cout << "Unknown" << endl; break;
        }
        cout << "Current Balance: " << balance << endl;
    }

    void changeAccountType(int newOption) {
        this->optn = newOption;
        cout << "Account type changed successfully!" << endl;
    }

    void showMenu() {
        cout << "Menu Options:" << endl;
        cout << "1. Display Account Details" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Change Account Type" << endl;
        cout << "5. Exit" << endl;
    }

    void handleMenuOption(int option) {
        switch (option) {
        case 1: displayDetails(person); break;
        case 2:
            double depositAmount;
            cout << "Enter the amount to deposit: ";
            cin >> depositAmount;
            deposit(depositAmount, person);
            break;
        case 3:
            double withdrawalAmount;
            cout << "Enter the amount to withdraw: ";
            cin >> withdrawalAmount;
            withdrawls(withdrawalAmount, person);
            break;
        case 4:
            int newOption;
            cout << "Enter the new account type (1 for Saving, 2 for Business, 3 for Industrial): ";
            cin >> newOption;
            changeAccountType(newOption);
            break;
        case 5: cout << "Exiting..." << endl; exit(0);
        default: cout << "Invalid option. Please try again." << endl;
        }
    }
};

int main() {
    bankServer my_Info;
    my_Info.personBalance(100000.00);

    int menuOption;
    do {
        my_Info.showMenu();
        cout << "Enter your choice: ";
        cin >> menuOption;
        my_Info.handleMenuOption(menuOption);
    } while (menuOption != 5);

    return 0;
}
