#include "tree.cpp"
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
struct cmd {
    std::string cmd;
    std::map<std::string, std::string> param;
};
int main() {
    setlocale(LC_ALL, "rus");
    std::vector<page> Tree;
    std::map<int, std::string> l;

    cmd command;
    while(true){
        std::string line;// = "command -param1 \"value 1\" -param2 \"value2\" -param3 \"val ue 3\"";
        
        getline(std::cin, line, '\n');
        line += " ";
        command.cmd = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ") + 1);

        while(int p = line.find("-") != -1){
            std::string param = "";
            while(line[0] != ' '){
                param += line[0];
                line.erase(0,1);
            }
            line.erase(0,1);
            std::string value = "";
            if(line.length() != 0){
                if(line[0] == '"'){
                    line.erase(0,1);
                    while(line[0] != '"'){
                        value += line[0];
                        line.erase(0,1);
                    }
                    line.erase(0,1);
                } else {
                    while(line[0] != ' '){
                        value += line[0];
                        line.erase(0,1);
                    }
                }
                line.erase(0,1);
            }
            command.param[param] = value;
        }

        if(command.cmd == "выход"){
            return 0;
        }
        if(command.cmd == "создать"){
            std::string name = command.param["название"];
            std::string from = command.param["из"];
        }
    }
    
    std::ofstream fout;
    fout.open("tree");
    fout << "[\n";
    for(int i = 0; i < Tree.size(); i++){
        fout << "(\n";
        fout << "name : \"" << Tree[i].name << "\"" << "\n";
        fout << "text : \"" << Tree[i].text << "\"" << "\n";

        fout << "{\n";
        std::map<int, std::string>::iterator it;
        for(it = Tree[i].link.begin(); it != Tree[i].link.end(); it++){
            fout << it->first << " : \"" << it->second << "\"\n";
        }
        fout << "}\n";
        fout << ")\n";
    }

    fout << "]\n";
    fout.close();

    return 0;
}