/*
How this ECS from tutorial works: 
Manager class holds entities, which are objects drawn on screen.
Each entity has components, which give it functionality. 
Each component has it's own class, so templates and lambdas are required in order to get and add components
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//forward declare classes
class Component;
class Entity;
class Manager;

//Component ID is size_t;
using ComponentID = std::size_t;

//Group
using Group = std::size_t;

//inline function (quicker than standard one) used to be expanded wherever we use it, rather then calling it
inline ComponentID getNewComponentTypeID() {

	//functions rememebers the lastID, because of the static, so first time it will be 1, next the ID's will just be incremented
	static ComponentID lastID = 0u;
	return lastID++;
};

// to allow us to have templetaized IDs, which means positions ID will be always 1, physics could always be 2 etc.
template <typename T> inline ComponentID getComponentTypeID() noexcept {

	static ComponentID typeID = getNewComponentTypeID();

	return typeID;
}


//Max number of components entity is able to hold:
constexpr std::size_t maxComponents = 32;
//Max number of groups:
constexpr std::size_t maxGroups = 32;

//Bitset for groups:
using GroupBitSet = std::bitset <maxGroups>;


//ComponentBitSet allows us to check if entity has got a selection of components, by comparing its bitset to the signature of a entity.
using ComponentBitSet = std::bitset <maxComponents>;
//ComponentArray is array of compomnent pointers of the size of our maxComponents 
using ComponentArray = std::array <Component*, maxComponents>;
//STD array syntax: std::array< type of variable, array size> name;

class Component {

public:
	Entity* entity;

	//Virtual functions to be overriden
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
	//Virtual Destructor
	virtual ~Component() {};
};

class Entity {

	Manager& manager;
	bool active = 1;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:

	//Constructor, manager member is set to mManager
	Entity(Manager& mManager) : manager(mManager) {

	}

	//Check if entity has a group
	bool hasGroup(Group mGroup) {

		return groupBitSet[mGroup];
	}

	//add to a group
	void addGroup(Group mGroup);

	//delete from a group
	void delGroup(Group mGroup) {

		groupBitSet[mGroup] = false;
	}

	void Update() {

		//go through whole components vector and call the methods
		for (auto& c : components) {
			c->Update();

		}
	}

	void Draw() {

		for (auto& c : components) {
			c->Draw();
		}
	}
	//function returning bool active:

	bool isActive() const {

		return active;
	}
	//remove inactive components
	void Destroy() {

		active = 0;
	}
	//check if entity has a componnent. 
	//The const member functions are the functions which are declared as constant in the program and objects called by them cannot be modified.
	template <typename T> bool hasComponnent() const {

		return componentBitSet[getComponentTypeID<T>()];
	}

	//add component to entity
	template <typename T, typename... TArgs> 
	T& addComponent(TArgs&&...mArgs) {

		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		//unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		//our TypeID = c, when we add the component it will always be in the same position in the array
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		//call init function
		c->Init();

		//return c address
		return *c;
	}

	//get commponent from the type
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
	
	//vector holding pointers to entites
	std::vector<std::unique_ptr<Entity>> entities;
	//array holding groupped entites
	std::array<std::vector <Entity*>, maxGroups> grouppedEntites;

public:

	//update all entities at once (it just calls the Update() for each different object in a vector.
	void Update() {

		for (auto& e : entities) e->Update();
	}

	//draw entities
	void Draw() {

		for (auto& e : entities) e->Draw();
	}
	//remove entities not visible on screen 
	void Refresh() {

		//remove entities from groups
		for (auto i(0u); i < maxGroups; i++) {

			auto& v(grouppedEntites[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity) {

				return !mEntity->isActive() || !mEntity->hasGroup(i);
				}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity) {

			return !mEntity->isActive();

			}), std::end(entities));
	}

	//Add entity m to group m
	void addtoGroup(Entity *mEntity, Group mGroup) {

		grouppedEntites[mGroup].emplace_back(mEntity);
	}

	//get entities list
	std::vector <Entity*>& getGroup(Group mGroup) {

		return grouppedEntites[mGroup];
	}

	//add entity to the world through this menager class

	Entity& addEntity() {

		Entity* e=new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

};