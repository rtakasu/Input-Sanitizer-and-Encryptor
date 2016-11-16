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
			
			string keyfile;	

			while( getline(myfile,line))
			{ 
				vector<string> command_array(0);

				istringstream iss(line);

				int i=0;
				while(iss.good()) {
					string temp;
					iss>>temp;
					command_array.push_back(temp);	
				}

				int command = checking_command(command_array);
				
				if (command == 0) {
					cout<<line<<": is an invalid command\n";	
				}
				else if (command == 1) {
					encrypt(command_array[1], command_array[2], keyfile);	
				}
				else if (command == 2) {
					decrypt(command_array[1], command_array[2], keyfile);	
				}
				else if (command == 3) {
					generate_keyfile(command_array[1], command_array[2]);	
				}
				else if (command == 4) {
					keyfile = command_array[1];
				}
			}
			myfile.close();
		}
		else cout << "Unable to open file\n";
		myfile.close();
		
	}				
	return 0;
}

int checking_command(vector<string>& command_array) {
	// Function takes in the line corresponding to a command and returns a number from 1-6 if it is a valid command,
	// If it's an invalid command, it returns 0

	if (command_array.size() == 3) {
		if (valid_argument(command_array[1]) && valid_argument(command_array[2])){
			if (command_array[0] == "encrypt") 
				return 1;
			else if (command_array[0] == "decrypt") 
				return 2;
			else if (command_array[0] == "password")
				return 3;	
		}	
	} else if (command_array.size() == 2) {
		if (valid_argument(command_array[1])){
			if (command_array[0] == "keyfile")
				return 4;
			else if (command_array[0] == "cd")
				return 5;
			else if (command_array[0] == "mkdir")
				return 6;
		}	
	}
	
	return 0;

}

bool valid_argument(string& argument){
	bool valid = true;
	for (char& c:argument) {
		if (is_whitespace(c)) {
			valid = false;	
			cout<<c<<"\n";
		}
	}	

	return valid;
}

bool is_alpha_numeric(char letter) {
	return 	((letter >= '0' && letter <= '9') || 
		(letter >= 'A' && letter <= 'Z') ||
		(letter >= 'a' && letter <= 'z') || 
		(letter == 131) ||  					// ƒ
		(letter == 138) ||                       		// Š
		(letter == 140) ||                                      // Œ
		(letter == 142) ||                                      // Ž
		(letter == 154) ||                                      // š
		(letter == 156) ||                                      // œ
		(letter == 158) ||                                      // ž
		(letter == 159) ||                                      // Ÿ
		(letter == 170) ||                                      // ª
		(letter == 178) ||                                      // ²
		(letter == 179) ||                                      // ³
		(letter == 185) ||                                      // ¹
		(letter == 186) ||                                      // º
		(letter >= 192 && letter <= 214) ||			// À - Ö 
		(letter >= 216 && letter <= 246) ||			// Ø - ö
		(letter >= 248 && letter <= 255)); 			// ø - ÿ	
}

bool is_whitespace(char letter) {
	return ((letter == ' ') ||
		(letter == '\t'));
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
				keyfile<<hex<<int(out[i]);	
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

	command = "openssl enc -aes-128-cbc -e -in "+input_file+" -out "+output_file+" \\-pass file:"+keyfile;		 
	return system(command.c_str());

}

int decrypt(string& input_file, string& output_file, string& keyfile)
{
	string command;

	command = "openssl enc -d -aes-128-cbc -in "+input_file+" -out "+output_file+" \\-pass file:"+keyfile;		 
	return system(command.c_str()); 
}
