#include <iostream>
#include "tree.cpp"
#include <fstream>
#include <string>
int main()
{
    std::vector<page> pageTree;
    std::ifstream fin;
    fin.open("tree");
    std::string s;
    page p;
    fin >> s;
    if (s == "[")
    {
        while (s != "]")
        {
            if (s == "[")
            {
                fin >> s;
                continue;
            }
            if (s == "(")
            {
                while (s != ")")
                {
                    if (s == "(")
                    {
                        fin >> s;
                        continue;
                    }
                    if (s == "name")
                    {
                        fin >> s;
                        std::string name;
                        char c = '\0';
                        fin.get(c);
                        fin.get(c);
                        fin.get(c);
                        while (c != '\"')
                        {
                            name += c;
                            fin.get(c);
                        }
                        p.name = name;
                    }
                    if (s == "text")
                    {
                        fin >> s;
                        std::string text;
                        char c = '\0';
                        fin.get(c);
                        fin.get(c);
                        fin.get(c);
                        while (c != '\"')
                        {
                            text += c;
                            fin.get(c);
                        }
                        p.text = text;
                    }
                    if (s == "{")
                    {
                        while (s != "}")
                        {
                            if (s == "{")
                            {
                                fin >> s;
                                continue;
                            }
                            int link = atoi(s.c_str());
                            std::string ans;
                            char c = '\0';
                            fin.get(c);
                            fin.get(c);
                            fin.get(c);
                            fin.get(c);
                            fin.get(c);
                            while (c != '\"')
                            {
                                ans += c;
                                fin.get(c);
                            }
                            p.link[link] = ans;
                            fin >> s;
                        }
                        fin >> s;
                    }
                    if (s != ")")
                    {
                        fin >> s;
                    }
                }
                pageTree.push_back(p);
                p = page();
            }
            if (s != "]")
            {
                fin >> s;
            }
        }
    }
    //Конец загрузки

    int page = 0;
    while (true)
    {
        std::cout << pageTree[page].name << "\n" << pageTree[page].text << "\n";
        std::map<int, std::string>::iterator it = pageTree[page].link.begin();
        int i = 1;
        std::vector<int> l;
        for (; it != pageTree[page].link.end(); it++)
        {
            std::cout << "[" << i << "] : " << it->second << "\n";
            l.push_back(it->first);
            i++;
        }

        std::cin >> page;
        page = l[page - 1];
    }

    return 0;
}