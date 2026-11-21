#ifndef LENGTHS_ROS_LENGTHS_HPP
#define LENGTHS_ROS_LENGTHS_HPP

#include <vector>
#include <optional>

std::optional<double> meanLength(const std::vector<double>& lengths);

int countNotLess(const std::vector<double>& lengths, double threshold);

#endif
