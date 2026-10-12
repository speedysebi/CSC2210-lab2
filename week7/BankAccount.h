/**
 * Course: CSC 2210, Fall 2026
 * Instructor: Dr. Chibuzo Ukegbu
 * BankAccount.h: Week 6 review exercise.
 *
 * This version of the class does not build, and it also has a logic error.
 * Fix BankAccount.h and BankAccount.cpp only. Do not change main.cpp.
 */
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
public:
    // Default account: owner "none", zero balance, and a new account number.
    BankAccount();

    // Explicit prevents a std::string from silently becoming an account.
    explicit BankAccount(const std::string& who);

    // Retains starting-balance support from the earlier constructor lesson.
    // The account number is now generated automatically, not passed by callers.
    BankAccount(const std::string& who, double start);

    // A new object must not copy an existing account's number or balance.
    BankAccount(const BankAccount&) = delete;
    // Existing accounts must not overwrite one another through assignment.
    BankAccount& operator=(const BankAccount&) = delete;

    // Automatically reduces the live-object count and logs the end of use.
    ~BankAccount();

    // Positive deposits increase this object's balance; others are ignored.
    void deposit(double amt);
    // Withdraw only a positive amount that does not exceed the balance.
    bool withdraw(double amt);

    // Read-only access to the account's data.
    // Const member functions must be marked const in their declarations.
    double getBalance() const;
    int getNumber() const;
    std::string getOwner() const;

    // Names need at least two characters. Invalid updates change nothing.
    void setOwner(std::string name);

    // Prints this object's number and balance as "1001: 50", then a newline.
    // The caller controls numeric formatting using stream manipulators.
    void print() const;

    // Call BankAccount::openAccounts(), even when no objects exist.
    // A static function has no this pointer and cannot select an account.
    static int openAccounts();

    // Returns the sum of the balances of the first size accounts in the array.
    static double totalBalance(const BankAccount accounts[], int size);

private:
    // Each BankAccount object contains its own three data members.
    std::string owner;
    const int number;
    double balance;

    // One shared copy of each counter exists outside individual objects.
    // inline allows definitions in this header across multiple .cpp files.
    inline static int nextNumber{1001};
    inline static int open{0};

    // A shared validation rule: constructor and setter both call it.
    // Static is appropriate because validation needs only the argument.
    static bool validOwner(const std::string& name);
};

#endif // BANKACCOUNT_H
