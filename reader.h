#ifndef FILEREADER
#define FILEREADER

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
class reader
{
private:
	static const int PAGE_SIZE = 256;
	string saved_file;
	ifstream readed;
	ofstream saved;
	list <string> file_cash;
	int all_pages = 0;
	int all_lines = 0;

public:
	void Load(string file_name);
	void Store(string file_name);
	void GetLine(int number_line);
	void InsLine(int number_line, string insert_line);
	void RepLine(int number_line, string insert_line);
	void DelLine(int number_line);

	void OpenPage(int number_page);
	void DelPage(int number_page);

protected:
	void check_file(string file_name);
};
#endif

