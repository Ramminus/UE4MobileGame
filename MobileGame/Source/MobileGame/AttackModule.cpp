// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModule.h"
#include "HealthModule.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EquipmentModule.h"
#include "DrawDebugHelpers.h"
#include "Sword.h"
#include "Teamable.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UAttackModule::UAttackModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bHasAttacked = true;
	
	// ...
}




// Called when the game starts
void UAttackModule::BeginPlay()
{
	Super::BeginPlay();
	HealthModule = Cast<UHealthModule>(GetOwner()->GetComponentByClass(UHealthModule::StaticClass()));
	EquipmentModule = Cast<UEquipmentModule>(GetOwner()->GetComponentByClass(UEquipmentModule::StaticClass()));
	// ...
	
}

void UAttackModule::DoWeaponAttack(UWeapon* const Weapon)
{

	switch(Weapon->GetWeaponType())
	{
		
		case EWeaponTypes::Sword:
			DoWeaponAttack_Sword(Weapon);
			break;
		default:
			FString ErrorLog = TEXT("No Attack implementation for type - ");
			ErrorLog.Append(UEnum::GetValueAsString(Weapon->GetWeaponType()));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, ErrorLog);
		
	}
}

void UAttackModule::DoWeaponAttack_Sword(UWeapon* const Weapon)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	TArray<AActor*> HitActors;

	const FVector OwnerPosFixed = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0);
	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), Weapon->GetAttackRange(), 32, FColor::Red, true, 10);
	FString RangeMessage = FString::Printf(TEXT("The Range is %f"), Weapon->GetAttackRange());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, RangeMessage);

	const bool bOverlapped = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(), Weapon->GetAttackRange(), ObjectTypes, nullptr, ActorsToIgnore, HitActors);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, bOverlapped ? TEXT("true") : TEXT("false"));
	if (bOverlapped) {
		for (int i = 0; i < HitActors.Num(); i++)
		{


			if (HitActors[i]->GetClass()->ImplementsInterface(UTeamable::StaticClass())) {

				//Fix the enemies position;
				const FVector EnemyPosFixed = FVector(HitActors[i]->GetActorLocation().X, HitActors[i]->GetActorLocation().Y, 0);

				FVector EnemyToCharacter = (EnemyPosFixed - OwnerPosFixed);
				EnemyToCharacter.Normalize();
				const float AngleBetween = FMath::Acos(FVector::DotProduct(EnemyToCharacter, GetOwner()->GetActorForwardVector()));
				if (FMath::RadiansToDegrees(AngleBetween) <= Cast<USword>(Weapon)->GetAttackAngle()) {
					ITeamable::Execute_GetHealthModule(HitActors[i])->TakeDamage(Weapon->GetDamage(), ITeamable::Execute_GetTeam(HitActors[i]), Weapon->GetOwnerTeam());
				}
			}

		}
	}
}




// Called every frame
void UAttackModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackModule::OnAttack()
{

	FString role = StaticEnum<EWeaponTypes>()->GetValueAsString(GetOwnerRole());

	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		ServerOnAttack();
		
	}
	else if(GetOwnerRole() == ROLE_Authority)
	{
		if ((HealthModule == nullptr) || (HealthModule->IsDead) || EquipmentModule->GetEquipedWeapon() == nullptr)return;
		
		DoWeaponAttack(EquipmentModule->GetEquipedWeapon());
		
	}
	//if ((HealthModule == nullptr) || (HealthModule->IsDead) || EquipmentModule->CurrentWeapon.AttachedItemID == -1)return;

	//ITeamable* OwnerTeamable = Cast<ITeamable>(GetOwner());
	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	//TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Add(GetOwner());
	//TArray<AActor*> HitActors;
	//const FVector OwnerPosFixed = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0);
	//if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(), EquipmentModule->CurrentWeapon.AttackRange, ObjectTypes, nullptr, ActorsToIgnore, HitActors)) {
	//	for (int i = 0; i < HitActors.Num(); i++)
	//	{
	//		
	//	
	//		if (HitActors[i]->GetClass()->ImplementsInterface(UTeamable::StaticClass())) {

	//			//Fix the enemies position;
	//			const FVector EnemyPosFixed = FVector(HitActors[i]->GetActorLocation().X, HitActors[i]->GetActorLocation().Y, 0);
	//			
	//			FVector EnemyToCharacter = (EnemyPosFixed - OwnerPosFixed);
	//			EnemyToCharacter.Normalize();
	//			const float AngleBetween = FMath::Acos(FVector::DotProduct(EnemyToCharacter, GetOwner()->GetActorForwardVector()));
	//			if (FMath::RadiansToDegrees(AngleBetween) <= EquipmentModule->CurrentWeapon.AttackAngle) {
	//				ITeamable::Execute_GetHealthModule(HitActors[i])->TakeDamage(EquipmentModule->CurrentWeapon.Damage, ITeamable::Execute_GetTeam(HitActors[i]), ITeamable::Execute_GetTeam(GetOwner()));
	//			}
	//		}

	//	}
	//}
	//
	//else if(GetOwnerRole() == ROLE_Authority){
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Server is Attacking"));
	//}
}

void UAttackModule::StartAttack()
{
	//Client logic
	if(GetOwnerRole() == ROLE_AutonomousProxy)
	{
		//Request to start attack to the server.
		ServerOnStartAttack();
		
	}
	// Server logic
	else if(GetOwnerRole() == ROLE_Authority)
	{
		

		//Function to call on all clients.
		MultiCastOnStartAttack();
	}
}
void UAttackModule::ServerOnStartAttack_Implementation()
{
	StartAttack();
}


void UAttackModule::MultiCastOnStartAttack_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, EquipmentModule->GetEquipedWeapon()->GetMontage()->GetName());
	MontageMeshComponent->GetAnimInstance()->Montage_Play(EquipmentModule->GetEquipedWeapon()->GetMontage(), 1, EMontagePlayReturnType::Duration);
}
void UAttackModule::ServerOnAttack_Implementation()
{
	OnAttack();
}


