#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<char>> arr;

void tile(int n, int x, int y, string location) {
    if (n == 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (arr[x + i][y + j] == 0) {
                    if (location == "up right" || location == "down left") {
                        arr[x + i][y + j] = 'R';
                    }
                    else if (location == "down right" || location == "up left") {
                        arr[x + i][y + j] = 'B';
                    }
                }
            }
        }
        return;
    }

    int r = 0, c = 0;
    for (int i = x; i < x + n; ++i) {
        for (int j = y; j < y + n; ++j) {
            if (arr[i][j] != 0) {
                r = i;
                c = j;
            }
        }
    }

    if (r < x + n / 2 && c < y + n / 2) {
        arr[x + n / 2][y + n / 2 - 1] = 'G';
        arr[x + n / 2][y + n / 2] = 'G';
        arr[x + n / 2 - 1][y + n / 2] = 'G';
    }
    else if (r >= x + n / 2 && c < y + n / 2) {
        arr[x + n / 2 - 1][y + n / 2] = 'G';
        arr[x + n / 2][y + n / 2] = 'G';
        arr[x + n / 2 - 1][y + n / 2 - 1] = 'G';
    }
    else if (r < x + n / 2 && c >= y + n / 2) {
        arr[x + n / 2][y + n / 2 - 1] = 'G';
        arr[x + n / 2][y + n / 2] = 'G';
        arr[x + n / 2 - 1][y + n / 2 - 1] = 'G';
    }
    else if (r >= x + n / 2 && c >= y + n / 2) {
        arr[x + n / 2 - 1][y + n / 2] = 'G';
        arr[x + n / 2][y + n / 2 - 1] = 'G';
        arr[x + n / 2 - 1][y + n / 2 - 1] = 'G';
    }

    tile(n / 2, x, y + n / 2, "down left");
    tile(n / 2, x, y, "down right");
    tile(n / 2, x + n / 2, y, "up right");
    tile(n / 2, x + n / 2, y + n / 2, "up left");
}

int main() {
    int n;
    cout << "Enter the value of n (where board size will be 2^n * 2^n, n > 1): ";
    cin >> n;

    int size = pow(2, n);

    arr.assign(size, vector<char>(size, 0));

    int missing_row, missing_col;
    cout << "Enter the row number of the missing tile: ";
    cin >> missing_row;
    cout << "Enter the column number of the missing tile: ";
    cin >> missing_col;

    arr[missing_row][missing_col] = 'x';

    tile(size, 0, 0, "up right");

    cout << "Tiled Board:" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}