
#include "reader.h"
void reader::Load(string file_name)
{
	saved_file = file_name;
	check_file(file_name);
	readed.open(saved_file);
	file_cash.clear();
	int counter_line = 0;
	string buffer = "";
	if (!readed.is_open())
	{
		printf("%s", "FAILED OPEN FILE\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (getline(readed, buffer))
		{
			file_cash.push_back(buffer);
			counter_line++;
			if (counter_line == PAGE_SIZE - 1)
			{
				all_pages++;
				counter_line = 0;
			}

		}
	}

	readed.close();
}

void reader::GetLine(int number_line)
{
	int actual_line = number_line;
	if (actual_line>file_cash.size())
	{
		printf("%s", "Line not found");
		return;
	}
	list<string>::iterator it = file_cash.begin();
	advance(it, actual_line - 1);
	cout << *it << endl;
}

void reader::DelLine(int number_line)
{
	check_file(saved_file);
	int actual_line = number_line;
	if (actual_line>file_cash.size())
	{
		printf("%s", "Line not found");
		return;
	}
	list<string>::iterator it = file_cash.begin();
	advance(it, actual_line - 1);
	file_cash.erase(it);
	all_lines--;
	if (all_lines<PAGE_SIZE*all_pages) all_pages--;
	printf("%s", "Line delited");
	Store(saved_file);
}

void reader::InsLine(int number_line, string insert_line)
{
	check_file(saved_file);
	int actual_line = number_line;
	if (actual_line>file_cash.size())
	{
		file_cash.push_back(insert_line);
		printf("%s", "Line add in last position in file");
		return;
	}
	list<string>::iterator it = file_cash.begin();
	advance(it, actual_line - 1);
	file_cash.insert(it, insert_line);
	all_lines++;
	if (all_lines >= PAGE_SIZE*all_pages) all_pages++;
	printf("%s", "Line inserted");
	Store(saved_file);
}

void reader::RepLine(int number_line, string insert_line)
{
	check_file(saved_file);
	int actual_line = number_line;
	if (actual_line>file_cash.size())
	{
		printf("%s", "Line not found");
		return;
	}
	list<string>::iterator it = file_cash.begin();
	advance(it, actual_line - 1);
	*it = insert_line;
	printf("%s", "Line replaced");
	Store(saved_file);
}

void reader::Store(string file_name)
{
	check_file(saved_file);
	saved.open(file_name);
	list<string>::iterator it = file_cash.begin();
	for (it = file_cash.begin(); it != file_cash.end(); ++it)
	{
		saved << *it << endl;
	}
	saved.close();
}

void reader::OpenPage(int number_page)
{
	if (number_page>all_pages + 1 || number_page <= 0) {
		printf("%s", "Page not found");
		return;
	}
	int page = number_page - 1;
	int range_begin = page*PAGE_SIZE;
	//int range_end = range_begin +PAGE_SIZE-1;
	list<string>::iterator it = file_cash.begin();
	advance(it, range_begin);
	if (page == all_pages)
	{
		for (1; it != file_cash.end(); ++it)
		{
			cout << *it << endl;
		}
	}
	else
	{
		for (int i = 0; i<PAGE_SIZE; i++)
		{
			cout << *it << endl;
			++it;
		}
	}
}

void reader::DelPage(int number_page)
{
	check_file(saved_file);
	if (number_page>all_pages + 1 || number_page <= 0)
	{
		printf("%s", "Page not found");
		return;
	}
	int page = number_page - 1;
	int range_begin = page*PAGE_SIZE;
	int range_end = range_begin + PAGE_SIZE;
	list<string>::iterator it_beg = file_cash.begin();
	list<string>::iterator it_end = file_cash.begin();
	advance(it_beg, range_begin);
	if (page == all_pages)
		advance(it_end, file_cash.size() - 1);
	else
		advance(it_end, range_end);
	file_cash.erase(it_beg, it_end);
	printf("%s", "Page deleted");
	Store(saved_file);
}

void reader::check_file(string file_name)
{
	try
	{
		readed.open(file_name);
	}
	catch (const ifstream::failure& e)
	{
		printf("%s", "Exception opening/reading file");
		exit(EXIT_FAILURE);
	}
	readed.close();
}

