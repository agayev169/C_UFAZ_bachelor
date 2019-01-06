#pragma once

#include "BigInteger.hpp"

class BigNumber {
private:
    BigInteger numerator_;
    BigInteger denominator_;
    bool negative_;
    static int precision_;
public:
    void simplify();
    BigNumber();
    BigNumber(const BigNumber &);
    BigNumber(const BigInteger &);
    BigNumber(int);
    BigNumber(const BigInteger &, const BigInteger &);
    BigNumber operator+(const BigNumber &) const;
    BigNumber operator-(const BigNumber &) const;
    BigNumber operator*(const BigNumber &) const;
    BigNumber operator*(const BigInteger &) const;
    BigNumber operator*(int) const;
    BigNumber operator^(const BigInteger &) const;
    BigNumber operator/(const BigNumber &) const;
    BigNumber operator/(const BigInteger &) const;
    BigNumber operator/(int) const;
    bool operator>(const BigNumber &) const;
    bool operator<(const BigNumber &) const;
    bool operator==(const BigNumber &) const;
    bool operator!=(const BigNumber &) const;
    bool operator>=(const BigNumber &) const;
    bool operator<=(const BigNumber &) const;
    BigNumber abs() const;
    void print(std::ostream &) const;
    static void set_precision(unsigned int);
    BigNumber sqrt() const;
};

int BigNumber::precision_ = -1;

std::ostream &operator<<(std::ostream &, const BigNumber &);