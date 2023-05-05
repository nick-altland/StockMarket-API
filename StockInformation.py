import csv
from datetime import date, timedelta
import pandas as pd
from matplotlib import pyplot as plt
import matplotlib.lines as mlines
import matplotlib as mpl
import yfinance as yf

# Print out all the information
# for key,value in stockInfo.items():
#     print(key, ":", value)
# print(stock.info['sector'])

# import os. argv
# index 1 in commandline
# image manip: Syntax to pass through

def createStocks(outfileContents, tickerNames, intervalLength, periodLength):
    stockNames = []

    # For each name in the tickerNames list
    for i in tickerNames:
        # assigns stock to be a ticker symbol from the tickerNames list and download the recent history for it
        stock = yf.Ticker(i)

        # stockInfo = stock.info
        #
        # for key,value in stockInfo.items():
        #     print(key, ":", value)
        # print(stock.info['sector'])

        # Add the required information to the outfile list
        outfileContents = getOutfileData(stock, outfileContents)

    # Get the stock values for all the tickers, this will be used for the graph
    # This is saved in a panda dataframe, which will allow us to access it through matplotlib
    stockValues = pd.DataFrame(yf.download(tickerNames, period=periodLength, interval=intervalLength)['Adj Close'])

    for i in stockValues:
        stockNames.append(i)

    # Call create graph to create and save a png image of the stocks
    createGraph(stockValues, stockNames, tickerNames)

    return outfileContents


# Use matplotlib to create a graph and save it
def createGraph(stockValues, stockNames, tickerNames):
    # Set the colors to default and create a constricted graph layout, so the legend will be outside the graph
    mpl.style.use('default')
    fig, axs = plt.subplot_mosaic([['left']], layout='constrained')

    # For each possible sizes (1-3), make sure the graph prints things out correctly with matching labels
    if len(stockNames) == 1:
        # Adds labels for each stock and positions the legend to the upper right
        axs['left'].plot(stockValues, label=tickerNames[0])
        fig.legend(loc='outside upper right')

    elif len(stockNames) == 2:
        axs['left'].plot(stockValues, label=[stockNames[0], stockNames[1]])
        fig.legend(loc='outside upper right')

    elif len(stockNames) == 3:
        axs['left'].plot(stockValues, label=[stockNames[0], stockNames[1], stockNames[2]])
        fig.legend(loc='outside upper right')

    # Adds a label for y axis, x-axis are dates so no need for label
    plt.ylabel('Price (USD)')
    # Rotate the values on the x-axis by 45 degrees so that  they do not run into each other if too close together
    plt.xticks(rotation=45)
    # Save the graph (or show it: )
    plt.show()
    #plt.savefig('images/stockData.png')


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


# Makes sure we are not pulling too much information for the graphs to clearly display
# by setting a small enough interval
def getIntervalLength(periodLength):
    if periodLength == "5d":
        intervalLength = "1h"
    else:
        intervalLength = "1d"

    return intervalLength


def main():
    # Create a list, to be filled by createStocks. Used to print out data to CSV file
    outfileContents = []

    # Get from C program:
    # Ticker Name
    # Length of interest (5d, 1mo, 6mo, 1y, 5y) (Drop down menu?)
    # Investment amount
    # Allow for multiple ticker names to be passed through, up to three
    # Add try/except loop for ticker validation

    # ticker names that are assigned through C++ program "SONY","AAPL","MSFT"
    tickerNames = ["SONY","AAPL","MSFT"]

    # Period length that is passed from C++ program
    periodLength = "1y"
    # Assign interval length, based on time period
    intervalLength = getIntervalLength(periodLength)

    # Call create stocks, which will loop through each of the ticker names call different functions on them
    outfileContents = createStocks(outfileContents, tickerNames, intervalLength, periodLength)

    # Save all the data to the outfile
    csvWriter(outfileContents)


main()
