#include <iostream>
#include <map>
#include <vector>

class Saving
{
private:
    // 1. System Input
    int
        income,
        expense;
    // 2. System Output
    int
        pctContribute,
        pensionThisYear,
        isaThisYear,
        bankThisYear,
        totalThisYear,
        taxThisYear,
        niThisYear;

    // 3. System Output (Computed outside of class object)
    int
        isaAccumulated,
        bankAccumulated,
        pensionAccumulated,
        totalAccumulated;

public:
    // Initialize Saving obj with known pctContribute
    Saving(std::map<std::string, int> &user, int income, int expense, int pctContribute)
    {
        std::vector<int> optimalSaving = initSaving(user, income, expense, pctContribute);
        this->income = income;
        this->expense = expense;
        this->pctContribute = optimalSaving.at(0);
        this->taxThisYear = optimalSaving.at(1);
        this->niThisYear = optimalSaving.at(2);
        this->pensionThisYear = optimalSaving.at(3);
        this->isaThisYear = optimalSaving.at(4);
        this->bankThisYear = optimalSaving.at(5);
        this->totalThisYear = optimalSaving.at(6);
    }

    // Initialize Saving obj with unknown pctContribute - Find optimized pct
    Saving(std::map<std::string, int> &user, int income, int expense)
    {
        std::vector<int> optimalSaving(7, -1);
        for (int i = 100; i >= 0; i--)
        {
            std::vector<int> currentSaving = initSaving(user, income, expense, i);
            // std::cout << "[DEBUG] PctContribute is " + std::to_string(currentSaving.at(0)) + " ; CurrentTotal = " + std::to_string(currentSaving.at(6)) << std::endl;
            if (currentSaving.at(6) > optimalSaving.at(6))
            {
                // std::cout << "[DEBUG] Optimal Saving Updated - New Total = " + std::to_string(currentSaving.at(6)) + "; Prior Total = " + std::to_string(optimalSaving.at(6)) << std::endl;
                // std::cout << "[DEBUG] Optimal Saving Updated - New PctContribute = " + std::to_string(currentSaving.at(0)) << std::endl;
                optimalSaving = currentSaving;
            }
        }
        this->income = income;
        this->expense = expense;
        this->pctContribute = optimalSaving.at(0);
        this->taxThisYear = optimalSaving.at(1);
        this->niThisYear = optimalSaving.at(2);
        this->pensionThisYear = optimalSaving.at(3);
        this->isaThisYear = optimalSaving.at(4);
        this->bankThisYear = optimalSaving.at(5);
        this->totalThisYear = optimalSaving.at(6);
        // display();
    }

    void display()
    {
        std::cout << "Saving - Income: " + std::to_string(income) << std::endl;
        std::cout << "Saving - Expense: " + std::to_string(expense) << std::endl;
        std::cout << "Saving - PctContribute: " + std::to_string(pctContribute) << std::endl;
        std::cout << "Saving - Pension: " + std::to_string(pensionThisYear) << std::endl;
        std::cout << "Saving - ISA: " + std::to_string(isaThisYear) << std::endl;
        std::cout << "Saving - BankSaving: " + std::to_string(bankThisYear) << std::endl;
        std::cout << "Saving - Total: " + std::to_string(totalThisYear) << std::endl;
        std::cout << "Saving - Tax: " + std::to_string(taxThisYear) << std::endl;
        std::cout << "Saving - NI: " + std::to_string(niThisYear) << std::endl;
    }

    int getIncome()
    {
        return this->income;
    }
    int getExpense()
    {
        return this->expense;
    }
    int getPctContribute()
    {
        return this->pctContribute;
    }
    int getPensionThisYear()
    {
        return this->pensionThisYear;
    }
    int getIsaThisYear()
    {
        return this->isaThisYear;
    }
    int getBankThisYear()
    {
        return this->bankThisYear;
    }
    int getTotalThisYear()
    {
        return this->totalThisYear;
    }
    int getTaxThisYear()
    {
        return this->taxThisYear;
    }
    int getNiThisYear()
    {
        return this->niThisYear;
    }
    int getIsaAccumulated()
    {
        return this->isaAccumulated;
    }

    int getBankAccumulated()
    {
        return this->bankAccumulated;
    }

    int getPensionAccumulated()
    {
        return this->pensionAccumulated;
    }

    int getTotalAccumulated()
    {
        return this->totalAccumulated;
    }

    void setIsaAccumulated(int newValue)
    {
        this->isaAccumulated = newValue;
    }

    void setBankAccumulated(int newValue)
    {
        this->bankAccumulated = newValue;
    }

    void setPensionAccumulated(int newValue)
    {
        this->pensionAccumulated = newValue;
    }

