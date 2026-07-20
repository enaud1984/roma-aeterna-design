#include "RomaAeterna.h"

#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogRomaAeterna);

class FRomaAeternaModule final : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override
	{
		UE_LOG(LogRomaAeterna, Log, TEXT("Roma Aeterna runtime module initialized."));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogRomaAeterna, Log, TEXT("Roma Aeterna runtime module shut down."));
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FRomaAeternaModule, RomaAeterna, "RomaAeterna");
