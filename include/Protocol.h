#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

class TableMode
{
public:
};

const enum struct DBActions {};

class TableProperties
{
};

constexpr int COMMIT = 0;
constexpr int READ_DISK = -1;
constexpr int TABLE_MODE_EDIT = 1;
constexpr int TABLE_MODE_CONST = 2;
constexpr int TABLE_MODE_RAM = 3;
constexpr int TABLE_MODE_HDD = 4;

constexpr int TABLE_ROW_MODE_RAM = 5;
constexpr int TABLE_ROW_MODE_HDD = 6;

constexpr int TABLE_REGISTER_SCHEMA = 99;

constexpr int TABLE_MODE_ADD = 100;
constexpr int TABLE_MODE_CHECK_DUP_ADD = 102;
//constexpr int TABLE_MODE_NO_CHECK_DUP_ADD	103

constexpr int TABLE_MODE_VIEW_ALL = 200;
constexpr int TABLE_MODE_VIEW_ONE = 201;

constexpr int TABLE_MODE_MODIFY_ALL = 300;
constexpr int TABLE_MODE_MODIFY_ONE = 301;

constexpr int TABLE_MODE_DELETE_ONE = 402;

constexpr int TABLE_PROP_NULL = 500;
constexpr int TABLE_PROP_NOT_NULL = 600;
constexpr int TABLE_UNIQUE = 700;

#endif