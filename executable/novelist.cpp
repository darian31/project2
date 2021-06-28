#include "pages.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <dirent.h>
#include <sys/types.h>

///Доступные новеллы
std::vector<std::string> novells;

///Команда.
/// std::string cmd - название команды
/// std::map<std::string, std::string> param - параметры команды, через "-"
struct cmd {
    std::string cmd;
    std::map<std::string, std::string> param;
    ///Очистить команду
    void clear() {
        cmd = "";
        param.clear();
    }
    ///Ввести команду
    void getcommand() {
        std::string line;

        getline(std::cin, line, '\n');
        line += " ";
        cmd = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ") + 1);

        while (int p = line.find("-") != -1) {
            std::string param_ = "";
            while (line[0] != ' ') {
                param_ += line[0];
                line.erase(0, 1);
            }
            line.erase(0, 1);
            std::string value = "";
            if (line.length() != 0) {
                if (line[0] == '"') {
                    line.erase(0, 1);
                    while (line[0] != '"') {
                        value += line[0];
                        line.erase(0, 1);
                    }
                    line.erase(0, 1);
                } else {
                    while (line[0] != ' ') {
                        value += line[0];
                        line.erase(0, 1);
                    }
                }
                line.erase(0, 1);
            }
            param[param_] = value;
        }
    }
};

///Массив страниц
std::vector<page> Pages;

///Показать страницу по айди, если айди введен неверно на выходе выведет
///сообщение и вернет false. Если все хорошо, то вернет true
bool showByID(std::string id) {
    if (checkid(id) == false) {
        std::cout << "Айди страницы введен неверно\n";
        return false;
    }
    if (std::atoi(id.c_str()) >= Pages.size()) {
        std::cout << "Такой страницы не существует\n";
        return false;
    }
    int i = std::atoi(id.c_str());
    std::cout << "id : " << i << "\nназвание: " << Pages[i].name << "\n";
    std::cout << "Ссылки на страницы: \n";
    std::map<int, std::string>::iterator it;

    for (it = Pages[i].link.begin(); it != Pages[i].link.end(); it++) {
        std::cout << "\t" << it->first << '(' << Pages[it->first].name << ')'
                  << " : " << it->second << '\n';
    }
    std::cout << "Текст:\n" << Pages[i].text;
    return true;
}

///Показать страницу по названию, если айди введен неверно на выходе выведет
///сообщение и вернет false. Если все хорошо, то вернет true
bool showByName(std::string name) {
    for (int i = 0; i < Pages.size(); i++) {
        if (Pages[i].name == name) {
            std::cout << "id : " << i << "\nназвание: " << Pages[i].name
                      << "\n";
            std::cout << "Ссылки на страницы: \n";
            std::map<int, std::string>::iterator it;

            for (it = Pages[i].link.begin(); it != Pages[i].link.end(); it++) {
                std::cout << "\t" << it->first << " : " << it->second << '\n';
            }
            std::cout << "Текст:\n" << Pages[i].text;
            break;
        }
    }
    return true;
}

///Добавляет путь из std::string from в std::string where, from и where это айди
///страниц с ответом std::string text
///Если text не указан, или айди указаны неверно, вернет false, иначе true
bool addway(std::string from, std::string where, std::string text) {
    if (from == "" || where == "" || text == "") {
        std::cout << "Для того чтобы добавить новый путь введите команду :\n";
        std::cout << "добавитьпуть -откуда <айди страницы из которой "
                     "будет данный путь> -куда <айди страницы куда "
                     "ведет этот путь> -ответ <ответ>\n";
        return false;
    }
    if (!(checkid(from) && checkid(where))) {
        std::cout << "Неправильно введеные id\nдобавитьпуть -откуда <айди "
                     "страницы из которой будет данный путь> -куда <айди "
                     "страницы куда ведет этот путь> -ответ <ответ>\n";
        return false;
    }
    int f = std::atoi(from.c_str());
    int w = std::atoi(where.c_str());
    if (f >= Pages.size()) {
        std::cout << "Страницы " << from << "не сущестует.\n";
    }
    if (w >= Pages.size()) {
        std::cout << "Страницы " << from << "не сущестует.\n";
    }
    if (f < Pages.size() && w < Pages.size()) {
        Pages[f].link[w] = text;
        std::cout << "добавлен путь из " << f << "(" << Pages[f].name << ")"
                  << " в " << w << "(" << Pages[w].name << ")\n";
    }
    return true;
}

///Создать новую страницу в Pages потом пользователю предложат ввести текст, в
///конце он должен написать "добавить"
///Если имя передано пустое, то вернет false и напишет сообщение, иначе вернет
///true
bool create(std::string name) {
    page p;

    if (name == "") {
        std::cout
            << "Для того чтобы добавить новую страницу введите команду :\n";
        std::cout << "создать -имя <название страницы>\n";
        return false;
    }

    std::cout << "Введите текст. В конце напишите \"добавить\"" << '\n';
    std::string text;
    std::string line = "";
    while (line != "добавить") {
        text += line + '\n';
        getline(std::cin, line, '\n');
    }
    p.name = name;
    p.text = text;

    Pages.push_back(p);

    std::cout << "Страница добавлена, номер страницы: " << Pages.size() - 1
              << '\n';
    return true;
}

