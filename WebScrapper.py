# Nicholas Altland
#
# CS120B: Final Project
#
# Stock Market API: WebScrapper

import pandas as pd
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager

driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()))
driver.get('https://en.wikipedia.org/wiki/Stock_market')

# Storing data in a list
results = []

# Add contents of page into content
content = driver.page_source

# Load contents into BeautifulSoup
soup = BeautifulSoup(content, 'html.parser')

# Loop through all elements returned by the findAll call
for element in soup.findAll(attrs={'class': 'title'}):
    name = element.find('a')
    results.append(name.text)

# Print Results to a CSV file
# Create a data table, in this case 2D
# Names is the Column, Results is the list from above
# We can create multiple columns
df = pd.DataFrame({'Names': results})
df.to_csv('WebData.csv', index=False, encoding='utf-8')
