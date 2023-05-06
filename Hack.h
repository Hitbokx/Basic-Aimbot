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

		if ( (!currPlayer) || (!(*(uintptr_t*)currPlayer)) || ((uintptr_t)currPlayer == (uintptr_t)localPlayer) )
			continue;

		int entTeam{ *(currPlayer->getTeam( )) };
		int localPlayerTeam{ *(localPlayer->getTeam( )) };

		if ( entTeam == localPlayerTeam )
			continue;

		int* entHealth{ currPlayer->getHealth( ) };
		int localPlayerHealth{ (*localPlayer->getHealth( )) };

		if ( *entHealth < 1 || localPlayerHealth < 1 );
			continue;

			Vector3* entOrigin{ currPlayer->getOrigin( ) };
			float currDistance{ localPlayer->getDistance( entOrigin ) };

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

	if ( closestEnemy )
	{
		LocalPlayer::Get( )->aimAt( closestEnemy->GetBonePos( 35 ) );
	}
}