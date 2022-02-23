#pragma once

void* Original_Interpolate_Caller_Location;

__int8 __thiscall Redirected_Interpolate(void* Player, void* Unknown_Variable)
{
	void* Local_Player = *(void**)607867332;

	if (Player != Local_Player)
	{
		*(__int8*)607715194 = 0;
	}

	__int8 Return_Value = (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller_Location))(Player, Unknown_Variable);

	if (Player != Local_Player)
	{
		*(__int8*)607715194 = 1;
	}

	return Return_Value;
}