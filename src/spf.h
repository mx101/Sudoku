//
// Created by Michael on 10/22/2019.
//

#ifndef SUDOKU_SPF_H
#define SUDOKU_SPF_H

#include <fstream>

class spf {
 public:
    std::filebuf* SetupFileReader(std::filebuf*, std::string);
    bool IsValidFile(std::istream&);

 private:

};


#endif //SUDOKU_SPF_H
