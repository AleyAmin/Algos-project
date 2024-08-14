#include <iostream>
#include <vector>
using namespace std;
void printMoves(const vector<pair<int, int>>& moves) {
    for (const auto& move : moves) {
        cout << "Move coin from position " << move.first;
        cout << " to position " << move.second << endl;
    }
}

void pairCoins(int n) {
    if (n % 4 != 0) {
        cout << "The puzzle cannot be solved for n = " << n << ". n must be a multiple of 4." << endl;
        return;
    }

    vector<int> coins(n, 1); 
    vector<pair<int, int>> moves;
    int jumpOver = 1; 

    for (int move = 1; move <= n / 2; ++move) {
        for (int i = 0; i < n; ++i) {
            if (coins[i] == 1) { 
                int jumpDistance = 0;
                int j = i + 1;

                while (j < n && jumpDistance < jumpOver) {
                    jumpDistance += coins[j];
                    ++j;
                }

                if (j < n && coins[j] == 1) {
                    coins[i] = 0;
                    coins[j] = 2; 
                    moves.push_back({ i, j });
                    break;
                }
            }
        }
        jumpOver++;
    }

    bool allPaired = true;
    for (int coin : coins) {
        if (coin == 1) {
            allPaired = false;
            break;
        }
    }


    printMoves(moves);

}

int main() {
    int n = 12;
    cout << "number of coins is " << n<<endl;
    pairCoins(n);
    return 0;
}