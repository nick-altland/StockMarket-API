/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: Investment subclass Bond source file
 *
 */

#include "Bond.h"

#include <iostream>
#include <iomanip>

using namespace std;

Bond ::Bond(){
    companyName = "Default Name";
    initialInvestment = 1.23;
    interestRate = 5.0;
    maturityPeriod = 1;
}

Bond::Bond(string companyName, float initialInvestment, float interestRate, int maturityPeriod)
     :Investment(companyName, initialInvestment), interestRate(interestRate), maturityPeriod(maturityPeriod){
}

float Bond::getInterestRate() const {
    return interestRate;
}

float Bond::getInterestEarned() const {
    return interestEarned;
}

int Bond::getMaturityPeriod() const {
    return maturityPeriod;
}

void Bond::setInterestRate(float interestRate) {
    this->interestRate = interestRate;
}

void Bond::setMaturityPeriod(int maturityPeriod) {
    this->maturityPeriod = maturityPeriod;
}

bool operator == (const Bond &first, const Bond &second){
    return first.getInterestEarned() == second.getInterestEarned();
}

bool operator > (const Bond &first, const Bond &second){
    return first.getInterestEarned() > second.getInterestEarned();
}

bool operator < (const Bond &first, const Bond &second){
    return first.getInterestEarned() < second.getInterestEarned();
}

bool operator != (const Bond &first, const Bond &second){
    return first.getInterestEarned() != second.getInterestEarned();
}

bool operator <= (const Bond &first, const Bond &second){
    return first.getInterestEarned() <= second.getInterestEarned();
}

bool operator >= (const Bond &first, const Bond &second){
    return first.getInterestEarned() >= second.getInterestEarned();
}

void Bond::printBond(Bond &userBond) {
    cout << endl << "(1) Company Name: " << userBond.getCompanyName() << endl;
    cout << "(2) Initial Investment: " << fixed << setprecision(2) << userBond.getInitialInvestment() << endl;
    cout << "(3) Interest Rate: " << userBond.getInterestRate() << endl;
    cout << "(4) Maturity Period: " << userBond.getMaturityPeriod() << endl << endl;
}

float Bond::calculateInterestEarned(Bond &bond) {
    float yearlyInterest;
    yearlyInterest = (bond.getInterestRate()*0.01) * bond.getInitialInvestment();
    this->interestEarned = bond.getMaturityPeriod() * yearlyInterest;

    return interestEarned;
}



