/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: Investment subclass Stock source file
 *
 */

#include "Stock.h"

#include <iostream>
#include <iomanip>

using namespace std;

Stock::Stock(){
    companyName = "Default Name";
    tickerName = "ABC";
    initialInvestment = 1.23;
    currentMarketValue = 123.45;
    expectedGrowth = 5.5;
    earningsPerShare = 3.5;
}

Stock::Stock(string companyName, float initialInvestment, string tickerName, float currentMarketValue, float expectedGrowth, float earningsPerShare)
      :Investment(companyName, initialInvestment), tickerName(tickerName), currentMarketValue(currentMarketValue), expectedGrowth(expectedGrowth), earningsPerShare(earningsPerShare){
}

string Stock::getTickerName() const{
    return tickerName;
}

float Stock::getCurrentMarketValue() const {
    return currentMarketValue;
}

float Stock::getExpectedGrowth() const {
    return expectedGrowth;
}

float Stock::getEarningsPerShare() const {
    return earningsPerShare;
}

float Stock::getIntrinsicDifference() const {
    return differenceOfIntrinsicToActual;
}

void Stock::setTickerName(std::string tickerName) {
    this->tickerName = tickerName;
}

void Stock::setCurrentMarketValue(float currentMarketValue) {
    this->currentMarketValue = currentMarketValue;
}

void Stock::setExpectedGrowth(float expectedGrowth) {
    this->expectedGrowth = expectedGrowth;
}

void Stock::setEarningsPerShare(float earningsPerShare) {
    this->earningsPerShare = earningsPerShare;
}

void Stock::setIntrinsicDifference(float differenceOfIntrinsicToActual) {
    this->differenceOfIntrinsicToActual = differenceOfIntrinsicToActual;
}

bool operator == (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() == second.getIntrinsicDifference();
}

bool operator > (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() > second.getIntrinsicDifference();
}

bool operator < (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() < second.getIntrinsicDifference();
}

bool operator != (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() != second.getIntrinsicDifference();
}

bool operator <= (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() <= second.getIntrinsicDifference();
}

bool operator >= (const Stock &first, const Stock &second){
    return first.getIntrinsicDifference() >= second.getIntrinsicDifference();
}

void Stock::printStock(Stock &userStock) {
    cout << endl << "(1) Company Name: " << userStock.getCompanyName() << endl;
    cout << "(2) Initial Investment: " << fixed << setprecision(2) << userStock.getInitialInvestment() << endl;
    cout << "(3) Ticker Name: " << userStock.getTickerName() << endl;
    cout << "(4) Current Market Value: " << userStock.getCurrentMarketValue() << endl;
    cout << "(5) Expected Growth: " << userStock.getExpectedGrowth() << endl;
    cout << "(6) Earnings Per Share (EPS): " << userStock.getEarningsPerShare() << endl << endl;
}


float Stock::calculateIntrinsicValue(Stock &stock) {
    float baseForNoGrowth = 8.5;
    float currentYield = 4.22;
    float averageYield = 4.4;

    this->intrinsicValue = (stock.getEarningsPerShare()  * (baseForNoGrowth + (2 * stock.getExpectedGrowth())) * averageYield)/currentYield;

    stock.setIntrinsicDifference(stock.getCurrentMarketValue() - intrinsicValue);

    return intrinsicValue;
}
