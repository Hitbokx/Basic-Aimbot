#include "LocalPlayer.h"
#include <Windows.h>
#include <cmath>

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

float LocalPlayer::getDistance( Vector3 other )
{
	LocalPlayer* localPlayer{ LocalPlayer::Get( ) };

	Vector3* myPos{ localPlayer->getOrigin( ) };
	Vector3 delta{ Vector3( other.x - myPos->x, other.y - myPos->y, other.z - myPos->z ) };

	return sqrt( delta.x * delta.x + delta.y * delta.y + delta.z * delta.z );
}

#define PI 3.14159265358f

void LocalPlayer::aimAt( Vector3* target )
{
	static uintptr_t eModuleBase{ (uintptr_t)GetModuleHandle( L"engine.dll" ) };
	static Vector3* viewAngles{ (Vector3*)(eModuleBase + offsets.ViewAnglesW) };

	Vector3 origin{ *getOrigin( ) };
	Vector3 viewOffset{ *getViewOffset( ) };

	Vector3* myPos{ &(origin + viewOffset) };

	Vector3 deltaVec{ Vector3( target->x - myPos->x, target->y - myPos->y, target->z - myPos->z ) };

	float deltaVecLength{ sqrt( deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z ) };

	float pitch{ -(asin( deltaVec.z / deltaVecLength ) * (180 / PI)) };
	float yaw{ atan2( deltaVec.y, deltaVec.x ) * (180 / PI) };

	if ( pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180 )
	{
		viewAngles->x = pitch;
		viewAngles->y = yaw;
	}
}