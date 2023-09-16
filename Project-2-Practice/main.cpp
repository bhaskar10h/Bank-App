#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string password;
    double balance;
    int accountType; // 1: Saving, 2: Business, 3: Industrial

public:
    BankAccount(string accNum, string pass, int type) {
        accountNumber = accNum;
        password = pass;
        balance = 0.0;
        accountType = type;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    bool verifyPassword(string pass) {
        return password == pass;
    }

    double getBalance() {
        return balance;
    }

    int getAccountType() {
        return accountType;
    }

    void deposit(double amt) {
        balance += amt;
        cout << "You have deposited an amount of $" << amt << ". Your new balance is $" << balance << endl;
    }

    bool withdraw(double amt) {
        if (amt <= balance) {
            balance -= amt;
            cout << "You have withdrawn an amount of $" << amt << ". Your new balance is $" << balance << endl;
            return true;
        }
        else {
            cout << "Insufficient balance. Your current balance is $" << balance << endl;
            return false;
        }
    }

    void displayDetails() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: ";
        switch (accountType) {
        case 1: cout << "Saving Account" << endl; break;
        case 2: cout << "Business Account" << endl; break;
        case 3: cout << "Industrial Account" << endl; break;
        default: cout << "Unknown" << endl; break;
        }
        cout << "Current Balance: $" << balance << endl;
    }

    void changeAccountType(int newType) {
        accountType = newType;
        cout << "Account type changed successfully!" << endl;
    }
};

class BankServer {
private:
    vector<BankAccount> accounts;

public:
    BankAccount* createAccount(string accNum, string pass, int type) {
        BankAccount newAccount(accNum, pass, type);
        accounts.push_back(newAccount);
        return &accounts.back(); // Return a pointer to the newly created account
    }

    BankAccount* findAccount(string accNum) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return nullptr; // Account not found
    }

    void showMenu() {
        cout << "Menu Options:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
    }

    void handleMenuOption(int option) {
        switch (option) {
        case 1: {
            string accNum, pass;
            int accType;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Password: ";
            cin >> pass;
            cout << "Enter Account Type (1 for Saving, 2 for Business, 3 for Industrial): ";
            cin >> accType;
            createAccount(accNum, pass, accType);
            cout << "Account created successfully!" << endl;
            break;
        }
        case 2: {
            string inputAccNum, inputPass;
            cout << "Enter Account Number: ";
            cin >> inputAccNum;
            cout << "Enter Password: ";
            cin >> inputPass;
            BankAccount* userAccount = findAccount(inputAccNum);
            if (userAccount != nullptr && userAccount->verifyPassword(inputPass)) {
                int menuOption;
                do {
                    showAccountMenu();
                    cout << "Enter your choice: ";
                    cin >> menuOption;
                    handleAccountMenuOption(userAccount, menuOption);
                } while (menuOption != 5);
            }
            else {
                cout << "Invalid account number or password. Please try again." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }

    void showAccountMenu() {
        cout << "Account Options:" << endl;
        cout << "1. Display Account Details" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Change Account Type" << endl;
        cout << "5. Logout" << endl;
    }

    void handleAccountMenuOption(BankAccount* account, int option) {
        switch (option) {
        case 1:
            account->displayDetails();
            break;
        case 2: {
            double depositAmount;
            cout << "Enter the amount to deposit: $";
            cin >> depositAmount;
            account->deposit(depositAmount);
            break;
        }
        case 3: {
            double withdrawalAmount;
            cout << "Enter the amount to withdraw: $";
            cin >> withdrawalAmount;
            account->withdraw(withdrawalAmount);
            break;
        }
        case 4: {
            int newType;
            cout << "Enter the new account type (1 for Saving, 2 for Business, 3 for Industrial): ";
            cin >> newType;
            account->changeAccountType(newType);
            break;
        }
        case 5:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }
};

int main() {
    BankServer bankServer;

    int menuOption;
    do {
        bankServer.showMenu();
        cout << "Enter your choice: ";
        cin >> menuOption;
        bankServer.handleMenuOption(menuOption);
    } while (menuOption != 3);

    return 0;
}
