#include "WaveManager.h"
#include "Engine/World.h"  // For spawning actors

UWaveManager::UWaveManager()
{
    // Initialize any default values if necessary
}

void UWaveManager::AddWave(const FWave& Wave)
{
    m_Waves.Add(Wave);
}

FWave UWaveManager::GetWave() const
{
    if (m_Waves.IsValidIndex(bM_CurrentWave))
    {
        return m_Waves[bM_CurrentWave];
    }

    // Return an empty wave if the index is invalid
    return FWave();
}

void UWaveManager::NextWave()
{
    if (m_Waves.IsValidIndex(bM_CurrentWave + 1))
    {
        bM_CurrentWave += 1;
        bM_IsPlayingWave = true;
        bM_WaveEnded = false;
    }
}

bool UWaveManager::CheckClearedAllWaves()
{
    if (!m_Waves.IsValidIndex(bM_CurrentWave + 1) && bM_WaveEnded == true)
    {
        return true;
    }

    return false;
}
