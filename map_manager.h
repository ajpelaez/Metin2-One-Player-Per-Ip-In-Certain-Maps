#pragma once

class MapManager: public singleton<MapManager>
{
	private:
		std::map<const DWORD, std::list<const DWORD>> m_map_manager = {
			{ 181, {} },
			{ 182, {} },
			{ 183, {} }
		};
		
	public:
		const bool      Initialize();
		void            Clear();
		void            Destroy();

		void            Enter(const LPCHARACTER ch);
		void            Disconnect(const LPCHARACTER ch);

		const size_t    GetIPMapCount(const DWORD dwMapIndex);
		const bool      IsPlayerIPInMap(const LPCHARACTER ch);
		const bool      IsUniqueIPMap(const DWORD dwMapIndex);
};
