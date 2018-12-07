#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<unsigned long int> dividers(unsigned long int n);
bool is_prime(int n);

int main(int argc, char *argv[]) {
    unsigned long int n;
    cin >> n;
    vector<unsigned long int> divs = dividers(n);
    cout << divs.size() << endl;
    if (divs.size() <= 1) {
        cout << "NO" << endl;
        return 0;
    }

    for (unsigned int i = 0; i < divs.size(); ++i) {
        cout << divs[i] << " ";
    }
    cout << endl;

    cout << "YES" << endl;
    cout << "2" << endl;
    unsigned long int x = 1, y = 1;
    while (x <= n / divs[0]) {
        y = (n - 1 - x * divs[0]) / divs[1];
        if ((double) (n - 1 - x * divs[0]) / divs[1] == y) {
            cout << x << " " << n / divs[0] << endl;
            cout << y << " " << n / divs[1] << endl;
            return 0;
        }
        ++x;
    }


    return 0;
}

bool is_prime(int n) {
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<unsigned long int> dividers(unsigned long int n) {
    vector<unsigned long int> divs(2);
    int j = 0;
    for (unsigned long int i = 2; i <= n / 2; ++i) {
        if (n % i == 0 && is_prime(i))
            divs[j++] = i;
        if (divs[1] != 0) return divs;
    }
    divs.resize(1);
    return divs;
}
