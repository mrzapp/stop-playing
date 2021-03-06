#include "StopPlaying.h"
#include "InteractiveActor.h"

// Sets default values
AInteractiveActor::AInteractiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

    UMeshComponent* MeshComponent = FindComponentByClass<UMeshComponent>();

    if(!MeshComponent) {
        UE_LOG(LogTemp, Error, TEXT("%s doesn't have a UMeshComponent!"), *GetName());
        return;
    }

    bInitialGravity = MeshComponent->IsGravityEnabled();
}

void AInteractiveActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    FVector Position = GetActorLocation();

    if(
        Position.X < -ResetThreshold || Position.X > ResetThreshold ||
        Position.Y < -ResetThreshold || Position.Y > ResetThreshold ||
        Position.Z < -ResetThreshold || Position.Z > ResetThreshold
    )
    {
        Reset();
    }
}

void AInteractiveActor::Interact(APawn* InteractingPawn)
{
    OnInteraction.Broadcast(InteractingPawn);
}

void AInteractiveActor::BeginReset()
{
    OnBeginReset.Broadcast();

    bResetting = true;
}

void AInteractiveActor::Reset()
{
    Super::Reset();
    
    FVector Zero;

    UMeshComponent* MeshComponent = FindComponentByClass<UMeshComponent>();

    if(!MeshComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("%s does not have a UMeshComponent"), *GetName());
        return;
    }
   
    MeshComponent->SetPhysicsLinearVelocity(Zero);
    MeshComponent->SetPhysicsAngularVelocity(Zero);
    MeshComponent->SetEnableGravity(bInitialGravity);

    UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetRootComponent());
    
    if(!PrimitiveComponent) { return; }
    
    PrimitiveComponent->SetMassScale(NAME_None, 1.f);
    
    bResetting = false;
}

