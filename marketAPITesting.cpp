/*
 * Nicholas Altland
 * CS120B: Final Project
 *
 * Stock Market API: Testing File
 *
 */

#include "Investment.h"
#include "marketAPI.h"
#include "Stock.h"

#include <iostream>

using namespace std;

bool testInvestment();
bool testStock();
bool testMarketAPI();

int main(){

    if(testInvestment()){
        cout << "All Investment test cases passed" << endl;
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

    Stock stockAPI;
    vector<Stock> testStockAPI;
    string stockFileName = "../testStocks.csv";
    string companyName = "company";


    return passed;
}





