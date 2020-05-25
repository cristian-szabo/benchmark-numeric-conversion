#pragma once

#define EXPAND(ARG) (ARG)
#define CONCAT(ARG0, ARG1) (ARG0##ARG1)
#define STRING(ARG) (#ARG)
#define NAME(ARG) STRING(ARG)

#define VA_ARGS_SIZE_GET(E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, SIZE, ...) SIZE
#define VA_ARGS_SIZE(...) EXPAND(VA_ARGS_SIZE_GET(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define JOIN_PARAM1(OP, param) OP(0, param)
#define JOIN_PARAM2(OP, param, ...) OP(1, param), EXPAND(JOIN_PARAM1(OP, __VA_ARGS__))
#define JOIN_PARAM3(OP, param, ...) OP(2, param), EXPAND(JOIN_PARAM2(OP, __VA_ARGS__))
#define JOIN_PARAM4(OP, param, ...) OP(3, param), EXPAND(JOIN_PARAM3(OP, __VA_ARGS__))
#define JOIN_PARAM5(OP, param, ...) OP(4, param), EXPAND(JOIN_PARAM4(OP, __VA_ARGS__))
#define JOIN_PARAM6(OP, param, ...) OP(5, param), EXPAND(JOIN_PARAM5(OP, __VA_ARGS__))
#define JOIN_PARAM7(OP, param, ...) OP(6, param), EXPAND(JOIN_PARAM6(OP, __VA_ARGS__))
#define JOIN_PARAM8(OP, param, ...) OP(7, param), EXPAND(JOIN_PARAM7(OP, __VA_ARGS__))
#define JOIN_PARAM9(OP, param, ...) OP(8, param), EXPAND(JOIN_PARAM8(OP, __VA_ARGS__))
#define JOIN_PARAM10(OP, param, ...) OP(9, param), EXPAND(JOIN_PARAM9(OP, __VA_ARGS__))
#define JOIN_PARAM11(OP, param, ...) OP(10, param), EXPAND(JOIN_PARAM10(OP, __VA_ARGS__))
#define JOIN_PARAM12(OP, param, ...) OP(11, param), EXPAND(JOIN_PARAM11(OP, __VA_ARGS__))
#define JOIN_PARAM13(OP, param, ...) OP(12, param), EXPAND(JOIN_PARAM12(OP, __VA_ARGS__))
#define JOIN_PARAM14(OP, param, ...) OP(13, param), EXPAND(JOIN_PARAM13(OP, __VA_ARGS__))
#define JOIN_PARAM15(OP, param, ...) OP(14, param), EXPAND(JOIN_PARAM14(OP, __VA_ARGS__))
#define JOIN_PARAM16(OP, param, ...) OP(15, param), EXPAND(JOIN_PARAM15(OP, __VA_ARGS__))
#define JOIN_PARAM(OP, NUM, ...) CONCAT(JOIN_PARAM, NUM) EXPAND((OP, __VA_ARGS__))

#define MAKE_TYPE_PARAM(ID, NAME) typename T##ID
#define MAKE_ARG_PARAM(ID, NAME) const T##ID &NAME
#define MAKE_TYPE_PARAMS(...) EXPAND(JOIN_PARAM(MAKE_TYPE_PARAM, VA_ARGS_SIZE(__VA_ARGS__), __VA_ARGS__))
#define MAKE_ARG_PARAMS(...) EXPAND(JOIN_PARAM(MAKE_ARG_PARAM, VA_ARGS_SIZE(__VA_ARGS__), __VA_ARGS__))
