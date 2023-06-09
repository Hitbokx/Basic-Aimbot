#pragma once
#include "Classes.h"
#include "Player.h"
#include "LocalPlayer.h"

Player* getClosestEnemy( )
{
	LocalPlayer* localPlayer{ LocalPlayer::Get( ) };

	float closestDistance{ 1000000 };
	int closestDistanceIndex{ -1 };

	int numPlayers{ *(Player::getMaxPlayer( )) };

	for ( int i{ 1 }; i < numPlayers; ++i )
	{
		Player* currPlayer{ Player::GetPlayer( i ) };

		if ( (!currPlayer) || (!(*(uintptr_t*)currPlayer)) || ((uintptr_t)currPlayer == (uintptr_t)localPlayer) || currPlayer->bDormant)
			continue;

		if ( currPlayer->team == *(localPlayer->getTeam()) )
			continue;

		if ( currPlayer->health < 1 || *(localPlayer->getHealth( )) < 1 )
			continue;

		float currDistance{ localPlayer->getDistance( currPlayer->playerCoordinates ) };

		if ( currDistance < closestDistance )
		{
			closestDistance = currDistance;
			closestDistanceIndex = i;
		}
	}

	if ( closestDistanceIndex == -1 )
		return NULL;
	else
		return Player::GetPlayer( closestDistanceIndex );
}

void Run( )
{
	Player* closestEnemy{ getClosestEnemy( ) };

	LocalPlayer* localPlayer{ LocalPlayer::Get( ) };

	if ( closestEnemy )
	{
		Vector3* bonePos{ closestEnemy->GetBonePos( 35 ) };
		localPlayer->aimAt( bonePos );
	}
}