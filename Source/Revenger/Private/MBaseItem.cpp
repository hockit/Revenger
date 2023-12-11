
#include "MBaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MCharacter.h"

// Sets default values
AMBaseItem::AMBaseItem()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
    RootComponent = SphereComp;

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
    StaticMeshComp->SetupAttachment(RootComponent);

    
}

void AMBaseItem::Interact_Implementation(APawn* InstigatorPawn)
{
    // Implementation in derived classes
}