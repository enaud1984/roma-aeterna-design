#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RATechnicalHUD.generated.h"

UCLASS()
class ROMAAETERNA_API ARATechnicalHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawPrototypeLine(const FString& Text, float X, float& Y, const FLinearColor& Color) const;
};
