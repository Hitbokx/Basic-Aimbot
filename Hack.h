#pragma once
#include "Classes.h"
#include "Player.h"
#include "LocalPlayer.h"

Player* getClosestEnemy( )
{
	LocalPlayer* localPlayer{ LocalPlayer::Get( ) };

	float closestDistance{ 1000000 };
	int closestDistanceIndex{ -1 };

	for ( int i{ 1 }; i < *Player::getMaxPlayer( ); ++i )
	{
		Player* currPlayer{ Player::GetPlayer( i ) };

		if ( !currPlayer || !(*(uintptr_t*)currPlayer) || (uintptr_t)currPlayer == (uintptr_t)localPlayer )
			continue;

		if ( *currPlayer->getTeam( ) == *localPlayer->getTeam( ) )
			continue;

		if ( *currPlayer->getHealth( ) < 1 || *localPlayer->getHealth( ) < 1 )
			continue;

		float currDistance{ localPlayer->getDistance( currPlayer->getOrigin( ) ) };

		if ( currDistance < closestDistance )
		{
			closestDistance = currDistance;
			closestDistanceIndex = i;
		}
	}

		if ( closestDistanceIndex == -1 )
			return NULL;

		return Player::GetPlayer( closestDistanceIndex );
}

void Run( )
{
	Player* closestEnemy{ getClosestEnemy( ) };

	if ( closestEnemy )
	{
		LocalPlayer::Get( )->aimAt( closestEnemy->GetBonePos( 35 ) );
	}
}