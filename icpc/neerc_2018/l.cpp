#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<vector<unsigned int>> &in) {
    for (unsigned int i = 1; i < in[0].size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (in[1][j] >= in[1][j + 1]) {j = -1; continue;}
            int tmp = in[0][j + 1];
            in[0][j + 1] = in[0][j];
            in[0][j] = tmp;

            tmp = in[1][j];
            in[1][j] = in[1][j + 1];
            in[1][j + 1] = tmp;
        }
    }
}

int main(int argc, char *argv[]) {
    int pop = 10e5, jobs = 10e5;
    // cin >> pop >> jobs;
    vector<vector<unsigned int>> in(2, vector<unsigned int>(pop));
    // for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < pop; ++j) {
            // cin >> in[i][j];
            in[0][j] = 10e5;
            in[1][j] = 10e9;
        }
    // }

    insertion_sort(in);

    long int dif = pop - jobs;
    vector<bool> jobs_done(jobs, false);
    unsigned long int total_time = 0;

    for (int i = 0; i < pop; ++i) {
        if (jobs_done[in[0][i] - 1] == false) {
            jobs_done[in[0][i] - 1] = true;
        } else if (dif > 0) {
            --dif;
        } else {
            total_time += in[1][i];
        }
    }

    cout << total_time << endl;

    return 0;
}