// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/TpsCharacter.h"

// Sets default values
ATpsCharacter::ATpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Setting the capsule size
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    
    // Setting movements rules
    // Allowing the character to rotate only around the Z (to use the root motion)
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;
    
    // Allow the character to rotate in the direction of the movement
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);
    
    // Setting the Jump Velocity and the control of the character when is in the air
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    // Setup the camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    // Allow the camera boom to rotate relative to the character
    CameraBoom->bUsePawnControlRotation = true;
    
    // Setup the camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    
    // Allow the camera to rotate relative to the Camera arm
    Camera->bUsePawnControlRotation = false;
    
    // Setup the Mesh
    
}

// Called when the game starts or when spawned
void ATpsCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

