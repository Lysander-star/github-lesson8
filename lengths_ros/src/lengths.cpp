#include "lengths_ros/lengths.hpp"

std::optional<double> meanLength(const std::vector<double>& lengths) {
    if (lengths.empty()) {
        return std::nullopt;
    }
    double sum = 0.0;
    for (double x : lengths) {
        sum += x;
    }
    return sum / lengths.size();
}

int countNotLess(const std::vector<double>& lengths, double threshold) {
    int count = 0;
    for (double x : lengths) {
        if (x >= threshold) {
            ++count;
        }
    }
    return count;
}
