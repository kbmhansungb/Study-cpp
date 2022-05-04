#pragma once
#include <memory>
#include <list>
#include <string>
#include <algorithm>
#include <iostream>

struct Initialize;
class GameObject;
class ComponentConstructor;

struct Initialize
{
    GameObject* owner;

    Initialize() = delete;
    Initialize(const Initialize&) = delete;
    Initialize(Initialize&&) = delete;

    Initialize(GameObject* owner_game_object) :
        owner(owner_game_object)
    {}
};

class Component
{
private:
    Initialize* _begin;
public:
    __declspec(property(get = get_initialize)) Initialize* begin;
    inline const Initialize* get_initialize() { return _begin; }

public:
    Component() = default;
    virtual ~Component() = default;

    friend GameObject;
    friend ComponentConstructor;
};
class ComponentConstructor
{
    std::unique_ptr<Initialize> begin;
    Component* component;

public:
    ComponentConstructor() 
        : component(nullptr) 
    {}
    ~ComponentConstructor()
    {
        if (component != nullptr)
        {
            component->~Component();
            free(component);
        }
    }

    void make_begin(GameObject* owner)
    {
        begin = std::make_unique<Initialize>(owner);
    }
    template <typename Type, typename... Args
        , typename = typename std::enable_if<std::is_convertible<Type, Component>::value>::type
    >
    void make_component(Args&&... args)
    {
        Type* mptr = (Type*)malloc(sizeof(Type));
        mptr->_begin = begin.get();

        new(mptr) Type(std::forward<Args>(args)...);
        component = mptr;
    }
    friend GameObject;
};

class GameObject
{
public:
    std::string name;
    GameObject(const std::string& object_name) : name(object_name)
    {}

private:
    std::list<std::unique_ptr<ComponentConstructor>> child_components;
public:
    template <typename Type, typename... Args
        , typename = typename std::enable_if<std::is_convertible<Type, Component>::value>::type
    >
    Type* add_component(Args&&... args)
    {
        child_components.emplace_back();
        auto& elum = child_components.back();
        elum = std::make_unique<ComponentConstructor>();

        elum->make_begin(this);
        elum->make_component<Type>(std::forward<Args>(args)...);

        return static_cast<Type*>(elum->component);
    }
    void remove_component(Component* component)
    {
        auto it = std::find_if(child_components.begin(), child_components.end(),
            [component](const std::unique_ptr<ComponentConstructor>& child_component)
            {
                return child_component->component == component;
            });

        if (it != child_components.end())
            child_components.erase(it);
    }
};

// 새로운 컴포넌트를 선언하고 테스트 하는 부분이다.

class NewComponent : public Component
{
    NewComponent()
    {
        copy_owner_name = begin->owner->name;
    }
    friend ComponentConstructor;

public:
    std::string copy_owner_name; // It is example.
};

void test()
{
    {
        GameObject object("Game object");
        auto test_component = object.add_component<NewComponent>();

        std::cout << test_component->copy_owner_name << std::endl;
    }
}