#pragma once

#include "CoreMinimal.h"
#include "api/Types.h"

#include <unordered_map>
#include <memory>

class LevelContext
{

public:
	LevelContext();
	~LevelContext();

	void InitializeLevel(const FString& msg);
	void UpdateLevel(const FString& msg);

	int GetWidth() const;
	int GetHeight() const;

	bool HasInitialized() const { return m_hasInitialized; }

private:
	int m_width = 0;
	int m_height = 0;
	bool m_hasInitialized = false;

	//std::unordered_map<std::shared_ptr<FCellPosition>, std::shared_ptr<FMine>> m_level;
};