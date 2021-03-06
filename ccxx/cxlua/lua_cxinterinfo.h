#ifndef LUA_CXINTERINFO_H
#define LUA_CXINTERINFO_H

#include "lua_base.h"

class GM_CCXX_LUA_API CxLuaInterInfo
{
protected:
    std::string tableNameImpl();

    std::map<std::string, fn_int_lua_t> tableMethodsImpl();

};

#endif // LUA_CXINTERINFO_H
