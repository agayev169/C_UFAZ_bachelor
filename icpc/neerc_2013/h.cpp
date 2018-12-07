#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int xor_f(int a, int b);
int and_f(int a, int b);

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    vector<int> input(n);
    for (int i = 0; i < n; i++) {
        cin >> input[i];
    }

    vector<vector<int> > xor_t(n);
    vector<vector<int> > and_t(n);

    for (int i = 0; i < n; i++) {
        vector<int> temp(n, 0);
        temp[i] = input[i];
        xor_t[i] = temp;
        and_t[i] = temp;
    }

    int res = n;

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            xor_t[i][j] = xor_f(xor_t[i][i], xor_t[i + 1][j]);
            and_t[i][j] = and_f(and_t[i][i], and_t[i + 1][j]);
            res += (and_t[i][j] == xor_t[i][j]) ? 1 : 0;
        }
    }

    cout << res << endl;

    return 0;
}

int xor_f(int a, int b) {
    int res = 0;
    int count = 0;
    while (a > 0 || b > 0) {
        int temp = (a % 2) ^ (b % 2);
        a /= 2;
        b /= 2;
        res = res + temp * pow(2, count++);
    }
}

int and_f(int a, int b) {
    int res = 0;
    int count = 0;
    while (a > 0 || b > 0) {
        int temp = (a % 2) & (b % 2);
        a /= 2;
        b /= 2;
        res = res + temp * pow(2, count++);
    }
}
