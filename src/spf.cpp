//
// Created by Michael on 10/22/2019.
//

#include "spf.h"

#include <iostream>

std::filebuf* spf::SetupFileReader(std::filebuf* file_reader, std::string given_filename) {
  file_reader->open(given_filename, std::ios::in);
  return file_reader;
}

bool spf::IsValidFile(std::istream& i_stream) {
  std::string toString;
  i_stream >> toString;
  return toString == "#spf1.0";
}
