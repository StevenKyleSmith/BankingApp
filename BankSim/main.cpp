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
    void createAccount(const string name, const string password,
            double initialBalance);
    BankAccount* login(const string& accountNumber, const string& password);
    BankAccount* findAccount(const string& accountNumber);
    void loadFromFile(const string& fileName);
    void saveToFile(const string& fileName);
    vector<BankAccount> getAccounts() const;
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
    BankAccount(string accNumber, string accName, string accPassword,
    double initialBalance);
    bool verifyPassword(const string& inputPassword) const;
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
    string getAccountNumber() const;
    string getName() const;
    string getPassword() const;
    void addTransaction(const string& description, double amount);
    void displayTransactions() const;
private: 
    string id;
    string name;
    string password;
    double balance;
    vector<Transaction> transactions;
};
void mainMenu(System& bankingSystem);
void accountMenu(BankAccount* account, System& bankingSystem);
void pauseScreen();
/*
 * 
 */
int main(int argc, char** argv)
{
    System bankingSystem;
    bankingSystem.loadFromFile("accounts.txt");
    mainMenu(bankingSystem);
    return 0;
}
void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any input buffer
    cin.get(); // Wait for user to press Enter
}
void mainMenu(System& bankingSystem)
{
    int choice;
    string name, accountNumber, password;
    double initialDeposit;
    BankAccount* loggedInAccount = nullptr;
    do
    {
        cout << "Welcome to the Banking System Simulation" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                cin.ignore();
                cout << "Please enter your first and last name: ";
                getline(cin, name);
                cout << "Please enter a password: ";
                cin >> password;
                cout << "Enter initial deposit: ";
                cin >> initialDeposit;
                bankingSystem.createAccount(name, password, initialDeposit);
                bankingSystem.saveToFile("accounts.txt");
                break;
            case 2:
                cin.ignore();
                cout << "Account number: ";
                cin >> accountNumber;
                cout << "Password: ";
                cin >> password;
                loggedInAccount = bankingSystem.login(accountNumber, password);
                if (loggedInAccount)
                {
                    accountMenu(loggedInAccount, bankingSystem);
                }
                break;
            case 3:
                return;
                break;
            default:
                cout << "Not a valid option." << endl;
        }
    } while (choice != 3);
}
void accountMenu(BankAccount* account, System& bankingSystem)
{
    int choice;
    double amount;
    do
    {
        clearScreen();
        cout << "Account Menu" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. View Balance" << endl;
        cout << "4. Transaction History" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                clearScreen();
                cout << "Enter deposit amount: $";
                cin >> amount;
                account->deposit(amount);
                bankingSystem.saveToFile("accounts.txt");
                pauseScreen();
                break;
            case 2:
                clearScreen();
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                account->withdraw(amount);
                bankingSystem.saveToFile("accounts.txt");
                pauseScreen();
                break;
            case 3:
                clearScreen();
                cout << "Balance: $" << fixed << setprecision(2) 
                        << account->getBalance() << endl;
                pauseScreen();
                break;
            case 4: 
                clearScreen();
                account->displayTransactions();
                pauseScreen();
                break;
            case 5:
                cout << "Logging out..." << endl;
                clearScreen();
                return;
                break;
            default:
                cout << "Not a valid option." << endl;
        }
    } while (true);
}
BankAccount* System::login(const string& accountNumber, const string& password)
    {
        BankAccount* account = findAccount(accountNumber);
        if (account && account->verifyPassword(password))
        {
            return account;
        }
        else
        {
            cout << "Invalid account number or password." << endl;
            return nullptr;
        }
    }
bool BankAccount::verifyPassword(const string& inputPassword) const
{
    return password == inputPassword;
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
void System::loadFromFile(const string& fileName)
{
    ifstream file(fileName);
    if (file.is_open())
    {
        accounts.clear();
        string accNumber, name, password;
        double balance;
        string line;
        
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, accNumber, ',');
            getline(ss, name, ',');
            getline(ss, password, ',');
            ss >> balance;
            
            accNumber.erase(0, accNumber.find_first_not_of(" \t"));
            accNumber.erase(accNumber.find_last_not_of(" \t") + 1);
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
            password.erase(0, password.find_first_not_of(" \t"));
            password.erase(password.find_last_not_of(" \t") + 1);
            
            if (!accNumber.empty() && !name.empty() && !password.empty() && ss) 
            {
                accounts.emplace_back(accNumber, name, password, balance);
            } 
        }
        file.close();
        cout << "Accounts loaded successfully from file.";
        clearScreen();
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
            file << accounts[i].getAccountNumber() << "," 
                 << accounts[i].getName() << "," 
                 << accounts[i].getPassword() << ","
                 << accounts[i].getBalance() << endl;
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
void System::createAccount(const string name, const string password,
        double initialBalance)
{
    string accountNumber = "ACC" + to_string(accounts.size() + 1);
    accounts.emplace_back(accountNumber, name, password, initialBalance);
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
string BankAccount::getPassword() const
{
    return password;
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
BankAccount::BankAccount(string accNumber, string accName, string accPassword,
        double initialBalance)
{
    id = accNumber;
    name = accName;
    password = accPassword;
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
