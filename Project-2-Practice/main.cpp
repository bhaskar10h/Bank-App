#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string password;
    string pin; // New member variable for pin number
    double balance;
    int accountType; // 1: Saving, 2: Business, 3: Industrial

public:
    BankAccount(string accNum, string pass, string pinNum, int type) {
        accountNumber = accNum;
        password = pass;
        pin = pinNum; // Initialize pin number
        balance = 0.0;
        accountType = type;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    bool verifyPassword(string pass) {
        return password == pass;
    }

    bool verifyPin(string pinNum) {
        return pin == pinNum;
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
    int maxLoginAttempts; // New member variable for maximum login attempts
    int loginAttempts; // New member variable to track login attempts
    time_t lastActivityTime; // New member variable to track last activity time

public:
    BankServer() {
        maxLoginAttempts = 3;
        loginAttempts = 0;
        lastActivityTime = time(0);
    }

    BankAccount* createAccount(string accNum, string pass, string pin, int type) {
        BankAccount newAccount(accNum, pass, pin, type);
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

    bool sendOTP(string phoneNumber) {
        // Code to send OTP through SMS
        // Return true if OTP sent successfully, false otherwise
        return true; // Assuming OTP is always sent successfully for this example
    }

    bool verifyOTP(string otp) {
        // Code to verify OTP
        // Return true if OTP is valid, false otherwise
        return otp == "1234"; // Assuming OTP is "1234" for this example
    }

    void showMenu() {
        cout << "Menu Options:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
    }

    void handleMenuOption(int option) {
        if (option == 2 && difftime(time(0), lastActivityTime) > 300) {
            cout << "Session timed out. Please log in again." << endl;
            return;
        }
        if (option == 2) {
            loginAttempts = 0;
        }

        switch (option) {
        case 1: {
            string accNum, pass, pin;
            int accType;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Password (at least 8 characters with uppercase, lowercase, and digits): ";
            cin >> pass;
            cout << "Enter Pin (4 digits): ";
            cin >> pin;
            cout << "Enter Account Type (1 for Saving, 2 for Business, 3 for Industrial): ";
            cin >> accType;
            createAccount(accNum, pass, pin, accType);
            cout << "Account created successfully!" << endl;
            break;
        }
        case 2: {
            string inputAccNum, inputPass, inputPin;
            cout << "Enter Account Number: ";
            cin >> inputAccNum;
            cout << "Enter Password: ";
            cin >> inputPass;
            BankAccount* userAccount = findAccount(inputAccNum);
            if (userAccount != nullptr && userAccount->verifyPassword(inputPass)) {
                cout << "Enter Pin: ";
                cin >> inputPin;
                if (userAccount->verifyPin(inputPin)) {
                    string phoneNumber;
                    cout << "Enter Phone Number: ";
                    cin >> phoneNumber;
                    if (sendOTP(phoneNumber)) {
                        string otp;
                        cout << "Enter OTP sent to your phone: ";
                        cin >> otp;
                        if (verifyOTP(otp)) {
                            lastActivityTime = time(0); 
                            int menuOption;
                            do {
                                showAccountMenu();
                                cout << "Enter your choice: ";
                                cin >> menuOption;
                                handleAccountMenuOption(userAccount, menuOption);
                            } while (menuOption != 5);
                        }
                        else {
                            cout << "Invalid OTP. Please try again." << endl;
                        }
                    }
                    else {
                        cout << "Failed to send OTP. Please try again later." << endl;
                    }
                }
                else {
                    cout << "Invalid pin. Please try again." << endl;
                }
            }
            else {
                cout << "Invalid account number or password. Please try again." << endl;
                loginAttempts++;
                if (loginAttempts >= maxLoginAttempts) {
                    cout << "Too many failed login attempts. Please try again later." << endl;
                    exit(1);
                }
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
    srand(time(0));

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
