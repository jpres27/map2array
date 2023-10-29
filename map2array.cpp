#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main (int argc, char **argv) {

    std::ifstream inputfile;
    std::ofstream outputfile ("maparray");


    if (argc > 1) {
        inputfile.open (argv[1]);
        if (! inputfile.is_open()) {
            std::cerr << "error: file open failed '" << argv[1] << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "error: no filename given." << std::endl;
        return 1;
    }

    std::string line, val;                
    std::vector<std::vector<int>> collisionMap;     // vector of int vectors

    while (std::getline (inputfile, line)) {        // read line in
        std::vector<int> v;                         // row vector
        std::stringstream s (line);
        while (getline (s, val, ','))               // get each value (',' delimited)
            v.push_back (std::stoi (val));          // add to row vector
        collisionMap.push_back (v);                 // add row vector to array
    }

    std::string delim = "";                         // set a delimiter so we don't get a comma before the first value
    outputfile << "int collisionMap[" << collisionMap[0].size() << "][" << collisionMap.size() << "] = {";
    for (auto& row : collisionMap) {                // iterate over rows
        for (auto& val : row) {                     // iterate over vals
            outputfile << delim << val;             // output to file
            delim = ", ";                           // update delimiter so we have commas except for the last value
            }               
    }
    outputfile << "};";
    outputfile.close();
    return 0;
}