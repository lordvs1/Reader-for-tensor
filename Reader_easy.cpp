
#include "reader.h"

using namespace std;

int main(int argc, char *argv[])
{
	reader object_reader;
	if (argv[1]) 
	{
		object_reader.Load(argv[1]);
		object_reader.OpenPage(1);
		object_reader.RepLine(rand() % 8 + 2, "this is my line 1");
		object_reader.RepLine(rand() % 4 + 1, "this is my line 2");
	}
	else
	{
		cout << "using: a.out 2.txt " << endl;
	}

    return 0;
}

