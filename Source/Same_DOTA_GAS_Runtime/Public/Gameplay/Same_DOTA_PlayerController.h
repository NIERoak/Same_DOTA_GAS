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

//自定义一个Unit的object检测通道
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

	//网络复制功能必须实现的函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ASame_DOTA_PlayerController();
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//鼠标操作部分
public:
	//屏幕绘画框部分	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	AActor* MouseHitActor;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,Category = "Mouse Drag")
	bool bOnMouseDrag;//鼠标左键是否按下
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector StartLocation;//鼠标按下的位置
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	FVector EndLocation;//鼠标松开的位置
		
	void GetMouseHitResultByChannal();

	//UI部分
	UPROPERTY(BlueprintReadOnly, Category = "UMG Ref")
	TObjectPtr<ASame_DOTA_HUD> MyHUD_Ref;

	//框选中的单位数组
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,  Category = "Mouse Drag")
	TArray<TObjectPtr<AActor>> Selected_UnitsSelf;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	TObjectPtr<AActor> Selected_UnitFriend=nullptr;//选中的第一个友方目标
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mouse Drag")
	TObjectPtr<AActor> Selected_UnitEnemy=nullptr;//选中的第一个敌方目标
	//框选单位函数
	UFUNCTION(BlueprintCallable, Category = "Mouse Drag")
	void SelectUnits();
		
	//TeamID and PlayerID
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, Category = "Char Team ID")
	ETeamID PC_TeamID=(ETeamID::None);

	UPROPERTY(Replicated,BlueprintReadWrite, EditAnywhere, Category = "Char Player ID")
	EPlayerID PC_PlayerID=(EPlayerID::None);
	//在服务器上设置队伍和玩家ID
	UFUNCTION(Server, Unreliable, WithValidation, BlueprintCallable, Category = "Char Team ID Player ID")
	void Server_SetPCTeamIDandPlayerID(ETeamID InTeamID, EPlayerID InPlayerID);
	virtual bool Server_SetPCTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID);


	//屏幕摄像机平移部分
	UPROPERTY(BlueprintReadOnly, Category = "Camera Pawn")
	TObjectPtr<ASame_DOTA_CameraPawn> MyCameraPawn_Ref;

	UFUNCTION(BlueprintPure, Category = "Camera Pawn Move")
	FVector MouseEdgeMove(float ScreenSizeRate, FVector HorizontalIncrease, FVector HorizontalDecreasing, FVector VerticalIncrease,FVector VerticalDecreasing);

	
	
public:
	//当前PC输入模式状态
	
	//强制自由攻击指令部分
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPrFreedomAttacking = false;

	//巡逻
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPrePatrol = false;

	TArray<FVector> PatrolPoints;



	//施法指令部分
	UPROPERTY(BlueprintReadOnly, Category = "Unit Input")
	bool bPreReleaseSkill = false;

	


	//增强输入部分
public:

	virtual void SetupInputComponent() override;
		

	//在点击的位置生成的粒子类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor_Attack;

	//输入上下文类型
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MouseLeftMappingContext;

	//按键输入类型
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


	//输入时不同实机触发绑定的句柄
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
