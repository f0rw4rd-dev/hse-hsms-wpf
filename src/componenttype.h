#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <string>

struct DBComponentType
{
    DBComponentType() {};
    DBComponentType(int id, std::string name) : id(id), name(name) {};

    int id;
    std::string name;
};

class ComponentType
{
public:
    ComponentType();
};

#endif // COMPONENTTYPE_H
