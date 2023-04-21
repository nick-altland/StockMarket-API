# Stock Market API and Web Scrapper
### Nick Altland, CS120B

Given the 1-5 character ticker name of a stock, look up information on that stock and output graphs

---

### Include a summary of your program, including a list of Module 2 concepts used:

DISCLAIMER: THIS PROGRAM IS IN NO WAY FINANCIAL ADVICE, AND IS FOR EDUCATIONAL AND THEORETICAL PURPOSES ONLY!

For Module two version of my open-ended project, I took the basic functions I built in module one moved a lot of the functionality to incorporate both Polymorphism and file input-output. 

- main.cpp: This is the driver for the API. No calculations are done here, but there are a few validation loops as well as a majority of the function calls. Many of the classes and objects are created here
- marketAPI: I think of this as the user interface. All the input validation is done here, and it acts as a layer between the user in main and the calculations being done in the Investment classes. All the file input and output is done here in readBondFile, readStockFile, writeBondFile, and writeStockFile.
- Investment: This is the superclass for the polymorphism. An investment HAS-A Company and an Initial investment amount, and after a calculation is called in the subclasses a yearly return. This last value is the one that the overload comparisons work off of.
- Bond: The first subclass, a Bond IS-A investment, and has additional variables that make it unique when compared to other investments. 
- Stock: The second subclass, a Stock IS-A investment, and again has unique characteristics.

The next step would be adding further subclasses of both Investment, but also of Bond and Stock, since both have subclasses that have different returns or modifiers that change how they behave. however, for the moment these are enough to work with.

The program is structured as follows. The user is greeted and given instructions. They are then prompted for the company name for a bond. This data, along with an empty vector of bonds is sent to marketAPI. The bond csv file is opened and read through, checking each line to see if it matches the company name. If it does, the line where it is found is saved. If not, the company is a new one to the program and the user is asked to enter information into it. However, if it has been found, the information is printed to the screen and the user can edit different variables. If the user edits a bond/creates a new one, the vector is sent to marketAPI and the file is overwritten from the vector. The exact same process is used to create a Stock, with different variables.

In the final step of the program, the bond and stock are analyzed. Calculations are done to see the yearly returns of both investments. Additionally, the stock's intrinsic value is compared to the current market price, and the user is told whether it is a good investment or not. Finally, the yearly returns are compared, and the user is told which would generate more wealth yearly.

The program then asks the user if they wish to go again, or wish to exit.

List of Module Two concepts used:
1. Polymorphism: Bond and Stock ARE-A Investment, which has-a company name and an investment amount. These subclasses are called in marketAPI, where they are compared in compareInvestments.
2. File Input/Output: Used extensively in marketAPI. The files are infoOnStocks.csv and infoOnBonds.csv. The data is pulled into a vector while it is searched, the (if needed) the file is rewritten, using data from the vector.

### Any known bugs at time of submission:

---

## Future plans for project:

The goal of this project is to create a stock market API that, utilizing a web scraper, will pull the trends of various stock values. This will include what it valued at currently in USD ($), previous daily values, and projected future values

I broke this into several steps:

### Stage 1: Ground work

This was the basics for module 1. Create a functioning program that accepts user entry and performs a calculation on the data to spit an output. I had originally planned on asking for a series of daily stock values and then projecting the next day's value. However, after some research I found that it was a much more difficult task than I had originally thought. This caused me to pivot to the project I created to calculate the intrinsic value then compare it to the actual value, creating a difference. This allowed me to see if the current stock price is overvalued or undervalued, allowing me to output rudimentary financial advice.

### Stage 2: Library of Data

This is where I began module 2. Originally I wanted to just prompt the user for a stock name and ticker name, then search a library to see if they exist. To meet the project requirements, I decided to add an additional investment: a bond. Besides this change, my actually accomplished exactly what I set out to do. I took user input, searched a file, and pulled the required information. Not only this, I also gave the user the ability to update the file. I then added more calculations to give more information about the investment. Structurally, everything is organized and works to a satisfactory degree. 

### Stage 3: Further Calculations

Now that a library has been built, I can move onto adding more calculations to the program. What is the current market trend? What will the price of the stock be tomorrow? One prompt I want to add is asking for the top stock of the day. This would provide the stock, from the library, with the largest negative value when compared to its current market price, then print it out to main. Additionally, I want to add better search functionality, and implement a data set level search algorithm make searching more efficient.

### Stage 4: Web Scrapper

This is the core, main stage of the project. I want to make a web scrapper that will pull the actual value of a stock from the internet and display it to the user. This will build on my previous step of creating a library, only instead of searching a library it will search the web. Additional data points that I want to pull could be:

* Data that can be turned into graphs that show previous growth and projected growth
* News articles on this stock

It will also calculate and make a general statement about if this stock is a good investment. The next step would be to have the user enter a general category, such as "technology" or "automotive" and provide the top three stocks in that industry. After that, the final step would be to provide the three best performing stocks of the day.


### Stage 5: Visual Update

Once the system works, the next step will be to implement a better UI. There are multiple ways to do this, but I plan on hosting it on a website, and using python or another program to create more visually appealing graphs.



### Citations:
- [Google uses Morningstar to display their stocks when searched. Use for web-scrapper? Pulled stock data from to test with](https://www.morningstar.com/stocks)
- [Formula to calculate the current market value of a stock](https://en.wikipedia.org/wiki/Benjamin_Graham_formula)
- [Price to earnings formula](https://smallbusiness.chron.com/calculate-companys-stock-price-21802.html)
- [Another site to scrape for data](https://www.macrotrends.net/stocks/charts/AAPL/apple/eps-earnings-per-share-diluted?q=Microsoft+expected+growth)
- [In-depth explanation of intrinsic models](https://valueinvesting.io/MSFT/valuation/intrinsic-value)
- [Intrinsic Value Calculator, to compare my outputs with](https://tradebrains.in/graham-calculator/)
- [How to transform a string to lowercase/uppercase](https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/)

### The grade you think you have earned:

I am going to go out on a limb here and say I earned a solid 100. I included multiple concepts from the module, implemented in interesting and efficient ways. Additionally, I built majorly on my module one project, scrapping some previously essential parts and creating whole new classes to work off each other. My project is sufficiently complex, with extensive user interaction and validation. Finally, the testing suite is exhaustive, and took too long to write. I am sure I missed some way to break my program, but I was not able to find it. Comments are robust and informative, and the lifespan is over a week.

In conclusion, I worked really, really hard on this, and am very proud. Please do not break it immediately. 

### Link to short video (less than 5 min) giving a brief overview of program:

https://youtu.be/omk18GDA0yo

---

FOR TESTING, I HAVE PROVIDED THE VALUES OF THREE STOCKS BELOW:

Apple (AAPL):
- Current Market Value: 154.50
- Expected Growth: 7.30
- Earnings per Share: 6.11

Microsoft (MSFT):
- Current Market Value: 258.35
- Expected Growth: 11.10
- Earnings per Share: 9.01

Sony (SONY):
- Current Market Value: 93.13
- Expected Growth: 7.90
- Earnings per Share: 6.07

CURRENTLY, THESE VALUES ARE IN THE INPUT/OUTPUT FILES, BUT FEEL FREE TO TWEAK SOME VALUES TO SEE WHAT CHANGES :)