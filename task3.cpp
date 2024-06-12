#include <iostream>
#include <vector>
#include <climits>

using namespace std;

pair<int, vector<int>> minMoves(int n) {
    vector<int> dp(n + 1, INT_MAX);
    vector<vector<int>> moves(n + 1);

    dp[0] = 0; 
    dp[1] = 1; 
    moves[1].push_back(1);

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + i;
        moves[i] = moves[i - 1];
        moves[i].push_back(i); 

        for (int j = i - 1; j >= 1; --j) {
            int currentMoves = dp[j] + (i - j) * 2;
            if (currentMoves < dp[i]) {
                dp[i] = currentMoves;
                moves[i] = moves[j];
                for (int k = j + 1; k <= i; ++k) {
                    moves[i].push_back(k); 
                    moves[i].push_back(j); 
                }
            }
        }
    }

    return { dp[n], moves[n] };
}

int main() {
    int n;
    cout << "Enter the number of switches: ";
    cin >> n;

    pair<int, vector<int>> result = minMoves(n);
    cout << "Minimum number of moves required to turn off all switches: " << result.first << endl;
    cout << "The sequence of moves is: \n";
    for (int move : result.second) {
        cout << "Toggle switch " << move << endl;
    }
    cout << endl;

    return 0;
}
