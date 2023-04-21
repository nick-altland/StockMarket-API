/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: Testing File
 *
 */

#include "Bond.h"
#include "Investment.h"
#include "marketAPI.h"
#include "Stock.h"

#include <iostream>

using namespace std;

bool testInvestment();
bool testBond();
bool testStock();
bool testMarketAPI();

int main(){

    if(testInvestment()){
        cout << "All Investment test cases passed" << endl;
    }
    if(testBond()){
        cout << "All Bond test cases passed" << endl;
    }
    if(testStock()){
        cout << "All Stock test cases passed" << endl;
    }
    if(testMarketAPI()){
        cout << "All MarketAPI test cases passed" << endl;
    }
    return 0;
}

bool testInvestment(){
    bool passed = true;
    Investment defaultTestInvest;
    if(defaultTestInvest.getCompanyName() != "Default Name"){
        cout << "Default Investment name initialization failed" << endl;
        passed = false;
    }
    if(defaultTestInvest.getInitialInvestment() - 1000.00 >= 0.001){
        cout << "Default Initial Investment failed" << endl;
        passed = false;
    }
    Investment testInvest("Google", 150.12);
    if(testInvest.getCompanyName() != "Google"){
        cout << "TestInvest name initialization failed" << endl;
        passed = false;
    }
    if(testInvest.getInitialInvestment() - 150.12 >= 0.001){
        cout << "TestInvest Initial Investment failed" << endl;
        passed = false;
    }
    testInvest.setCompanyName("Apple");
    if(testInvest.getCompanyName() != "Apple"){
        cout << "Set Investment company name failed" << endl;
        passed = false;
    }
    testInvest.setInitialInvestment(123.45);
    if(testInvest.getInitialInvestment() - 123.45 >= 0.001){
        cout << "Set Initial Investment Failed" << endl;
        passed = false;
    }
    testInvest.setYearlyReturns(123.45);
    defaultTestInvest.setYearlyReturns(12.34);
    if(testInvest < defaultTestInvest){
        cout << "Investment Comparison failed" << endl;
        passed = false;
    }

    return passed;
}

bool testBond(){
    bool passed = true;

    Bond defaultTestBond;
    if(defaultTestBond.getInterestRate() - 5 >= 0.001){
        cout << "Default Bond Interest Rate failed" << endl;
        passed = false;
    }
    if(defaultTestBond.getMaturityPeriod() != 1){
        cout << "Default Bond Maturity Period failed" << endl;
        passed = false;
    }
    if(defaultTestBond.calculateInterestEarned(defaultTestBond) - 250.00 >= 0.001){
        cout << "Default Bond calculate interest failed" << endl;
        passed = false;
    }

    Bond testB("Google", 2000.00, 10, 10);
    if(testB.getCompanyName() != "Google"){
        cout << "Bond name initialization failed" << endl;
        passed = false;
    }
    if(testB.getInitialInvestment() - 2000.00 >= 0.001){
        cout << "Bond Initial Investment initialization failed" << endl;
        passed = false;
    }
    if(testB.getInterestRate() - 10.0 >= 0.001){
        cout << "Bond get interest rate initialization failed" << endl;
        passed = false;
    }
    if(testB.getMaturityPeriod() != 10){
        cout << "Bond get maturity period initialization failed" << endl;
        passed = false;
    }
    testB.calculateInterestEarned(testB);
    if(testB.getInterestEarned() - 2000.0 >= 0.001){
        cout << "Calculate Interest on first iteration of testB failed" << endl;
        passed = false;
    }

    testB.setCompanyName("Apple");
    if(testB.getCompanyName() != "Apple"){
        cout << "Bond set company name failed" << endl;
        passed = false;
    }
    testB.setInitialInvestment(3000.00);
    if(testB.getInitialInvestment() - 3000.00 >= 0.001){
        cout << "Bond set Initial Investment Failed" << endl;
        passed = false;
    }
    testB.setInterestRate(5);
    if(testB.getInterestRate() - 5.0 >= 0.0001){
        cout << "Bond set interest rate failed" << endl;
        passed = false;
    }
    testB.setMaturityPeriod(5);
    if(testB.getMaturityPeriod() != 5){
        cout << "Bond set Maturity Period failed" << endl;
        passed = false;
    }
    testB.calculateInterestEarned(testB);
    if(testB.getInterestEarned() - 750.00 >= 0.001){
        cout << "Calculate Interest Earned on second iteration of testB failed" << endl;
        passed = false;
    }
    if(defaultTestBond > testB){
        cout << "Bond comparison failed" << endl;
        passed = false;
    }

    return passed;
}

