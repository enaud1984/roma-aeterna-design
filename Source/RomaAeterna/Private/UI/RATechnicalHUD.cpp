#include "UI/RATechnicalHUD.h"

#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Player/RACharacter.h"

void ARATechnicalHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !GEngine)
	{
		return;
	}

	const ARACharacter* Character = GetOwningPawn() ? Cast<ARACharacter>(GetOwningPawn()) : nullptr;
	const FString ViewMode = Character ? Character->GetViewModeDisplayName().ToString() : TEXT("Non disponibile");
	float Y = 32.0f;
	constexpr float X = 32.0f;

	DrawPrototypeLine(TEXT("ROMA AETERNA - HUD PROTOTIPO TECNICO"), X, Y, FLinearColor(0.93f, 0.75f, 0.32f));
	DrawPrototypeLine(FString::Printf(TEXT("Visuale: %s"), *ViewMode), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("WASD  Movimento"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Mouse  Visuale"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Shift  Corsa"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("Spazio  Salto"), X, Y, FLinearColor::White);
	DrawPrototypeLine(TEXT("F9  Prima / terza persona"), X, Y, FLinearColor::White);
}

void ARATechnicalHUD::DrawPrototypeLine(const FString& Text, const float X, float& Y, const FLinearColor& Color) const
{
	Canvas->SetDrawColor(Color.ToFColor(true));
	Canvas->DrawText(GEngine->GetSmallFont(), Text, X, Y, 1.0f, 1.0f);
	Y += 20.0f;
}
