#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void function1(){
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
	++writer = 0x80; // р
	++writer = 33; //0x21; // !
	ofile.close();


	std::ifstream in("input.txt");
	std::string contents((std::istreambuf_iterator<char>(in)), 
		std::istreambuf_iterator<char>());
	in.close();

	for(int i = 0; i < contents.length(); i++) 
		std::cout << int(contents.at(i)) << " ";

	std::cout << std::endl;
}


//функция для выполнения ТЗ из файла Morphology_letter.txt
void function2(){
	std::vector<std::string> ArrayString;
	
	setlocale(LC_ALL, "");
	std::ifstream file("Morphology_test.txt");

	string str;             
	int ind = 0;
	//Считываем файл и выполняем пункт 1.
	//1) удалить первые три строки файла
	while(getline(file,str)) 
	{                
		//Условие для того, чтобы убрать первые три строки
		if(ind > 2){
			ArrayString.push_back(str);
			//Вывод на экран первого шага. 
			//std::cout << ArrayString.at(ind - 3) << endl; 
		}
		ind++;
	}
	file.close(); // файл уже не нужен.

	//2) в получившемся в конце каждой нечетной строки удалить переход на следующую строку, 
    //т.е. склетить 1 и 2-ю, 3 и 4-ю строки и т.д, превращение будет следующие
	//Добавляем к строке вторую строку
	for(int i = 0; i < ArrayString.size(); i+=2){
		ArrayString.at(i) = ArrayString.at(i) + ArrayString.at(i+1);
	}
	//Удаляем лишние строки
	for(int i = 1; i < ArrayString.size(); i++){
		ArrayString.erase(ArrayString.begin() + i);
	}
	//Вывод на экран второго шага. 
	/*for(int i = 0; i < ArrayString.size(); i++){
		std::cout << ArrayString.at(i) << endl;
	}
	std::cout << std::endl;*/

	//3) удалить "[/']" по всему тексту (т.е. заменить их на пустые строки)
	//Объединю сразу с 4 пунктом
	//заменить "[']" на "'", заменить на ";" четыре подстроки по всему тексту: " [b]", "[/b] [i]", "[/i] [p]см.[/p] [ref]", "[/ref]"
	for(int i = 0; i < ArrayString.size(); i++){
		std::string str;
		char c;
		for(int j = 0; j < ArrayString.at(i).size(); j++){
			c = ArrayString.at(i).at(j);
			//Убираем [/']
			if(ArrayString.at(i).at(j) == '[' &&
				ArrayString.at(i).at(j + 1) == '/' &&
				ArrayString.at(i).at(j + 2) == '\'' &&
				ArrayString.at(i).at(j + 3) == ']'){
					j += 3;
			}
			//Меняем ['] на '
			else if(ArrayString.at(i).at(j) == '[' &&
				ArrayString.at(i).at(j + 1) == '\'' &&
				ArrayString.at(i).at(j + 2) == ']'){
					j += 2;
					str += '\'';
			}
			//Меняем " [b]" на ;
			else if(ArrayString.at(i).at(j) == ' ' &&
				ArrayString.at(i).at(j + 1) == '[' &&
				ArrayString.at(i).at(j + 2) == 'b' &&
				ArrayString.at(i).at(j + 3) == ']'){
					j += 3;
					str += ';';
			}
			//Меняем "[/b] [i]" на ;
			else if(ArrayString.at(i).at(j) == '[' &&
				ArrayString.at(i).at(j + 1) == '/' &&
				ArrayString.at(i).at(j + 2) == 'b' &&
				ArrayString.at(i).at(j + 3) == ']' &&
				ArrayString.at(i).at(j + 4) == ' ' &&
				ArrayString.at(i).at(j + 5) == '[' &&
				ArrayString.at(i).at(j + 6) == 'i' &&
				ArrayString.at(i).at(j + 7) == ']'){
					j += 7;
					str += ';';
			}
			//Меняем "[/i] [p]см.[/p] [ref]" на ;
			else if(ArrayString.at(i).at(j) == '[' &&
				ArrayString.at(i).at(j + 1) == '/' &&
				ArrayString.at(i).at(j + 2) == 'i' &&
				ArrayString.at(i).at(j + 3) == ']' &&
				ArrayString.at(i).at(j + 4) == ' ' &&
				ArrayString.at(i).at(j + 5) == '[' &&
				ArrayString.at(i).at(j + 6) == 'p' &&
				ArrayString.at(i).at(j + 7) == ']' &&
				ArrayString.at(i).at(j + 8) == 'с' &&
				ArrayString.at(i).at(j + 9) == 'м' &&
				ArrayString.at(i).at(j + 10) == '.' &&
				ArrayString.at(i).at(j + 11) == '[' &&
				ArrayString.at(i).at(j + 12) == '/' &&
				ArrayString.at(i).at(j + 13) == 'p' &&
				ArrayString.at(i).at(j + 14) == ']' &&
				ArrayString.at(i).at(j + 15) == ' ' &&
				ArrayString.at(i).at(j + 16) == '[' &&
				ArrayString.at(i).at(j + 17) == 'r' &&
				ArrayString.at(i).at(j + 18) == 'e' &&
				ArrayString.at(i).at(j + 19) == 'f' &&
				ArrayString.at(i).at(j + 20) == ']'){
					j += 20;
					str += ';';
			}
			//Меняем "[/ref]" на ;
			else if(ArrayString.at(i).at(j) == '[' &&
				ArrayString.at(i).at(j + 1) == '/' &&
				ArrayString.at(i).at(j + 2) == 'r' &&
				ArrayString.at(i).at(j + 3) == 'e' &&
				ArrayString.at(i).at(j + 4) == 'f' &&
				ArrayString.at(i).at(j + 5) == ']'){
					j += 5;
					str += ';';
			}
			else str += c;
		}
		ArrayString.at(i) = str;
	}

	//Вывод на экран третий и четвертый шаг. 
	/*for(int i = 0; i < ArrayString.size(); i++){
		std::cout << ArrayString.at(i) << endl;
	}
	std::cout << std::endl;*/

	//5) во второй колонке (т.е. между 1-м и 2-м знаками ";") во всех строках заменить
    //	"мн" на "мн неизв":
	//  "инф" на "инф инф инф"
	for(int i = 0; i < ArrayString.size(); i++){
		std::string str;
		char c;
		int NumberTZ = 0; //количество Точек с Запятыми, нам нужно проверять после второго появление ;
		for(int j = 0; j < ArrayString.at(i).size(); j++){
			c = ArrayString.at(i).at(j);
			if(ArrayString.at(i).at(j) == ';') NumberTZ++;
			if(ArrayString.at(i).at(j) == 'м' &&
				ArrayString.at(i).at(j + 1) == 'н' && NumberTZ == 2){
					j += 1;
					str += "мн неизв";
			}
			else if(ArrayString.at(i).at(j) == 'и' &&
				ArrayString.at(i).at(j + 1) == 'н' && 
				ArrayString.at(i).at(j + 2) == 'ф' && NumberTZ == 2){
					j += 2;
					str += "инф инф инф";
			}
			else str += c;
		}
		ArrayString.at(i) = str;
	}

	//Вывод на экран пятый шаг. 
	for(int i = 0; i < ArrayString.size(); i++){
		std::cout << ArrayString.at(i) << endl;
	}
	std::cout << std::endl;

	//6) также во второй колонке во всех строчках переставить в конец подстроки
	//	" воз":
	//	" крат":
	for(int i = 0; i < ArrayString.size(); i++){
		std::string str;
		char c;
		int NumberTZ = 0; //количество Точек с Запятыми, нам нужно проверять после второго появление ;
		bool voz = false;
		bool krat = false;
		for(int j = 0; j < ArrayString.at(i).size(); j++){
			c = ArrayString.at(i).at(j);
			if(ArrayString.at(i).at(j) == ';'){
				NumberTZ++;
				if(NumberTZ == 3 && voz){
					str += " воз";
				}
				if(NumberTZ == 3 && krat){
					str += " крат";
				}
			}
			if(ArrayString.at(i).at(j) == ' ' &&
				ArrayString.at(i).at(j + 1) == 'в' && 
				ArrayString.at(i).at(j + 2) == 'о' &&
				ArrayString.at(i).at(j + 3) == 'з' && NumberTZ == 2){
					j += 3;
					voz = true;
			}
			else if(ArrayString.at(i).at(j) == ' ' &&
				ArrayString.at(i).at(j + 1) == 'к' && 
				ArrayString.at(i).at(j + 2) == 'р' && 
				ArrayString.at(i).at(j + 3) == 'а' && 
				ArrayString.at(i).at(j + 4) == 'т' && NumberTZ == 2){
					j += 4;
					krat = true;
			}
			else str += c;
		}
		ArrayString.at(i) = str;
	}

	//Вывод на экран шестой шаг. 
	for(int i = 0; i < ArrayString.size(); i++){
		std::cout << ArrayString.at(i) << endl;
	}
	std::cout << std::endl;

	//7) во второй колонке пробелы заменить на ";", и если их окажется меньше 7, добавить в конец столько, чтобы было 7, т.е. чтобы вторая колонка превратилась в 8 колонок:
	for(int i = 0; i < ArrayString.size(); i++){
		std::string str;
		char c;
		int NumberTZ = 0; //количество Точек с Запятыми, нам нужно проверять после второго появление ;
		int NumberColumn = 0; //для подсчета ; во второй колонке
		for(int j = 0; j < ArrayString.at(i).size(); j++){
			c = ArrayString.at(i).at(j);
			if(ArrayString.at(i).at(j) == ';'){ 
				NumberTZ++;
				if(NumberTZ == 3){
					for(int k = NumberColumn; k < 7; k++) str += ';';
				}
			}
			if(ArrayString.at(i).at(j) == ' ' && NumberTZ == 2){
				str += ';';
				NumberColumn++;
			}
			else str += c;
		}
		ArrayString.at(i) = str;
	}

	//Вывод на экран 7-ой шаг. 
	for(int i = 0; i < ArrayString.size(); i++){
		std::cout << ArrayString.at(i) << endl;
	}
	std::cout << std::endl;
}

void main(){
	function2();
	system("pause");
}
