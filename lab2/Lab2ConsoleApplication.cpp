#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>
#include <windows.h>
#include <functional>

using namespace std;

int RED = 4;

int WHITE = 15;

void setCharacterColor(int colorNumber) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorNumber);
}

vector<double> getRandomlyFilledArrayOfSizeN(const int size, const double min = -10, const double max = 10) {
	random_device randomSeed;
	mt19937 randomNumberGenerator(randomSeed());
	uniform_real_distribution<> randomNumberRange(min, max);
	vector<double> randomlyFilledVector;
	for (int i = 0; i < size; i++) {
		randomlyFilledVector.push_back(randomNumberRange(randomNumberGenerator));
	}
	return randomlyFilledVector;
}

void printHighlightingSuitableElements(vector<double> vector, function<bool(double)> unaryPredicate) {
	for_each(begin(vector), end(vector),
		[unaryPredicate](double element) {
			bool needToBeHighlighted = unaryPredicate(element);
			if (needToBeHighlighted) {
				setCharacterColor(RED);
			}
			cout << element << endl;
			if (needToBeHighlighted) {
				setCharacterColor(WHITE);
			}
		}
	);
}

void subTask1NumbersLessThen3(const vector<double>& vector) {
	cout << "Number of elements less then 3: " << 
		count_if(begin(vector), end(vector), [](double element) {return element < 3; }) << endl;
}

void subTask2SumOfNumbersAfterLastNegative(const vector<double>& vector) {
	auto lastNegativeElement = find_if(
		rbegin(vector),
		rend(vector),
		[](double element) {return element < 0; }
	).base();
	cout << "Sum of numbers ignoring fractional part that are located after last negative number: "
		<< accumulate(lastNegativeElement, end(vector), 0, [](int sum, double value) {return sum += (int)value; }) << endl;
}

bool isWithin20Percent(double val, double maxVal) {
	return abs(maxVal - val) <= 0.2 * maxVal;
}

void subTask3Sorting(vector<double>& vector, double maxValue) {
	sort(
		begin(vector),
		end(vector),
		[maxValue](double element1, double element2) {
			bool isFirstElementInBound = isWithin20Percent(element1, maxValue);
			bool isSecondElementInBould = isWithin20Percent(element2, maxValue);
			if (isFirstElementInBound && isSecondElementInBould) {
				return element1 > element2;
			}
			else if (!isSecondElementInBould) {
				return isFirstElementInBound;
			}
			else {
				return false;
			}
		}
	);
}

function<bool(double)> predicateforElementsAffectedBySorting(double maxValue) {
	return [maxValue](double element) {return isWithin20Percent(element, maxValue); };
}

int main() {
	cout << "Enter number of elements in array: ";
	string numberOfElements;
	getline(cin, numberOfElements);

	vector<double> randomlyFilledVector = getRandomlyFilledArrayOfSizeN(stoi(numberOfElements));

	cout << "Generated vector: " << endl;

	double maxValueInVector = *max_element(begin(randomlyFilledVector), end(randomlyFilledVector));

	printHighlightingSuitableElements(randomlyFilledVector, predicateforElementsAffectedBySorting(maxValueInVector));

	subTask1NumbersLessThen3(randomlyFilledVector);

	subTask2SumOfNumbersAfterLastNegative(randomlyFilledVector);

	subTask3Sorting(randomlyFilledVector, maxValueInVector);

	cout << "Sorted array: " << endl;

	printHighlightingSuitableElements(randomlyFilledVector, predicateforElementsAffectedBySorting(maxValueInVector));

}
