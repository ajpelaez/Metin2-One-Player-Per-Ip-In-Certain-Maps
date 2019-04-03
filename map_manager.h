#pragma once

class MapManager: public singleton<MapManager>
{
	private:
		std::map<DWORD, std::list<DWORD>> m_map_manager = {
			{ 181, {} },
			{ 182, {} },
			{ 183, {} }
		};
		
	public:
		void      Initialize();
		void            Clear();
		void            Destroy();

		void            Enter(const LPCHARACTER ch);
		void            Disconnect(const LPCHARACTER ch);

		const size_t    GetIPMapCount(const DWORD dwMapIndex);
		const bool      IsPlayerIPInMap(const LPCHARACTER ch);
		const bool      IsUniqueIPMap(const DWORD dwMapIndex);
};