    void setTotalAccumulated(int newValue)
    {
        this->totalAccumulated = newValue;
    }

private:
    int calculatePensionAllowance(int income, int thresholdLimitPension, int allowancePension, int allowancePensionMin)
    {
        if (income > thresholdLimitPension)
        {
            return std::max((int)(allowancePension - ((income - thresholdLimitPension) / 2.0)), allowancePensionMin);
        }
        else
        {
            return allowancePension;
        }
    }
    int calculateTaxAllowance(int isRemittanceBasis, int income, int pension, int thresholdNoTaxAllowance, int thresholdLimitTaxAllowance, int allowanceTax)
    {
        if (isRemittanceBasis == 1 || income - pension > thresholdNoTaxAllowance)
        {
            return 0;
        }
        else if (income - pension > thresholdLimitTaxAllowance)
        {
            return allowanceTax - (income - pension - thresholdLimitTaxAllowance) / 2;
        }
        else
        {
            return allowanceTax;
        }
    }
    int calculateTax(int income, int pension, int currentTaxAllowance, int thresholdTaxBasic, int thresholdTaxHigher, double rateTaxBasic, double rateTaxHigher, double rateTaxAdditional)
    {
        int tax;
        if (income - pension <= currentTaxAllowance)
        {
            return 0;
        }
        else
        {
            int currentTaxableIncome = income - pension - currentTaxAllowance;
            if (currentTaxableIncome > thresholdTaxBasic)
            {
                tax = (int)(thresholdTaxBasic * rateTaxBasic);
                currentTaxableIncome -= thresholdTaxBasic;
                if (currentTaxableIncome > thresholdTaxHigher)
                {
                    tax += (int)(thresholdTaxHigher * rateTaxHigher + (currentTaxableIncome - thresholdTaxHigher) * rateTaxAdditional);
                }
                else
                {
                    tax += (int)(rateTaxHigher * currentTaxableIncome);
                }
                return tax;
            }
            else
            {
                // taxableIncome less than or equal to basic rate band (37700)
                return (int)(currentTaxableIncome * rateTaxBasic);
            }
        }
    }
    int calculateNI(int income, int allowanceNI, int thresholdNI, double rateNIBasic, double rateNIAdvanced)
    {
        int currentIncomeExNIAllowance = income - allowanceNI;
        if (currentIncomeExNIAllowance > thresholdNI)
        {
            return thresholdNI * rateNIBasic + (currentIncomeExNIAllowance - thresholdNI) * rateNIAdvanced;
        }
        else
        {
            return currentIncomeExNIAllowance * rateNIBasic;
        }
    }
    std::vector<int> initSaving(std::map<std::string, int> &user, int income, int expense, int pctContribute)
    {
        std::vector<int> result(7, -1);
        result.at(0) = pctContribute;
        // Variables
        int tax, pension, currentPensionAllowance, currentTaxAllowance, currentTakeHomeIncome, currentSaving, currentNI, currentTaxableIncome;
        // Default Configuration
        int allowanceTax, allowanceNI, allowancePensionMin, allowancePension,
            thresholdNI, thresholdTaxBasic, thresholdTaxHigher, thresholdTaxAdditional, thresholdLimitPension, thresholdNoTaxAllowance, thresholdLimitTaxAllowance;
        double rateTaxBasic, rateTaxHigher, rateTaxAdditional, rateNIBasic, rateNIAdvanced;
        allowanceTax = 12570;
        allowanceNI = 12570;
        allowancePension = 60000;
        allowancePensionMin = 10000;
        rateTaxBasic = 0.2;
        rateTaxHigher = 0.4;
        rateTaxAdditional = 0.45;
        rateNIBasic = 0.12;
        rateNIAdvanced = 0.02;
        thresholdNoTaxAllowance = 125140;
        thresholdLimitTaxAllowance = 100000;
        thresholdTaxAdditional = thresholdTaxBasic + thresholdTaxHigher;
        thresholdLimitPension = 260000;
        thresholdNI = 37700;
        thresholdTaxBasic = 37700;
        thresholdTaxHigher = 87440;

        // 0. Calculate Pension Contributed Amount
        pension = (int)income * pctContribute / 100;

        // 1. Calculate Pension Allowance
        currentPensionAllowance = calculatePensionAllowance(income, thresholdLimitPension, allowancePension, allowancePensionMin);
        // [Condition Check] Reject Case - if Pension Contribution exceeds pension allowance - which would make pension taxable at highest income tax rate
        if (pension > currentPensionAllowance)
        {
            return result;
        }

        // 2. Calculate Personal Tax Allowance
        currentTaxAllowance = calculateTaxAllowance(user["isRemittanceBasis"], income, pension, thresholdNoTaxAllowance, thresholdLimitTaxAllowance, allowanceTax);
        // 3. Calculate Personal Tax
        tax = calculateTax(income, pension, currentTaxAllowance, thresholdTaxBasic, thresholdTaxHigher, rateTaxBasic, rateTaxHigher, rateTaxAdditional);
        // 4. Calculate NI (National Insurance)
        currentNI = calculateNI(income, allowanceNI, thresholdNI, rateNIBasic, rateNIAdvanced);
        // 5. Calculate Net Saving
        currentSaving = income - pension - tax - currentNI - expense;

        // [Condition Check] Reject if Cash (ISA + Bank Saving Account) is less than 20% of Pre Tax Income
        if (currentSaving < 0 || currentSaving < user["cashToIncomeRatio"] * income / 100.0)
        {
            return result;
        }
        else
        {
            result.at(1) = tax;
            result.at(2) = currentNI;
            result.at(3) = (int)income * (pctContribute + user["pctPensionCompanyMatch"]) / 100;
            if (currentSaving > 20000)
            {
                // result[4] --> isaThisYear
                result.at(4) = 20000;
                // result[5] --> bankThisYear
                result.at(5) = currentSaving - 20000;
            }
            else
            {
                // result[4] --> isaThisYear
                result.at(4) = currentSaving;
                // result[5] --> bankThisYear
                result.at(5) = 0;
            }
            result.at(6) = result.at(3) + result.at(4) + result.at(5);
            return result;
        }
    }
};
