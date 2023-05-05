#pragma once

#include <iostream>
#include <Windows.h>

#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK			(NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF
#define NUM_SERIAL_NUM_BITS		(32 - NUM_ENT_ENTRY_BITS)

#define	MAX_EDICT_BITS				11			
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)

class CBaseHandle
{
public:
	friend class EntityList;

public:

	int GetEntryIndex( ) const;

	int GetSerialNumber( ) const;

protected:

	unsigned long	m_Index;
};

class Vector3
{
public:

	float x{};
	float y{};
	float z{};

	Vector3( )
	{
		x = y = z = 0;
	}

	Vector3( float x, float y, float z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3& operator+( Vector3 arg )
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;

		return *this;
	}

	Vector3& operator-( Vector3 arg )
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;

		return *this;
	}
};

class PlayerEnt
{
public:
	char pad_0000[32]; //0x0000
	Vector3 vecAngles; //0x0020
	char pad_002C[121]; //0x002C
	int8_t lifeState; //0x00A5
	char pad_00A6[2]; //0x00A6
	int32_t health; //0x00A8
	char pad_00AC[4]; //0x00AC
	int32_t team; //0x00B0
	char pad_00B4[72]; //0x00B4
	Vector3 viewOffset; //0x00FC
	char pad_0108[24]; //0x0108
	Vector3 velocity; //0x0120
	char pad_012C[126]; //0x012C
	bool bDormant; //0x01AA
	char pad_01AB[237]; //0x01AB
	Vector3 viewAngles; //0x0298
	char pad_02A4[192]; //0x02A4
	Vector3 playerCoordinates; //0x0364
	char pad_0370[12]; //0x0370
	uint32_t flag; //0x037C
	char pad_0380[660]; //0x0380
	int32_t flag2; //0x0614
	char pad_0618[760]; //0x0618
	Vector3 gunCrossHair; //0x0910
	char pad_091C[864]; //0x091C
	int32_t primaryAmmoMag; //0x0C7C
	int32_t secondaryAmmoMag; //0x0C80
	char pad_0C84[40]; //0x0C84
	Vector3 N00000B51; //0x0CAC
	Vector3 N00000B52; //0x0CB8
	char pad_0CC4[248]; //0x0CC4
	bool specGlowEnabled; //0x0DBC
	bool glowEnabled; //0x0DBD
	bool boldGlowEnabled; //0x0DBE
	char pad_0DBF[1]; //0x0DBF
	int32_t glowIndex; //0x0DC0
	char pad_0DC4[180]; //0x0DC4
	uint32_t commandFlags; //0x0E78
	char pad_0E7C[732]; //0x0E7C
	float onTarget; //0x1158
	char pad_115C[24]; //0x115C
	uint32_t commandFlag2; //0x1174
	char pad_1178[8]; //0x1178
	uint32_t commandFlags3; //0x1180
	char pad_1184[304]; //0x1184
	int32_t primaryAmmo; //0x12B4
	int32_t secondaryAmmo; //0x12B8
	char pad_12BC[156]; //0x12BC
	int32_t commandFlags4; //0x1358
	char pad_135C[1320]; //0x135C
	int32_t crossHairId; //0x1884
	char pad_1888[14316]; //0x1888
}; //Size: 0x5074

class CEntInfo
{
public:
	class PlayerEnt* m_pEntity; //0x0000
	int32_t m_SerialNumber; //0x0004
	class CEntInfo* previous; //0x0008
	class CEntInfo* next; //0x000C
}; //Size: 0x0010

class Entity
{
public:
	char pad_0000[168]; //0x0000
	int32_t health; //0x00A8
}; //Size: 0x00AC

class EntityList
{
public:
	char pad_0000[4]; //0x0000
	class CEntInfo world; //0x0004
	class CEntInfo EntList[23]; //0x0014

}; //Size: 0x0184

struct offsets_t
{
	uintptr_t entList{ 0xBDD998 };
	uintptr_t entList2{ 0xc56474 };
	uintptr_t localPlayer{ 0xC484F0 };
	uintptr_t flags{ 0x37C };
	uintptr_t fJump{ 0xC8F7C0 };
	uintptr_t fAttack{ 0xC8F7CC };
	uintptr_t crossHairId{ 0x1884 };
	uintptr_t numPlayers{ 0x5DBE44 };
	uintptr_t dwGlowObjectManager{ 0xBE0890 };
	uintptr_t clientState{ 0x465a58 };
	uintptr_t ViewAnglesW{ 0x46a5dc };
	uintptr_t MaxClients{ 0x465d0c };

	uintptr_t health{ 0x00A8 }; //
	uintptr_t team{ 0x00B0 }; //
//	uintptr_t viewAngles{ 0x0298 }; //
	uintptr_t vecViewOffset{ 0x00FC }; //
	uintptr_t vecOrigin{ 0x038C }; //
	uintptr_t boneMatrix{ 0x05B0 };
};

static offsets_t offsets{};