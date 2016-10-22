#include "StopPlaying.h"
#include "ControlPanelActorConnector.h"

#include "ControlPanel.h"

void UControlPanelActorConnector::OnInteract(APawn* InteractingPawn)
{
    Super::OnInteract(InteractingPawn);

    AControlPanel* ParentControlPanel = Cast<AControlPanel>(GetOwner());

    if(!ParentControlPanel) { return; }
    
    ParentControlPanel->SetConnectedActor(ConnectedActor);
}

void UControlPanelActorConnector::Init()
{
    Super::Init();

    if(!ConnectedActor) { return; }
    if(!GetInteractiveActor()) { return; }

    UTextRenderComponent* TextRenderComponent = GetInteractiveActor()->FindComponentByClass<UTextRenderComponent>();

    if(!TextRenderComponent) { return; }

    TextRenderComponent->SetText(ConnectedActor->GetName());
}
