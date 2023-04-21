/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: marketAPI.h source File
 *
 */

#include "Bond.h"
#include "marketAPI.h"
#include "Stock.h"
#include "Investment.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;


MarketAPI::MarketAPI() {
    lineNumber = 0;
    fileHeader = "";
}

MarketAPI::MarketAPI(int lineNumber, string fileHeader) {
    this->lineNumber = lineNumber;
    this->fileHeader = fileHeader;
}

Bond MarketAPI:: readBondFile(string &fileName, vector<Bond> &bondFromFile, string &inputCompanyName){

    cout << endl;

    ifstream bondFile;
    bondFile.open(fileName);

    string header;
    string companyName;
    float initialInvestment;
    float interestRate;
    int maturityPeriod;
    char comma;

    bool found = false;

    if (bondFile){
        getline(bondFile, header);
        this->fileHeader = header;
    }
    else{
        cout << "Could not open file" << endl;
    }

    int count = 0;

    while (bondFile && bondFile.peek() != EOF){

        getline(bondFile, companyName, ',');

        companyName.erase(remove(companyName.begin(), companyName.end(), '\n'), companyName.end());

        bondFile >> initialInvestment;
        bondFile >> comma;

        bondFile >> interestRate;
        bondFile >> comma;

        bondFile >> maturityPeriod;

        Bond newBond(companyName, initialInvestment, interestRate, maturityPeriod);

        bondFromFile.push_back(newBond);

        if(companyName == inputCompanyName){
            this->lineNumber = count;
            // cout << "Bond company name found on line " << lineNumber + 1 << endl;
            found = true;
        }
        ++count;
    }

    bondFile.close();

    if(found){
        return bondFromFile[lineNumber];
    }
    else{
        this->lineNumber = count;

        Bond emptyBond;
        return emptyBond;
    }
}


Stock MarketAPI:: readStockFile(string &fileName, vector<Stock> &stocksFromFile, string &inputCompanyName){

    cout << endl;

    ifstream stockFile;
    stockFile.open(fileName);

    string header;
    string companyName;
    string tickerName;
    float initialInvestment;
    float currentMarketValue;
    float expectedGrowth;
    float earningsPerShare;
    char comma;
    bool found;

    if (stockFile){
        getline(stockFile, header);
        this->fileHeader = header;
    }
    else{
        cout << "Could not open file" << endl;
    }

    int count = 0;

    while (stockFile && stockFile.peek() != EOF){

        getline(stockFile, companyName, ',');

        stockFile >> initialInvestment;
        stockFile >> comma;

        getline(stockFile, tickerName, ',');

        stockFile >> currentMarketValue;
        stockFile >> comma;

        stockFile >> expectedGrowth;
        stockFile >> comma;

        stockFile >> earningsPerShare;

        companyName.erase(remove(companyName.begin(), companyName.end(), '\n'), companyName.end());

        Stock newStock(companyName, initialInvestment, tickerName, currentMarketValue, expectedGrowth, earningsPerShare);

        stocksFromFile.push_back(newStock);

        if(companyName == inputCompanyName){
            this->lineNumber = count;
            // cout << "Stock company name found on line " << lineNumber + 1 << endl;
            found = true;
        }
        ++count;
    }

    stockFile.close();

    if(found){
        return stocksFromFile[lineNumber];
    }
    else{
        this->lineNumber = count;

        Stock emptyStock;
        return emptyStock;
    }
}

void MarketAPI::writeBondFile(string &fileName, vector<Bond> &bonds) {

    ofstream outFile;
    outFile.open(fileName);

    outFile << fileHeader << endl;

    for(int i = 0; i < bonds.size() -1; ++i){
        outFile << bonds[i].getCompanyName() << ",";
        outFile << bonds[i].getInitialInvestment() << ",";
        outFile << bonds[i].getInterestRate() << ",";
        outFile << bonds[i].getMaturityPeriod() << endl;
    }

    outFile << bonds[bonds.size() -1].getCompanyName() << ",";
    outFile << bonds[bonds.size() -1].getInitialInvestment() << ",";
    outFile << bonds[bonds.size() -1].getInterestRate() << ",";
    outFile << bonds[bonds.size() -1].getMaturityPeriod();

    outFile.close();
}

