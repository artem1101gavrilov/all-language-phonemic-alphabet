#include <iostream>
#include <fstream>

using namespace std;

void main(){
	//Из https://habr.com/post/107679/
	ofstream ofile("input.txt", std::ios::binary);
	ostreambuf_iterator<char> writer(ofile);
	writer   = 0xCF; // П
	++writer = 0xF0; // р
	++writer = 0xE8; // и
	++writer = 0xE2; // в
	++writer = 0xE5; // е
	++writer = 0xF2; // т
	++writer = 0x2C; // ,
	++writer = 0x20; //  
	++writer = 0xEC; // м
	++writer = 0xE8; // и
	++writer = 0xF0; // р
	++writer = 0x21; // !
	ofile.close();

	int n = 0;
	fstream F;
	char a;
	F.open("input.txt");
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
