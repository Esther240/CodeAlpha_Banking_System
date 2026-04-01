#include <iostream>
#include <vector>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    float amount;

    Transaction(string t, float a) {
        type = t;
        amount = a;
    }
};

// Account class
class Account {
public:
    int accountNumber;
    float balance;
    vector<Transaction> history;

    Account(int accNo) {
        accountNumber = accNo;
        balance = 0;
    }

    void deposit(float amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "✅ Deposited\n";
    }

    void withdraw(float amount) {
        if (amount > balance) {
            cout << "❌ Insufficient balance\n";
            return;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "✅ Withdrawn\n";
    }

    void showDetails() {
        cout << "Balance: " << balance << endl;
        cout << "--- Transactions ---\n";
        for (auto &t : history) {
            cout << t.type << " : " << t.amount << endl;
        }
    }
};

// Customer class
class Customer {
public:
    string name;
    Account account;

    Customer(string n, int accNo) : account(accNo) {
        name = n;
    }
};

// Find customer by account number
Customer* findCustomer(vector<Customer> &customers, int accNo) {
    for (auto &c : customers) {
        if (c.account.accountNumber == accNo) {
            return &c;
        }
    }
    return nullptr;
}

int main() {
    vector<Customer> customers;
    int choice;

    do {
        cout << "\n===== BANK SYSTEM =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. Show Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int accNo;
        float amount;

        switch (choice) {

            case 1: {
                string name;
                cout << "Enter name: ";
                cin >> name;

                cout << "Enter account number: ";
                cin >> accNo;

                customers.push_back(Customer(name, accNo));
                cout << "✅ Customer created\n";
                break;
            }

            case 2: {
                cout << "Enter account number: ";
                cin >> accNo;

                Customer* c = findCustomer(customers, accNo);
                if (!c) {
                    cout << "❌ Account not found\n";
                    break;
                }

                cout << "Enter amount: ";
                cin >> amount;

                c->account.deposit(amount);
                break;
            }

            case 3: {
                cout << "Enter account number: ";
                cin >> accNo;

                Customer* c = findCustomer(customers, accNo);
                if (!c) {
                    cout << "❌ Account not found\n";
                    break;
                }

                cout << "Enter amount: ";
                cin >> amount;

                c->account.withdraw(amount);
                break;
            }

            case 4: {
                int fromAcc, toAcc;
                cout << "From account: ";
                cin >> fromAcc;
                cout << "To account: ";
                cin >> toAcc;

                Customer* sender = findCustomer(customers, fromAcc);
                Customer* receiver = findCustomer(customers, toAcc);

                if (!sender || !receiver) {
                    cout << "❌ Invalid account\n";
                    break;
                }

                cout << "Enter amount: ";
                cin >> amount;

                if (amount > sender->account.balance) {
                    cout << "❌ Insufficient funds\n";
                    break;
                }

                sender->account.withdraw(amount);
                receiver->account.deposit(amount);

                cout << "✅ Transfer successful\n";
                break;
            }

            case 5: {
                cout << "Enter account number: ";
                cin >> accNo;

                Customer* c = findCustomer(customers, accNo);
                if (!c) {
                    cout << "❌ Account not found\n";
                    break;
                }

                cout << "Name: " << c->name << endl;
                c->account.showDetails();
                break;
            }

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 6);

    return 0;
}