#include "api/LevelContext.h"
#include <utility/Utility.h>


LevelContext::LevelContext()
{
}

LevelContext::~LevelContext()
{
}

void LevelContext::InitializeLevel(const FString& msg)
{
	if (m_hasInitialized)
	{
		return;
	}
	Utility::Get().FindNumOfColumnsAndRows(msg, m_height, m_width);
	m_hasInitialized = true;
}

void LevelContext::UpdateLevel(const FString& msg)
{
	if (!m_hasInitialized)
	{
		return;
	}
	Utility::Get().UpdateMines(msg);
}

int LevelContext::GetWidth() const
{
	return m_width;
}

int LevelContext::GetHeight() const
{
	return m_height;
}
