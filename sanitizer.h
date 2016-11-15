#ifndef __SANITIZER_H__
#define __SANITIZER_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <iomanip>
#include <boost/format.hpp>
#include <sstream>

#include <openssl/evp.h>

using namespace std;

int generate_keyfile(string& password, string& output_file);

int encrypt(string& input_file, string& output_file, string& keyfile);

int decrypt(string& input_file, string& output_file, string& keyfile);

#endif
