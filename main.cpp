/*
 * Nicholas Altland
 * CS120B: Final Project
 *
 * Stock Market API: main File
 *
 */

#include "Investment.h"
#include "marketAPI.h"
#include "Stock.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Different OSs use different CLI commands to run Python
#ifdef _WIN32
const string python = "python";
#else
const string python = "python";
#endif

int main() {
    char userInputContinue = 'y';           // Used for main while loop, which exits when it is 'n'
    string stockFile = "../infoOnStocks.csv";   // Stock name
    string tickerNames;                         // Company name

    // Great user and explain what the program does
    cout << "Welcome to Nick Altland's Stock Market API." << endl;
    cout << "You will be prompted to enter up to three ticker names for the stocks you are interested in." << endl;
    cout << "I will then retrieve data on these stocks and, after performing a series of calculations, ";
    cout << "inform you on which is the better investment" << endl;
    cout << "You can then choose to find run through again or exit the program." << endl;

    // While loop for entire program.
    while (userInputContinue != 'n') {

        // Create a Stock marketAPI
        MarketAPI stockAPI(1, "replace me");

        // Create a Stock vector
        vector<Stock> stocksFromFile;

        // Number of tickers the user will be entering today
        int numberOfTickers = 0;
        while (numberOfTickers == 0) {
            cout << "How many stocks are you interested in today?(1-3): ";
            numberOfTickers = MarketAPI::validatePositiveInteger();
            if (numberOfTickers > 3) {
                cout << endl << "Please enter a number less the three and greater then 0";
                numberOfTickers = 0;
            }
        }

        // Create a vector to hold the names of the tickers, then iterate through and fill it
        vector<string> namesOfTickers;
        for (int i = 0; i < numberOfTickers; ++i) {
            // Ask user for the company name for a Stock
            cout << "What is the name of the company you would like to get a stock from today?: ";
            tickerNames = MarketAPI::validateTickerName();
            namesOfTickers.push_back(tickerNames);
        }

        // Command line string to call python script to scrape the web for information
        string command = python + " ../StockInformation.py " + to_string(numberOfTickers) + " 1y ";

        for(string name: namesOfTickers){
            command.append(name + " ");
        }

        cout << command << endl;

        system(command.c_str());

        // For each stock on file add it to a vector of stocks, then pass that vector back to main
        stocksFromFile = stockAPI.readStockFile(stockFile, stocksFromFile);

        // Set the initial investment for each ticker
        for(Stock tick : stocksFromFile){
            cout << "How much are you planning to invest in " << tick.getTickerName() << "?: ";
            tick.setInitialInvestment(MarketAPI::validateFloatValue());
        }

        cout << "Here are the values of the stocks you requested: " << endl;

        // Compare the three stocks
        stockAPI.compareInvestments(stocksFromFile);

        system(R"(C:\Users\nlalt\Desktop\stockData.png)");

        // Ask them if they create a new stock and a new bond. If yes, loop. If not, break loop
        cout << endl << "Do you wish to look up another Investment? (y/n): ";
        userInputContinue = MarketAPI::validateGoAgain();
    }

    cout << endl << "Thank you for using Nick Altland's Stock Market API" << endl;

    return 0;
}
