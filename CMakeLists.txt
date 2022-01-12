cmake_minimum_required(VERSION 3.16.3)
project(exprl_cpp)

enable_testing()

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else ()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_library(exprl_cpp OBJECT
        src/ExpressionEvaluator.h
        src/Globals.h
        src/eval/Context.cpp src/eval/include/Context.h
        src/eval/EvaluationException.cpp src/eval/include/EvaluationException.h
        src/eval/Expression.cpp src/eval/include/Expression.h
        src/eval/Variable.cpp src/eval/include/Variable.h
        src/eval/impl/AddExpression.cpp src/eval/impl/include/AddExpression.h
        src/eval/impl/AndExpression.cpp src/eval/impl/include/AndExpression.h
        src/eval/impl/ConcatExpression.cpp src/eval/impl/include/ConcatExpression.h
        src/eval/impl/CondExpression.cpp src/eval/impl/include/CondExpression.h
        src/eval/impl/DebugExpression.cpp src/eval/impl/include/DebugExpression.h
        src/eval/impl/DivExpression.cpp src/eval/impl/include/DivExpression.h
        src/eval/impl/EndsExpression.cpp src/eval/impl/include/EndsExpression.h
        src/eval/impl/EqExpression.cpp src/eval/impl/include/EqExpression.h
        src/eval/impl/GteExpression.cpp src/eval/impl/include/GteExpression.h
        src/eval/impl/GtExpression.cpp src/eval/impl/include/GtExpression.h
        src/eval/impl/InExpression.cpp src/eval/impl/include/InExpression.h
        src/eval/impl/LenExpression.cpp src/eval/impl/include/LenExpression.h
        src/eval/impl/LiteralExpression.cpp src/eval/impl/include/LiteralExpression.h
        src/eval/impl/LteExpression.cpp src/eval/impl/include/LteExpression.h
        src/eval/impl/LtExpression.cpp src/eval/impl/include/LtExpression.h
        src/eval/impl/MaxExpression.cpp src/eval/impl/include/MaxExpression.h
        src/eval/impl/MinExpression.cpp src/eval/impl/include/MinExpression.h
        src/eval/impl/ModExpression.cpp src/eval/impl/include/ModExpression.h
        src/eval/impl/MulExpression.cpp src/eval/impl/include/MulExpression.h
        src/eval/impl/NeqExpression.cpp src/eval/impl/include/NeqExpression.h
        src/eval/impl/NotExpression.cpp src/eval/impl/include/NotExpression.h
        src/eval/impl/OrExpression.cpp src/eval/impl/include/OrExpression.h
        src/eval/impl/StartsExpression.cpp src/eval/impl/include/StartsExpression.h
        src/eval/impl/SubExpression.cpp src/eval/impl/include/SubExpression.h
        src/eval/impl/SubstrExpression.cpp src/eval/impl/include/SubstrExpression.h
        src/eval/impl/SubstrlExpression.cpp src/eval/impl/include/SubstrlExpression.h
        src/eval/impl/VarExpression.cpp src/eval/impl/include/VarExpression.h
        src/parser/Parser.cpp src/parser/include/Parser.h
        src/util/StringUtilities.cpp src/util/include/StringUtilities.h)

add_executable(tests test/Doctest.cpp test/ExpressionEvaluatorTest.cpp test/eval/ExpressionTest.cpp test/parser/ParserTest.cpp $<TARGET_OBJECTS:exprl_cpp>)

target_link_libraries(tests PRIVATE Threads::Threads)
