/*
 * Nicholas Altland
 * CS120B: Open Ended Project
 *
 * Stock Market API: Investment subclass Bond header file
 *
 */

#ifndef M2OEP_NALTLAND_BOND_H
#define M2OEP_NALTLAND_BOND_H

#include "Investment.h"

class Bond : public Investment {

private:
    float interestRate;
    float interestEarned = 0.0;
    int maturityPeriod;

public:
    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Creates a default Bond
     */
     Bond();

    /**
     * Requires: The company the bond is from, the initial investment, the rate of interest,
     *           and the maturityTime of the bond
     * Modifies: Nothing
     * Effects: Creates a bond object
     */
    Bond(std::string companyName, float initialInvestment, float interestRate, int maturityPeriod);

    // Getters
    float getInterestRate() const;
    float getInterestEarned() const;
    int getMaturityPeriod() const;

    // Setters
    void setInterestRate(float interestRate);
    void setMaturityPeriod(int maturityPeriod);

    // Overload Operands
    friend  bool operator == (const Bond &first, const Bond &second);
    friend bool operator > (const Bond &first, const Bond &second);
    friend bool operator < (const Bond &first, const Bond &second);
    friend bool operator != (const Bond &first, const Bond &second);
    friend bool operator <= (const Bond &first, const Bond &second);
    friend bool operator >= (const Bond &first, const Bond &second);


    /** printBond
     * Requires: A bond
     * Modifies: nothing
     * Effects: Prints out all the values of a bond
     */
    void printBond(Bond &userBond);

    /** calculateInterestEarned
     * Requires: interest rate, maturity period, and initialInvestment
     * Modifies: interestEarned
     * Effects: Uses a formula to calculate the interest earned over the life time of a bond
     */
    float calculateInterestEarned(Bond &bond);

};


#endif //M2OEP_NALTLAND_BOND_H
