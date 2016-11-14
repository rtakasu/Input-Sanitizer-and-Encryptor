#include "sanitizer.h"

int main(int argc, char*argv[])
{
	for (int i=1; i<argc; i++)
	{
		string line;	
		ifstream myfile;
		myfile.open(argv[i]);
	
		if (myfile.is_open())
		{
			while( getline(myfile,line))
			{
				cout<<"Executing command: "<<line;
				int j=system(line.c_str());
				cout<<"The value was: "<<j;
				//cout << line << "\n";
			}
			myfile.close();
		}
		else std::cout << "Unable to open file\n";
		myfile.close();
		

	}

		
	return 0;
}


