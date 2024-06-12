#include <iostream>
#include <cmath>
#include <string>

void replaceDisk(int n, int k, std::string from_peg, std::string helper_peg, std::string to_peg) {
    if (n == 0) {
        std::cout << std::endl; // print nothing if there's no disks
        return;
    }
    replaceDisk(n - 1, k, from_peg, to_peg, helper_peg);
    std::cout << "Take disk number " << (n + k) << " from peg " << from_peg << " to peg " << to_peg << std::endl;
    replaceDisk(n - 1, k, helper_peg, from_peg, to_peg);
}

void revReplace(int n, std::string from_peg, std::string helper_peg1, std::string to_peg, std::string helper_peg2) {
    int k = static_cast<int>(n + 1 - std::round(std::sqrt(2 * n + 1)));
    if (k == 0) {
        std::cout << "Take disk number 1 from peg " << from_peg << " to peg " << to_peg << std::endl;
        return;
    }
    revReplace(k, from_peg, to_peg, helper_peg1, helper_peg2);
    replaceDisk(n - k, k, from_peg, helper_peg2, to_peg);
    revReplace(k, helper_peg1, from_peg, to_peg, helper_peg2);
}

int main() {
    std::cout << "\n";
    revReplace(8, "A", "B", "C", "D"); // calling the function with 8 disks and 4 pegs
    return 0;
}

