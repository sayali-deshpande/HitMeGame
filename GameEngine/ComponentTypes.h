#ifndef _COMPONENTTYPES_H
#define _COMPONENTTYPES_H
#include <iostream>

typedef enum ComponentTypes
{
	CT_PositionComponent,
	CT_SpriteComponent,
	CT_PhysicsComponent,
	CT_COMPONENT_MAX,
}ComponentTypes;

typedef enum ObjectTypes
{
	OT_Player,
	OT_StaticPlayer,
	OT_Bullet,
	OT_Enemy,
	OT_ENDDOOR,
	OT_DIAMOND,
	OT_MAX,
}ObjectTypes;

#endif