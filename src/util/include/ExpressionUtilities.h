#ifndef EXPRL_CPP_EXPRESSIONUTILITIES_H
#define EXPRL_CPP_EXPRESSIONUTILITIES_H

#include <unordered_set>
#include <vector>
#include <memory>

#include "../../eval/include/Expression.h"

namespace mythtitans::exprl::util {

    std::unordered_set<std::string>
    getLiteralVariables(const std::vector<std::shared_ptr<eval::Expression>>& expressions);

    template<class ... ExpressionType>
    std::unordered_set<std::string> getLiteralVariables(std::shared_ptr<ExpressionType> ... expressions) {
        return getLiteralVariables(std::vector{std::move(expressions)...});
    }

}

#endif //EXPRL_CPP_EXPRESSIONUTILITIES_H
