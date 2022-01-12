#ifndef EXPRL_CPP_STRINGUTILITIES_H
#define EXPRL_CPP_STRINGUTILITIES_H

#include <string>

namespace mythtitans::exprl::util {

    bool starts_with(const std::string& str, const std::string& prefix);

    bool ends_with(const std::string& str, const std::string& suffix);

    bool contains(const std::string& str, const std::string& content);

}

#endif //EXPRL_CPP_STRINGUTILITIES_H
