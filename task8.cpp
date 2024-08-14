#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

int find_fake_box() {
    int real_weight = 10; 
    int fake_weight = 9;  
    vector<vector<int>> boxes(50, vector<int>(50, real_weight)); 

    srand(time(0));  
    int fake_box = rand() % 50; 
    fill(boxes[fake_box].begin(), boxes[fake_box].end(), fake_weight); 

    int expected_weight = (50 * 51 / 2) * real_weight;  
    int actual_weight = 0;  
    for (int i = 1; i <= 50; ++i) {
        actual_weight += i * boxes[i - 1][0];
        cout << "Taking " << i << " piece(s) from box " << i << endl;
    }

    cout << "The fake box is number: " << expected_weight - actual_weight << endl;  
    return expected_weight - actual_weight;  
}

int main() {
    // Test the function
    find_fake_box();
    return 0;
}
