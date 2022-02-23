#pragma once

void* Original_Run_Command_Caller_Location;

void __thiscall Redirected_Run_Command(void* Prediction, void* Player, void* User_Command, void* Move_Helper)
{
	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller_Location))(Prediction, Player, User_Command, Move_Helper);

	void* Local_Player = *(void**)607867332;

	__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

	float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

	Uncompressed_Recoil[Tick_Base][0] = Recoil[0];

	Uncompressed_Recoil[Tick_Base][1] = Recoil[1];
}