#include "sort.h"

void sort::process(const char* fileName) {
	// read file
	ifstream FileInput;
	FileInput.open(fileName);

	if (!FileInput) {
		cout << "File open fail!!" << endl;
	}
	char c;
	string line;
	while ((c = FileInput.get()) != EOF) {
		FileInput.get();
		if (c == '0') {  //Do the insertion sort
			getline(FileInput, line, ' ');
			bool isBinary = (stoi(line) == 0) ? false : true;
			getline(FileInput, line, ' ');
			int length_ins = stoi(line);
			getline(FileInput, line);
			int target = stoi(line);

			for (int i = 0; i < length_ins; i++) {
				if (i == length_ins - 1)
					getline(FileInput, line);
				else
					getline(FileInput, line, ' ');
				insertion.push_back(stoi(line)); //Insert the number to the insertion vector
			}
			InsertionSort(); //Run the insertion sort
			if (isBinary) BinarySearch(0, target); //Whether do the binary search
			else cout << endl;
			insertion.clear();
		}
		else if (c == '1') { //Do the bucket sort
			getline(FileInput, line, ' ');
			bool isBinary = (stoi(line) == 0) ? false : true;
			getline(FileInput, line, ' ');
			int length_buc = stoi(line);
			getline(FileInput, line);
			int target = stoi(line);

			for (int i = 0; i < length_buc; i++) {
				if (i == length_buc - 1)
					getline(FileInput, line);
				else
					getline(FileInput, line, ' ');
				bucket.push_back(stoi(line)); //Insert the number to the bucket vector
			}
			BucketSort();  //Run the bucket sort
			if (isBinary) BinarySearch(1, target);  //Whether do the binary search
			else cout << endl;
			bucket.clear();
		}
	}
	FileInput.close();
}

void sort::InsertionSort() {
	//TODO:
	//Use the insert vector to perform insertion sort.

	output(0, 0); //print the result after the insertion sort
}

void sort::BucketSort() {
	//TODO:
	//Use the bucket vector to perform bucket sort.
	//Note: Don't forget to print the result at each round end.
}

void sort::BinarySearch(int number, int target) {
	//TODO:
	//number = 0 means that use the insertion vector to find the target
	//number = 1 means that use the bucket vector to find the target
	//target means that we want to find the number.
}

void sort::output(int number, int round) {
	if (number == 0) {
		cout << "Insertion Sort : ";
		//TODO:  output the insertion sort result
		cout << endl;
	}
	else {
		if (round == 1) cout << "Bucket Sort" << endl;
		cout << round << " : ";
		//TODO: output the bucket sort result each round

		cout << endl;
	}
}
