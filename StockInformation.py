import csv
from datetime import date, timedelta
import pandas as pd
from matplotlib import pyplot as plt
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
    # Create a list that will be used in graph creation
    graphData = []

    # For each name in the tickerNames list
    for i in tickerNames:
        # assigns stock to be a ticker symbol from the tickerNames list and download the data for it
        stock = yf.Ticker(i)

        # Get the stock values for the required stock, this will be used for the graph
        stockValues = pd.DataFrame(yf.download(tickerNames, period=periodLength, interval=intervalLength)['Adj Close'])
        graphData.append(stockValues)

        outfileContents = getOutfileData(stock, outfileContents)

    createGraph(graphData)

    return outfileContents


def createGraph(graphData):
    plt.plot(graphData[0])
    plt.show()


# Write out the stock information to a CSV file. This will allow it to be used for calculations in the C++ file
def csvWriter(header, outfileContents):
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


def getIntervalLength(periodLength):
    if periodLength == "5d" or periodLength == "1d":
        intervalLength = "1h"
    else:
        intervalLength = "1d"

    return intervalLength


def main():
    header = ['name', 'initialInvestment', 'ticker', 'currentMarketValue', 'expectedGrowth', 'earningsPerShare']
    outfileContents = []

    # Period length
    periodLength = "1y"

    intervalLength = getIntervalLength(periodLength)

    # ticker names that are assigned through C++ program
    tickerNames = ["MSFT"]  # , "AAPL", "SONY"

    outfileContents = createStocks(outfileContents, tickerNames, intervalLength, periodLength)

    csvWriter(header, outfileContents)


main()
