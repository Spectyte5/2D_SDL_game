#include "Entity_component_sys.h"

void Entity::addGroup(Group mGroup) {

	groupBitSet[mGroup] = true;

	manager.addtoGroup(this,mGroup);
}
