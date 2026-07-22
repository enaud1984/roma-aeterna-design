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
	int32 ActiveVariants = 0;
	FString Seeds;
	TArray<FString> MaterialSummaries;
	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<ARARomanProceduralBuildingActor> It(World); It; ++It)
		{
			++BuildingCount;
			GeneratedModules += It->GetGeneratedInstanceCount();
			LocalCategories += It->GetLocallyResolvedCategoryCount();
			FallbackCategories += It->GetFallbackCategoryCount();
			ActiveVariants += It->GetActiveMaterialVariantCount();
			if (MaterialSummaries.Num() < 3 && It->GetActiveMaterialVariantCount() > 0)
			{
				MaterialSummaries.Add(It->GetActiveMaterialSummary());
			}
			if (BuildingCount <= 5) Seeds += FString::Printf(TEXT("%s%d"), BuildingCount > 1 ? TEXT(", ") : TEXT(""), It->BuildingParameters.RandomSeed);
		}
	}
	const FString ViewMode = Character ? Character->GetViewModeDisplayName().ToString() : TEXT("Non disponibile");
	float Y = 32.0f;
	constexpr float X = 32.0f;

	DrawPrototypeLine(TEXT("ROMA AETERNA - CONSOLIDAMENTO VISUALE ROMANO"), X, Y, FLinearColor(0.93f, 0.75f, 0.32f));
	DrawPrototypeLine(FString::Printf(TEXT("Visuale: %s"), *ViewMode), X, Y, FLinearColor::White);
	DrawPrototypeLine(FString::Printf(TEXT("Edifici: %d  Moduli: %d"), BuildingCount, GeneratedModules), X, Y, FLinearColor::White);
	DrawPrototypeLine(FString::Printf(TEXT("Seed iniziali: %s"), *Seeds), X, Y, FLinearColor(0.72f, 0.78f, 0.84f));
	DrawPrototypeLine(TEXT("WASD  Movimento"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Mouse  Visuale"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Shift  Corsa"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Spazio  Salto"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("F1 HUD | F2 Label | F3 Bounds | F4 Interazioni"), X, Y, FLinearColor(0.72f, 0.78f, 0.84f));
	DrawPrototypeLine(TEXT("F5 Rigenera | F6 Utilities | F7 Asset locali | F9 Visuale"), X, Y, FLinearColor(0.72f, 0.78f, 0.84f));
	const bool bLocalActive = Character && Character->AreLocalAssetsEnabled() && URARomanVisualCatalog::IsLocalCatalogAvailable();
	DrawPrototypeLine(bLocalActive ? TEXT("LOCAL ASSETS ACTIVE") : TEXT("PLACEHOLDER FALLBACK ACTIVE"), X, Y,
		bLocalActive ? FLinearColor(0.35f, 0.95f, 0.45f) : FLinearColor(0.95f, 0.72f, 0.30f));
	DrawPrototypeLine(FString::Printf(TEXT("Materiali: categorie locali=%d fallback=%d varianti=%d"),
		LocalCategories, FallbackCategories, ActiveVariants), X, Y, FLinearColor(0.72f, 0.86f, 0.92f));
	if (MaterialSummaries.Num() > 0)
	{
		DrawPrototypeLine(FString::Printf(TEXT("Attivi: %s"), *FString::Join(MaterialSummaries, TEXT(" | "))),
			X, Y, FLinearColor(0.72f, 0.78f, 0.84f));
	}
	if (Character)
	{
		DrawPrototypeLine(FString::Printf(TEXT("Debug: label=%s bounds=%s interazioni=%s utilities=%s"),
			Character->AreBuildingLabelsVisible() ? TEXT("on") : TEXT("off"),
			Character->AreCollisionBoundsVisible() ? TEXT("on") : TEXT("off"),
			Character->AreInteractionPointsVisible() ? TEXT("on") : TEXT("off"),
			Character->AreUtilityNodesVisible() ? TEXT("on") : TEXT("off")), X, Y, FLinearColor(0.60f, 0.85f, 0.65f));
	}
}

void ARATechnicalHUD::DrawPrototypeLine(const FString& Text, const float X, float& Y, const FLinearColor& Color) const
{
	Canvas->SetDrawColor(Color.ToFColor(true));
	Canvas->DrawText(GEngine->GetSmallFont(), Text, X, Y, 1.0f, 1.0f);
	Y += 20.0f;
}
