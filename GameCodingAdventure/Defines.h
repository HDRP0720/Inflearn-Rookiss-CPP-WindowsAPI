#pragma once

#define DECLARE_SINGLETON(classname)   \
private:                            \
    classname() {}                  \
public:                             \
    static classname* GetInstance() \
    {                               \
        static classname s_instance;\
        return &s_instance;         \
    }

#define GET_SINGLETON(classname)   classname::GetInstance()