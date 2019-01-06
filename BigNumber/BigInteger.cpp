#include <iostream>
#include "BigInteger.hpp"

BigInteger::BigInteger(int number = 0) {
    if (number < 0) {
        negative_ = true;
        number *= -1;
    }
    do {
        number_.push_back(number % BASE);
        number /= BASE;
    } while (number > 0);
}

BigInteger::BigInteger(const std::string &number) {
    if (number.empty()) {
        number_.push_back(0);
    } else {
        BigInteger res;
        for (int i = number.size() - 1; i >= 0; --i) {
            res = res + ((BigInteger(10)^(number.size() - 1 - i)) * ((int) number[i] - '0'));
        }
        number_ = res.number_;
    }
}

BigInteger::BigInteger(const BigInteger &x) {
    number_ = x.number_;
    negative_ = x.negative_;
}

BigInteger BigInteger::operator+(const BigInteger &x) const {
    BigInteger result;
    result.number_.clear();
    unsigned carrier = 0;
    if (negative_ && x.negative_) {
        result.negative_ = true;
    }
    if (!negative_ && x.negative_) {
        return *this - x.abs();
    }
    if (negative_ && !x.negative_) {
        return x - this->abs();
    }
    for (auto i = 0u; i < std::max(number_.size(), x.number_.size()); ++i) {
        int nn = (i >= number_.size()) ? 0 : number_[i];
        int xx = (i >= x.number_.size()) ? 0 : x.number_[i];
        result.number_.push_back((nn + xx + carrier) % BASE);
        carrier = (nn + xx + carrier) / BASE;
    }
    if (carrier != 0) result.number_.push_back(carrier);
    return result;
}

BigInteger BigInteger::operator-(const BigInteger &x) const {
    if (!negative_ && x.negative_) {
        return *this + x.abs();
    }
    BigInteger result;
    result.number_.clear();
    BigInteger left = *this;
    BigInteger right = x;
    if (negative_ && !x.negative_) {
        return (abs() + x) * (-1);
    }

    if (abs() < x.abs()) {
        left = x;
        right = *this;
        result.negative_ = true;
    }
    
    unsigned int carrier = 0;
    for (auto i = 0u; i < std::max(number_.size(), x.number_.size()); ++i) {
        unsigned int nn = (i >= left.number_.size()) ? 0 : left.number_[i];
        unsigned int xx = (i >= right.number_.size()) ? 0 : right.number_[i];
        if (nn >= xx + carrier) {
            result.number_.push_back((nn - xx - carrier) % BASE);
            carrier = 0;
        } else {
            result.number_.push_back((nn + BASE - xx - carrier) % BASE);
            carrier = 1;
        }
    }

    result.clear();

    if (result.number_.size() == 0) result = BigInteger(0);

    return result;
}

BigInteger BigInteger::operator*(const BigInteger &x) const {
    BigInteger result;
    result.number_.clear();
    for (auto i = 0u; i < x.number_.size(); ++i) {
        unsigned carrier = 0;
        BigInteger mult;
        mult.number_.clear();
        for (auto j = 0u; j < i; ++j) {
            mult.number_.push_back(0);
        }
        auto xx = x.number_[i];
        for (auto j = 0u; j < number_.size(); ++j) {
            auto nn = number_[j];
            unsigned long long int k = 1ULL * nn * xx + carrier;
            mult.number_.push_back(k % BASE);
            carrier = k / BASE;
        }
        if (carrier != 0) {
            mult.number_.push_back(carrier);
        }

        result = result + mult;
    }

    if (result.number_[result.number_.size() - 1] == 0) return BigInteger();

    result.negative_ = negative_ ^ x.negative_;
    return result;
}

BigInteger BigInteger::operator^(const BigInteger &n) const {
    BigInteger result(1);
    
    for (BigInteger i = 0; i < n; i = i + 1) {
        result = result * *this;
    }

    return result;
}

