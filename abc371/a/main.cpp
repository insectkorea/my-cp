#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    char S_AB, S_AC, S_BC;
    cin >> S_AB >> S_AC >> S_BC;

    // Define all permutations
    vector<vector<char>> perms = {{'A', 'B', 'C'}, {'A', 'C', 'B'},
                                  {'B', 'A', 'C'}, {'B', 'C', 'A'},
                                  {'C', 'A', 'B'}, {'C', 'B', 'A'}};

    for (auto &perm : perms) {
        // Assign age ranks
        int age_A, age_B, age_C;
        for (int i = 0; i < 3; ++i) {
            if (perm[i] == 'A') age_A = i + 1;
            if (perm[i] == 'B') age_B = i + 1;
            if (perm[i] == 'C') age_C = i + 1;
        }

        bool match = true;
        // Check S_AB
        if (S_AB == '<') {
            if (!(age_A < age_B)) {
                match = false;
            }
        } else {  // S_AB == '>'
            if (!(age_A > age_B)) {
                match = false;
            }
        }

        // Check S_AC
        if (S_AC == '<') {
            if (!(age_A < age_C)) {
                match = false;
            }
        } else {  // S_AC == '>'
            if (!(age_A > age_C)) {
                match = false;
            }
        }

        // Check S_BC
        if (S_BC == '<') {
            if (!(age_B < age_C)) {
                match = false;
            }
        } else {  // S_BC == '>'
            if (!(age_B > age_C)) {
                match = false;
            }
        }

        if (match) {
            // Find the person with age_rank == 2
            if (age_A == 2) {
                cout << "A" << endl;
            } else if (age_B == 2) {
                cout << "B" << endl;
            } else {  // age_C == 2
                cout << "C" << endl;
            }
            return 0;
        }
    }

    return 0;
}
