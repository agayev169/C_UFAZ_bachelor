#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    int n; // Number of blocks
    cin >> n;
    vector<long long int> res(n + 1);

    res[0] = 0;
    res[1] = 1;
    res[2] = 0;
    res[3] = 1;
    res[4] = 1;
    res[5] = 1;
    res[6] = 1;
    res[7] = 1;

    // TODO finish the algorithm
    for (unsigned int i = 8; i <= n; i++) {
        int count = 1;
        int first = (i + 1) / 2;
        if (i % 2 == 0) {
            int second = 2;
            while (first - 2 >= second) {
                first--;
                second++;
                count += res[second];
            }
        } else {
            int second = 1;
            while (first - 2 >= second) {
                if (second == 0) {
                    first -= 2;
                    second += 2;
                    count++;
                } else {
                    first--;
                    second++;
                    count += res[second];
                }
            }
        }
        res[i] = count;
    }

    cout << "res: " << res[n] << endl;

    return 0;
}