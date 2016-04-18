#pragma once

#include <vector>
#include <algorithm>
#include "IMeasureCalculator.h"

class PetuninMeasureCalculator: public IMeasureCalculator
{
	public:
		virtual double Calculate(std::vector<double> sample1, std::vector<double> sample2) const;
};