#pragma once

void* Original_Run_Command_Caller_Location;

void __thiscall Redirected_Run_Command(void* Prediction, void* Player, void* User_Command, void* Move_Helper)
{
	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller_Location))(Prediction, Player, User_Command, Move_Helper);

	void* Local_Player = *(void**)607867332;

	__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

	float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

	__builtin_memcpy(Uncompressed_Velocity[Tick_Base], Velocity, sizeof(Uncompressed_Velocity[Tick_Base]));

	float* Base_Velocity = (float*)((unsigned __int32)Local_Player + 276);

	__builtin_memcpy(Uncompressed_Base_Velocity[Tick_Base], Base_Velocity, sizeof(Uncompressed_Base_Velocity[Tick_Base]));

	float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

	__builtin_memcpy(Uncompressed_Recoil[Tick_Base], Recoil, sizeof(Uncompressed_Recoil[Tick_Base]));

	Uncompressed_Stamina[Tick_Base] = *(float*)((unsigned __int32)Local_Player + 4016);
}