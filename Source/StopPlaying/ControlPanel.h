#pragma once

#include "StopPlaying.h"

#include "EnvironmentActor.h"
#include "ControlPanelButton.h"
#include "ControlPanelActorConnector.h"

#include "GameFramework/Actor.h"
#include "ControlPanel.generated.h"

UCLASS()
class STOPPLAYING_API AControlPanel : public AActor
{
	GENERATED_BODY()

public:	
	AControlPanel();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

    /**
     * Sets the appropriate panel title
     */
    void SetTitle();
    
    /**
     * Gets abstract active state
     */
    bool IsEffectActive(EControlPanelEffectType EffectType);

    /**
     * Sets abstract active state
     */
    void SetEffectActive(EControlPanelEffectType EffectType, float EffectScale, bool bNewState);

    /**
     * Sets the connected actor
     */
    void SetConnectedActor(AEnvironmentActor* NewActor);

private:
    AEnvironmentActor* ConnectedActor = nullptr;

    // These will be automatically assigned
    UTextRenderComponent* TitleComponent = nullptr;
    TArray<UControlPanelActorConnector*> ActorConnectors;
    TArray<UControlPanelButton*> Buttons;

    // Timed properties
    float UpdateWidgetsTimer = 0.f;
    
    /**
     * Initialises all widgets
     */
    void InitAllWidgets();

    /**
     * Updates all widgets
     */
    void UpdateAllWidgets();

    /**
     * Get gravity state
     */
    bool GetGravity();

    /**
     * Set gravity state
     */
    void SetGravity(bool bIsEnabled);
    
    /**
     * Get collision state
     */
    bool GetCollision();

    /**
     * Set collision state
     */
    void SetCollision(bool bIsEnabled);

    /**
     * Get world time state
     */
    bool GetWorldTime();

    /**
     * Set world time state
     */
    void SetWorldTime(bool bIsEnabled, float EffectScale);
    
    /**
     * Get world gravity state
     */
    bool GetWorldGravity();

    /**
     * Set world gravity state
     */
    void SetWorldGravity(bool bIsEnabled, float EffectScale);
   
    /**
     * Set translation state
     */
    void SetTranslation(bool bIsEnabled, float EffectScale);

    /**
     * Get translation state
     */
    bool GetTranslation();
    
    /**
     * Set rotation state
     */
    void SetRotation(bool bIsEnabled, float EffectScale);

    /**
     * Get rotation state
     */
    bool GetRotation();
    
    /**
     * Set scale state
     */
    void SetScale(bool bIsEnabled, float EffectScale);

    /**
     * Get scale state
     */
    bool GetScale();
    
    /**
     * Gets the mesh component of the connected actor
     */
    UMeshComponent* GetMeshComponent();

};
