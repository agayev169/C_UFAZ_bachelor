#pragma once

#include <deque>
#include <iostream>

class BigInteger {
private:
    enum {BASE = 0x11111111};
    // enum {BASE = 10};
    std::deque<unsigned int> number_;
    bool negative_ = false;
public:
    BigInteger(int);
    BigInteger(const BigInteger &);
    BigInteger(const std::string &);
    BigInteger operator+(const BigInteger &) const;
    BigInteger operator-(const BigInteger &) const;
    BigInteger operator*(const BigInteger &) const;
    BigInteger operator^(const BigInteger &) const;
    BigInteger operator/(const BigInteger &) const;
    BigInteger operator%(const BigInteger &) const;
    bool operator>(const BigInteger &) const;
    bool operator<(const BigInteger &) const;
    bool operator==(const BigInteger &) const;
    bool operator!=(const BigInteger &) const;
    bool operator>=(const BigInteger &) const;
    bool operator<=(const BigInteger &) const;
    bool isNegative() const;
    BigInteger abs() const;
    void clear();
    unsigned int digits() const;
    static BigInteger gcd(const BigInteger &, const BigInteger &);
    static BigInteger lcm(const BigInteger &, const BigInteger &);

    void print(std::ostream &) const;
};

std::ostream &operator<<(std::ostream &, const BigInteger &);