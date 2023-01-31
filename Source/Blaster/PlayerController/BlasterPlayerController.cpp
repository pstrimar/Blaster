// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerController.h"
#include "Blaster/HUD/BlasterHUD.h"
#include "Blaster/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blaster/Character/BlasterCharacter.h"

void ABlasterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    BlasterHUD = Cast<ABlasterHUD>(GetHUD());
}

void ABlasterPlayerController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(InPawn);
    if (BlasterCharacter)
    {
        SetHUDHealth(BlasterCharacter->GetHealth(), BlasterCharacter->GetMaxHealth());
        SetHUDDeathMessage("");
    }
}

void ABlasterPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

    bool bHUDValid = BlasterHUD && 
        BlasterHUD->CharacterOverlay && 
        BlasterHUD->CharacterOverlay->HealthBar && 
        BlasterHUD->CharacterOverlay->HealthText;
    if (bHUDValid)
    {
        const float HealthPercent = Health / MaxHealth;
        BlasterHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
        FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt32(Health), FMath::CeilToInt32(MaxHealth));
        BlasterHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
    }
}

void ABlasterPlayerController::SetHUDScore(float Score)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

    bool bHUDValid = BlasterHUD && 
        BlasterHUD->CharacterOverlay && 
        BlasterHUD->CharacterOverlay->ScoreAmount;

    if (bHUDValid)
    {
        FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt32(Score));
        BlasterHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
    }
}

void ABlasterPlayerController::SetHUDDefeats(int32 Defeats)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

    bool bHUDValid = BlasterHUD && 
        BlasterHUD->CharacterOverlay && 
        BlasterHUD->CharacterOverlay->DefeatsAmount;

    if (bHUDValid)
    {
        FString DefeatsText = FString::Printf(TEXT("%d"), Defeats);
        BlasterHUD->CharacterOverlay->DefeatsAmount->SetText(FText::FromString(DefeatsText));
    }
}

void ABlasterPlayerController::SetHUDDeathMessage(FString KillerName)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
    bool bHUDValid = BlasterHUD &&
        BlasterHUD->CharacterOverlay &&
        BlasterHUD->CharacterOverlay->KilledByText &&
        BlasterHUD->CharacterOverlay->KillerPlayerText;

    if (bHUDValid)
    {
        BlasterHUD->CharacterOverlay->KillerPlayerText->SetText(FText::FromString(KillerName));
        BlasterHUD->CharacterOverlay->KilledByText->SetVisibility(KillerName == "" ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
        BlasterHUD->CharacterOverlay->KillerPlayerText->SetVisibility(KillerName == "" ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
    }
}

void ABlasterPlayerController::SetHUDWeaponName(FString WeaponName)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
    bool bHUDValid = BlasterHUD &&
        BlasterHUD->CharacterOverlay &&
        BlasterHUD->CharacterOverlay->WeaponName;

    if (bHUDValid)
    {
        BlasterHUD->CharacterOverlay->WeaponName->SetText(FText::FromString(WeaponName));
    }
}

void ABlasterPlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

    bool bHUDValid = BlasterHUD && 
        BlasterHUD->CharacterOverlay && 
        BlasterHUD->CharacterOverlay->WeaponAmmoAmount;

    if (bHUDValid)
    {
        FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
        BlasterHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::FromString(AmmoText));
    }
}

void ABlasterPlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
    BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

    bool bHUDValid = BlasterHUD && 
        BlasterHUD->CharacterOverlay && 
        BlasterHUD->CharacterOverlay->CarriedAmmoAmount;

    if (bHUDValid)
    {
        FString AmmoText = FString::Printf(TEXT("%d"), Ammo);
        BlasterHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::FromString(AmmoText));
    }
}
