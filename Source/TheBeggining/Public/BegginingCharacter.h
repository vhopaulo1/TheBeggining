// Bacon Mug - 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BegginingCharacter.generated.h"


UCLASS()
class THEBEGGINING_API ABegginingCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* CameraComponent;

public:
	// Sets default values for this character's properties
	ABegginingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
