#if WITH_DEV_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "World/Modular/RARomanConstructionValidator.h"
#include "World/Modular/RARomanProceduralBuildingActor.h"
#include "Engine/World.h"
#include <limits>
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRARomanModularFoundationTest,"RomaAeterna.ModularFoundation.Core.LOCAL_UNREAL_TEST_REQUIRED",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRARomanModularFoundationTest::RunTest(const FString& Parameters){
 FRARomanBuildingParameters P; TestEqual(TEXT("Default building"),P.BuildingType,ERARomanBuildingType::SimpleHouse); TestTrue(TEXT("Default dimensions"),P.WidthCm>0&&P.DepthCm>0);
 FRARomanBuildingParameters N=P; N.WidthCm=-1; N.BayCount=0; N=URARomanBuildingRuleLibrary::NormalizeBuildingParameters(N); TestTrue(TEXT("Normalization"),N.WidthCm>0&&N.BayCount>0);
 TestEqual(TEXT("Bay width"),URARomanBuildingRuleLibrary::CalculateBayWidth(P),200.f);
 FTransform T=URARomanBuildingRuleLibrary::CalculateGridAlignedTransform(FVector(123,177,0),FRotator(0,44,0),FVector(1,1,1),50,90); TestEqual(TEXT("Grid X"),T.GetLocation().X,100.0);
 FRARomanGenerationResult A=URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(P); FRARomanGenerationResult B=URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(P); TestEqual(TEXT("Determinism"),A.GeneratedPlacements.Num(),B.GeneratedPlacements.Num()); TestTrue(TEXT("Simple house"),A.bSuccess&&A.GeneratedPlacements.Num()>0);
 P.BuildingType=ERARomanBuildingType::Taberna; TestTrue(TEXT("Taberna"),URARomanBuildingRuleLibrary::BuildTabernaLayout(P).GeneratedPlacements.Num()>0);
 P.BuildingType=ERARomanBuildingType::Temple; P.ArchitecturalOrder=ERARomanArchitecturalOrder::Doric; TestTrue(TEXT("Temple"),URARomanBuildingRuleLibrary::BuildTempleLayout(P).GeneratedPlacements.Num()>0);
 P.BuildingType=ERARomanBuildingType::StreetSection; TestTrue(TEXT("Street"),URARomanBuildingRuleLibrary::BuildStreetSectionLayout(P).GeneratedPlacements.Num()>0);
 TArray<FRARomanGenerationMessage> W,E; P.WidthCm=-10; URARomanConstructionValidator::ValidateParameters(P,W,E); TestTrue(TEXT("Negative rejected"),E.Num()>0); E.Empty(); P.WidthCm=std::numeric_limits<float>::infinity(); URARomanConstructionValidator::ValidateParameters(P,W,E); TestTrue(TEXT("Non finite rejected"),E.Num()>0);
 URARomanModuleCatalog* C=NewObject<URARomanModuleCatalog>(); FRARomanModuleDefinition M; M.ModuleId="dup"; C->Modules.Add(M); C->Modules.Add(M); E.Empty(); C->ValidateCatalog(W,E); TestTrue(TEXT("Duplicate IDs"),E.Num()>0);
 TArray<FName> Tags; TestTrue(TEXT("Compatible module"),URARomanBuildingRuleLibrary::IsModuleCompatible(M,FRARomanBuildingParameters(),Tags)); TArray<FRARomanModuleDefinition> Sel=URARomanBuildingRuleLibrary::SelectCompatibleModules(nullptr,FRARomanBuildingParameters(),ERARomanModuleCategory::Wall,Tags,W); TestEqual(TEXT("Null catalog safe"),Sel.Num(),0);
 FRARomanGenerationResult R=URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(FRARomanBuildingParameters()); for(const auto& Pm:R.GeneratedPlacements){TestTrue(TEXT("Finite transform"),Pm.Transform.GetLocation().ContainsNaN()==false);} FRARomanBuildingParameters Low; Low.MaximumModuleCount=1; TestFalse(TEXT("MaximumModuleCount respected"),URARomanBuildingRuleLibrary::BuildSimpleHouseLayout(Low).bSuccess); return true; }
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRAProceduralBuildingActorRuntimeTest,"RomaAeterna.ModularFoundation.ProceduralBuildingActor.LOCAL_UNREAL_TEST_REQUIRED",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRAProceduralBuildingActorRuntimeTest::RunTest(const FString& Parameters){
 UWorld* World=UWorld::CreateWorld(EWorldType::Game,false); TestNotNull(TEXT("World test creato"),World); if(!World){return false;}
 ARARomanProceduralBuildingActor* Actor=World->SpawnActor<ARARomanProceduralBuildingActor>(); TestNotNull(TEXT("Actor procedurale creato"),Actor); if(!Actor){World->DestroyWorld(false); return false;}
 Actor->BuildingParameters.BuildingType=ERARomanBuildingType::SimpleHouse; const bool bGenerated=Actor->GenerateBuilding(); TestTrue(TEXT("GenerateBuilding casa"),bGenerated); TestTrue(TEXT("Istanze generate"),Actor->GetGeneratedInstanceCount()>0); const int32 FirstCount=Actor->GetGeneratedInstanceCount(); TestTrue(TEXT("Categoria muri presente"),Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Wall)>0);
 Actor->ClearGeneratedBuilding(); TestEqual(TEXT("ClearGeneratedBuilding azzera istanze"),Actor->GetGeneratedInstanceCount(),0);
 Actor->GenerateBuilding(); TestEqual(TEXT("Seconda generazione senza accumulo"),Actor->GetGeneratedInstanceCount(),FirstCount);
 Actor->BuildingParameters.BuildingType=ERARomanBuildingType::Taberna; Actor->GenerateBuilding(); TestTrue(TEXT("Taberna contiene prop"),Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Prop)>0);
 Actor->BuildingParameters.BuildingType=ERARomanBuildingType::Temple; Actor->BuildingParameters.ArchitecturalOrder=ERARomanArchitecturalOrder::Doric; Actor->GenerateBuilding(); TestTrue(TEXT("Tempio contiene podio"),Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Podium)>0);
 Actor->BuildingParameters.BuildingType=ERARomanBuildingType::StreetSection; Actor->GenerateBuilding(); TestTrue(TEXT("Strada contiene pavimenti"),Actor->GetInstanceCountByCategory(ERARomanModuleCategory::Floor)>0);
 Actor->BuildingParameters.MaximumModuleCount=1; TestFalse(TEXT("MaximumModuleCount blocca generazione"),Actor->GenerateBuilding());
 Actor->ModuleCatalog.Reset(); Actor->BuildingParameters=FRARomanBuildingParameters(); TestTrue(TEXT("Catalogo nullo non causa crash"),Actor->GenerateBuilding());
 World->DestroyWorld(false); return true; }

#endif
