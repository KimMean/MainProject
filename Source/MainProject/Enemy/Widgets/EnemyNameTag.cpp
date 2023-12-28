#include "Enemy/Widgets/EnemyNameTag.h"

#include "Components/TextBlock.h"

#include "Utilities/DebugLog.h"

void UEnemyNameTag::SetNameTag(FText InName)
{
	NameTag->SetText(InName);
}
