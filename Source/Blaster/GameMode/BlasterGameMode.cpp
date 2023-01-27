// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterGameMode.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter *ElimmedCharacter, ABlasterPlayerController *VictimController, ABlasterPlayerController *AttackerController)
{
    if (ElimmedCharacter)
    {
        ElimmedCharacter->Elim();
    }
}

void ABlasterGameMode::RequestRespawn(ACharacter *ElimmedCharacter, AController *ElimmedController)
{
    if (ElimmedCharacter)
    {
        ElimmedCharacter->Reset();
        ElimmedCharacter->Destroy();
    }
    if (ElimmedController)
    {
        TArray<AActor*> PlayerStarts;
        TArray<AActor*> Players;
        UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
        UGameplayStatics::GetAllActorsOfClass(this, ABlasterCharacter::StaticClass(), Players);

        float MaxDistance = 0.f;
        AActor* FarthestPlayerStart = PlayerStarts[0];
        for (AActor* Player : Players)
        {
            for (AActor* PlayerStart : PlayerStarts)
            {
                float Distance = (Player->GetActorLocation() - PlayerStart->GetActorLocation()).Size();
                if (Distance > MaxDistance)
                {
                    MaxDistance = Distance;
                    FarthestPlayerStart = PlayerStart;
                }
            }            
        }
        
        
        RestartPlayerAtPlayerStart(ElimmedController, FarthestPlayerStart);
    }
}
