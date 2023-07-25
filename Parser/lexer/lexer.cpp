#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "LexAnalyse.h"
#include "Compiler.h"
using namespace std;

int main()
{
    ifstream ifStream("test1.asm");
    if (!ifStream.bad())
    {
        string line;
        list<string> linesList;
        while (getline(ifStream, line))
        {
            linesList.push_back(line);
        }
        analyser p(linesList);
        p.analyse_code();
        p.print();

        Compiler x(p.processedCode);
        x.first_view();
        x.second_view();

        ofstream out("first_view.txt");
        out << x.get_listing();
        out.close();
    }
    return 0;
}
