# Stock Market API and Web Scrapper

### Nick Altland, CS120B, Final Project

### Project plan:

- Create GitHub and starter code (done)
- Build out code base
    - Copy code from previous project (done)
    - Add a search for the Ticker and Stock name (Have to write Python Scrapper first)
- Change previous code so that it makes more sense with the structure of this project
    - Create main driver
    - Add more calculations
      - Description
      - Dividends
      - Performance
        - Short Term
        - Long Term
      - Income Rations
      - Debt Ratios
      - Revenue
- Add Python code
    - Webscrapper. How will it integrate with the C++
    - Graph making. Will matplotlib work or are there better options
- Add testing suite
- Add ability to compare more then just two stocks
- Add GUI using QT programs

[Raw Data](https://www.macrotrends.net/stocks/stock-screener)
[Articles on Stock](https://www.morningstar.com/stocks)
[YaHoo Finance](https://finance.yahoo.com)
[Google Finance](https://www.google.com/finance/?hl=en)

### Python Web Scrapper:

- Basics: [Tutorial from Oxylabs](https://oxylabs.io/blog/python-web-scraping)

NOTES:
- Web Scrapping: Automated process of gathering public data
- Python libraries to choose from:
  - Requests: Simple but limited
  - Beautiful Soup: Used alongside Requests. Uses parser to extract data
    - Good for beginners
  - Ixml:
    - Fast powerful easy-to-use HTML and XML parsing
    - Needs "Requests" library to pull HTML strings
    - Impacted by poor HTML
  - Selenium
    - Can pull from websites that uses JavaScript
    - Used for execution of test cases or test scripts on web applications
    - Needs: Web Browser, the driver for the browser, and the pip packages
  
- This tutorial uses Beautiful Soup, Pandas, and Selenium

What I can do is pull all the stocks from the website (over 6000) and add them to a csv file. 
I can then take that file and use it as the search parameters for the webscrapper,
going directly to that page (adding the name to the end of the HTTPS link)

- [Additional Tutorial from Real Python](https://realpython.com/python-web-scraping-practical-introduction/)