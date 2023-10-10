#include <map>
#include <unordered_map>
#include <iostream>
#include "../Saving/Saving.cpp"

class Profile
{
private:
	std::map<int, Saving> Savings;

public:
	Profile(std::map<std::string, int> &user, int initIncome, int initExpense)
	{
		updateSavings(user, initIncome, initExpense);
		displaySavings();
	}

private:
	void updateSavings(std::map<std::string, int> &user, int initIncome, int initExpense)
	{
		// 1. Initialize the first Saving with user AND pctContribute with NO latestSaving
		Saving saving(user, initIncome, initExpense);
		// Saving saving(user, 119101, 38244, 22);
		updateTotalSaving(saving, user);
		this->Savings.insert(std::pair<int, Saving>(user["ageNow"], saving));
		// this->Savings.insert(std::pair<int, Saving>(user["ageNow"], saving));
		Saving *latestSaving = &saving;
		// 2. Create Saving for each age, with user AND pctContribute AND latestSaving.

		for (int i = user["ageNow"] + 1; i <= user["ageRetire"]; i++)
		{
			int incomeThisYear, expenseThisYear;
			// [WORK TO BE DONE IN HERE] Condition to check if this is a year for promotion;
			if ((i - user["ageNow"]) % user["intervalPromotion"] == 0)
			{
				// this is a promotion year
				std::cout << "Promotion Year: " + std::to_string(i);
				incomeThisYear = (int)(latestSaving->getIncome() * (1 + (user["incrementPromotion"] / 100.0)));
			}
			else
			{
				// this is a non-promotion year
				std::cout << "Non-Promotion Year: " + std::to_string(i);
				incomeThisYear = (int)(latestSaving->getIncome() * (1 + (user["incrementAnnual"] / 100.0)));
			}
			expenseThisYear = (int)(latestSaving->getExpense() * (1 + (user["inflation"] / 100.0)));
			std::cout << "; Expense: " + std::to_string(expenseThisYear);
			std::cout << "; Income: " + std::to_string(incomeThisYear) << std::endl;
			Saving saving(user, incomeThisYear, expenseThisYear);
			updateTotalSaving(latestSaving, saving, user);
			this->Savings.insert(std::pair<int, Saving>(i, saving));
			latestSaving = &saving;
		}
	}
	void displaySavings()
	{
		std::cout << "year,income,expense,pctContribute,pensionThisYear,isaThisYear,bankThisYear,totalThisYear,taxThisYear,niThisYear,isaAccumulated,bankAccumulated,pensionAccumulated,totalAccumulated" << std::endl;
		for (auto &x : this->Savings)
		{
			std::cout << std::to_string(x.first) + ','
					  << std::to_string(x.second.getIncome()) + ','
					  << std::to_string(x.second.getExpense()) + ','
					  << std::to_string(x.second.getPctContribute()) + ','
					  << std::to_string(x.second.getPensionThisYear()) + ','
					  << std::to_string(x.second.getIsaThisYear()) + ','
					  << std::to_string(x.second.getBankThisYear()) + ','
					  << std::to_string(x.second.getTotalThisYear()) + ','
					  << std::to_string(x.second.getTaxThisYear()) + ','
					  << std::to_string(x.second.getNiThisYear()) + ','
					  << std::to_string(x.second.getIsaAccumulated()) + ','
					  << std::to_string(x.second.getBankAccumulated()) + ','
					  << std::to_string(x.second.getPensionAccumulated()) + ','
					  << std::to_string(x.second.getTotalAccumulated()) << std::endl;
		}
	}
	void updateTotalSaving(Saving *lastSaving, Saving &currentSaving, std::map<std::string, int> &user)
	{
		// 1. Init local variables
		int currentIsaAccumulated, currentBankAccumulated, currentPensionAccumulated;
		// 2. Calculate investment return
		currentIsaAccumulated = lastSaving->getIsaAccumulated() * (1 + (user["returnIsaAnnual"] / 100.0));
		currentIsaAccumulated += currentSaving.getIsaThisYear();
		currentBankAccumulated = lastSaving->getBankAccumulated() * (1 + (user["returnBankSavingAnnual"] / 100.0));
		currentBankAccumulated += currentSaving.getBankThisYear();
		currentPensionAccumulated = lastSaving->getPensionAccumulated() * (1 + (user["returnPensionAnnual"] / 100.0));
		currentPensionAccumulated += currentSaving.getPensionThisYear();
		// 3. Update investment return in current saving
		currentSaving.setIsaAccumulated(currentIsaAccumulated);
		currentSaving.setBankAccumulated(currentBankAccumulated);
		currentSaving.setPensionAccumulated(currentPensionAccumulated);
		currentSaving.setTotalAccumulated(currentIsaAccumulated + currentBankAccumulated + currentPensionAccumulated);
	}
	void updateTotalSaving(Saving &currentSaving, std::map<std::string, int> &user)
	{
		// If no prior saving obj available (which means this is the first saving) - set accumulated = thisYear
		currentSaving.setIsaAccumulated(currentSaving.getIsaThisYear());
		currentSaving.setBankAccumulated(currentSaving.getBankThisYear());
		currentSaving.setPensionAccumulated(currentSaving.getPensionThisYear());
		currentSaving.setTotalAccumulated(currentSaving.getIsaThisYear() + currentSaving.getBankThisYear() + currentSaving.getPensionThisYear());
	}
};