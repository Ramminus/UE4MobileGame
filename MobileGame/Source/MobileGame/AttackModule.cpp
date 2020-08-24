// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModule.h"
#include "HealthModule.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EquipmentModule.h"
#include <MobileGame\Teamable.h>


// Sets default values for this component's properties
UAttackModule::UAttackModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
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


// Called every frame
void UAttackModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackModule::OnAttack()
{
	if ((HealthModule == nullptr) || (HealthModule->IsDead) || EquipmentModule->CurrentWeapon.AttachedItemID == -1)return;

	ITeamable* OwnerTeamable = Cast<ITeamable>(GetOwner());
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	TArray<AActor*> HitActors;
	const FVector OwnerPosFixed = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0);
	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(), 500, ObjectTypes, nullptr, ActorsToIgnore, HitActors)) {
		for (int i = 0; i < HitActors.Num(); i++)
		{
			
		
			if (HitActors[i]->GetClass()->ImplementsInterface(UTeamable::StaticClass())) {

				//Fix the enemies position;
				const FVector EnemyPosFixed = FVector(HitActors[i]->GetActorLocation().X, HitActors[i]->GetActorLocation().Y, 0);
				
				FVector EnemyToCharacter = (EnemyPosFixed - OwnerPosFixed);
				EnemyToCharacter.Normalize();
				const float AngleBetween = FMath::Acos(FVector::DotProduct(EnemyToCharacter, GetOwner()->GetActorForwardVector()));
				if (FMath::RadiansToDegrees(AngleBetween) <= EquipmentModule->CurrentWeapon.AttackAngle) {
					ITeamable::Execute_GetHealthModule(HitActors[i])->TakeDamage(EquipmentModule->CurrentWeapon.Damage, ITeamable::Execute_GetTeam(HitActors[i]), ITeamable::Execute_GetTeam(GetOwner()));
				}
			}

		}
	}
}


