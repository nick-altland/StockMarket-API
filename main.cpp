/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: main File
 *
 */


#include "Bond.h"
#include "Investment.h"
#include "marketAPI.h"
#include "Stock.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    char userInputContinue = 'y';           // Used for main while loop, which exits when it is 'n'
    char valid;                             // Used for checking both bond and stock while loops
    string bondFile = "../infoOnBonds.csv";     // Bond name
    string stockFile = "../infoOnStocks.csv";   // Stock name
    string companyName;                         // Company name
    int valueToChange = 0;                      // Integer for user input

    // Great user and explain what the program does
    cout << "Welcome to Nick Altland's Stock Market API." << endl;
    cout << "You will be prompted first for a Bond, then for a Stock" << endl;
    cout << "Be sure to check to see if this investment already exists in our database!" << endl;
    cout << "After you have found two investments, I will compare their yearly returns and tell you which seems like a better investment." << endl;
    cout << "You can then choose to find run through again or exit the program." << endl << endl;

    // While loop for entire program.
    while(userInputContinue != 'n'){

        // Create a bond marketAPI
        MarketAPI bondAPI(1, "replace me");

        // Create a bond vector
        vector<Bond> bondsFromFile;

        // Ask user for the company name for a bond
        cout<< "What is the name of the company you would like to get a bond from today?: ";
        companyName = MarketAPI::validateString();

        // Search the file for the company name
        Bond userBond = bondAPI.readBondFile(bondFile, bondsFromFile, companyName);

        // If the bond returned has default values, it means that the company name was not found. Prompt user for new values
        if(userBond.getCompanyName() == "Default Name"){
            cout << "I do not have this Bond on record. Please enter the values for it." << endl;
            userBond.setCompanyName(companyName);
            cout << "What is the value of the Initial Investment in " << companyName << "?: ";
            userBond.setInitialInvestment(MarketAPI::validateFloatValue());
            cout << "What is the interest rate of the bond?: ";
            userBond.setInterestRate(MarketAPI::validateFloatValue());
            cout << "What is the maturity period (in years)?: ";
            userBond.setMaturityPeriod(MarketAPI::validatePositiveInteger());

            // Append this bond to the end of the vector
            bondsFromFile.push_back(userBond);

            // Since a bond has been added, we need to write this out to the file
            bondAPI.writeBondFile(bondFile, bondsFromFile);
        }
        // Else, this is not a new bond, so print out values and ask user if they would like to change anything
        else{
            cout << "We have this bond on file!" << endl;
            userBond.printBond(userBond);

            // Get input from user
            cout<< "Does the data above look correct? (y/n): ";
            valid = MarketAPI::validateGoAgain();

            // While the values are not correct, ask them what they would like to change
            while(valid == 'n' || valid == 'N'){
                cout << "What line would you like to change? (Enter 1 for Name, 2 for Investment Amount, 3 for Interest Rate, or 4 for Maturity?: ";
                valueToChange = MarketAPI::validatePositiveInteger();
                // While the value is not 1-4
                while(valueToChange < 1 || valueToChange > 4){
                    cout << "I am sorry, that was not one of the options" << endl;
                    cout << "What line would you like to change? (Enter 1 for Name, 2 for Investment Amount, 3 for Interest Rate, or 4 for Maturity?: ";
                    valueToChange = MarketAPI::validatePositiveInteger();
                }
                if(valueToChange == 1){
                    cout << "What is the new company name?: ";
                    userBond.setCompanyName(MarketAPI::validateString());
                }
                if(valueToChange == 2){
                    cout << "What is the new initial investment amount?: ";
                    userBond.setInitialInvestment(MarketAPI::validateFloatValue());
                }
                if(valueToChange == 3){
                    cout << "What is the new interest rate?: ";
                    userBond.setInterestRate(MarketAPI::validateFloatValue());
                }
                if(valueToChange == 4){
                    cout << "What is the new Maturity Period?: ";
                    userBond.setMaturityPeriod(MarketAPI::validatePositiveInteger());
                }

                cout << "Are you finished editing the values of this bond? (y/n): ";
                valid = MarketAPI::validateGoAgain();

                // If they are done editing the value of the bond, print the new value and rewrite the file
                if(valid == 'y' || valid == 'Y'){
                    cout << "The new values of your bond are: " << endl;
                    userBond.printBond(userBond);

                    // Go to the line that this bond was on and overwrite it
                    bondsFromFile.at(bondAPI.getLineNumber()) = userBond;

                    // Since the Bond has been changed, we need to write this out to the file
                    bondAPI.writeBondFile(bondFile, bondsFromFile);
                }
            }
        }

        // Create a Stock marketAPI
        MarketAPI stockAPI(1, "replace me");

        // Create a Stock vector
        vector<Stock> stocksFromFile;

        // Ask user for the company name for a Stock
        cout << endl << "What is the name of the company you would like to get a stock from today?: ";
        companyName = MarketAPI::validateString();

        // Search the file for the company name
        Stock userStock = stockAPI.readStockFile(stockFile, stocksFromFile, companyName);

        // If the Stock returned has default values, it means that the company name was not found. Prompt user for new values
        if(userStock.getCompanyName() == "Default Name" && userStock.getTickerName() == "ABC"){
            cout << "I do not have this Stock on record. Please enter the values for it." << endl;
            userStock.setCompanyName(companyName);
            cout << "What is the value of the Initial Investment in " << companyName << "?: ";
            userStock.setInitialInvestment(MarketAPI::validateFloatValue());
            cout << "What is the ticker name of this stock?: ";
            userStock.setTickerName(MarketAPI::validateTickerName());
            cout << "What is this stock currently valued at on the market?: ";
            userStock.setCurrentMarketValue(MarketAPI::validateFloatValue());
            cout << "What is the expected growth of " << userStock.getCompanyName() << "? : ";
            userStock.setExpectedGrowth(MarketAPI::validateFloatValue());
            cout << "What are the earnings per share (EPS) of " << userStock.getCompanyName() << ": ";
            userStock.setEarningsPerShare(MarketAPI::validateFloatValue());

            // Append this stock to the end of the vector
            stocksFromFile.push_back(userStock);

            // Since a stock has been added, we need to write this out to the file
            stockAPI.writeStockFile(stockFile, stocksFromFile);
        }
        // Else, this is not a new stock, so print out values and ask user if they would like to change anything
        else{
            cout << "We have this stock on file!" << endl;
            userStock.printStock(userStock);

            // Get input from user
            cout<< "Does the data above look correct? (y/n): ";
            valid = MarketAPI::validateGoAgain();

            // While loop to see if user wants to update any information
            while(valid == 'n' || valid == 'N'){
                cout << "What line would you like to change? (Enter 1 for Name, 2 for Investment Amount...etc?: ";
                valueToChange = MarketAPI::validatePositiveInteger();
                // While the user does not choose a value from the list
                while(valueToChange < 1 || valueToChange > 6){
                    cout << "I am sorry, that was not one of the options" << endl;
                    cout << "What line would you like to change? (Enter a number 1-6): ";
                    valueToChange = MarketAPI::validatePositiveInteger();
                }
                if(valueToChange == 1){
                    cout << "What is the new company name?: ";
                    userStock.setCompanyName(MarketAPI::validateString());
                }
                if(valueToChange == 2){
                    cout << "What is the new initial investment amount?: ";
                    userStock.setInitialInvestment(MarketAPI::validateFloatValue());
                }
                if(valueToChange == 3){
                    cout << "What is the new ticker name?: ";
                    userStock.setTickerName(MarketAPI::validateTickerName());
                }
                if(valueToChange == 4){
                    cout << "What is the updated current market value?: ";
                    userStock.setCurrentMarketValue(MarketAPI::validateFloatValue());
                }
                if(valueToChange == 5){
                    cout << "What is the updated expected growth: ";
                    userStock.setExpectedGrowth(MarketAPI::validateFloatValue());
                }
                if(valueToChange == 6){
                    cout << "What is the updated EPS?: ";
                    userStock.setEarningsPerShare(MarketAPI::validateFloatValue());
                }

                // Ask them if they are done editing the stock
                cout << "Are you finished editing the values of this stock? (y/n): ";
                valid = MarketAPI::validateGoAgain();

                // If they are done editing, then print out the new stock values. Overwrite it, and rewrite the stock file
                if(valid == 'y' || valid == 'Y'){
                    cout << "The new values of your stock are: " << endl;
                    userStock.printStock(userStock);

                    // Go to the line that this stock was on and overwrite it
                    stocksFromFile.at(stockAPI.getLineNumber()) = userStock;

                    // Since the stock has been changed, we need to write this out to the file
                    stockAPI.writeStockFile(stockFile, stocksFromFile);
                }
            }
        }

        MarketAPI::compareInvestments(userBond, userStock);

        // Ask them if they create a new stock and a new bond. If yes, loop. If not, break loop
        cout << endl << "Do you wish to look up another Investment? (y/n): ";
        userInputContinue = MarketAPI::validateGoAgain();
    }

    cout << endl << "Thank you for using Nick Altland's Stock Market API" << endl;

    return 0;
}

