/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: marketAPI.h source File
 *
 */

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