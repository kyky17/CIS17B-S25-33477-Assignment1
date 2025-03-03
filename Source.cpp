#include <iostream>
#include <string>
#include <limits>

using namespace std;

class BankAccount
{
private:
    //Private member variables for accountHolderName, accountNumber, and balance.
    string accountHolderName;
    double accountNumber;
    double balance;

public:
    BankAccount(string name, double accountNum, double startBalance = 0)
    {
        accountHolderName = name;
        accountNumber = accountNum;
        balance = (startBalance >= 0) ? startBalance : 0;//greater than or equal to zero, eval to 0 if negative
    }

    //Public member functions for deposit(double amount), withdraw(double amount), and getBalance().
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
        else
        {
            throw invalid_argument("Desposit must be positive");//try catch block
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0)
        {
            balance -= amount;
        }
        else if (amount > balance)
        {
            throw runtime_error("Insufficient Funds");//amount for runtime error
        }
        else
        {
            throw invalid_argument("Withdrawl must be positive");//dealing with non negatives
        }
    }

    double getBalance() const
    {
        return balance;//returns the balance 
    }
};

void userMenu()
{
    cout << "1. Create account \n";
    cout << "2. Deposit money \n";
    cout << "3. Withdrawl money \n";
    cout << "4. Check balance \n";
    cout << "5. Exit \n";
}

void invalidInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//limit buffer
    cout << "Invalid input! Please enter a valid number between 1 and 5.\n";
}

void invalidInputCase()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input! Please enter a valid number \n";
}

int main()
{
    BankAccount* account = nullptr;
    int choice;
    double amount;

    do
    {
        userMenu();//menu
        cout << "Enter your choice ";
        cin >> choice;
        if (cin.fail())
        {
            invalidInput();
        }

        switch (choice)
        {
        case 1:
        {
            string name;
            double accountNum;
            double startDeposit;

            cout << "Enter account holder name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter account number: ";
            cin >> accountNum;

            if (cin.fail())
            {
                invalidInputCase();
                break;
            }

            cout << "Enter initial deposit: ";
            cin >> startDeposit;

            if (cin.fail() || startDeposit < 0)
            {
                invalidInputCase();
                break;
            }

            account = new BankAccount(name, accountNum, startDeposit);//account object
            cout << "Account successfully created!\n";
            break;
        }

        case 2://deposit money
            if (!account)
            {
                cout << "No account found! Please create an account first.\n";
                break;
            }

            cout << "Enter deposit amount:$  ";
            cin >> amount;

            if (cin.fail() || amount <= 0)
            {
                invalidInputCase();
                break;
            }

            account->deposit(amount);  //call deposit function from BankAccount class
            cout << "Deposit successful!\n";
            break;

        case 3:  //Withdrawl money
            if (!account)
            {
                cout << "No account found! Please create an account first.\n";
                break;
            }
            cout << "Enter withdrawal amount: $ ";
            cin >> amount;

            if (cin.fail() || amount <= 0) //if input is not integer or amount is less than 0 then ivnalid case
            {
                invalidInputCase();
                break;
            }

            account->withdraw(amount);
            cout << "Withdrawl successful!\n";
            break;

        case 4:
            if (!account)
            {
                cout << "No account found! Please create an account first.\n";
                break;
            }
            cout << "Current balance: $" << account->getBalance() << endl;
            break;

        case 5:
            cout << "Thank you for using the Simple Bank System!\n";
            break;

        default:
            cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }

    } while (choice != 5);//exit

    return 0;
}

