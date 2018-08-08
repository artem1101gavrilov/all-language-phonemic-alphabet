#include <iostream>
#include <fstream>
using namespace std;

void main(){
	int n = 0;
	fstream F;
	char a;
	F.open("text.txt");
	if (F)
	{
		while (!F.eof())
		{
			F>>a;
			cout<<a;
			n++;
		}
		F.close();
		cout << endl << "n=" << n << endl;
	}
	system("pause");
}