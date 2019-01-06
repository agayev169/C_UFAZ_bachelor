#include "BigNumber.hpp"

BigNumber::BigNumber(): numerator_(0), denominator_(1), negative_(false) {}

BigNumber::BigNumber(const BigInteger &x): numerator_(x), denominator_(1), negative_(false) {}

BigNumber::BigNumber(const BigInteger &numerator, const BigInteger &denominator):
    numerator_(numerator.abs()), denominator_((denominator != 0) ? denominator.abs() : 1),
    negative_(numerator.isNegative() ^ denominator.isNegative()) {
    }

BigNumber::BigNumber(const BigNumber &x): 
    numerator_(x.numerator_), denominator_(x.denominator_), negative_(x.negative_) {}

BigNumber::BigNumber(int x):
    numerator_(x), denominator_(1), negative_(x >= 0 ? false : true) {}

BigNumber BigNumber::operator+(const BigNumber &x) const {
    if (!negative_ && x.negative_) return *this - x.abs();
    if (negative_ && !x.negative_) return x - abs();
    BigInteger lcm_ = lcm(denominator_, x.denominator_);
    BigInteger num   = numerator_ * (lcm_ / denominator_) + 
                       x.numerator_ * (lcm_ / x.denominator_);
    BigInteger denom = lcm_;
    BigNumber result(num, denom);
    if (negative_ && x.negative_) {
        result.negative_ = true;
    }
    return result;
}

BigNumber BigNumber::operator-(const BigNumber &x) const {
    if (!negative_ && x.negative_) return *this + x.abs();
    if (negative_ && !x.negative_) return (abs() + x.abs()) * (-1);
    if (negative_ &&  x.negative_) return x.abs() - abs();

    BigNumber left(*this);
    BigNumber right(x);
    bool negative = false;
    if (abs() < x.abs()) {
        left = x;
        right = *this;
        negative = true;
    }

    BigInteger lcm_ = lcm(left.denominator_, right.denominator_);
    BigInteger num   = left.numerator_ * (lcm_ / left.denominator_) - 
                       right.numerator_ * (lcm_ / right.denominator_);
    BigInteger denom = lcm_;
    BigNumber result(num, denom);
    result.negative_ = negative;
    return result;
}

BigNumber BigNumber::operator*(const BigNumber &x) const {
    auto gcd1 = gcd(numerator_, x.denominator_);
    auto gcd2 = gcd(denominator_, x.numerator_);
    BigInteger num   = (numerator_ / gcd1) * (x.numerator_ / gcd2);
    BigInteger denom = (denominator_ / gcd2) * (x.denominator_ / gcd1);
    BigNumber result(num, denom);
    result.negative_ = negative_ ^ x.negative_;
    return result;
}

BigNumber BigNumber::operator*(const BigInteger &x) const {
    BigInteger num   = numerator_ * x;
    BigInteger denom = denominator_;
    BigNumber result(num, denom);
    result.simplify();
    result.negative_ = negative_ ^ x.isNegative();
    return result;
}

BigNumber BigNumber::operator*(int x) const {
    BigInteger num   = numerator_ * x;
    BigInteger denom = denominator_;
    BigNumber result(num, denom);
    result.simplify();
    result.negative_ = negative_ ^ (x < 0);
    return result;
}

BigNumber BigNumber::operator^(const BigInteger &n) const {
    BigNumber result = 1;
    
    for (BigInteger i = 0; i < n; i = i + 1) {
        result = result * *this;
    }

    return result;
}

BigNumber BigNumber::operator/(const BigNumber &x) const {
    auto gcd1 = gcd(numerator_, x.numerator_);
    auto gcd2 = gcd(denominator_, x.denominator_);
    BigInteger num   = (numerator_ / gcd1) * (x.denominator_ / gcd2);
    BigInteger denom = (denominator_ / gcd2) * (x.numerator_ / gcd1);
    BigNumber result(num, denom);
    result.negative_ = negative_ ^ x.negative_;
    return result;
}

BigNumber BigNumber::operator/(const BigInteger &x) const {
    BigNumber result(this->numerator_, this->denominator_);
    result.negative_ = this->negative_;
    result.denominator_ = result.denominator_ * x;
    result.negative_ = negative_ ^ x.isNegative();
    return result;
}

BigNumber BigNumber::operator/(int x) const {
    BigNumber result(this->numerator_, this->denominator_);
    result.negative_ = this->negative_;
    result.denominator_ = result.denominator_ * x;
    result.negative_ = negative_ ^ (x < 0);
    return result;
}

bool BigNumber::operator>(const BigNumber &x) const {
    if (negative_ && !x.negative_) return false;
    if (!negative_ && x.negative_) return true;
    if (negative_ && x.negative_) return this->abs() < x.abs();
    return (numerator_ * x.denominator_ > denominator_ * x.numerator_);
}

bool BigNumber::operator==(const BigNumber &x) const {
    return ((numerator_ * x.denominator_ == denominator_ * x.numerator_ && 
    negative_ == x.negative_) || (numerator_ == 0 && x.numerator_ == 0));
}

bool BigNumber::operator<(const BigNumber &x) const {
    return !(*this > x) && !(*this == x);
}

bool BigNumber::operator!=(const BigNumber &x) const {
    return !(*this == x);
}

bool BigNumber::operator>=(const BigNumber &x) const {
    return *this > x || *this == x;
}

bool BigNumber::operator<=(const BigNumber &x) const {
    return *this < x || *this == x;
}

void BigNumber::simplify() {
    auto gcd_ = gcd(numerator_, denominator_);
    numerator_ = numerator_ / gcd_;
    denominator_ = denominator_ / gcd_;    
}

BigNumber BigNumber::abs() const {
    BigNumber result(numerator_.abs(), denominator_.abs());
    result.negative_ = false;
    return result;
}

BigNumber BigNumber::sqrt() const {
    BigNumber left = 0;
    BigNumber right = *this;
    BigNumber precision(1, 1000);
    std::cout << "precision: " << precision << std::endl;
    if (*this > 1) {
        auto middle = (left + right) / 2;
        BigNumber sq = middle^2;
        if (sq <= *this + precision || sq >= *this - precision) {
            return middle;
        } else if (sq < *this) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

void BigNumber::set_precision(unsigned int precision) {
    precision_ = precision;
}

void BigNumber::print(std::ostream &s) const {
    BigInteger whole = numerator_ / denominator_;
    BigInteger partial;
    if (precision_ == -1) {
        partial = ((numerator_ % denominator_) * (BigInteger(10) ^ std::max((unsigned int) 10, denominator_.digits()))) /
            denominator_;
    } else {
        partial = ((numerator_ % denominator_) * (BigInteger(10) ^ precision_)) /
            denominator_;
    }
    // TODO
    if (negative_) s << "-";
    s << whole << ".";
    for (auto i = 0u; i < precision_ - partial.digits(); ++i) s << "0";
    s << partial;
}

std::ostream &operator<<(std::ostream &s, const BigNumber &x) {
    x.print(s);
    return s;
}
