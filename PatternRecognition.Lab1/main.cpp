#include <vector>
#include <iostream>
#include <time.h>
#include <string>
#include "IMeasureCalculator.h"
#include "PetuninMeasureCalculator.h"
#include "OptimisedPetuninMeasureCalculator.h"
#include "OptimisedWithTreePetuninMeasureCalculator.h"

double Rand(const double & min, const double & max);

std::vector<double> GenerateRandomSequence(const int & size, const double & min, const double & max);

void CalculateAndMeasure(IMeasureCalculator* measureCalculator, const std::vector<double> & x, const std::vector<double> & y, const std::string & message);

int main()
{
	srand (time(NULL));

	const int size = 1000;
	const double min = 0;
	const double max = 10;

	std::vector<double> x = GenerateRandomSequence(size, min, max);
	std::vector<double> y = GenerateRandomSequence(size, min, max);

	clock_t time;
	double ms;
	double result = 0.0;
	IMeasureCalculator* measureCalculator;

	/// Not Optimised
	measureCalculator = new PetuninMeasureCalculator();
	CalculateAndMeasure(measureCalculator, x, y, "Not optimised.");

	/// Not Optimised
	measureCalculator = new OptimisedPetuninMeasureCalculator();
	CalculateAndMeasure(measureCalculator, x, y, "Optimised only with precalculation of points in adjucent intervals.");

	/// Not Optimised
	measureCalculator = new OptimisedWithTreePetuninMeasureCalculator();
	CalculateAndMeasure(measureCalculator, x, y, "Optimised with precalculation, binary search (have not influence on asymptotic), interval tree for finding sums.");
		
	std::cin.get();

	delete measureCalculator;
	
	return 0;
}

double Rand(const double & min, const double & max)
{
    return min + (max - min) * (double)rand() / (double)RAND_MAX;
}

std::vector<double> GenerateRandomSequence(const int & size, const double & min, const double & max)
{
	std::vector<double> res;
	res.reserve(size);

	for(int i = 0; i < size; ++i)
		res.push_back(Rand(min, max));

	return res;
}

void CalculateAndMeasure(IMeasureCalculator* measureCalculator, const std::vector<double> & x, const std::vector<double> & y, const std::string & message)
{
	double time = clock();

	double result = measureCalculator->Calculate(x, y);

	time = clock() - time;

	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	std::cout << message << std::endl;
	std::cout << "Result: " << result <<std::endl;
	std::cout << "Finished!\nTime elapsed (NOT optimised): " << ms << " ms" << std::endl << std::endl << std::endl;
}