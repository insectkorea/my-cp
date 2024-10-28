#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to perform coordinate compression
vector<ll> compress_coordinates(vector<ll> &positions) {
    vector<ll> sorted = positions;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    return sorted;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N;
    cin >> N;
    vector<ll> A(N);
    for (auto &x : A) cin >> x;

    ll Q;
    cin >> Q;
    vector<pair<ll, ll>> tasks(Q);
    vector<ll> Gi(Q);
    for (int i = 0; i < Q; i++) {
        cin >> tasks[i].first >> tasks[i].second;
        Gi[i] = tasks[i].second;
    }

    // To handle shifting, include Gi +/- Q +10
    vector<ll> all_positions = A;
    for (auto g : Gi) {
        all_positions.push_back(g);
        // To the left, ensure non-negative positions
        if (g >= Q + 10) {
            all_positions.push_back(g - Q - 10);
        } else {
            all_positions.push_back(0);
        }
        // To the right
        all_positions.push_back(g + Q + 10);
    }

    // Coordinate compression
    vector<ll> sorted_positions = compress_coordinates(all_positions);
    // Map original position to compressed position
    auto get_id = [&](ll val) -> ll {
        return lower_bound(sorted_positions.begin(), sorted_positions.end(),
                           val) -
               sorted_positions.begin();
    };

    // Initialize set of free positions
    set<ll> free_pos;
    for (auto pos : sorted_positions) {
        free_pos.insert(pos);
    }

    // Map to track person's current position
    // 1-based indexing
    vector<ll> person_pos(N + 1);
    // Map to track which person is at which position
    unordered_map<ll, ll> pos_to_person;

    for (int i = 1; i <= N; i++) {
        person_pos[i] = A[i - 1];
        pos_to_person[A[i - 1]] = i;
        free_pos.erase(A[i - 1]);  // Occupied
    }

    ll total_movements = 0;

    for (int i = 0; i < Q; i++) {
        ll Ti = tasks[i].first;
        ll Gi_val = tasks[i].second;

        ll current_pos = person_pos[Ti];

        // If Gi_val is free, assign
        if (free_pos.find(Gi_val) != free_pos.end()) {
            // Movement steps
            total_movements += abs(current_pos - Gi_val);

            // Update mappings
            free_pos.erase(Gi_val);
            pos_to_person.erase(current_pos);
            pos_to_person[Gi_val] = Ti;
            person_pos[Ti] = Gi_val;
        } else {
            // Find the nearest free position to Gi_val
            // Using lower_bound
            auto it = free_pos.lower_bound(Gi_val);
            ll right = (it != free_pos.end()) ? *it : LLONG_MAX;
            ll left = (it != free_pos.begin()) ? *(--it) : LLONG_MIN;

            // Determine the closest
            ll assigned_pos;
            if (right == LLONG_MAX) {
                assigned_pos = left;
            } else if (left == LLONG_MIN) {
                assigned_pos = right;
            } else {
                if (abs(right - Gi_val) < abs(Gi_val - left)) {
                    assigned_pos = right;
                } else {
                    assigned_pos = left;
                }
            }

            // Movement steps for Ti
            total_movements += abs(current_pos - Gi_val);

            // Now, shift the existing person at Gi_val to assigned_pos
            ll existing_person = pos_to_person[Gi_val];
            total_movements +=
                abs(existing_person != 0 ? abs(Gi_val - assigned_pos) : 0);

            // Update mappings
            pos_to_person.erase(Gi_val);
            pos_to_person[assigned_pos] = existing_person;
            person_pos[existing_person] = assigned_pos;

            // Assign Ti to Gi_val
            pos_to_person[Gi_val] = Ti;
            person_pos[Ti] = Gi_val;

            // Remove assigned_pos from free positions
            free_pos.erase(assigned_pos);
        }
    }

    cout << total_movements;
}
