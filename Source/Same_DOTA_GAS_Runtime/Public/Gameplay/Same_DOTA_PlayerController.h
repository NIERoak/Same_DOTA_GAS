// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h" 
#include "GameFramework/PlayerController.h"
#include "Templates/SubclassOf.h"
#include "Gameplay/Same_DOTA_HUD.h"
#include "Gameplay/Same_DOTA_CameraPawn.h"

#include "EnhancedInputComponent.h"

#include "Gameplay/Enum/BaseEnum.h"

#include "Same_DOTA_PlayerController.generated.h"

//�Զ���һ��Unit��object���ͨ��
#define Unit ECC_GameTraceChannel1

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//���縴�ƹ��ܱ���ʵ�ֵĺ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ASame_DOTA_PlayerController();
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//����������
public:
	//��Ļ�滭�򲿷�	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	AActor* MouseHitActor;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,Category = "Mouse Drag")
	bool bOnMouseDrag;//�������Ƿ���
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector StartLocation;//��갴�µ�λ��
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector EndLocation;//����ɿ���λ��
		
	void GetMouseHitResultByChannal();

	//UI����
	UPROPERTY(BlueprintReadOnly, Category = "UMG Ref")
	TObjectPtr<ASame_DOTA_HUD> MyHUD_Ref;

	//��ѡ�еĵ�λ����
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Mouse Drag")
	TArray<TObjectPtr<AActor>> Selected_UnitsSelf;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	TObjectPtr<AActor> Selected_UnitFriend=nullptr;//ѡ�еĵ�һ���ѷ�Ŀ��
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	TObjectPtr<AActor> Selected_UnitEnemy=nullptr;//ѡ�еĵ�һ���з�Ŀ��
	//��ѡ��λ����
	UFUNCTION(BlueprintCallable, Category = "Mouse Drag")
	void SelectUnits();
		
	//TeamID and PlayerID
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char Team ID")
	ETeamID PC_TeamID=(ETeamID::None);

	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere, Category = "Char Player ID")
	EPlayerID PC_PlayerID=(EPlayerID::None);
	//�ڷ����������ö�������ID
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable, Category = "Char Team ID Player ID")
	void Server_SetPCTeamIDandPlayerID(ETeamID InTeamID, EPlayerID InPlayerID);
	virtual bool Server_SetPCTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID);


	//��Ļ�����ƽ�Ʋ���
	UPROPERTY(BlueprintReadOnly, Category = "Camera Pawn")
	TObjectPtr<ASame_DOTA_CameraPawn> MyCameraPawn_Ref;

	UFUNCTION(BlueprintPure, Category = "Camera Pawn Move")
	FVector MouseEdgeMove(float ScreenSizeRate, FVector HorizontalIncrease, FVector HorizontalDecreasing, FVector VerticalIncrease,FVector VerticalDecreasing);

	
	
public:
	//��ǰPC����ģʽ״̬
	
	//ǿ�����ɹ���ָ���
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPrFreedomAttacking = false;

	//Ѳ��
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPrePatrol = false;

	TArray<FVector> PatrolPoints;



	//ʩ��ָ���
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPreReleaseSkill = false;

	


	//��ǿ���벿��
public:

	virtual void SetupInputComponent() override;
		

	//�ڵ����λ�����ɵ���������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor_Attack;

	//��������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MouseLeftMappingContext;

	//������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetMouseLeftClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetMouseRightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReleaseSkill_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReleaseSkill_2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReleaseSkill_3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReleaseSkill_4;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnitFreedomAttackMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnitPatrolAction;


	//����ʱ��ͬʵ�������󶨵ľ��
	void OnMouseLeftClikInputStarted();
	void OnMouseLeftClikTriggered();
	void OnMouseLeftClikReleased();

	void OnMouseRightClikInputStarted();
	void OnMouseRightClikTriggered();
	void OnMouseRightClikReleased();

	void OnReleaseSkill_1Started();
	void OnReleaseSkill_2Started();
	void OnReleaseSkill_3Started();
	void OnReleaseSkill_4Started();

	void OnUnitFreedomAttackMoveStarted();
	
	void OnUnitPatrolStarted();
	void OnUnitPatrolReleased();
};
