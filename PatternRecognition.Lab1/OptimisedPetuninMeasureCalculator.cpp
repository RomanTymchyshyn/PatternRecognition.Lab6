#include "OptimisedPetuninMeasureCalculator.h"

// Total time complexity: O(n^3)
double OptimisedPetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y) const
{
	sort(x.begin(), x.end());
	
	double count = 0;
	double n = x.size();
	double m = y.size();
	double N = n * (n - 1) / 2;
	double g = 3.0;

	int numberOfAdjucentIntervals = n - 1;
	std::vector<int> frequencies(numberOfAdjucentIntervals, 0);

	//calculate frequencies in adjucent intervals
	// This takes O(m*n) time
	for (int i = 0; i < numberOfAdjucentIntervals; ++i)
	{
		for (int k = 0; k < m; ++k)
		{
			if (x[i] < y[k] && y[k] <= x[i + 1])
			{
				++frequencies[i];
			}
		}					
	}

	// This takes 1/6 * n * (n^2 + 3*n + 2) = O(n^3)
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			double h = 0;
			for (int k = i; k < j; ++k)
			{
				h += frequencies[k];
			}

			h /= m;

			double p1 = (h * m + g * g / 2 - g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			double p2 = (h * m + g * g / 2 + g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			double p = (j - i) / (n + 1.0);
			
			if (p1 < p && p <= p2)
				count++;
		}
	}

	return count / N;
}