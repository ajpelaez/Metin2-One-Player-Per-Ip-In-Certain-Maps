#include "stdafx.h"
#include "buffer_manager.h"
#include "char.h"
#include "char_manager.h"
#include "map_manager.h"
#include "desc.h"

void MapManager::Initialize()
{
	Clear();
}

void MapManager::Destroy()
{
	Clear();
}

// Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
void MapManager::Clear()
{
	for (auto iter = m_map_manager.begin(); iter != m_map_manager.end(); ++iter)
		iter->second.clear();
}

// Count elements with a specific key, return 1 (if the element is found) or zero (otherwise).
const bool MapManager::IsUniqueIPMap(const DWORD dwMapIndex)
{
	return m_map_manager.count(dwMapIndex) != 0;
}

// Returns the number of elements in the map container.
const size_t MapManager::GetIPMapCount(const DWORD dwMapIndex)
{
	return (m_map_manager[dwMapIndex]).size();
}


void MapManager::Disconnect(const LPCHARACTER ch)
{
	if (!ch)
		return;

	const DWORD dwMapIndex = ch->GetMapIndex();	
	if (!IsUniqueIPMap(dwMapIndex))
		return;

	// Remove the player id from map list if exist.
	const auto it = std::find(m_map_manager[dwMapIndex].begin(), m_map_manager[dwMapIndex].end(), ch->GetPlayerID());
	if (it != m_map_manager[dwMapIndex].end())
		m_map_manager[dwMapIndex].erase(it);
}

void MapManager::Enter(const LPCHARACTER ch)
{
	if (!ch)
		return;
	
	const DWORD dwPID = ch->GetPlayerID();
	const DWORD dwMapIndex = ch->GetMapIndex();

	if (!IsUniqueIPMap(dwMapIndex))
		return;

	// Return iterator to the first element satisfying the condition or last if no such element is found.
	const auto it = std::find(m_map_manager[dwMapIndex].begin(), m_map_manager[dwMapIndex].end(), dwPID);

	// If no element is found in the map, find() returns map.end().
	if (it != m_map_manager[dwMapIndex].end())
		return;

	// Add the player id into map list.
	m_map_manager[dwMapIndex].emplace_back(dwPID);
}

const bool MapManager::IsPlayerIPInMap(const LPCHARACTER ch)
{	
	if (!ch)
		return false;

	if (!IsUniqueIPMap(ch->GetMapIndex()))
		return false;

	if (GetIPMapCount(ch->GetMapIndex()) == 0)
		return false;

	LPCHARACTER pkChar = NULL;
	// Range-based for loop, iterating the std::list with player pids.
	for (DWORD dwPID : m_map_manager[ch->GetMapIndex()])
	{
		if (!(pkChar = CHARACTER_MANAGER::instance().FindByPID(dwPID)))
			continue;

		if (!strcmp(ch->GetDesc()->GetHostName(), pkChar->GetDesc()->GetHostName()) && ch->GetPlayerID() != pkChar->GetPlayerID())
			return true;
	}
	
	return false;
}