#pragma once
#include "Classes.h"

class LocalPlayer
{
private:

	LocalPlayer( );

public:

	static LocalPlayer* Get( );

	Vector3* getOrigin( );
	Vector3* getViewOffset( );

	int* getHealth( );
	int* getTeam( );
	void aimAt( Vector3* target );
	float getDistance( Vector3* );
};