#pragma once

#include "CoreMinimal.h"
#include "WaveManager.generated.h"


// Struct to represent an enemy group
USTRUCT(BlueprintType)
struct FEnemyGroup
{
    GENERATED_BODY()

public:
    // The type of enemy to spawn (BP_BaseEnemy or other Blueprints)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Group")
    TSubclassOf<class AActor> EnemyType; // This can be any Blueprint derived from AActor

    // The number of enemies to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Group")
    int32 Count;

    // Constructor
    FEnemyGroup()
        : EnemyType(nullptr), Count(0) {
    }
};

// Struct to define a wave of enemies
USTRUCT(BlueprintType)
struct FWave
{
    GENERATED_BODY()

public:
    // An array of enemy groups
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
    TArray<FEnemyGroup> EnemyGroups;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
    float SpawnDelay{ 0.5 };

    // Add an enemy group
    void AddEnemyGroup(TSubclassOf<AActor> EnemyType, int32 Count)
    {
        FEnemyGroup NewGroup;
        NewGroup.EnemyType = EnemyType;
        NewGroup.Count = Count;
        EnemyGroups.Add(NewGroup);
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
    int32 WaveWinMoneyReward{ 200 };
};

// Forward declare the UClass type of BP_BaseEnemy
UCLASS(Blueprintable)
class MYPROJECT_API UWaveManager : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Manager")
    TObjectPtr<AActor> bM_SpawnLocation{};

    // A list of waves
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Manager")
    TArray<FWave> m_Waves;

    // Add a wave
    UFUNCTION(BlueprintCallable, Category = "Wave Manager")
    void AddWave(const FWave& Wave);

    // Retrieve a wave by index
    UFUNCTION(BlueprintCallable, Category = "Wave Manager")
    FWave GetWave() const;

    UFUNCTION(BlueprintCallable, Category = "Wave Manager")
    void NextWave();

    UFUNCTION(BlueprintCallable, Category = "Wave Manager")
    bool CheckClearedAllWaves();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Manager")
    bool bM_WaveEnded{true};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Manager")
    int32 bM_CurrentWave{ -1 };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave Manager")
    bool bM_IsPlayingWave{ false };

    // Constructor
    UWaveManager();
};
