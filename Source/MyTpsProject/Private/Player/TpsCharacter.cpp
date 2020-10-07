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
    bUseControllerRotationPitch = false; // Y axis
    bUseControllerRotationYaw = true; // Z axis
    bUseControllerRotationRoll = false; // X axis
    
    // Allow the character to rotate a bit in the direction of the movement
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);
    
    // Setting the Jump Velocity and the control of the character when is in the air
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.2f;

    GetCharacterMovement()->MaxWalkSpeed = 550.0f;
    
    // Setup the camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 70.0f, 0.0f);
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->bEnableCameraRotationLag = true;
    CameraBoom->CameraLagSpeed = 10.0f;
    CameraBoom->CameraRotationLagSpeed = 10.0f;
    CameraBoom->CameraLagMaxDistance = 10.0f;

    // Allow the camera boom to rotate relative to the character
    CameraBoom->bUsePawnControlRotation = true;
    
    // Setup the camera
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    
    // Allow the camera to rotate relative to the Camera arm
    Camera->bUsePawnControlRotation = false;
    
    // Setup the Mesh
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> PlayerSkeletalMesh(TEXT("/Game/Character/Player/Mesh/SK_Mannequin.SK_Mannequin"));

    // If The mesh is found then use it 
    if (PlayerSkeletalMesh.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(PlayerSkeletalMesh.Object);
        GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
        GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
        GetMesh()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    }

    bSprinting = false;
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

    // Binding input to character movements
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATpsCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATpsCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

// Used to handle Forward/back movement
void ATpsCharacter::MoveForward(float Axis)
{
    // Update animation movement data
    InputX = Axis;
    UpdateAnimationMovementData();


    // Get the Character's Yaw rotation
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

    // Calculate the forward direction
    const FVector DirectionVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    // Add the movement
    AddMovementInput(DirectionVector, Axis);

}

// Used to handle right/left movement
void ATpsCharacter::MoveRight(float Axis)
{
    // Update animation movement data
    InputY = Axis;
    UpdateAnimationMovementData();


    // Get the Character's Yaw rotation
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

    // Calculate the forward direction
    const FVector DirectionVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // Add the movement
    AddMovementInput(DirectionVector, Axis);
}

void ATpsCharacter::UpdateAnimationMovementData()
{
    /*
    * MATHEMATICS USED FOR ANIMATION
    */

    // Calculate Rotation delta between Camera and Capsule rotation when using camera lag 
    // in order to get the mouse rotation
    const FRotator CameraRotation = Camera->GetComponentRotation();
    const FRotator CapsuleRotation = GetCapsuleComponent()->GetComponentRotation();

    const FRotator CameraCapsuleDelta = FRotator::MakeFromEuler(CameraRotation.Euler() - CapsuleRotation.Euler());


    // Calculate the Rotation delta between the input rotation and the mouse rotation to get the direction rotation
    const FVector InputVector(InputX, InputY, 0.0f);
    const FRotator InputRotation = InputVector.Rotation();

    const FRotator Delta = FRotator::MakeFromEuler(CameraCapsuleDelta.Euler() - InputRotation.Euler());

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Direction : %f"), Delta.Yaw));
        GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Yellow, FString::Printf(TEXT("Input X : %f"), InputX));
        GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Yellow, FString::Printf(TEXT("Input Y : %f"), InputY));
    }

    // Update Direction
    Direction = Delta.Yaw;

}


