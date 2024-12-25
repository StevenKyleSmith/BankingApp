/*
 *
 * Created on December 25, 2024, 4:17 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void clearScreen();
class BankAccount;
class System
{
public:
    void createAccount(const string name, double initialBalance);
    BankAccount* findAccount(const string& accountNumber);
    void saveToFile(const string& fileName);
    vector<BankAccount> getAccounts() const;
private:
    vector<BankAccount> accounts;
};
class BankAccount 
{
public:
    BankAccount();
    BankAccount(string accNumber, string accName, double initialBalance);
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
    string getAccountNumber() const;
    string getName() const;
    void displayTransactions() const;
private: 
    string id;
    string name;
    double balance;
    vector<string> transactions;
};
/*
 * 
 */
int main(int argc, char** argv)
{
    System bankingSystem;
    int choice;
    string name;
    double initialDeposit;
    string option;
    string userAccNum;
    BankAccount* verifyAccount;
    double deposit;
    vector<BankAccount> openAccounts;
    string case2Option;
    do
    {
    cout << "Welcome to the Banking System Simulation" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. View Balance" << endl;
    cout << "5. Transaction History" << endl;
    cout << "6. Exit" << endl;
    cout << endl << "Enter your choice: ";
    cin >> choice;
    
    switch(choice)
    {
        case 1:
            clearScreen();
            cin.ignore();
            cout << "    ==|Account Creation|==" << endl;
            cout << "______________________________" << endl;
            cout << "Please enter your first and last name: " << endl;
            getline(cin, name);
            cout << "Please enter your initial deposit amount: ";
            cin >> initialDeposit;
            while(initialDeposit < 0)
            {
                cout << "Cannot deposit negative funds, please enter a positive amount: ";
                cin >> initialDeposit;
            }
            bankingSystem.createAccount(name, initialDeposit);
            bankingSystem.saveToFile("accounts.txt");
            cout << "Account successfully created!" << endl;
            cin.ignore();
            break;
        case 2:
            clearScreen();
            cin.ignore();
            cout << "        ==|Deposits|==" << endl;
            cout << "______________________________" << endl;
            cout << "|LOGIN|" << endl;
            cout << "Please enter your Account number: ";
            cin >> userAccNum;
            verifyAccount = bankingSystem.findAccount(userAccNum);
            if(verifyAccount != nullptr)
            {
                do
                {
                    cout << "Please enter deposit amount: " << endl;
                    cin >> deposit;
                    while(deposit < 0)
                    {
                        cout << "Cannot deposit negative funds, please enter a positive amount: ";
                        cin >> deposit;
                    }
                    cout << endl << "Account Number: " << userAccNum << endl
                            << "Amount to Deposit: " << fixed << setprecision(2) 
                            << deposit << endl;
                    
                    verifyAccount->deposit(deposit);
                    cout << "Deposit successful! " << endl;
                    bankingSystem.saveToFile("accounts.txt");
                    
                    cout << "Would you like to make another deposit? (y/n)" << endl;
                    cin >> case2Option;
                }while(tolower(case2Option[0]) == 'y');
            }
            else
            {
             cout << "Account Not Found. Please enter a valid account number in"
                     " order to make deposits." << endl;   
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        default: 
            cout << "Not a valid option." << endl;
    }  
    cout << "Return to main menu?(y/n)" << endl;
    cin >> option;
    clearScreen();


}while(tolower(option[0] == 'y'));
    return 0;
}
vector<BankAccount> System::getAccounts() const
{
    return accounts;
}
void System::saveToFile(const string& fileName)
{
    ofstream file(fileName);
    if(file.is_open())
    {
        for(int i = 0; i < accounts.size(); i++)
        {
            file << accounts[i].getAccountNumber() << ", " 
                    << accounts[i].getName() << ", " << 
                    accounts[i].getBalance() << endl;
        }
        file.close();
        cout << "Data saved to file" << endl;
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}
BankAccount* System::findAccount(const string& accountNumber)
{
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].getAccountNumber() == accountNumber)
        {
            return &accounts[i];
        }
    }
    return nullptr;
}
void System::createAccount(const string name, double initialBalance)
{
    string accountNumber = "ACC" + to_string(accounts.size() + 1);
    accounts.emplace_back(accountNumber, name, initialBalance);
    cout << "Account successfully created! Account Number: " << accountNumber << endl;
}
void BankAccount::displayTransactions() const
{
    for(int i = 0; i < transactions.size(); i++)
    {
        cout << i << endl;
    }
}
string BankAccount::getName() const
{
    return name;
}
string BankAccount::getAccountNumber() const
{
    return id;
}
double BankAccount::getBalance() const
{
    return balance;
}
void BankAccount::withdraw(double amount)
{
    if(amount <= balance)
    {
        balance-=amount;
        transactions.push_back("Withdrawal: $" + to_string(amount));
    }
    else
    {
        cout << "Insufficient funds!";
    }
    
}
void BankAccount::deposit(double amount)
{
    balance+=amount;
    transactions.push_back("Deposit: $" + to_string(amount));
}
BankAccount::BankAccount(string accNumber, string accName, double initialBalance)
{
    id = accNumber;
    name = accName;
    balance = initialBalance;
    
}
BankAccount::BankAccount()
{
    id = "0";
    name = "";
    balance = 0.0;
    transactions.push_back("Account Created");
}
void clearScreen()
{
    for(int i = 0; i < 30; i++)
    {
        cout << endl;
    }
}
