#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Entity;
class Component;
class Manager;

using ComponentId = std::size_t;
using Group = std::size_t;

// autoincrement id to give unique id to each component
inline ComponentId getNewComponentTypeId()
{
    static ComponentId lastId = 0u; // zero unsigned
    return lastId++;
}

// unique id per type ??
template <typename T> inline ComponentId getComponentTypeId() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "");
    static ComponentId typeId = getNewComponentTypeId();
    return typeId;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

// make sure entities have the components we need ???
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity
{

private:
    bool active = true;
    // a vector is an array which we don't know size
    std::vector<std::unique_ptr<Component>> components;

    Manager& manager;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager& mManager) : manager(mManager) {}

    void update()
    {
        for (auto& c : components)
            c->update();
    }

    void draw()
    {
        for (auto& c : components)
            c->draw();
    }

    bool isActive() const
    {
        return active;
    }
    void destroy()
    {
        active = false;
    }

    // tell true or false if is has a type component attached
    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeId<T>()];
    }

    // wtf is that syntax wtf is cpp ??
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));

        // ???
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeId<T>()] = c;
        componentBitSet[getComponentTypeId<T>()] = true;

        c->init();

        return *c;
    }

    // TODO this is buggy and crash
    template <typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }

    bool hasGroup(Group mGroup)
    {
        return componentBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

};


class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    void update()
    {
        for (auto& e : entities)
            e->update();
    }
    void draw()
    {
        for (auto &e : entities)
            e->draw();
    }
    void refresh()
    {
        for (auto i(0u); i < maxGroups; i++)
        {
            auto& v(groupedEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
                               {
                                   return !mEntity->isActive() || !mEntity->hasGroup(i);
                               })        ,
                               std::end(v)
                );
        }
        // removes entities that aren't active
        entities.erase(
            std::remove_if(
                std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
        std::end(entities));


    }

    void AddToGroup(Entity* mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    Entity& addEntity() //create and return a managed entity (pointer to?)
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

#endif // ECS_H

