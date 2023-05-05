#include "Player.h"

int* Player::getMaxPlayer( )
{
	static uintptr_t eModuleBase{ (uintptr_t)GetModuleHandle( L"engine.dll" ) };
	int* pNumPlayers{ (int*)(eModuleBase + offsets.numPlayers) };
	return pNumPlayers;
}

Player* Player::GetPlayer( int index )
{
	static uintptr_t cModuleBase{ (uintptr_t)GetModuleHandle( L"client.dll" ) };
	static EntityList* pEntList{ *(EntityList**)(cModuleBase + offsets.entList) };

	return (Player*)(pEntList->EntList[index].m_pEntity); 
}

Vector3* Player::getOrigin( )
{
	return (Vector3*)(*(uintptr_t*)this + offsets.vecOrigin);
}

Vector3* Player::getViewOffset( )
{
	return (Vector3*)(*(uintptr_t*)this + offsets.vecViewOffset);
}

int* Player::getHealth( )
{
	return (int*)(*(uintptr_t*)this + offsets.health);
}

int* Player::getTeam( )
{
	return (int*)(*(uintptr_t*)this + offsets.team);
}

Vector3* Player::GetBonePos( int boneID )
{
	uintptr_t boneMatrix{ *(uintptr_t*)(*(uintptr_t*)this + offsets.boneMatrix) };
	static Vector3 bonePos{};
	bonePos.x = *(float*)(boneMatrix + 0x30 * boneID + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * boneID + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * boneID + 0x2C);

	return &bonePos;
}