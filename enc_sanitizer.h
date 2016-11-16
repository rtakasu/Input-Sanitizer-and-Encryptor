#ifndef __SANITIZER_H__
#define __SANITIZER_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <vector>

#include <openssl/evp.h>

using namespace std;

int checking_command(vector<string>& command_array);

bool valid_argument(string& argument);

bool is_whitespace(char letter);

bool is_escape_char(char letter);

int generate_keyfile(string& password, string& output_file);

int encrypt(string& input_file, string& output_file, string& keyfile);

int decrypt(string& input_file, string& output_file, string& keyfile);

#endif
