// Bacon Mug - 2020


#include "BegginingCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABegginingCharacter::ABegginingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpringArmComponent->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void ABegginingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABegginingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABegginingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABegginingCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABegginingCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABegginingCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABegginingCharacter::LookUp);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ABegginingCharacter::OnStartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ABegginingCharacter::OnStopJump);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &ABegginingCharacter::OnInteract);
	PlayerInputComponent->BindAction(TEXT("Hook"), EInputEvent::IE_Pressed, this, &ABegginingCharacter::OnHook);
	PlayerInputComponent->BindAction(TEXT("UseItem"), EInputEvent::IE_Pressed, this, &ABegginingCharacter::OnUseItem);

}

void ABegginingCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABegginingCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABegginingCharacter::Turn(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABegginingCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABegginingCharacter::OnStartJump()
{
	bPressedJump = true;
}

void ABegginingCharacter::OnStopJump()
{
	bPressedJump = false;
}

void ABegginingCharacter::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Interagiu!"));
}

void ABegginingCharacter::OnHook()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Ativou Hook!"));
}

void ABegginingCharacter::OnUseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Silver, TEXT("Usou o item"));
}