#pragma once

#include "CoreMinimal.h"
#include "World/Modular/RARomanModularTypes.h"
#include "RARomanDecorationTypes.generated.h"

UENUM(BlueprintType)
enum class ERARomanRoomDecorType : uint8
{
	None, PlainService, PopularDomestic, MediumDomestic, WealthyDomestic, Commercial, Productive,
	ThermalCold, ThermalWarm, ThermalHot, ReligiousSimple, PublicSimple, Courtyard, Garden, Storage
};

UENUM(BlueprintType)
enum class ERAPompeianDecorativeStyle : uint8
{
	FirstStyleInspired, SecondStyleInspired, ThirdStyleInspired, FourthStyleInspired, PlainPlaster, ServicePlaster
};

UENUM(BlueprintType)
enum class ERARomanFloorDecorationType : uint8
{
	OpusSigninum, GeometricMosaic, SimplePolychromeMosaic, OpusSectileInspired,
	BrickFloor, StoneFloor, PackedEarth, ProductiveFloor, ThermalFloor
};

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanDecorationPalette
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName PaletteId = TEXT("PompeianTechnical");
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor BaseColor = FLinearColor(0.55f, 0.13f, 0.08f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor AccentColor = FLinearColor(0.68f, 0.42f, 0.12f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor BorderColor = FLinearColor(0.10f, 0.09f, 0.08f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Saturation = 0.75f;
};

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanPaintedPanelDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName PanelId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D OffsetCm = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector2D SizeCm = FVector2D(120.f, 140.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bFigurativePlaceholder = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> Tags;
};

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanWallZoneDefinition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ZoneId = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float StartHeightCm = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float HeightCm = 60.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FLinearColor Color = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct ROMAAETERNA_API FRARomanWallDecorationProfile
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) ERAPompeianDecorativeStyle Style = ERAPompeianDecorativeStyle::PlainPlaster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FRARomanDecorationPalette Palette;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FRARomanWallZoneDefinition> Zones;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FRARomanPaintedPanelDefinition> Panels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Seed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Conservation = 0.65f;
};
