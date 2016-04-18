#pragma once

#include <vector>
#include <algorithm>

class IMeasureCalculator
{
	public:
		virtual double Calculate(std::vector<double> sample1, std::vector<double> sample2) const = 0;
};