#include "RapidEditor.h"
#include "UnrealEdGlobals.h"
#include "AI/Common/PatrolVisualizer.h"
#include "Components/SphereComponent.h"
#include "Editor/UnrealEdEngine.h"

#define LOCTEXT_NAMESPACE "FRapidEditorModule"

void FRapidEditorModule::StartupModule()
{
	//const TSharedPtr<FPatrolVisualizer> PatrolVisualizer = MakeShareable(new FPatrolVisualizer());

	//GUnrealEd->RegisterComponentVisualizer(USphereComponent::StaticClass()->GetFName(), PatrolVisualizer);
}

void FRapidEditorModule::ShutdownModule()
{
	//GUnrealEd->UnregisterComponentVisualizer(USphereComponent::StaticClass()->GetFName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRapidEditorModule, RapidEditor)
