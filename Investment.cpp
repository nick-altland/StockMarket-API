/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: Investment Super Class source file
 *
 */

#include "Investment.h"

using namespace std;

Investment ::Investment() {
    companyName = "Default Name";
    initialInvestment = 1000.00;
}

Investment ::Investment(string companyName, float initialInvestment) {
    this->companyName = companyName;
    this->initialInvestment = initialInvestment;
}

string Investment::getCompanyName() const{
    return companyName;
}

float Investment::getInitialInvestment() const {
    return initialInvestment;
}

float Investment::getYearlyReturns() const {
    return yearlyReturns;
}

void Investment::setCompanyName(string companyName) {
    this->companyName = companyName;
}

void Investment::setInitialInvestment(float initialInvestment) {
    this->initialInvestment = initialInvestment;
}
void Investment::setYearlyReturns(float yearlyReturns) {
    this->yearlyReturns = yearlyReturns;
}

bool operator == (const Investment &first, const Investment &second){
    return first.getYearlyReturns() == second.getYearlyReturns();
}

bool operator > (const Investment &first, const Investment &second){
    return first.getYearlyReturns() > second.getYearlyReturns();
}

bool operator < (const Investment &first, const Investment &second){
    return first.getYearlyReturns() < second.getYearlyReturns();
}

bool operator != (const Investment &first, const Investment &second){
    return first.getYearlyReturns() != second.getYearlyReturns();
}

bool operator <= (const Investment &first, const Investment &second){
    return first.getYearlyReturns() <= second.getYearlyReturns();
}

bool operator >= (const Investment &first, const Investment &second){
    return first.getYearlyReturns() >= second.getYearlyReturns();
}

