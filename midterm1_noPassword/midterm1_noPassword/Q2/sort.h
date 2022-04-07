#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class sort {
	vector<int> insertion;
	vector<int> bucket;
public:
	void process(const char* fileName);
	void InsertionSort();
	void BucketSort();
	void BinarySearch(int, int);
	void output(int, int);
};