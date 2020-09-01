// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Teamable.h"
#include "EnemyBase.h"

void USword::OnAttack(UWorld* WorldContext,  AActor* AttackerActor)
{
	//Object type filters for Sphere Actor Ovelap.
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	//Ignore Attacker
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AttackerActor);
	//Hit actors array.
	TArray<AActor*> HitActors;
	//Fixed Attacker Actor Position to check on HitActors positions
	const FVector OwnerPosFixed = FVector(AttackerActor->GetActorLocation().X, AttackerActor->GetActorLocation().Y, 0);
	const bool bOverlapped = UKismetSystemLibrary::SphereOverlapActors(WorldContext, AttackerActor->GetActorLocation(), GetAttackRange(), ObjectTypes, nullptr, ActorsToIgnore, HitActors);

	if (bOverlapped) {
		//Hit Actors Loop
		for (int i = 0; i < HitActors.Num(); i++)
		{

			//Check if it is Implementing the UTeamable Interface.
			if (HitActors[i]->GetClass()->ImplementsInterface(UTeamable::StaticClass())) {

				//Fix the enemies position;
				const FVector EnemyPosFixed = FVector(HitActors[i]->GetActorLocation().X, HitActors[i]->GetActorLocation().Y, 0);
				//Vector From the Character to the enemy.
				FVector CharacterToEnemy = (EnemyPosFixed - OwnerPosFixed);
				CharacterToEnemy.Normalize();

				//Get the angle between the Hit Actor and the attacker in the X Y Plane
				const float AngleBetween = FMath::Acos(FVector::DotProduct(CharacterToEnemy, AttackerActor->GetActorForwardVector()));
				//Damage the hit actor if it is within the swords attack angle.
				if (FMath::RadiansToDegrees(AngleBetween) <= GetAttackAngle()) {
					
					ITeamable::Execute_GetHealthModule(HitActors[i])->TakeDamage(GetDamage(), ITeamable::Execute_GetTeam(HitActors[i]), GetOwnerTeam());
				}
			}

		}
	}
}
