#include "pages.h"
#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <sys/types.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGNETA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

bool check(std::string id) {
    for (int i = 0; i < id.length(); i++)
        if (!std::isdigit(id[i]))
            return false;

    return true;
}

int main() {
    std::string f;
    DIR *dir = opendir(".");
    std::cout << "Введите номер новеллы\n";
    std::vector<std::string> novells;
    if (dir) {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL) {
            std::string filename = ent->d_name;
            if (int dot = filename.find(".novell") != -1) {
                int i = 0;
                std::string n;
                while (filename[i] != '.') {
                    n += filename[i];
                    i++;
                    if (i == filename.length())
                        break;
                }
                novells.push_back(n);
            }
        }
    } else {
        std::cout << "Ошибка открытия директории\n";
    }

    for (int i = 0; i < novells.size(); i++) {
        std::cout << i + 1 << ": " << novells[i] << "\n";
    }
    std::string i_str;

    while (true) {
        std::cin >> i_str;
        //i_str = "2";
        if (!check(i_str)) {
            std::cout << "Введите нормально1"
                      << "\n";
            continue;
        }
        int i = std::atoi(i_str.c_str());
        if ((i > 0) && (i <= novells.size())) {
            f = novells[i - 1];
            break;
        } else {
            std::cout << "Введите нормально2"
                      << "\n";
        }
    }

    std::vector<page> pageTree;
    std::ifstream fin;
    f += ".novell";
    fin.open(f);

    std::string s;
    page p;
    fin >> s;
    if (s == "[") {
        while (s != "]") {
            if (s == "[") {
                fin >> s;
                continue;
            }
            if (s == "(") {
                while (s != ")") {
                    if (s == "(") {
                        fin >> s;
                        continue;
                    }
                    if (s == "name") {
                        fin >> s;
                        std::string name;
                        char c = '\0';
                        fin.get(c);
                        fin.get(c);
                        fin.get(c);
                        while (c != '\"') {
                            name += c;
                            fin.get(c);
                        }
                        p.name = name;
                    }
                    if (s == "text") {
                        fin >> s;
                        std::string text;
                        char c = '\0';
                        fin.get(c);
                        fin.get(c);
                        fin.get(c);
                        while (c != '\"') {
                            text += c;
                            fin.get(c);
                        }
                        p.text = text;
                    }
                    if (s == "{") {
                        while (s != "}") {
                            if (s == "{") {
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
                            while (c != '\"') {
                                ans += c;
                                fin.get(c);
                            }
                            p.link[link] = ans;
                            fin >> s;
                        }
                        fin >> s;
                    }
                    if (s != ")") {
                        fin >> s;
                    }
                }
                pageTree.push_back(p);
                p = page();
            }
            if (s != "]") {
                fin >> s;
            }
        }
    }
    //Конец загрузки

    int page = 0;
    while (true) {
        std::cout << RED << pageTree[page].name << RESET << "\n"
                  << pageTree[page].text << "\n";
        std::map<int, std::string>::iterator it = pageTree[page].link.begin();
        int i = 1;
        std::vector<int> l;
        for (; it != pageTree[page].link.end(); it++) {
            std::cout << "[" << i << "] : " << it->second << "\n";
            l.push_back(it->first);
            i++;
        }
        std::string page_str;
        while (true) {
            std::cin >> page_str;
            if (check(page_str)) {
                page = std::atoi(page_str.c_str());
                if (page > 0 && page <= l.size()) {
                    page = l[page - 1];
                    break;
                } else {
                    std::cout << "Неверно указан номер\n";
                }
            } else {
                std::cout << "Неверно указан номер\n";
            }
        }
    }

    return 0;
}