void MarketAPI::writeStockFile(string &fileName, vector<Stock> &stocks) {

    ofstream outFile;
    outFile.open(fileName);

    outFile << fileHeader << endl;

    for (int i = 0; i < stocks.size() - 1; ++i) {
        outFile << stocks[i].getCompanyName() << ",";
        outFile << stocks[i].getInitialInvestment() << ",";
        outFile << stocks[i].getTickerName() << ",";
        outFile << stocks[i].getCurrentMarketValue() << ",";
        outFile << stocks[i].getExpectedGrowth() << ",";
        outFile << stocks[i].getEarningsPerShare() << endl;
    }

    outFile << stocks[stocks.size() - 1].getCompanyName() << ",";
    outFile << stocks[stocks.size() - 1].getInitialInvestment() << ",";
    outFile << stocks[stocks.size() - 1].getTickerName() << ",";
    outFile << stocks[stocks.size() - 1].getCurrentMarketValue() << ",";
    outFile << stocks[stocks.size() - 1].getExpectedGrowth() << ",";
    outFile << stocks[stocks.size() - 1].getEarningsPerShare();

    outFile.close();
}

int MarketAPI::getLineNumber() const {
    return lineNumber;
}

void MarketAPI::compareInvestments(Bond &bond, Stock &stock) {
    float bondInterestEarned;

    // See how much interest the bond will earn over its life span
    bondInterestEarned =  bond.calculateInterestEarned(bond);
    bond.setYearlyReturns(bondInterestEarned/bond.getMaturityPeriod());

    stock.calculateIntrinsicValue(stock);

    stock.setYearlyReturns((stock.getEarningsPerShare()*stock.getInitialInvestment())/stock.getCurrentMarketValue());

    cout << endl << "A Bond with " << bond.getCompanyName() << " will generate a total of " << bondInterestEarned << " interest over it's life span of " << bond.getMaturityPeriod() << " years,";
    cout << " given an investment of " << bond.getInitialInvestment() << "$."<< endl;

    cout << "The stock of ";
    if(stock.getIntrinsicDifference() >=0){
        cout << stock.getCompanyName() << " is currently OVERVALUED on the market by " << stock.getIntrinsicDifference() << ". I would not recommend purchasing it." << endl;
    }
    else if(stock.getIntrinsicDifference() < 0){
        cout << stock.getCompanyName() << " is currently UNDERVALUED on the market by " << stock.getIntrinsicDifference() << ". It may be a good purchase." << endl;
    }
    cout << endl;

    // Print out the Stock earnings per share * the amount invested / stock price. This would be the yearly amount earned
    cout << "As for which will be more profitable yearly: " << endl;
    cout << "Your bond will earn you " << bond.getYearlyReturns() << " yearly" << endl;
    cout << "Your stock will earn you " << stock.getYearlyReturns() << " yearly" << endl;

    if(bond.getYearlyReturns() > stock.getYearlyReturns()){
        cout << "Your bond with " << bond.getCompanyName() << " will earn you more yearly then your stock with " << stock.getCompanyName() << endl;
    }
    else if(bond.getYearlyReturns() < stock.getYearlyReturns()){
        cout << "Your stock with " << stock.getCompanyName() << " will earn you more yearly then your bond with " << bond.getCompanyName() << endl;
    }
    else{
        cout << "Both your stock and your bond will earn equal amounts this year." << endl;
    }

}

string MarketAPI::validateString() {
    bool userInputValid = false;
    int maxNumberOfLoops = 0;
    string userInput;

    while (!userInputValid) {

        if(maxNumberOfLoops == 5){
            cout << endl << "Error. Too many attempted entries. Using placeholder value" << endl;
            return "Placeholder";
        }

        getline(cin, userInput);
        cin.clear();
        if (userInput.length() < 1) {
            cout << "No input. Please enter a valid company name: ";
        }
        else {
            userInputValid = true;
        }
        ++maxNumberOfLoops;
    }
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
    return userInput;
}

