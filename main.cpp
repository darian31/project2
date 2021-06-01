#include <iostream>
#include "tree.cpp"
#include <fstream>
#include <string>
int main() {
    std::vector<page> pageTree;
    std::ifstream fin;
    fin.open("tree");
    char line[2048];

    while(!fin.eof()){
        page pageNode;
        fin.getline(line, 2048);
        fin.getline(line, 2048);
        std::string name;
        std::string text;

        fin.getline(line, 2048);
        name = line;
        fin.getline(line, 2048);
        text = line;
        fin.getline(line, 2048);

        std::string line1;
        line1 = line;

        while(line1 != ")"){
            pageNode.link.push_back(atoi(line1.c_str()));
            fin.getline(line, 2048);
            line1 = line;
        }
        pageNode.name = name;
        pageNode.text = text;
        pageTree.push_back(pageNode);
    }
    

    return 0;
}