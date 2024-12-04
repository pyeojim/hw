#include <iostream>
using namespace std;

int main() {
	int iNum = 0;
	int iNums[3] = { 1, 2, 3 };
	int* pNum = &iNum;
	int* pNums1 = &iNums[0];
	int* pNums2 = iNums; // &iNums ?
	cout << pNums1 << endl << pNums2 << endl;
	cout << *pNums1 << endl << *pNums2 << endl;
	cout << iNums[1] << endl << pNums1[1] << endl << pNums2[1] << endl;
	return 0;
}