///Показать все страницы в Pages, всегда позвращает true
bool showAll() {
    std::cout << "номер\tназвание" << '\n';
    for (int i = 0; i < Pages.size(); i++) {
        std::cout << i << '\t' << Pages[i].name << '\n';
    }
    return true;
}

///Открыть уже существующую новеллу
///Если такой новеллы не существует, то выведет ошибку и вернет false
bool open(std::string file) {
    if (file == "") {
        std::cout << "Для того чтобы открыть уже существующую новеллу "
                     "введите команду :\n";
        std::cout << "открыть -файл <название новеллы>\n";
        return false;
    }
    int i = 0;
    for(; i < novells.size(); i++){
        if(novells[i] == file){
            break;
        }
    }
    if (i == novells.size()){
        std::cout << "Новелла \"" << file << "\" не найдена";
        return false;
    }
    std::ifstream fin;
    fin.open(file + ".novell");
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
                Pages.push_back(p);
                p = page();
            }
            if (s != "]") {
                fin >> s;
            }
        }
    }
    return true;
}

///Удалить страницу
///На вход принимает айди в виде строки (std::string)
///Если айди указан неверно, то возвращает false
bool deletePage(std::string idstr) {
    std::vector<page> newTree;
    if (idstr == "") {
        std::cout << "Чтобы удалить страницу введите команду: \n";
        std::cout << "удалить -айди <айди страницы>\n";
        return false;
    }
    if (!checkid(idstr)) {
        std::cout << "Айди введен неверно \n";
        return false;
    }

    int id = std::atoi(idstr.c_str());
    if (id >= Pages.size() || id < 0) {
        std::cout << "Страницы с таким айди не существует\n";
        return false;
    }
    for (int i = 0; i < Pages.size(); i++) {
        if (i == id)
            continue;
        std::map<int, std::string>::iterator it;
        std::map<int, std::string> newlink;
        for (it = Pages[i].link.begin(); it != Pages[i].link.end(); it++) {
            int ilink = it->first;
            std::string linkstring = it->second;

            if (ilink > id) {
                newlink[ilink - 1] = linkstring;
            }
            if (ilink < id) {
                newlink[ilink] = linkstring;
            }
        }
        Pages[i].link = newlink;
        newTree.push_back(Pages[i]);
    }
    Pages.swap(newTree);
    std::cout << "Комната с id " << id
              << " была удалена, все id комнат с id выше " << id
              << " были снижены на 1\n";
    return true;
}


int main() {
    std::string f;
    cmd command;
    DIR *dir = opendir(".");
    std::cout << "Привет!\nСоздайте новую новеллу или загрузите старую для "
                 "измения\nСписок "
                 "установленных новелл: \n";
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
                std::cout <<"[*]" << n << '\n';
            }
        }
    } else {
        std::cout << "Ошибка открытия директории\n";
    }
    std::cout << "Чтобы открыть уже сохраненную новеллу введите \n \"открыть "
                 "-файл название\"\n";

    while (true) {
        command.getcommand();

        if (command.cmd == "сохранить") {
            f = command.param["-файл"];
            if (f == "") {
                std::cout << "Чтобы сохранить новеллу введите команду : \n "
                             "сохранить -файл <название>\n";
                continue;
            }
            break;
        }
        if (command.cmd == "создать") {
            create(command.param["-имя"]);
            continue;
        }
        if (command.cmd == "открыть") {
            std::string file = command.param["-файл"];
            open(file);
        }

        if (command.cmd == "добавитьпуть") {
            std::string from = command.param["-откуда"];
            std::string where = command.param["-куда"];
            std::string text = command.param["-ответ"];
            addway(from, where, text);
        }
        if (command.cmd == "показать") {
            if (command.param.find("-айди") == command.param.end() &&
                command.param.find("-название") == command.param.end()) {
                std::cout << "Для того чтобы посмотреть уже существующую "
                             "страницу введите команду :\n";
                std::cout << "показать -айди <айди страницы>\nили: \nпоказать "
                             "-название <название страницы>\n";
                continue;
            }

            if (command.param.find("-айди") != command.param.end()) {
                showByID(command.param["-айди"]);
            } else if (command.param.find("-название") != command.param.end()) {
                std::string name = command.param["-название"];
                showByName(name);
            }
        }
        if (command.cmd == "показатьвсе") {
            showAll();
        }

        if (command.cmd == "удалить") {
            deletePage(command.param["-айди"]);
        }
        command.clear();
    }

    std::ofstream fout;
    fout.open(f + ".novell");
    fout << "[\n";
    for (int i = 0; i < Pages.size(); i++) {
        fout << "(\n";
        fout << "name : \"" << Pages[i].name << "\""
             << "\n";
        fout << "text : \"" << Pages[i].text << "\""
             << "\n";

        fout << "{\n";
        std::map<int, std::string>::iterator it;
        for (it = Pages[i].link.begin(); it != Pages[i].link.end(); it++) {
            fout << it->first << " : \"" << it->second << "\"\n";
        }
        fout << "}\n";
        fout << ")\n";
    }

    fout << "]\n";
    fout.close();

    return 0;
}