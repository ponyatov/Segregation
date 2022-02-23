#pragma once

void Redirected_Run_Prediction()
{
	if (*(__int8*)540609192 == 6)
	{
		static void* Prediction = *(void**)540494880;

		using Update_Type = void(__thiscall**)(void* Prediction, void* Unknown_Parameter_1, __int8 Unknown_Parameter_2, void* Unknown_Parameter_3, __int32 Outgoing_Command_Number);

		(*Update_Type(*(unsigned __int32*)Prediction + 12))(Prediction, *(void**)540609292, 1, *(void**)540627876, *(__int32*)540627868 + *(__int32*)540627872);
	}
}