bool testStock(){
    bool passed = true;
    Stock defaultTestStock;
    if(defaultTestStock.getTickerName() != "ABC") {
        cout << "Default Stock get Ticker Name failed" << endl;
        passed = false;
    }
    if(defaultTestStock.getCurrentMarketValue() - 123.45 >= 0.001){
        cout << "Default Stock get Current Market Value Failed" << endl;
        passed = false;
    }
    if(defaultTestStock.getExpectedGrowth() - 5.5 >= 0.001){
        cout << "Default Stock get expected growth failed" << endl;
        passed = false;
    }
    if(defaultTestStock.getEarningsPerShare() - 3.5 >= 0.001){
        cout << "Default Stock get EPS failed " << endl;
        passed = false;
    }
    if(defaultTestStock.calculateIntrinsicValue(defaultTestStock) - 71.1611 >= 0.001){
        cout << "Stock calculate intrinsic value failed" << endl;
        passed = false;
    }
    if(defaultTestStock.getIntrinsicDifference() - 52.2888 >= 0.001){
        cout << "Stock get intrinsic difference failed "<< endl;
        passed = false;
    }

    Stock testS("Google", 150.12, "GOOG", 220.45, 7.10, 10.2);
    if(testS.getCompanyName() != "Google"){
        cout << "Stock name initialization failed" << endl;
        passed = false;
    }
    if(testS.getInitialInvestment() - 150.12 >= 0.001){
        cout << "Stock Initial Investment initialization failed" << endl;
        passed = false;
    }
    if(testS.getTickerName() != "GOOG"){
        cout << "Stock ticker name initialization failed" << endl;
        passed = false;
    }
    if(testS.getCurrentMarketValue() - 220.45 >= 0.001){
        cout << "Stock Current Market Value initialization failed" << endl;
        passed = false;
    }
    if(testS.getExpectedGrowth() - 7.10 >= 0.001){
        cout << "Stock Get Expected Grown initialization failed" << endl;
        passed = false;
    }
    if(testS.getEarningsPerShare() - 10.2 >= 0.001){
        cout << "Stock Earnings per share initialization failed" << endl;
    }

    testS.setCompanyName("Apple");
    if(testS.getCompanyName() != "Apple"){
        cout << "Stock set company name failed" << endl;
        passed = false;
    }
    testS.setInitialInvestment(123.45);
    if(testS.getInitialInvestment() - 123.45 >= 0.001){
        cout << "Stock set Initial Investment Failed" << endl;
        passed = false;
    }
    testS.setTickerName("APPL");
    if(testS.getTickerName() != "APPL"){
        cout << "Stock set ticker name failed" << endl;
        passed = false;
    }
    testS.setCurrentMarketValue(100.23);
    if(testS.getCurrentMarketValue() - 100.23 >= 0.001){
        cout << "Stock set Current Market Value failed" << endl;
        passed = false;
    }
    testS.setExpectedGrowth(4.0);
    if(testS.getExpectedGrowth() - 4.0 >= 0.001){
        cout << "Stock set Expected Growth failed" << endl;
        passed = false;
    }
    testS.setEarningsPerShare(8.0);
    if(testS.getEarningsPerShare() - 8.0 >= 0.001){
        cout << "Stock set earnings per share failed" << endl;
        passed = false;
    }
    if(testS.calculateIntrinsicValue(testS) - 137.63 >= 0.001){
        cout << "Stock Calculate Intrinsic Value failed" << endl;
        passed = false;
    }
    if(testS.getIntrinsicDifference() + 37.4003 >= 0.0001){
        cout << "Stock tests get intrinsic difference failed " << endl;
        passed = false;
    }
    if(testS > defaultTestStock){
        cout << "Stock comparison failed " << endl;
        passed = false;
    }

    return passed;
}

bool testMarketAPI(){
    bool passed = true;

    MarketAPI defaultAPI;

    if(defaultAPI.getLineNumber() != 0){
        cout << "MarketAPI default construction failed" << endl;
        passed = false;
    }
    Bond bondAPI;
    vector<Bond> testBondAPI;
    string bondFileName = "../testBonds.csv";
    string companyName = "company";

    bondAPI = defaultAPI.readBondFile(bondFileName, testBondAPI, companyName);
    if(bondAPI.getCompanyName() != "company" && bondAPI.getInitialInvestment() - 500 >= 0.001
       && bondAPI.getInterestRate() - 5 >= 0.001 && bondAPI.getMaturityPeriod() != 20){
        cout << "Market API: Bond construction failed" << endl;
        passed = false;
    }

    Stock stockAPI;
    vector<Stock> testStockAPI;
    string stockFileName = "../testStocks.csv";
    companyName = "company";

    stockAPI = defaultAPI.readStockFile(stockFileName, testStockAPI, companyName);
    if(stockAPI.getCompanyName() != "company" && stockAPI.getInitialInvestment() - 500 >= 0.001
       && stockAPI.getCurrentMarketValue() - 55.5 >= 0.001 && stockAPI.getTickerName() != "COM"){
        cout << "Market API: Stock construction failed" << endl;
        passed = false;
    }

    return passed;
}





