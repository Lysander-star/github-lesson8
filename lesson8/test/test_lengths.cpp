#include "lengths.hpp"
#include <iostream>
#include <vector>

static int failures = 0;

static void check(bool ok, const char* name) {
    if (ok) {
        std::cout << "[PASS] " << name << "\n";
    } else {
        std::cout << "[FAIL] " << name << "\n";
        ++failures;
    }
}

int main() {
    std::vector<double> a{1.0, 2.0, 3.0, 4.0};
    std::vector<double> empty{};

    auto m = meanLength(a);
    check(m.has_value() && m.value() == 2.5, "meanLength([1,2,3,4]) == 2.5");

    auto e = meanLength(empty);
    check(!e.has_value(), "meanLength(empty) -> no value (nullopt)");

    check(countNotLess(a, 3.0) == 2, "countNotLess([1,2,3,4], 3.0) == 2");
    check(countNotLess(a, 4.0) == 1, "boundary: exactly equal to threshold counted");
    check(countNotLess(empty, 3.0) == 0, "countNotLess(empty) == 0");

    if (failures != 0) {
        std::cout << failures << " test(s) FAILED\n";
        return 1;
    }
    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
