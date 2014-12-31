//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
//=============================================================================//
#include "cbase.h"
#include "ai_default.h"
#include "ai_task.h"
#include "ai_schedule.h"
#include "ai_hull.h"
#include "soundent.h"
#include "jl\npc_dilophosaurus.h"
#include "game.h"
#include "npcevent.h"
#include "entitylist.h"
#include "activitylist.h"
#include "ai_basenpc.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar	sk_dilophosaurus_health( "sk_dilophosaurus_health", "0" );
ConVar	sk_dilophosaurus_melee_dmg( "sk_dilophosaurus_melee_dmg", "0" );

#define	DILOPHOSAURUS_MODEL	"models/jl/dinosaurs/dilophosaurus.mdl"

//=========================================================
// Private animevents
//=========================================================

//int DILOPHOSAURUS_AE_FOOTSTEPWALK;
//int DILOPHOSAURUS_AE_FOOTSTEPRUN;

//=========================================================
// Private activities
//=========================================================

//Activity ACT_DILOPHOSAURUS_ACTIVITY;
//Activity ACT_DILOPHOSAURUS_ACTIVITY2;

//=========================================================
// Shared interaction
//=========================================================
//int g_interactionExample = 0; // REMEMBER TO ADD THIS TO AI_Interactions.h
//int g_interactionExample2 = 0; // REMEMBER TO ADD THIS TO AI_Interactions.h


//=========================================================
//=========================================================

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CDilophosaurus::Precache( void )
{
	PrecacheModel( DILOPHOSAURUS_MODEL );

	BaseClass::Precache();
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CDilophosaurus::Spawn( void )
{
	Precache();

	SetModel( DILOPHOSAURUS_MODEL );
	SetHullType(HULL_WIDE_SHORT);
	SetHullSizeNormal();

	SetSolid( SOLID_BBOX );
	AddSolidFlags( FSOLID_NOT_STANDABLE );
	SetMoveType( MOVETYPE_STEP );
	SetBloodColor( BLOOD_COLOR_RED );
	m_iHealth				= sk_dilophosaurus_health.GetFloat();
//	m_iMaxHealth			= m_iHealth;
	m_flFieldOfView	= 0.5; // indicates the width of this NPC's forward view cone ( as a dotproduct result )
	m_NPCState	= NPC_STATE_NONE;

	CapabilitiesClear();

	CapabilitiesAdd( bits_CAP_TURN_HEAD | bits_CAP_MOVE_GROUND );
	// innate Range attack ( howling / shaking)	
	CapabilitiesAdd( bits_CAP_INNATE_RANGE_ATTACK1 | bits_CAP_INNATE_RANGE_ATTACK2 );
	
	// innate Melee attack ( charge+head attack / bite attack (from fish bite or byte missed with event )	
	CapabilitiesAdd( bits_CAP_INNATE_MELEE_ATTACK1 | bits_CAP_INNATE_MELEE_ATTACK2 );
	
	BaseClass::Spawn();
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CDilophosaurus::Classify( void )
{
	return	CLASS_NONE;
}