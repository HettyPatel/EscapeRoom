// Het Patel 2021

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//Check for physics handle component
	FindPhysicsHandle();
	SetupInputComponent();
	
}

void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent){
		UE_LOG(LogTemp, Warning, TEXT("Input Component Detected! %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this,&UGrabber::Release);
	}

}

void UGrabber::FindPhysicsHandle(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle){
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle is found!"));
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component is Found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Key Pressed!"));

	// Only ray cast if button is pressed and see if we reach.
	GetFirstPhysicsBodyInReach();

	//Try and reach any actors with collosion channel set. 
	
	//if we hit something than attach the physics handle

	//TODO attach a physics handle
}

void UGrabber::Release(){
	UE_LOG(LogTemp, Warning, TEXT("Key Released!"));
	//Releaase the physics handle.
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If Physics Handle is attached move the object we are holding.
	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{
	
	//Get Player's view point 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Logging out to Test
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	// Draw a line from player showing the reach

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	//Reachout from player! (Raycasting) out to a certain distance! (can change where they can reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	//See what the raycast is hitting! 

	AActor* ActorHit = Hit.GetActor();

	if(ActorHit){
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *ActorHit->GetName());
	}

	return Hit;

}

