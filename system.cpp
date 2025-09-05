#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string name;
    double balance;

    BankAccount(int accNo, string accName, double bal = 0) {
        accountNumber = accNo;
        name = accName;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << " successfully!\n";
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn " << amount << " successfully!\n";
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    void showBalance() {
        cout << "Account No: " << accountNumber
             << " | Name: " << name
             << " | Balance: " << balance << "\n";
    }

    // Save account to file
    void save(ofstream &out) {
        out << accountNumber << " " << name << " " << balance << "\n";
    }
};

vector<BankAccount> accounts;

// Load all accounts from file
void loadAccounts() {
    ifstream in("accounts.txt");
    int accNo;
    string name;
    double bal;
    while (in >> accNo >> name >> bal) {
        accounts.push_back(BankAccount(accNo, name, bal));
    }
    in.close();
}

// Save all accounts to file
void saveAccounts() {
    ofstream out("accounts.txt");
    for (auto &acc : accounts) {
        acc.save(out);
    }
    out.close();
}

// Find account by account number
BankAccount* findAccount(int accNo) {
    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) return &acc;
    }
    return nullptr;
}

int main() {
    loadAccounts(); // load saved accounts

    int choice;
    while (true) {
        cout << "\n==== Banking Menu ====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            cout << "Enter Account No: ";
            cin >> accNo;
            cout << "Enter Name: ";
            cin >> name;
            accounts.push_back(BankAccount(accNo, name));
            cout << "Account created!\n";
        }
        else if (choice == 2) {
            int accNo; double amount;
            cout << "Enter Account No: ";
            cin >> accNo;
            BankAccount *acc = findAccount(accNo);
            if (acc) {
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc->deposit(amount);
            } else cout << "Account not found!\n";
        }
        else if (choice == 3) {
            int accNo; double amount;
            cout << "Enter Account No: ";
            cin >> accNo;
            BankAccount *acc = findAccount(accNo);
            if (acc) {
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc->withdraw(amount);
            } else cout << "Account not found!\n";
        }
        else if (choice == 4) {
            int accNo;
            cout << "Enter Account No: ";
            cin >> accNo;
            BankAccount *acc = findAccount(accNo);
            if (acc) acc->showBalance();
            else cout << "Account not found!\n";
        }
        else if (choice == 5) {
            saveAccounts();
            cout << "Goodbye! Accounts saved.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
