#include "LocalPlayer.h"
#include <Windows.h>
#include <cmath>

void aimAt( Vector3* target );

LocalPlayer* LocalPlayer::Get( )
{
	static uintptr_t cModuleBase{ (uintptr_t)GetModuleHandle( L"client.dll" ) };
	static LocalPlayer* localPlayer{ (LocalPlayer*)(cModuleBase + offsets.localPlayer) };

	return localPlayer;
}

Vector3* LocalPlayer::getOrigin( )
{
	return (Vector3*)(*(uintptr_t*)this + offsets.vecOrigin);
}

Vector3* LocalPlayer::getViewOffset( )
{
	return (Vector3*)(*(uintptr_t*)this + offsets.vecViewOffset);
}

int* LocalPlayer::getHealth( )
{
	return (int*)(*(uintptr_t*)this + offsets.health);
}

int* LocalPlayer::getTeam( )
{
	return (int*)(*(uintptr_t*)this + offsets.team);
}

float LocalPlayer::getDistance( Vector3* other )
{
	Vector3* myPos{ getOrigin( ) };
	Vector3 delta{ Vector3( other->x - myPos->x,other->y - myPos->y, other->z - myPos->z ) };

	return sqrt( delta.x * delta.x + delta.y * delta.y + delta.z * delta.z );
}

