#include <vector>
#include <iostream>

struct transferStruct {
	int* numbers;
	int sz;
	int current;

	//constructor
	transferStruct(int size) : sz{size} {
		//Allocates sz ints on the heap
		numbers = new int[sz];
	}

	//destructor
	~transferStruct() {
		delete[] numbers;
	}
};


//Done with this for now
/*struct betterStruct {
	std::vector<int> numbers;

	betterStruct(int sz) {
		numbers = std::vector<int>(sz);
	}
};*/


class vector {
	int* members;
	//Number of data members
	int length = 0;
	int sz;

	void expand();

public:
	vector(int size) {
		sz = size;
		members = new int[sz];
	}

	~vector() {
		delete[] members;
	}

	void pushBack(int n);

	int& get(int idx) {
		if (idx > length)
			throw std::exception();
		

		return members[idx];
	}
};



void vector::pushBack(int n) {
	/*If the vector is full,
	we need to expand the vector*/
	if (++length > sz) {
		expand();
	}

	members[length-1] = n;
}

void vector::expand() {
	/*Double the allocation size, which
	is what the C++ standard library vector
	does in its implementation*/
	sz *= 2;
	int* newAlloc = new int[sz];
	
	//Copy every data member to the new allocation
	for (int i = 0; i < length; i++) {
		newAlloc[i] = members[i];
	}

	delete[] members;

	/*Change the members to point to the new
	allocation*/
	members
	 = newAlloc;
}




void myVecFunction(vector& myVec) {
	for (int i = 0; i < 5; i++)
		myVec.pushBack(i*5);
}

void myWeirdFunction(transferStruct& badStr) {
	for (int i = 0; i < 5; i++) {
		badStr.current++;
		if (badStr.current > badStr.sz) {
			badStr.sz *= 2;

			int* tmp = badStr.numbers;
			badStr.numbers = new int[badStr.sz];
			delete[] tmp;
		}

		badStr.numbers[i] = i*5;
	}
}

int main() {
	vector myVec(2);
	transferStruct badStr(2);

	myWeirdFunction(badStr);
	myVecFunction(myVec);

	std::cout << "Hello world!";
}