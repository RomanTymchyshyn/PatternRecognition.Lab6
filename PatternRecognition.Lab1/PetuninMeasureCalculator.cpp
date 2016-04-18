#include "PetuninMeasureCalculator.h"

//Total time complexity: O(m * n^2)
double PetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y) const
{
	sort(x.begin(), x.end());
	double count = 0;
	double n = x.size();
	double m = y.size();
	double N = n * (n - 1) / 2;
	double g = 3.0;

	// This takes 1/2 * m * n * (n + 1) time, i.e. O(m * n^2)
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double h = 0.0;
			for (int k = 0; k < m; k++)
				if (x[i] < y[k] && y[k] <= x[j])
					h++;
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