// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABatteryMan::ABatteryMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // Setting size for collision capsule

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Character moves in the direction of input
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	// Rate at which the character rotates to face movement direction 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	//Jump settings
	GetCharacterMovement()->JumpZVelocity = 600.f; 
	//How much control the player has over the character when in air
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//Attach the camera boom to the root component
	CameraBoom->SetupAttachment(RootComponent);
	
	//How far away the camera is from the character
	CameraBoom->TargetArmLength = 300.0f;
	// Rotate the arm based on the controller
	CameraBoom->bUsePawnControlRotation = true; 

	//Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//Attach the follow camera to the end of the boom
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//Camera does not rotate relative to arm
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;
	Power = 100.0f;

}

// Called when the game starts or when spawned
void ABatteryMan::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABatteryMan::OnBeginOverlap); //Register the overlap event
	
	//Create and add the power widget to the viewport
	if (Player_Power_Widget_Class != nullptr) //Check if the widget class is set
	{
		Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class); //Create the widget
		Player_Power_Widget->AddToViewport(); //Add the widget to the viewport
	}
	
}

// Called every frame
void ABatteryMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Power -= DeltaTime * Power_Threshold; //Decrease power over time

	if (Power <= 0.0f) //If power is less than or equal to 0
	{
		if (!bDead)
		{
			bDead = true; //Set dead to true

			GetMesh()->SetSimulatePhysics(true); //Enable physics simulation on the mesh

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABatteryMan::RestartGame, 3.0f, false); //Restart the level after 3 seconds
		}
	}

}

// Called to bind functionality to input
void ABatteryMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Binds turn to the axis mapping
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput); 
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); //IE_Pressed binds jump to when the key is pressed
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); //IE_Released binds stop jumping to when the key is released

	PlayerInputComponent->BindAxis("MoveForward", this, &ABatteryMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatteryMan::MoveRight);

}

void ABatteryMan::MoveForward(float aixs)
{
	if (!bDead) //if not dead
	{
		//Move the character forward/backward

		//Find the forward direction
		const FRotator Rotation = Controller->GetControlRotation(); //Get the rotation of the controller
		const FRotator YawRotation(0, Rotation.Yaw, 0); 

		//calculate the forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 

		AddMovementInput(Direction, aixs);

	}
}
void ABatteryMan::MoveRight(float aixs)
{
	if (!bDead) //if not dead
	{
		//Move the character forward/backward

		//Find the forward direction
		const FRotator Rotation = Controller->GetControlRotation(); //Get the rotation of the controller
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//calculate the forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); //use Y instead of X

		AddMovementInput(Direction, aixs);

	}
}

void ABatteryMan::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false); //Restart the level
}

void ABatteryMan::OnBeginOverlap(class UPrimitiveComponent* HitComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Handle overlap event here

	if (OtherActor->ActorHasTag("Recharge"))
	{
		Power += 10.f; //Increase power by 10
		
		//Cap the power to 100
		if (Power >= 100.0f)
			Power = 100.0f;

		OtherActor->Destroy(); //Destroy the recharge actor
	}
}


