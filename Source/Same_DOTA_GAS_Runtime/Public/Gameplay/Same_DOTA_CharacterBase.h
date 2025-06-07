
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


//�Զ���һ��Unit��object���ͨ��
#define Unit ECC_GameTraceChannel1
//��ǰ����
//class AbilitySystemComponent;
//class AttributeSet;
class USame_DOTA_WidgetComponent;

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_CharacterBase : public ACharacter, public IAbilitySystemInterface,
	public ISame_DOTA_TemplateInterface
{
	GENERATED_BODY()

public:
	//���縴�ƹ��ܱ���ʵ�ֵĺ���
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

	//�����ɫ����
	void InitCharAbilities();
	//�������ҿ����������״̬���ƵĽ�ɫ������ʵ��������������
	/*virtual void PossessedBy(AController* NewController)override;ֻ�ڷ�����ִ��
	virtual void OnRep_PlayerState()override;*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<USame_DOTA_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<USame_DOTA_AttributeSet> AttributeSet;


public:
	
	FTimerHandle ApplyMinAttackIntervalHandle;
	
	//�з�Ŀ�깥�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem Abilities")
	TObjectPtr<ASame_DOTA_CharacterBase> AttackTargetChar = nullptr;//ָ���Ĺ���Ŀ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem Abilities")
	TArray<TObjectPtr<ASame_DOTA_CharacterBase>> WithinRangeEnemies;//��Χ�ڵĵ���
	
	//Ѳ������
	TArray<FVector> PartolLocationPoints;//Ѳ�ߵ�
	int LastIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Melee")
	void TryAttackAbility();

	UFUNCTION(BlueprintCallable, Category = "Melee Interval")
	void ApplyMinAttackInterval();

	UFUNCTION(BlueprintCallable, Category = "Try Melee Loop")
	void TryMeleeLoop();//��ͨ����ѭ�����

	UFUNCTION(BlueprintCallable, Category = "Attack Move")
	void AttackMoveToActor(ASame_DOTA_CharacterBase* TargetActor);//�ƶ���Ŀ��󹥻�

	UFUNCTION(BlueprintCallable, Category = "Freedom Attack")
	void FreedomAttack();//���ɹ���ģʽ������

	UFUNCTION(BlueprintCallable, Category = "Freedom Attack")
	void PatrolMoveToPoint(int InIndex);//���ɹ���ģʽ������



	UFUNCTION()
	void HandleCharMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);//Ai Moveί��


	//�ӿڣ������ƶ�
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void UnitMoveTo(FVector InLocation, AActor* HitActor);
	//����IAbilitySystemInterface�ӿ��еĴ��麯��
	virtual void UnitMoveTo_Implementation(FVector InLocation, AActor* HitActor) override;
	//�ӿڣ������ƶ�
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit AttackMove To")
	void UnitAttackMoveTo(FVector InLocation, bool bFreedomAttack);
	virtual void UnitAttackMoveTo_Implementation(FVector InLocation, bool bFreedomAttack) override;
	//�ӿڣ�Ѳ��
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void UnitPatrol(const TArray<FVector>& InLocationPoints);
	virtual void UnitPatrol_Implementation(const TArray<FVector>& InLocationPoints) override;		
	//�ӿڣ��ͷŽ���
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void TryReleaseSkill(int InSkillIndex);
	virtual void TryReleaseSkill_Implementation(int InSkillIndex) override;
	//�ӿڣ���ȡ�������
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	FVector GetSocketLocation(FName InSocketName);
	virtual FVector GetSocketLocation_Implementation(FName InSocketName) override;

public:
	//Death
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bDeath = false;//�Ƿ�����

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bPlayingAnimationMontage = false;//�Ƿ��ڲ��Ŷ�����

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bApplyingMeleeLoop = false;//�Ƿ���ѭ����ͨ������

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bAttackToActor = false;//ǿ�ƹ���ĳ��Ŀ��

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bFreedomAttacking = false;//�Ƿ������ɹ���ģʽ

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bFindNearestActor = false;//�Ƿ��ҵ�����ĵ���

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bMovingToNearestActor = false;//�Ƿ������ƶ������

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char State")
	bool bPrePatrol = false;//Ѳ��

	void ReSetCharAllState();//���ý�ɫ����״̬

public:

	//TeamID and PlayerID
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "PC Team ID")
	ETeamID Char_TeamID = (ETeamID::None);

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "PC Team ID")
	EPlayerID Char_PlayerID = (EPlayerID::None);

	//�ڷ����������ö�������ID
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable, Category = "PC Team ID Player ID")
	void Server_SetCharTeamIDandPlayerID(ETeamID InTeamID, EPlayerID InPlayerID);
	virtual bool Server_SetCharTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID);

	//��ɫ���ܵȼ�
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
	//�������
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



//Ѫ��UI
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget Component")
	USame_DOTA_WidgetComponent* WidgetComponent;
	
};
