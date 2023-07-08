#pragma once

UENUM(BlueprintType)
enum class ECharacterWorld : uint8
{
	ECW_Reality UMETA(DisplayName = "Reality"),
	ECW_Dream UMETA(DisplayName = "Dream")
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle"),
	ECS_Interacting UMETA(DisplayName = "Interacting"),
	ECS_Attacking UMETA(DisplayName = "Attacking"),
	ECS_HoldingItem UMETA(DisplayName = "HoldingItem"),
	ECS_HoldingInteractable UMETA(DisplayName = "HoldingInteractable"),
	ECS_Dead UMETA(DisplayName = "Dead"),
	ECS_HitReaction UMETA(DisplayName = "HitReaction")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "Hovering"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_None UMETA(DisplayName = "None"),
	EIS_Attached UMETA(DisplayName = "Attached")
};

enum class EPortalState : uint8
{
	EPS_Opened,
	EPS_Closed
};

UENUM(BlueprintType)
enum EDeathPose
{
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),

	EDP_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
};