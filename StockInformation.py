import csv
from datetime import date, timedelta
import pandas as pd
from matplotlib import pyplot as plt
import matplotlib.lines as mlines
import matplotlib as mpl
import yfinance as yf


# Get from C program:
# Ticker Name
# Length of interest (1d, 5d, 1mo, 6mo, 1y, 5y) (Drop down menu?)
# Allow for multiple ticker names to be passed through. Run program as a loop
# for every ticker passed through. Max 3?

# Print out all the information
# for key,value in stockInfo.items():
#     print(key, ":", value)
# print(stock.info['sector'])


def createStocks(outfileContents, tickerNames, intervalLength, periodLength):
    stockNames = []

    # For each name in the tickerNames list
    for i in tickerNames:
        # assigns stock to be a ticker symbol from the tickerNames list and download the recent history for it
        stock = yf.Ticker(i)

        # Add the required information to the outfile list
        outfileContents = getOutfileData(stock, outfileContents)

    # Get the stock values for all the tickers, this will be used for the graph
    stockValues = pd.DataFrame(yf.download(tickerNames, period=periodLength, interval=intervalLength)['Adj Close'])

    for i in stockValues:
        stockNames.append(i)

    # Call create graph to create and save a png image of the stocks
    createGraph(stockValues, stockNames)

    return outfileContents


# Use matplotlib to create a graph and save it
def createGraph(stockValues, stockNames):

    mpl.style.use('default')
    fig, axs = plt.subplot_mosaic([['left']], layout='constrained')

    if len(stockNames) == 1:
        axs['left'].plot(stockValues, label=stockNames[0])
        fig.legend(loc='outside upper right')

    elif len(stockNames) == 2:
        axs['left'].plot(stockValues, label=[stockNames[0], stockNames[1]])
        fig.legend(loc='outside upper right')

    elif len(stockNames) == 3:
        axs['left'].plot(stockValues, label=[stockNames[0], stockNames[1], stockNames[2]])
        fig.legend(loc='outside upper right')

    plt.ylabel('Price (USD)')
    plt.xticks(rotation=45)
    plt.show()
    # plt.savefig('images/stockData.png')


# Write out the stock information to a CSV file. This will allow it to be used for calculations in the C++ file
def csvWriter(outfileContents):
    header = ['name', 'initialInvestment', 'ticker', 'currentMarketValue', 'expectedGrowth', 'earningsPerShare']
    # Save data to a CSV file, Use this to create graphs and for Stock comparisons
    with open('infoOnStocks.csv', 'w', encoding='UTF8', newline='') as outfile:
        # Create a CSV writer
        writer = csv.writer(outfile)

        # write the header
        writer.writerow(header)

        # write multiple rows
        writer.writerows(outfileContents)


# Pull relevant values from the stock in question and assign them to variables
# Then add the variables to a list, which is added to the outfile contents
# Return outfileContents
def getOutfileData(stock, outfileContents):
    companyName = stock.info['shortName']
    initialInvestment = '1000'
    ticker = stock.info['symbol']
    currentMarketValue = stock.info['currentPrice']
    unroundedEG = (((stock.info['fiftyDayAverage'] - stock.info['twoHundredDayAverage'])
                    / stock.info['twoHundredDayAverage']) * 100)
    expectedGrowth = round(unroundedEG, 2)
    earningsPerShare = (stock.info['trailingEps'])

    outfileRow = [companyName, initialInvestment, ticker, currentMarketValue, expectedGrowth, earningsPerShare]
    outfileContents.append(outfileRow)

    return outfileContents


# Makes sure we are not pulling too much information for the graphs by setting a small enough interval
def getIntervalLength(periodLength):
    if periodLength == "5d" or periodLength == "1d":
        intervalLength = "1h"
    else:
        intervalLength = "1d"

    return intervalLength


def main():
    # Create a list, to be filled by createStocks. Used to print out data to CSV file
    outfileContents = []

    # ticker names that are assigned through C++ program ,"MSFT"
    tickerNames = ["SONY","AAPL","MSFT"]

    # Period length that is passed from C++ program
    periodLength = "1y"
    # Assign interval length, based on time period
    intervalLength = getIntervalLength(periodLength)

    # Call create stocks, which will loop through eacb of the ticker names call different functions on them
    outfileContents = createStocks(outfileContents, tickerNames, intervalLength, periodLength)

    # Save all the data to the outfile
    csvWriter(outfileContents)


main()
