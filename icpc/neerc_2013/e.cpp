#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    string target;
    cin >> target;
    int n;
    cin >> n;
    vector<string> matchs(n);

    int same_n = 0;
    for (int i = 0; i < n; i++) {
        string candidate;
        cin >> candidate;
        bool same = true;
        for (int j = 0; j < 9; j++) {
            if (target[j] != '*' && target[j] != candidate[j]) {
                same = false;
                break;
            }
        }
        if (same) {
            matchs[same_n++] = candidate;
        }
    }

    cout << same_n << endl;
    for (int i = 0; i < same_n; i++) {
        cout << matchs[i] << endl;
    }


    return 0;
}
