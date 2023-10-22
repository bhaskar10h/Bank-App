#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

class BankAccount {
private:
    string accountNumber;
    string password;
    string pin;
    double balance;
    int accountType;
    vector<pair<string, double>> transactionHistory; 
    double interestRate;

public:
    BankAccount(string accNum, string pass, string pinNum, int type, double interest)
        : accountNumber(accNum), password(pass), pin(pinNum), balance(0.0), accountType(type), interestRate(interest) {}

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
        recordTransaction("Deposit", amt);
    }

    bool withdraw(double amt) {
        if (amt <= balance) {
            balance -= amt;
            cout << "You have withdrawn an amount of $" << amt << ". Your new balance is $" << balance << endl;
            recordTransaction("Withdrawal", amt);
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

    void recordTransaction(string transactionType, double amount) {
        transactionHistory.push_back(make_pair(transactionType, amount));
    }

    void displayTransactionHistory() {
        cout << "Transaction History:" << endl;
        for (const auto& transaction : transactionHistory) {
            cout << "Type: " << transaction.first << ", Amount: $" << transaction.second << endl;
        }
    }

    void applyInterest() {
        double interestAmount = balance * (interestRate / 100);
        balance += interestAmount;
        cout << "Interest of $" << interestAmount << " applied. Your new balance is $" << balance << endl;
        recordTransaction("Interest", interestAmount);
    }

    void changePassword(string newPassword) {
        password = newPassword;
        cout << "Password changed successfully!" << endl;
    }
};

class BankServer {
private:
    vector<BankAccount> accounts;
    int maxLoginAttempts;
    int loginAttempts;
    time_t lastActivityTime;

public:
    BankServer() {
        maxLoginAttempts = 3;
        loginAttempts = 0;
        lastActivityTime = time(0);
    }

    BankAccount* createAccount(string accNum, string pass, string pin, int type, double interest) {
        BankAccount newAccount(accNum, pass, pin, type, interest);
        accounts.push_back(newAccount);
        return &accounts.back();
    }

    BankAccount* findAccount(string accNum) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    bool sendOTP(string phoneNumber) {
        return true;
    }

    bool verifyOTP(string otp) {
        return otp == "1234";
    }

    void showMenu() {
        cout << "Menu Options:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. View All Accounts" << endl;
        cout << "4. Close Account" << endl;
        cout << "5. Exit" << endl;
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
                double interest;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Password (at least 8 characters with uppercase, lowercase, and digits): ";
                cin >> pass;
                cout << "Enter Pin (4 digits): ";
                cin >> pin;
                cout << "Enter Account Type (1 for Saving, 2 for Business, 3 for Industrial): ";
                cin >> accType;
                cout << "Enter Interest Rate: ";
                cin >> interest;
                createAccount(accNum, pass, pin, accType, interest);
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
                                } while (menuOption != 6);
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
                viewAllAccounts();
                break;
            case 4: {
                string accNum;
                cout << "Enter Account Number to close: ";
                cin >> accNum;
                closeAccount(accNum);
                break;
            }
            case 5:
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
        cout << "5. Display Transaction History" << endl;
        cout << "6. Apply Interest" << endl;
        cout << "7. Change Password" << endl;
        cout << "8. Logout" << endl;
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
                account->displayTransactionHistory();
                break;
            case 6:
                account->applyInterest();
                break;
            case 7: {
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                changePassword(account, newPassword);
                break;
            }
            case 8:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    void viewAllAccounts() {
        for (const auto& account : accounts) {
            account.displayDetails();
            cout << "--------------------------" << endl;
        }
    }

    void closeAccount(string accNum) {
        auto it = find_if(accounts.begin(), accounts.end(),
            [accNum](const BankAccount& acc) { return acc.getAccountNumber() == accNum; });

        if (it != accounts.end()) {
            accounts.erase(it);
            cout << "Account " << accNum << " closed successfully." << endl;
        }
        else {
            cout << "Account not found." << endl;
        }
    }

    void changePassword(BankAccount* account, string newPassword) {
        account->changePassword(newPassword);
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
    } while (menuOption != 5);

    return 0;
}
