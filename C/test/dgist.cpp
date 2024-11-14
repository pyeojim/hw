#include <string.h>
#include <iostream>
using namespace std;
int main(){
int iNums[2][3] = { 1, 2, 3, 4, 5, 6 };
cout << iNums << endl;
cout << *iNums << endl;
cout << **iNums << endl;
cout << **(iNums + 1) << endl;
cout << *((*iNums) + 1) << endl;
cout << *((*(iNums + 1)) + 1) << endl;
cout << *((*(iNums + 1)) + 1) + 1 << endl;
system("pause");
return 0;
}