string MarketAPI::validateTickerName(){
    bool userInputValid = false;
    int maxNumberOfLoops = 0;
    string userInput;

    while(!userInputValid){
        if(maxNumberOfLoops == 5){
            cout << endl << "Error. Too many attempted entries. Using placeholder value" << endl;
            return "ABC";
        }
        getline(cin, userInput);
        cin.clear();

        userInputValid = true;

        if (userInput.length() < 1){
            cout << "No input. Please enter a valid ticker name: ";
            userInputValid = false;
        }
        else if (userInput.length() > 5){
            cout << "Please enter a valid ticker name, no more then five letters: ";
            userInputValid = false;
        }
        else{
            for (int i = 0; i < userInput.length(); ++i) {
                if (!isalpha(userInput[i])) {
                    cout << "Please enter a valid ticker name, using alpha characters: ";
                    userInputValid = false;
                    break;
                }
            }
        }
        ++maxNumberOfLoops;
    }
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    return userInput;
}

float MarketAPI::validateFloatValue() {
    bool userInputValid = false;
    int maxNumberOfLoops = 0;
    float stockValue;
    int count;
    int numberOfDecimals = 0;
    string userInput;
    stringstream stringToFloat;

    while(!userInputValid){
        if(maxNumberOfLoops == 5){
            cout << endl << "Error. Too many attempted entries. Using placeholder value" << endl;
            return 1.5;
        }

        userInputValid = true;
        count = 0;
        numberOfDecimals = 0;

        getline(cin, userInput);
        cin.clear();

        if(userInput.length() < 1){
            cout << "No input. Please enter a valid number: ";
            userInputValid = false;
        }
        else if((userInput[0] == '-' || userInput[0] == '.') && userInput.length() == 1){
            cout << "Please enter a valid number: ";
            userInputValid = false;
        }
        else{
            if((userInput[0] == '-' || userInput[0] == '.') && userInput.length() > 1){
                ++count;
            }
            for (int i = count; i < userInput.length(); ++i) {
                if (!isdigit(userInput[i])) {
                    if(userInput[i]=='.'){
                        ++numberOfDecimals;
                        if(numberOfDecimals > 1){
                            userInputValid = false;
                            cout << "Too many decimals. Please enter a valid number: ";
                            break;
                        }
                    }
                    else{
                        cout << "Please enter a valid numeric value, with no symbols or letters: ";
                        userInputValid = false;
                        break;
                    }
                }
            }
        }
        ++maxNumberOfLoops;
    }
    stringToFloat << userInput;
    stringToFloat >> stockValue;
    return stockValue;
}

char MarketAPI::validateGoAgain(){
    bool userInputValid = false;
    int maxNumberOfLoops = 0;
    string userInput;
    char userInputCharacter;

    while(!userInputValid) {
        if (maxNumberOfLoops == 5) {
            cout << endl << "Error. Too many attempted entries. Using placeholder value" << endl;
            return 'n';
        }

        getline(cin, userInput);
        cin.clear();

        if(userInput.length() < 1){
            cout << "No input. Please enter a valid character (y/n): ";
        }
        else if(userInput.length() > 1){
            cout << "Please enter a valid, single character (y/n): ";
        }
        else{
            userInputCharacter = userInput[0];
            if(userInputCharacter == 'y' || userInputCharacter == 'n' || userInputCharacter == 'Y' || userInputCharacter == 'N'){
                userInputValid = true;
            }
            else{
                cout << "Please enter either 'y' or 'n': ";
            }
        }
        ++maxNumberOfLoops;
    }
    return userInputCharacter;
}

int MarketAPI::validatePositiveInteger(){
    bool userInputValid = false;
    int maxNumberOfLoops = 0;
    int positiveInteger;
    string userInput;
    stringstream stringToInt;

    while(!userInputValid){
        if(maxNumberOfLoops == 5){
            cout << endl << "Error. Too many attempted entries. Using placeholder value" << endl;
            return 5;
        }

        userInputValid = true;
        getline(cin, userInput);
        cin.clear();

        if(userInput.length() < 1){
            cout << "No input. Please enter a valid number: ";
            userInputValid = false;
        }
        else if(userInput == "0"){
            cout << "Please enter a value greater then zero: ";
            userInputValid = false;
        }
        else{
            for (int i = 0; i < userInput.length(); ++i) {
                if (!isdigit(userInput[i])) {
                    cout << "Please enter a positive integer value:";
                    userInputValid = false;
                    break;
                }
            }
        }
        ++maxNumberOfLoops;
    }

    stringToInt << userInput;
    stringToInt >> positiveInteger;

    return positiveInteger;
}