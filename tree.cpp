#include <string>
#include <map>
#include <vector>

struct page{
    public:
        std::string name;
        std::string text;
        std::map<int, std::string> link;
        page(std::string name_, std::string text_, std::map<int, std::string> link_) {
            name = name_;
            text = text_;
            link = link_;
        }
        page() {}

};