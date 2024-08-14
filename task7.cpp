#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool canHitTarget(int n) {
    if (n <= 1) return false;

    vector<bool> dp(n, false);
    dp[0] = dp[1] = true;

    for (int i = 2; i < n; ++i) {
        dp[i] = dp[i - 1] || dp[i - 2];
    }

    return dp[n - 1];
}

int minShotsToHitTarget(int n) {
    if (n <= 1) return 0;
    vector<int> dp(n);
    dp[0] = 0; 

    for (int i = 1; i < n; ++i) {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (j + 1 >= i) { 
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[n - 1]; 
}

int main() {
    int n;
    cout << "Enter the number of hiding spots: ";
    cin >> n;

    if (canHitTarget(n)) {
        cout << "The shooter can guarantee hitting the target." << endl;
    }
    else {
        cout << "The shooter cannot guarantee hitting the target." << endl;
    }

    int minShots = minShotsToHitTarget(n);
    cout << "Minimum shots needed to hit the target: " << minShots << endl;

    return 0;
}
