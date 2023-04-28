import csv
import datetime
from dateutil.relativedelta import relativedelta
import pandas as pd
import matplotlib.pyplot as plt
from datetime import date
import yfinance as yf

# Get from C program:
# Ticker Name
# Length of interest (1d, 5d, 1mo, 6mo, 1y, 5y) (Drop down menu?)
# Allow for multiple ticker names to be passed through. Run program as a loop
#   for every ticker passed through. Max 3?

header = ['name', 'initialInvestment', 'ticker', 'currentMarketValue', 'expectedGrowth', 'earningsPerShare']
outfileContents = []

# ticker names that are assigned through C++ program
tickerNames = ["MSFT"]

# Period length
periodLength = "5d"

# Download the last five years of data for the ticker names and save it to a dictionary
todayDate = date.today()
oneYearAgoDate = date.today() - relativedelta(years=5)
data = yf.download(tickerNames, start=oneYearAgoDate, end=todayDate, group_by="ticker")

# For each name in the tickerNames list
for i in tickerNames:
    # assigns stock to be a ticker symbol from the tickerNames list
    stock = yf.Ticker(i)

    # Gets stock info
    stockInfo = stock.info

    # Print out all the information
    # for key,value in stockInfo.items():
    #     print(key, ":", value)

    # Pull relevant values from the stock in question and assign them to variables
    # Then add the variables to a list, which is added to the outfile contents
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

    # print(stock.info['sector'])
    # print(stock.info['open'])
    # print(stock.info['dayLow'])
    # print(stock.info['dayHigh'])


# Save data to a CSV file. Use this to create graphs and for Stock comparisons
with open('infoOnStocks.csv', 'w', encoding='UTF8', newline='') as outfile:
    # Create a CSV writer
    writer = csv.writer(outfile)

    # write the header
    writer.writerow(header)

    # write multiple rows
    writer.writerows(outfileContents)

