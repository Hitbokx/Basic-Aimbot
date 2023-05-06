#pragma once
#include "Classes.h"

class Player :public PlayerEnt
{
private:

	Player( );

public:

	static int* getMaxPlayer( );
	static Player* GetPlayer( int index );

	Vector3* getOrigin( );
	Vector3* getViewOffset( );

	int* getHealth( );
	int* getTeam( );
	Vector3* GetBonePos( int boneID );
};