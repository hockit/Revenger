
#include "MAttributeComponent.h"

UMAttributeComponent::UMAttributeComponent()
{
	Health = 100.f;
}


bool UMAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChange.Broadcast(nullptr, this, Health, Delta);
	return true;
}
