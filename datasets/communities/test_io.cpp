 	

// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
  string line;
  ifstream myfile ("train.csv");
  int i = 0;
  if (myfile.is_open())
  {
    while(myfile.good())
    {
      getline (myfile,line, ',');
      // std::stof(line);
      std::cout << line.empty() << " ";
      std::cout << line << " ";
      getline (myfile,line, '\n');
      std::cout << i << " :: " << myfile.good() << endl;
      i++;
    }
    myfile.close();
  }

  return 0;
}
