// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

#include "TpsCharacter.generated.h"

UCLASS()
class MYTPSPROJECT_API ATpsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATpsCharacter();
    
    // Camera components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* Camera;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bSprinting;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float InputX;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float InputY;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float Direction;
    
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Axis);

    void MoveRight(float Axis);

private:

    // Set the animation data from movement
    void UpdateAnimationMovementData();


};