BigInteger BigInteger::operator/(const BigInteger &x) const {
    if (x.number_.size() == 1 && x.number_[0] == 0) return BigInteger(INT32_MAX);
    BigInteger result;
    result.number_.clear();

    BigInteger numer;
    numer.number_.clear();
    for (auto i = 0u; i < number_.size(); ++i) {
        if (numer.number_.size() == 1 && numer.number_[0] == 0) numer.number_.clear();
        numer.number_.push_front(number_[number_.size() - i - 1]);

        unsigned long int left = 0;
        unsigned long int right = BASE;
        while (right > left) {
            unsigned long int middle = (left + right) / 2;
            if (numer >= x * BigInteger(middle)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        --left;
        
        result.number_.push_front(left);
        numer = numer - x * left;
    }

    result.clear();

    if (result.number_.size() == 0) return BigInteger();

    result.negative_ = negative_ ^ x.negative_;
    return result;
}

BigInteger BigInteger::operator%(const BigInteger &x) const {
    if (x.number_.size() == 1 && x.number_[0] == 0) return BigInteger(INT32_MAX);

    BigInteger numer;
    numer.number_.clear();
    for (auto i = 0u; i < number_.size(); ++i) {
        if (numer.number_.size() == 1 && numer.number_[0] == 0) numer.number_.clear();
        numer.number_.push_front(number_[number_.size() - i - 1]);

        unsigned long int left = 0;
        unsigned long int right = BASE;
        while (right > left) {
            unsigned long int middle = (left + right) / 2;
            if (numer >= x * BigInteger(middle)) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        --left;
        
        numer = numer - x * BigInteger(left);
    }

    return numer;
}

bool BigInteger::operator>(const BigInteger &x) const {
    if ((number_.size() > x.number_.size() && !negative_ && !x.negative_) 
        || (number_.size() < x.number_.size() && negative_ && x.negative_) 
        || (!negative_ && x.negative_)) return true;

    if ((number_.size() < x.number_.size() && !negative_ && !x.negative_) 
        || (number_.size() > x.number_.size() && negative_ && x.negative_) 
        || (negative_ && !x.negative_)) return false;

    if (negative_ && x.negative_) {
        BigInteger n_pos(*this);
        n_pos.negative_ = false;
        BigInteger x_pos(x);
        x_pos.negative_ = false;
        return n_pos < x_pos;
    }
    for (int i = number_.size() - 1; i >= 0; --i) {
        int nn = number_[i];
        int xx = x.number_[i];
        if (nn > xx) return true;
        if (nn < xx) return false;
    }
    return false;
}

bool BigInteger::operator<(const BigInteger &x) const {
    if ((number_.size() > x.number_.size() && !negative_ && !x.negative_) 
        || (number_.size() < x.number_.size() && negative_ && x.negative_)
        || (!negative_ && x.negative_)) return false;

    if ((number_.size() < x.number_.size() && !negative_ && !x.negative_)
        || (number_.size() > x.number_.size() && negative_ && x.negative_)
        || (negative_ && !x.negative_)) return true;
        
    if (negative_ && x.negative_) {
        BigInteger n_pos(*this);
        n_pos.negative_ = false;
        BigInteger x_pos(x);
        x_pos.negative_ = false;
        return n_pos > x_pos;
    }

    for (int i = number_.size() - 1; i >= 0; --i) {
        int nn = number_[i];
        int xx = x.number_[i];
        if (nn > xx) return false;
        if (nn < xx) return true;
    }
    return false;
}

bool BigInteger::operator==(const BigInteger &x) const {
    if (number_.size() > x.number_.size() || (!negative_ && x.negative_) || 
        number_.size() < x.number_.size() || (negative_ && !x.negative_)) return false;
    for (int i = number_.size() - 1; i >= 0; --i) {
        int nn = number_[i];
        int xx = x.number_[i];
        if (nn > xx || nn < xx) return false;
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger &x) const {
    return !(*this == x);
}

bool BigInteger::operator>=(const BigInteger &x) const {
    return (*this > x || * this == x);
}

bool BigInteger::operator<=(const BigInteger &x) const {
    return (*this < x || *this == x);
}

bool BigInteger::isNegative() const {
    return negative_;
}

BigInteger BigInteger::abs() const {
    BigInteger result(*this);
    result.negative_ = false;
    return result;
} 

void BigInteger::clear() {
    for (int i = number_.size() - 1; i >= 0; --i) {
        if (number_[i] != 0) break;
        number_.pop_back();
    }
}

static BigInteger gcd(const BigInteger &x, const BigInteger &y) { 
    if (x == 0) return BigInteger(y);
    if (y == 0) return BigInteger(x);
    auto a(x);
    auto b(y);
    while (b != 0) {
        BigInteger temp(b);
        b = a % b;
        a = BigInteger(temp);
    }
    return a;
}

static BigInteger lcm(const BigInteger &x, const BigInteger &y) { 
    return BigInteger(x * y / gcd(x, y));
}

void BigInteger::print(std::ostream &s) const {
    std::string result = "";
    auto n(*this);
    while (n.abs() > 0) {
        auto dig = (n % 10).number_[0]; 
        result = (char) (dig + '0') + result;
        n = n / 10;
    }
    if (result.empty()) s << '0';
    else {
        if (negative_) result = "-" + result;
        s << result;
    }
}

unsigned int BigInteger::digits() const {
    return number_.size();
}

std::ostream &operator<<(std::ostream &s, const BigInteger &n) {
    n.print(s);
    return s;
}