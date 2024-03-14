// Create startup game. All rights reserved.


#include "GameObjects/Placement/CSInteractableObject.h"

ACSInteractableObject::ACSInteractableObject()
{
	AnimationComponent = CreateDefaultSubobject<UCSAnimationComponent>("AnimationComponent");
}
