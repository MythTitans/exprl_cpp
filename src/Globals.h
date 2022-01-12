#ifndef EXPRL_CPP_GLOBALS_H
#define EXPRL_CPP_GLOBALS_H

#include <string>

namespace mythtitans::exprl::globals {

    static constexpr auto NOT_EXPRESSION = "not";
    static constexpr auto AND_EXPRESSION = "and";
    static constexpr auto OR_EXPRESSION = "or";
    static constexpr auto ADD_EXPRESSION = "add";
    static constexpr auto SUB_EXPRESSION = "sub";
    static constexpr auto MUL_EXPRESSION = "mul";
    static constexpr auto DIV_EXPRESSION = "div";
    static constexpr auto MOD_EXPRESSION = "mod";
    static constexpr auto STARTS_EXPRESSION = "starts";
    static constexpr auto ENDS_EXPRESSION = "ends";
    static constexpr auto IN_EXPRESSION = "in";
    static constexpr auto SUBSTR_EXPRESSION = "substr";
    static constexpr auto SUBSTRL_EXPRESSION = "substrl";
    static constexpr auto LEN_EXPRESSION = "len";
    static constexpr auto EQ_EXPRESSION = "eq";
    static constexpr auto NEQ_EXPRESSION = "neq";
    static constexpr auto LT_EXPRESSION = "lt";
    static constexpr auto LTE_EXPRESSION = "lte";
    static constexpr auto GT_EXPRESSION = "gt";
    static constexpr auto GTE_EXPRESSION = "gte";
    static constexpr auto MIN_EXPRESSION = "min";
    static constexpr auto MAX_EXPRESSION = "max";
    static constexpr auto VAR_EXPRESSION = "var";
    static constexpr auto COND_EXPRESSION = "cond";
    static constexpr auto CONCAT_EXPRESSION = "concat";
    static constexpr auto DEBUG_EXPRESSION = "debug";

}

#endif //EXPRL_CPP_GLOBALS_H
