#pragma once

void* Original_Run_Command_Caller_Location;

void __thiscall Redirected_Run_Command(void* Prediction, void* Player, void* User_Command, void* Move_Helper)
{
	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller_Location))(Prediction, Player, User_Command, Move_Helper);

	void* Local_Player = *(void**)607867332;

	__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

	float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

	Uncompressed_Velocity[Tick_Base][0] = Velocity[0];

	Uncompressed_Velocity[Tick_Base][1] = Velocity[1];

	Uncompressed_Velocity[Tick_Base][2] = Velocity[2];

	float* Base_Velocity = (float*)((unsigned __int32)Local_Player + 276);

	Uncompressed_Base_Velocity[Tick_Base][0] = Base_Velocity[0];

	Uncompressed_Base_Velocity[Tick_Base][1] = Base_Velocity[1];

	Uncompressed_Base_Velocity[Tick_Base][2] = Base_Velocity[2];

	float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

	Uncompressed_Recoil[Tick_Base][0] = Recoil[0];

	Uncompressed_Recoil[Tick_Base][1] = Recoil[1];

	Uncompressed_Fall_Velocity[Tick_Base] = *(float*)((unsigned __int32)Local_Player + 2972);

	Uncompressed_Stamina[Tick_Base] = *(float*)((unsigned __int32)Local_Player + 4016);
}