/**
 * Course: CSC 2210, Fall 2026
 * Instructor: Dr. Chibuzo Ukegbu
 * main.cpp: Driver for the BankAccount class.
 */

#include <iomanip>
#include <iostream>
#include <string>
#include "BankAccount.h"

// Pass by const reference: no copying, and read-only access.
void printStatement(const BankAccount& account) {
    std::cout << "Owner: " << account.getOwner()
              << " | Account: " << account.getNumber()
              << " | Balance: $" << account.getBalance()
              << '\n';
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::boolalpha;

    // A static member function works before any account exists.
    std::cout << "Initially open: "
              << BankAccount::openAccounts() << "\n\n";

    {
        // Exercise all three constructors.
        BankAccount guest;
        BankAccount ada{"Ada"};
        BankAccount ben{"Ben", 50.0};

        // Constructors print Open messages with trailing spaces.
        std::cout << "\n\n--- Initial accounts ---\n";
        printStatement(guest);
        printStatement(ada);
        printStatement(ben);

        std::cout << "Currently open: "
                  << BankAccount::openAccounts() << '\n';

        // Each account has its own balance.
        std::cout << "\n--- Deposits ---\n";
        ada.deposit(100.0);
        ben.deposit(25.0);
        ada.deposit(-10.0); // Rejected: balance stays unchanged.

        printStatement(ada); // $100.00
        printStatement(ben); // $75.00

        // Withdrawal returns whether the operation succeeded.
        std::cout << "\n--- Withdrawals ---\n";
        std::cout << "Withdraw $30 from Ada: "
                  << ada.withdraw(30.0) << '\n';   // true
        std::cout << "Withdraw $200 from Ada: "
                  << ada.withdraw(200.0) << '\n';  // false
        std::cout << "Withdraw $0 from Ada: "
                  << ada.withdraw(0.0) << '\n';    // false

        printStatement(ada); // $70.00

        // The setter accepts valid names and ignores invalid updates.
        std::cout << "\n--- Updating an owner ---\n";
        guest.setOwner("Chibuzo");
        printStatement(guest);

        guest.setOwner("X"); // Too short: Chibuzo remains the owner.
        printStatement(guest);

        // A const reference can refer to a non-const account.
        std::cout << "\n--- Read-only access ---\n";
        const BankAccount& view = ada;
        printStatement(view);

        // Ada can still change through a non-const name.
        ada.deposit(5.0);
        std::cout << "Balance seen through view: $"
                  << view.getBalance() << '\n'; // $75.00

        // A reference is an alias, not another BankAccount object.
        BankAccount& alias = ben;
        alias.deposit(10.0);
        printStatement(ben); // $85.00

        std::cout << "Open after creating references: "
                  << BankAccount::openAccounts() << '\n'; // 3

        // The temporary account closes automatically at the inner brace.
        std::cout << "\n--- Nested scope ---\n";
        {
            BankAccount temp{"Temp", 20.0};
            std::cout << '\n';
            printStatement(temp);

            std::cout << "Open inside nested scope: "
                      << BankAccount::openAccounts() << '\n'; // 4
        }

        std::cout << "\nOpen after nested scope: "
                  << BankAccount::openAccounts() << '\n'; // 3

        // Default construction creates a separate account per element.
        std::cout << "\n--- Array of accounts ---\n";
        {
            constexpr int BRANCH_SIZE{2};
            BankAccount branch[BRANCH_SIZE];

            branch[0].setOwner("Dee");
            branch[1].setOwner("Lee");

            branch[0].deposit(40.0);
            branch[1].deposit(60.0);

            std::cout << '\n';

            // Use references because copying BankAccount is deleted.
            double totalBalance{0.0};

            for (const BankAccount& account : branch) {
                printStatement(account);
                totalBalance += account.getBalance();
            }

            std::cout << "Branch total: $" << totalBalance << '\n';
            std::cout << "Open with branch accounts: "
                      << BankAccount::openAccounts() << '\n'; // 5
        } // Array elements are destroyed in reverse order.

        std::cout << "\nOpen after branch scope: "
                  << BankAccount::openAccounts() << '\n'; // 3



        // Private data cannot be accessed directly:
        // ada.balance = 1000.0;

        // A const reference cannot call a non-const member function:
        // view.deposit(10.0);

        // Copy construction is deleted:
        // BankAccount copy{ada};

        // Copy assignment is deleted:
        // ben = ada;

        // explicit blocks an implicit string-to-account conversion:
        // std::string name{"Zoe"};
        // printStatement(name);

        std::cout << "\nLeaving the main account scope:\n";
    } // ben, ada, and guest are destroyed in reverse construction order.

    // This statement runs after all accounts have been destroyed.
    std::cout << "\nFinally open: "
              << BankAccount::openAccounts() << '\n'; // 0

    return 0;
}
