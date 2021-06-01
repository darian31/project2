#include "tree.cpp"
#include <map>
#include <vector>
#include <fstream>
int main() {
    std::vector<page> Tree;
    std::map<int, std::string> l;
    l[0] = "text";
    l[1] = "ans wer dfadfsfda sdfs\nasdfagsa\nadf sdf sadf f";
    l[2] = "a\nf\n\nadfsad";
    Tree.push_back(page("name1\nnext Line\n Line 3", 
    "text\nText line 1\nText line 2\n text line 3\n text line 4", l));
    l.clear();

    
    l[2] = "a\n\nnswer";
    Tree.push_back(page("name2", 
    "text", l));
    l.clear();

    Tree.push_back(page("name 3", "text text test\ntest", l));
    l.clear();
    
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