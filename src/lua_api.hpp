#pragma once
#include <lua.hpp>
// std
#include <string>
// local
#include "util.hpp"

// Simple wrapper class around lua C api to load Brepviewer functions and types
class Lua {
private:
    // Private member Lua::L to track state
    lua_State* L;
public:
    ///@brief Load Lua file & create new Lua state
    ///@param lua_dir The root lua module directory
    ///@param lua_path The file path relative to lua_dir
    Lua(std::string lua_dir, std::string lua_path);
    // Delete copy constructor
    Lua(const Lua&) = delete;
    // Free Lua state
    ~Lua();
    // Generic lua value type
    class Value {
    private:
        int m_type;
        size_t m_size;
        void* m_value;
    public:
        // returns type id, i.e. LUA_TNUMBER
        inline int type() const {return m_type;}
        inline bool exists() const {
            if (m_type == LUA_TNONE)
                return false;
            else
                return true;
        }
        std::string to_string();
        bool to_bool();
        int to_int();
        float to_float();
    };
    // Creates a table on the registry
    // returns it's key (void*) in the registry
    void* new_table();
    // Creates a C++ closure from a lambda and assigns it to a lua global
    void add_closure(std::string name, auto func);
    // Assigns a Lua global to a C++ function
    void add_function(std::string name, lua_CFunction func);
    // Set Lua global
    template<typename T>
    void set_global(std::string name);
    // Sets fields in a table, will optionally create it if it doesn't exist
    void set_field();
    // Gets a lua global
    // returns false if it couldn't be found
    bool get_global(std::string name);
    // Gets a field in a table
    // returns false if it couldn't be found
    bool get_field();
};
