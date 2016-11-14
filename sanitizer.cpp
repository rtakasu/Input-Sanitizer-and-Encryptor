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
	string pwd = "pa";
	string key = "key.key";
	generate_keyfile(pwd, key);
	
	string in = "test.txt";
	string out = "out.txt";
	string keyfile = "key.key";
	encrypt(in,out,keyfile);

	string in2 = "out.txt";
	string out2 = "decrypted.txt";
	decrypt(in2,out2,keyfile);
			
	return 0;
}

int generate_keyfile(string& password, string& output_file)
{

	size_t i;
	unsigned char* out;
	unsigned char salt_value[] = {'s','a','l','t'};
	ofstream keyfile(output_file);

	out = (unsigned char *) malloc(sizeof(unsigned char)*20);
	printf("password: %s\n", password.c_str());

	if (keyfile.is_open())
	{
		if (PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), strlen(password.c_str()), salt_value, sizeof(salt_value), 1, 20, out))
		{
			for (i=0;i<20;i++)
			{
				//keyfile <<hex<<setfill('0')<<setw(2)<< out[i];
				//cout <<hex<<setfill('0')<<setw(2)<< out[i]<<" ";		
				
				//keyfile << boost::format("%02x") %out[i];
				//cout << boost::format("%02x") %out[i];
				//cout <<hex<<out[1];
				//sprintf(keyfile,"%02x", out[i]);
				printf("%02x", out[i]);
			}
	

		}			
	
	}
	else
		cout<<"Unable to open file";
	
	free(out);
	keyfile.close();
	return 0;

}

int encrypt(string& input_file, string& output_file, string& keyfile)
{
	string command;

	command = "openssl enc -aes-128-cbc -e -in "+input_file+" -out "+output_file;//+" \ -pass file:"+keyfile;		 
	return system(command.c_str());

}

int decrypt(string& input_file, string& output_file, string& keyfile)
{
	string command;

	command = "openssl enc -d -aes-128-cbc -in "+input_file+" -out "+output_file;//+" \ -pass file:"+keyfile;		 
	return system(command.c_str()); 
}
