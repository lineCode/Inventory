// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Component/HBItemContainerComponent.h"
#include "UI/HBItemContainerWidget.h"
#include "Blueprint/WidgetTree.h"


//////////////////////////////////////////////////////////////////////////
// AInventoryCharacter

AInventoryCharacter::AInventoryCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	// Create a ItemContainerComponent
	Inventory = CreateDefaultSubobject<UHBItemContainerComponent>(TEXT("ItemContainerComponent"));

	Inventory2 = CreateDefaultSubobject<UHBItemContainerComponent>(TEXT("ItemContainerComponent2"));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	//MainWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(GetController()), MainWidgetClass);

	InitInventory();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AInventoryCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AInventoryCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AInventoryCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AInventoryCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AInventoryCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AInventoryCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AInventoryCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AInventoryCharacter::OnResetVR);
}

void AInventoryCharacter::InitInventory()
{
	if (Inventory)
	{
		//MainWidget->GetChildren();

		Inventory->SetContainerSize(FIntPoint(10, 5));
		UHBItemContainerWidget* InventoryWidget = CreateWidget<UHBItemContainerWidget>(Cast<APlayerController>(GetController()), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->InitContainer(Inventory);
		InventoryWidget->SetPositionInViewport(FVector2D(0, 30));

		Inventory->OnItemAdded.AddDynamic(InventoryWidget, &UHBItemContainerWidget::OnItemAdded);
		Inventory->OnItemDeleted.AddDynamic(InventoryWidget, &UHBItemContainerWidget::OnItemDeleted);
		Inventory->OnItemCountChanged.AddDynamic(InventoryWidget, &UHBItemContainerWidget::OnCountChanged);



		Inventory2->SetContainerSize(FIntPoint(5, 5));
		UHBItemContainerWidget* InventoryWidget2 = CreateWidget<UHBItemContainerWidget>(Cast<APlayerController>(GetController()), InventoryWidgetClass);
		InventoryWidget2->AddToViewport();
		InventoryWidget2->InitContainer(Inventory2);
		InventoryWidget2->SetPositionInViewport(FVector2D(500, 30));

		Inventory2->OnItemAdded.AddDynamic(InventoryWidget2, &UHBItemContainerWidget::OnItemAdded);
		Inventory2->OnItemDeleted.AddDynamic(InventoryWidget2, &UHBItemContainerWidget::OnItemDeleted);
		Inventory2->OnItemCountChanged.AddDynamic(InventoryWidget2, &UHBItemContainerWidget::OnCountChanged);

		//FInputModeGameAndUI Mode;
		//Mode.SetLockMouseToViewport(true);
		//Mode.SetHideCursorDuringCapture(false);
		//SetInputMode(Mode);
		//UserInterface->AddToViewport(9999); // Z-order, this just makes it render on the very top.
	}
	
}

void AInventoryCharacter::PickUpItem(FPickableItemData PickableItemData)
{
	//UHBItemObject* NewItemObject = NewObject<UHBItemObject>(Inventory, UHBItemObject::StaticClass());
	//
	////AddedItems.Add(NewItemObject);

	//NewItemObject->SetItemData();

	//UE_LOG(LogTemp, Warning, TEXT("PickUpItem %s"), *Name.ToString());

	if (PickableItemData.Data)
	{
		//Inventory->AddItem(PickableItemData);
	}

	
}

void AInventoryCharacter::PickUpItemWithDef(TSubclassOf<UHBInventoryItemDefinition> ItemDefination, int32 Count)
{
	Inventory->AddItemDef(ItemDefination, Count);

}


void AInventoryCharacter::OnResetVR()
{
	// If Inventory is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Inventory.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AInventoryCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AInventoryCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AInventoryCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AInventoryCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AInventoryCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AInventoryCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
