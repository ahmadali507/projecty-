#include <iostream>
#include <vector>

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::vector<int> solution(std::vector<int> pegs) {
    int n = pegs.size();
    std::vector<int> distances;

    for (int i = 0; i < n - 1; ++i) {
        distances.push_back(pegs[i + 1] - pegs[i]);
    }

    if (n < 2) {
        return {-1, -1};
    }

    if (n == 2) {
        if (distances[0] % 3 == 0 && distances[0] >= 3) {
            int radius = 2* distances[0] / 3;
            return {radius, 1};
        } else {
            return {-1, -1};
        }
    }

    int sumDistances = 0;
    for (int distance : distances) {
        sumDistances += distance;
    }

    if (sumDistances % 3 == 0) {
        int radius = (2 * sumDistances) / 3;
        int commonDivisor = gcd(radius, 1);
        return {radius / commonDivisor, 1 / commonDivisor};
    } else {
        return {-1, -1};
    }
}

int main() {
    std::vector<int> pegs = {1, 51};

    std::vector<int> result = solution(pegs);

    std::cout << "Result: [" << result[0] << ", " << result[1] << "]" << std::endl;

    return 0;
}
