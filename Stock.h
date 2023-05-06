/*
 * Nicholas Altland
 * CS120B: Final Project
 *
 * Stock Market API: Investment subclass Stock header file
 *
 */

#ifndef FINAL_PROJECT_NALTLAND_STOCK_H
#define FINAL_PROJECT_NALTLAND_STOCK_H

#include "Investment.h"

class Stock : public Investment {

private:
    std::string tickerName;
    float currentMarketValue;
    float expectedGrowth;
    float earningsPerShare;
    float intrinsicValue = 0.0;
    float differenceOfIntrinsicToActual = 0.0;

public:
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: Creates a default stock
     */
     Stock();

    /**
     * Requires: A series of variables that make up a stock. Company name, investment amount
     *           ticker name, and current market value of the stock
     * Modifies: nothing
     * Effects: Creates a stock investment
     */
    Stock(std::string companyName, float initialInvestment, std::string tickerName, float currentMarketValue, float expectedGrowth, float earningsPerShare);

    // Getters
    std::string getTickerName() const;
    float getCurrentMarketValue() const;
    float getExpectedGrowth() const;
    float getEarningsPerShare() const;
    float getIntrinsicDifference() const;

    // Setters
    void setTickerName(std::string tickerName);
    void setCurrentMarketValue(float currentMarketValue);
    void setExpectedGrowth(float expectedGrowth);
    void setEarningsPerShare(float earningsPerShare);
    void setIntrinsicDifference(float differenceOfIntrinsicToActual);

    // Overload Operands
    friend  bool operator == (const Stock &first, const Stock &second);
    friend bool operator > (const Stock &first, const Stock &second);
    friend bool operator < (const Stock &first, const Stock &second);
    friend bool operator != (const Stock &first, const Stock &second);
    friend bool operator <= (const Stock &first, const Stock &second);
    friend bool operator >= (const Stock &first, const Stock &second);


    /** printStock
     * Requires: A stock
     * Modifies: nothing
     * Effects: Prints out the values of a stock
     */
    void printStock(Stock &userStock);

    /** calculateIntrinsicValue
     * Requires: a stock object
     * Modifies: called the setting for differenceOfIntrinsicToActual
     * Effects: Uses a formula to calculate the intrinsic value of the stock, then compares it to the actual value of the
     *          stock to see if the stock is over or underpriced
     */
    float calculateIntrinsicValue(Stock &stock);

};


#endif //FINAL_PROJECT_NALTLAND_STOCK_H
