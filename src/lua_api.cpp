#include "lua_api.hpp"

Lua::Lua(std::string lua_dir, std::string lua_path) {
    L=luaL_newstate();
    // load lua std libr
    luaL_openlibs(L);
    // setup package search paths
    std::string lua_src =
        "package.path=package.path..';" + getDirectory(lua_path) + "/?.lua'\n" +
        "package.path=package.path..';" + getDirectory(lua_path) + "/?/init.lua'\n";
    luaL_dostring(L, lua_src.c_str());
};
Lua::~Lua() {
    lua_close(L);
};
