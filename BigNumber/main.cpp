#include <iostream>
#include "BigInteger.cpp"
#include "BigNumber.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    BigNumber::set_precision(7);
    BigNumber n = 25;
    cout << n.sqrt() << endl;
    // BigNumber pi;
    // BigNumber k(1, 1);

    // BigNumber::set_precision(100);

    // for (int i = 0; i < 50; ++i) {
    //     auto a1 = BigNumber(4, 8 * i + 1);
    //     auto a2 = BigNumber(2, 8 * i + 4);
    //     auto a3 = BigNumber(1, 8 * i + 5);
    //     auto a4 = BigNumber(1, 8 * i + 6);
    //     pi = pi + k * (a1 - a2 - a3 - a4);
    //     k = k / 16;
    // }

    // cout << pi << endl;

    return 0;
}