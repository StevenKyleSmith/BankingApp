/*
 *
 * Created on December 25, 2024, 4:17 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
void clearScreen();
class BankAccount;
class System
{
public:
    void createAccount(const string name, double initialBalance);
    BankAccount* findAccount(const string& accountNumber);
    void loadFromFile(const string& fileName);
    void saveToFile(const string& fileName);
    vector<BankAccount> getAccounts() const;
    bool findAcc(const string& account);
private:
    vector<BankAccount> accounts;
};
struct Transaction
{
    string description;
    double amount;
    
    Transaction();
    Transaction(const string& desc, double amt);
            
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
    void addTransaction(const string& description, double amount);
    void displayTransactions() const;
private: 
    string id;
    string name;
    double balance;
    vector<Transaction> transactions;
};
void mainMenu();
/*
 * 
 */
int main(int argc, char** argv)
{
    System bankingSystem;
    BankAccount* verifyAccount;
    vector<BankAccount> openAccounts;
    bankingSystem.loadFromFile("accounts.txt");
    int choice;
    double initialDeposit;
    double deposit, withdrawal;
    string name;
    string option;
    string userAccNum;
    string case2Option, case3Option;
    do
    {
        mainMenu();
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
                    cout << "Cannot deposit negative funds, please enter "
                            "a positive amount: ";
                    cin >> initialDeposit;
                }
                bankingSystem.createAccount(name, initialDeposit);
                bankingSystem.saveToFile("accounts.txt");

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
                if(bankingSystem.findAcc(userAccNum))
                {
                    do
                    {
                        cout << "Please enter deposit amount: " << endl;
                        cin >> deposit;
                        while(deposit < 0)
                        {
                            cout << "Cannot deposit negative funds, please "
                                    "enter a positive amount: ";
                            cin >> deposit;
                        }
                        cout << endl << "Account Number: " << userAccNum << endl
                                << "Amount to Deposit: " << fixed << 
                                setprecision(2) << deposit << endl;

                        if(verifyAccount != nullptr)
                        {
                            verifyAccount->deposit(deposit);
                        }
                        else
                        {
                            cout << "Account not found." << endl;
                        }
                        cout << "Deposit successful! " << endl;
                        bankingSystem.saveToFile("accounts.txt");

                        cout << "Would you like to make another deposit? (y/n)" 
                                << endl;
                        cin >> case2Option;
                    }while(tolower(case2Option[0]) == 'y');
                }
                else
                {
                 cout << "Account Not Found. Please enter a valid account "
                         "number in"
                         " order to make deposits." << endl;   
                }
                break;
            case 3:
                clearScreen();
                cin.ignore();
                cout << "      ==|Withdrawals|==" << endl;
                cout << "______________________________" << endl;
                cout << "|LOGIN|" << endl;
                cout << "Please enter your Account number: ";
                cin >> userAccNum;
                verifyAccount = bankingSystem.findAccount(userAccNum);
                if(verifyAccount != nullptr)
                {
                    do
                    {
                        cout << "Please enter withdrawal amount: " << endl;
                        cin >> withdrawal;
                        while(withdrawal > verifyAccount->getBalance())
                        {
                            cout << "Insufficient funds, please enter a valid "
                                    "amount: ";
                            cin >> withdrawal;
                        }
                        cout << endl << "Account Number: " << userAccNum << endl
                                << "Amount to Withdraw: " << fixed << 
                                setprecision(2) << withdrawal << endl;

                        verifyAccount->withdraw(withdrawal);
                        cout << "withdraw successful! " << endl;
                        bankingSystem.saveToFile("accounts.txt");

                        cout << "Would you like to make another withdrawal? "
                                "(y/n)" << endl;
                        cin >> case3Option;
                    }while(tolower(case3Option[0]) == 'y');
                }
                else
                {
                 cout << "Account Not Found. Please enter a valid account "
                         "number in"
                         " order to make deposits." << endl;   
                }
                break;
            case 4:
                clearScreen();
                cin.ignore();
                cout << "     ==|View Balance|==" << endl;
                cout << "______________________________" << endl;
                cout << "|LOGIN|" << endl;
                cout << "Please enter your Account number: ";
                cin >> userAccNum;
                verifyAccount = bankingSystem.findAccount(userAccNum);
                if(verifyAccount != nullptr)
                {
                    clearScreen();
                    cout << "  Account Balance" << endl;
                    cout << "____________________" << endl;
                    cout << "Account Number: " << 
                            verifyAccount->getAccountNumber() << endl;
                    cout << "Active Checking: " << verifyAccount->getBalance();
                    cout << endl << endl;
                }
                else
                {
                 cout << "Account Not Found. Please enter a valid account "
                         "number in order to view account balances." << endl;   
                }
                break;
            case 5:
                clearScreen();
                cin.ignore();
                cout << "   ==|Transaction History|==" << endl;
                cout << "______________________________" << endl;
                cout << "|LOGIN|" << endl;
                cout << "Please enter your Account number: ";
                cin >> userAccNum;
                verifyAccount = bankingSystem.findAccount(userAccNum);
                if(verifyAccount != nullptr)
                {
                    clearScreen();
                    cout << "Account Number: " << userAccNum << endl;
                    verifyAccount->displayTransactions();
                    cout << endl << endl;
                }
                else
                {
                 cout << "Account Not Found. Please enter a valid account "
                         "number in order to view transaction history." << endl;   
                }
                break;
            case 6:
                return 1;
                break;
            default: 
                cout << "Not a valid option." << endl;
            }  
            cout << "Return to main menu?(y/n)" << endl;
            cin >> option;
            clearScreen();
        } while(tolower(option[0] == 'y'));
    return 0;
}
void mainMenu()
{
    cout << "Welcome to the Banking System Simulation" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. View Balance" << endl;
    cout << "5. Transaction History" << endl;
    cout << "6. Exit" << endl;
    cout << endl << "Enter your choice: ";
}
Transaction::Transaction()
{
    description = ""; 
    amount = 0.0;
}
Transaction::Transaction(const string& desc, double amt)
{
    description = desc;
    amount = amt;
}
void BankAccount::addTransaction(const string& description, double amount)
{
    transactions.emplace_back(description, amount);
}
vector<BankAccount> System::getAccounts() const
{
    return accounts;
}
bool System::findAcc(const string& accountNumber) 
{
    for (size_t i = 0; i < accounts.size(); ++i)
    {
        const BankAccount& account = accounts[i]; 
        if (account.getAccountNumber() == accountNumber) 
        {
            return true; 
        }
    }
    return false; 
}
void System::loadFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (file.is_open())
    {
        accounts.clear();
        string accNumber, name;
        double balance;
        string line;
        
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, accNumber, ',');
            getline(ss, name, ',');
            ss >> balance;
            
            if (!accNumber.empty() && !name.empty() && ss) 
            {
                accounts.emplace_back(accNumber, name, balance);
            } 
            else
            {
                cout << "Skipping invalid account entry in file: " << line << endl;
            }
        }
        file.close();
        cout << "Accounts loaded successfully from file." << endl;
    }
    else
    {
        cout << "Error: Could not open file for loading accounts." << endl;
    }
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
    cout << endl << "Account successfully created! Account Number: " 
            << accountNumber << endl << "Name: " << name << endl << "Initial "
            "Balance: " << initialBalance << endl;
}
void BankAccount::displayTransactions() const
{
    if (transactions.empty())
    {
        cout << "No transaction history available." << endl;
    }
    else
    {
        for(int i = 0; i < transactions.size(); i++)
        {
            cout << transactions[i].description << ": $" << fixed 
                    << setprecision(2) << transactions[i].amount << endl;
        }
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
        addTransaction("Withdrawal", amount);
    }
    else
    {
        cout << "Insufficient funds!";
    }
    
}
void BankAccount::deposit(double amount)
{
    balance+=amount;
    addTransaction("Deposit", amount);
}
BankAccount::BankAccount(string accNumber, string accName, double initialBalance)
{
    id = accNumber;
    name = accName;
    balance = initialBalance;
    
    addTransaction("Iinitial Deposit", initialBalance);
    
}
BankAccount::BankAccount()
{
    id = "0";
    name = "";
    balance = 0.0;
}
void clearScreen()
{
    for(int i = 0; i < 30; i++)
    {
        cout << endl;
    }
}
