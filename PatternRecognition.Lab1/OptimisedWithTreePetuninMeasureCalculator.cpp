#include "OptimisedWithTreePetuninMeasureCalculator.h"

int binarySearch(const std::vector<double>& container, const int & size, double element)
{
    const std::vector<double>::const_iterator endIt = container.end();

    int left = 0;
    int right = size;

    if (container.size() == 0
        || container.front() > element
        || container.back() < element) {
        return -1;
    }

    while (right - left > 0) {
        int mid = left + (right - left) / 2;

        if (element <= container[mid]) {
            right = mid;
        } else if (element > container[mid+1]){
            left = mid + 1;
        } else {
			return mid;
		}
    }
	
    return -1;
}

class IntervalTree
{
	private:
		std::vector<int> tree;
		void Build(const std::vector<int> & a, const int & v, const int & tl, const int & tr);
	public:
		IntervalTree(const std::vector<int> & a, const int & v, const int & tl, const int & tr);
		int Sum(const int & v, const int & tl, const int & tr, const int & l, const int & r);
};

IntervalTree::IntervalTree(const std::vector<int> & a, const int & v, const int & tl, const int & tr)
{
	tree = std::vector<int>((tr - tl + 1) * 4, 0);

	Build(a, v, tl, tr);
}

void IntervalTree::Build(const std::vector<int> & a, const int & v, const int & tl, const int & tr)
{
	if (tl == tr)
		tree[v] = a[tl];
	else {
		int tm = (tl + tr) / 2;
		Build(a, v*2, tl, tm);
		Build(a, v*2+1, tm+1, tr);
		tree[v] = tree[v*2] + tree[v*2+1];
	}
}

int IntervalTree::Sum(const int & v, const int & tl, const int & tr, const int & l, const int & r)
{
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return tree[v];
	int tm = (tl + tr) / 2;
	return Sum (v*2, tl, tm, l, std::min(r,tm))
		+ Sum (v*2+1, tm+1, tr, std::max(l,tm+1), r);
}

//Total time complexity: O(n^2 * log(n) = O(m * log(n)) + O(n) + O(n^2 * log(n)
double OptimisedWithTreePetuninMeasureCalculator::Calculate(std::vector<double> x, std::vector<double> y) const
{
	sort(x.begin(), x.end());
	
	double count = 0;
	double n = x.size();
	double m = y.size();
	double N = n * (n - 1) / 2;
	double g = 3.0;

	int numberOfAdjucentIntervals = n - 1;
	std::vector<int> frequencies(numberOfAdjucentIntervals, 0);

	// calculate frequencies in adjucent intervals
	// This takes O(m*log(n)) time
	for (int k = 0; k < m; ++k)
	{
		int interval = binarySearch(x, n, y[k]);
		if (interval > -1)
		{
			++frequencies[interval];
		}					
	}

	// This takes O(n) time
	IntervalTree tree(frequencies, 1, 0, numberOfAdjucentIntervals - 1);

	// This takes 1/2 * n* (n - 1) * log(n) time, which asymptotically is O(n^2 * log(n))
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			//This takes O(log(n)) time
			double h = tree.Sum(1, 0, numberOfAdjucentIntervals - 1, i, j - 1) / m;

			double p1 = (h * m + g * g / 2 - g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			double p2 = (h * m + g * g / 2 + g * sqrt(h * (1 - h) * m + g * g / 4)) / (m + g * g);
			double p = (j - i) / (n + 1.0);
			
			if (p1 < p && p <= p2)
				count++;
		}
	}

	return count / N;
}