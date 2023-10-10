
// C++ program to display "Hello World"
// Header file for input output functions

#include <iostream>
#include <map>
#include "./Profile/Profile.cpp"
using namespace std;

// Main() function: where the execution of
// program begins
int main()
{
    std::cout << "Process started." << std::endl;
    std::map<std::string, int> user;
    // Param to definte number of years
    user["ageNow"] = 25;
    user["ageRetire"] = 45;

    // Param to define constraint
    user["cashToIncomeRatio"] = 20;

    // Param to compute income and expense per year
    user["inflation"] = 3;
    user["incrementAnnual"] = 6;
    user["incrementPromotion"] = 20;
    user["intervalPromotion"] = 10;
    user["pctPensionCompanyMatch"] = 0;
    user["isRemittanceBasis"] = 0;

    // Param to define investment return and wealth (optimization target)
    user["returnIsaAnnual"] = 7;
    user["returnBankSavingAnnual"] = 2;
    user["returnPensionAnnual"] = 5;

    int initIncome = 100000;
    int initExpense = 35000;
    Profile profile(user, initIncome, initExpense);
};
