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
