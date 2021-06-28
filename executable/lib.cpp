#include "pages.hpp"
#include <string>
#include <cctype>
///Проверка айди, если айди содержит символы, то выводит false, но если все в
///порядке, то true
bool checkid(std::string id) {
    for (int i = 0; i < id.length(); i++)
        if (!std::isdigit(id[i]))
            return false;

    return true;
}