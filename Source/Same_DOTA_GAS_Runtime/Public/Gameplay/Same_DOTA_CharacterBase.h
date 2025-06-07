
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"

#include "GAS/Same_DOTA_AbilitySystemComponent.h"
#include "GAS/Same_DOTA_AttributeSet.h"

#include "Interface/Same_DOTA_TemplateInterface.h"
#include "Gameplay/Enum/BaseEnum.h"

#include "Components/DecalComponent.h"

#include "AIController.h"
#include "AIModule.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"

#include "Same_DOTA_CharacterBase.generated.h"


//自定义一个Unit的object检测通道
#define Unit ECC_GameTraceChannel1
//类前声明
//class AbilitySystemComponent;
//class AttributeSet;
class USame_DOTA_WidgetComponent;

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_CharacterBase : public ACharacter, public IAbilitySystemInterface,
	public ISame_DOTA_TemplateInterface
{
	GENERATED_BODY()

public:
	//网络复制功能必须实现的函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sets default values for this character's properties
	ASame_DOTA_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category = "Ai Controller Ref")
	TObjectPtr<AAIController> CharAiPC_Ref = nullptr;


public:

	virtual USame_DOTA_AbilitySystemComponent* GetAbilitySystemComponent() const override;
	USame_DOTA_AttributeSet* GetAttributeSet()const { return AttributeSet; }

	//给予角色技能
	void InitCharAbilities();
	//如果是玩家控制器或玩家状态控制的角色，还得实现以下两个函数
	/*virtual void PossessedBy(AController* NewController)override;只在服务器执行
	virtual void OnRep_PlayerState()override;*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<USame_DOTA_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<USame_DOTA_AttributeSet> AttributeSet;


public:
	
	FTimerHandle ApplyMinAttackIntervalHandle;
	
	//敌方目标攻击检测
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem Abilities")
	TObjectPtr<ASame_DOTA_CharacterBase> AttackTargetChar = nullptr;//指定的攻击目标

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem Abilities")
	TArray<TObjectPtr<ASame_DOTA_CharacterBase>> WithinRangeEnemies;//范围内的敌人
	
	//巡逻数据
	TArray<FVector> PartolLocationPoints;//巡逻点
	int LastIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Melee")
	void TryAttackAbility();

	UFUNCTION(BlueprintCallable, Category = "Melee Interval")
	void ApplyMinAttackInterval();

	UFUNCTION(BlueprintCallable, Category = "Try Melee Loop")
	void TryMeleeLoop();//普通攻击循环检测

	UFUNCTION(BlueprintCallable, Category = "Attack Move")
	void AttackMoveToActor(ASame_DOTA_CharacterBase* TargetActor);//移动到目标后攻击

	UFUNCTION(BlueprintCallable, Category = "Freedom Attack")
	void FreedomAttack();//自由攻击模式检测敌人

	UFUNCTION(BlueprintCallable, Category = "Freedom Attack")
	void PatrolMoveToPoint(int InIndex);//自由攻击模式检测敌人



	UFUNCTION()
	void HandleCharMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);//Ai Move委托


	//接口：基础移动
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void UnitMoveTo(FVector InLocation, AActor* HitActor);
	//重载IAbilitySystemInterface接口中的纯虚函数
	virtual void UnitMoveTo_Implementation(FVector InLocation, AActor* HitActor) override;
	//接口：攻击移动
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit AttackMove To")
	void UnitAttackMoveTo(FVector InLocation, bool bFreedomAttack);
	virtual void UnitAttackMoveTo_Implementation(FVector InLocation, bool bFreedomAttack) override;
	//接口：巡逻
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void UnitPatrol(const TArray<FVector>& InLocationPoints);
	virtual void UnitPatrol_Implementation(const TArray<FVector>& InLocationPoints) override;		
	//接口：释放节能
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void TryReleaseSkill(int InSkillIndex);
	virtual void TryReleaseSkill_Implementation(int InSkillIndex) override;
	//接口：获取插槽坐标
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	FVector GetSocketLocation(FName InSocketName);
	virtual FVector GetSocketLocation_Implementation(FName InSocketName) override;

public:
	//Death
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bDeath = false;//是否死亡

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bPlayingAnimationMontage = false;//是否在播放动作中

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bApplyingMeleeLoop = false;//是否在循环普通攻击中

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bAttackToActor = false;//强制攻击某个目标

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bFreedomAttacking = false;//是否开启自由攻击模式

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bFindNearestActor = false;//是否找到最近的敌人

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bMovingToNearestActor = false;//是否正在移动向敌人

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bPrePatrol = false;//巡逻

	void ReSetCharAllState();//重置角色所有状态

public:

	//TeamID and PlayerID
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "PC Team ID")
	ETeamID Char_TeamID = (ETeamID::None);

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "PC Team ID")
	EPlayerID Char_PlayerID = (EPlayerID::None);

	//在服务器上设置队伍和玩家ID
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable, Category = "PC Team ID Player ID")
	void Server_SetCharTeamIDandPlayerID(ETeamID InTeamID, EPlayerID InPlayerID);
	virtual bool Server_SetCharTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID);

	//角色技能等级
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable, Category = "Skills Level")
	void Server_UpSkillsLevel(int InSkillIndex, int InAddLevels);
	virtual bool Server_UpSkillsLevel_Validate(int InSkillIndex, int InAddLevels);

public:
	//Release Skill
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem Abilities")
	FGamepalyAbilityInfo GetAbilityInfoByClass(TSubclassOf<USame_DOTA_GameplayAbilityBase>Ability_Class,int InLevel);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem Abilities")
	void CharReleaseSkill(int Skill_Index);




	
	
public:
	//贴花组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Decal")
	UDecalComponent* Decal_SelectedRing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Decal")
	UMaterialInstanceDynamic* DynMaterialInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decal")
	FLinearColor SelfUnit_Color = FLinearColor(0.f, 0.5f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decal")
	FLinearColor FriendUnit_Color = FLinearColor(1.f, 0.7f, 0.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Decal")
	FLinearColor EnemyUnit_Color = FLinearColor(1.f, 0.f, 0.f, 1.f);
	

	UFUNCTION(BlueprintCallable, Category = "Decal")
	void SetSelectedRingMaterial();

	UFUNCTION(BlueprintCallable, Category = "Decal")
	void SetSelectedRingVisibility(bool bVisible);



//血条UI
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget Component")
	USame_DOTA_WidgetComponent* WidgetComponent;
	
};
