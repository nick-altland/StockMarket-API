# Stock Market API and Web Scrapper

### Nick Altland, CS120B, Final Project

### Directions:

- Install Modules and Variable Names:
  - C++:
    - There are no modules needed to be downloaded, but the variable userDesktop in main.cpp needs to be changed to the correct path directory. This is where the graph image will be saved when the python program runs (line 32). I could have kept the show statement in the python program, but I wanted the graph to appear at the end where it makes more sense.
    - If the window's machine uses "py" instead of "python, that has to be changed on line 21"
  - Python:
    - pip install yfinance
    - pip install matplotlib
    - pip install pandas

### Summary of the Program

The program begins by greeting the user and explaining the general idea of the program. It then enters a while loop so the program can repeat any number of times. Upon entering, it creates a marketAPI object and a vector of stocks. These will be used throughout the program. The user is then prompted to enter how many stocks they want to get information on. This is restricted down to 3 to simplify things down the road. At each user input, a validation loop is called to ensure the input is not garbage.

A vector of strings is then filled with each ticker name, and the user is prompted to enter the interval of time the data needs to be pulled from. A command line statement is then created and called, using data passed in from above, calling the python script StockInformation.py.

The python script takes all the information from the command line statement and creates a list of ticker names. A try/except statement is included incase the user entered an invalid ticker name. If they did, the program just uses the values from the last time the program was run. If the ticker names are valid, we enter the creatStocks. For each ticker name passed in, yfinance scrapes the YaHoo finance API to pull all data on the stock. The relevant data is selected and added to a list, which is written to a CSV file. At the same time, a graph is created used matplotlib, then saved to the user Desktop. The program then terminates.

After the python program terminates, the C++ program reads the stock information scrapped from YaHoo from the CSV file. Each are added to the stock vector from above and passed to the MarketAPI function compareInvestments. In this function, various other Investment and Stock functions are called to calculate which stock will perform the best. Finally, back in main, another commandline statement is called to show the graph created above. The user is then prompted to see if they want to go again.

### Concepts Used

- module 1: User validation
- module 2: Polymorphism, user input, file input and output
- module 3: Python and command line, matplotlib
- module 4: Displaying images

### The OS 

- I created this program on Windows 10. I have no way of testing it on Linux or MacOS

### Grade You Think You have Earned

I only need a 30 on this project, and looking at the requirements, I know I have earned at least that. This project was done for personal enjoyment and exploration, and the grade was the knowledge I gained along the way. That being said, 168.2. Some code is based on previous projects, but is heavily modified.

SOURCES:

[MatPlotLib: Tutorial on Creating a Legend](https://matplotlib.org/stable/tutorials/intermediate/legend_guide.html)
[Project yfinance](https://pypi.org/project/yfinance/)
[YaHoo Finance](https://finance.yahoo.com)

LINK TO VIDEO:

https://youtu.be/GMKAVyUaOdc