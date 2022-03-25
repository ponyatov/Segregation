#pragma once

void* Original_Setup_Move_Caller_Location;

void __thiscall Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	__builtin_memset((float*)((unsigned __int32)Player + 276), 0, sizeof(float[3]));

	(decltype(&Redirected_Setup_Move)(Original_Setup_Move_Caller_Location))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}