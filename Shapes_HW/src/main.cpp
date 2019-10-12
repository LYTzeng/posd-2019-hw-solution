#include <iostream>
#include <string>
#include <fstream>
#include "terminal.h"

int main(int argc, char **argv)
{
    //bin/geo input.txt output.txt [area perimeter  sumOfSquares]  [inc dec]
    if (argc < 5)
    {
        Terminal terminal("Unuseful User Input!");
        terminal.showResult();
        return 0;
    }
    else
    {
        std::string inputPath(argv[1]);
        std::string outputPath(argv[2]);
        std::string featureArg(argv[3]);
        std::string orderingArg(argv[4]);

        std::ifstream file;
        file.open(inputPath);
        std::string inputLine;
        std::getline(file, inputLine);
        file.close();

        std::ofstream wrFile;
        wrFile.open(outputPath);
        Terminal terminal(inputLine + " " + featureArg + " " + orderingArg);
        wrFile << terminal.showResult();
        wrFile.close();
        return 0;
    }
}
