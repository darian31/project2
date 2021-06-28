#include <string>
#include <map>
#include <vector>


///Страница
struct page{
    public:
        ///Название страницы
        std::string name;
        ///Текст страницы
        std::string text;
        ///Библиотека путей, ведущих из страницы
        std::map<int, std::string> link;

        page(std::string name_, std::string text_, std::map<int, std::string> link_) {
            name = name_;
            text = text_;
            link = link_;
        }
        page() {}
};

///Проверка айди, если айди содержит символы, то выводит false, но если все в
///порядке, то true
bool checkid(std::string id);
