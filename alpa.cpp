#include <iostream>
#include <fstream>

using namespace std;

void main(){
	setlocale(LC_ALL, "");

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


	std::ifstream in("input.txt");
	std::string contents((std::istreambuf_iterator<char>(in)), 
		std::istreambuf_iterator<char>());

	for(int i = 0; i < contents.length(); i++) 
		std::cout << contents.at(i);

	std::cout << std::endl;
	system("pause");
}
