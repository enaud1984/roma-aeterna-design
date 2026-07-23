#include "UI/RATechnicalHUD.h"

#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Player/RACharacter.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "World/Modular/RARomanVisualCatalog.h"

void ARATechnicalHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !GEngine)
	{
		return;
	}

	const ARACharacter* Character = GetOwningPawn() ? Cast<ARACharacter>(GetOwningPawn()) : nullptr;
	if (Character && !Character->IsTechnicalHudVisible())
	{
		return;
	}
	int32 BuildingCount = 0;
	int32 GeneratedModules = 0;
	int32 LocalCategories = 0;
	int32 FallbackCategories = 0;
	FString Seeds;
	const ARARomanProceduralBuildingActor* NearestAccessible = nullptr;
	double NearestDistanceSquared = TNumericLimits<double>::Max();
	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
		{
			++BuildingCount;
			GeneratedModules += It->GetGeneratedInstanceCount();
			LocalCategories += It->GetLocalMaterialBindingCount();
			FallbackCategories += It->GetFallbackMaterialBindingCount();
			if (BuildingCount <= 5) Seeds += FString::Printf(TEXT("%s%d"), BuildingCount > 1 ? TEXT(", ") : TEXT(""), It->BuildingParameters.RandomSeed);
			if (Character && It->IsAccessibleInteriorArchetype())
			{
				const double DistanceSquared = FVector::DistSquared(Character->GetActorLocation(), It->GetActorLocation());
				if (DistanceSquared < NearestDistanceSquared) { NearestDistanceSquared = DistanceSquared; NearestAccessible = *It; }
			}
		}
	}
	const FString ViewMode = Character ? Character->GetViewModeDisplayName().ToString() : TEXT("Non disponibile");
	float Y = 32.0f;
	constexpr float X = 32.0f;

	DrawPrototypeLine(TEXT("ROMA AETERNA - CONSOLIDAMENTO VISUALE ROMANO"), X, Y, FLinearColor(0.93f, 0.75f, 0.32f));
	DrawPrototypeLine(FString::Printf(TEXT("%s | Edifici %d | Moduli %d | Seed %s"), *ViewMode, BuildingCount, GeneratedModules, *Seeds), X, Y, FLinearColor::White);
	const bool bLocalActive = Character && Character->AreLocalAssetsEnabled() && URARomanVisualCatalog::IsLocalCatalogAvailable();
	DrawPrototypeLine(bLocalActive ? TEXT("MATERIALI LOCALI ATTIVI") : TEXT("MATERIALI FALLBACK ATTIVI"), X, Y,
		bLocalActive ? FLinearColor(0.35f, 0.95f, 0.45f) : FLinearColor(0.95f, 0.72f, 0.30f));
	DrawPrototypeLine(FString::Printf(TEXT("Binding locali %d | fallback %d | tetti %s | decorazioni %s"),
		LocalCategories, FallbackCategories,
		Character && Character->AreAccessibleRoofsVisible() ? TEXT("visibili") : TEXT("nascosti"),
		Character && Character->AreDecorationsEnabled() ? TEXT("attive") : TEXT("disattive")),
		X, Y, FLinearColor(0.72f, 0.86f, 0.92f));
	DrawPrototypeLine(TEXT("WASD/Mouse | Shift | Spazio | E accesso | F1 nasconde HUD"), X, Y, FLinearColor(0.82f, 0.84f, 0.86f));
	DrawPrototypeLine(TEXT("F5 rebuild | F7 materiali | F9 camera | F10 tetti | F11 decorazioni"), X, Y, FLinearColor(0.72f, 0.78f, 0.84f));
	if (Character)
	{
		const FString Message = Character->GetActiveTechnicalMessage();
		if (!Message.IsEmpty())
		{
			DrawPrototypeLine(Message, X, Y, FLinearColor(1.0f, 0.78f, 0.18f));
		}
		if (NearestAccessible)
		{
			DrawPrototypeLine(FString::Printf(TEXT("Vicino: %s | stanza=%s | %s"),
				*NearestAccessible->GetName(), *NearestAccessible->CurrentRoomName.ToString(),
				*NearestAccessible->GetDecorationSummary()), X, Y, FLinearColor(0.92f, 0.70f, 0.42f));
		}
	}
}

void ARATechnicalHUD::DrawPrototypeLine(const FString& Text, const float X, float& Y, const FLinearColor& Color) const
{
	Canvas->SetDrawColor(Color.ToFColor(true));
	Canvas->DrawText(GEngine->GetSmallFont(), Text, X, Y, 1.0f, 1.0f);
	Y += 20.0f;
}
