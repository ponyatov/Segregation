#pragma once

__int8 Is_First_Command_Predicted;

void* Original_Run_Simulation_Caller_Location;

void __thiscall Redirected_Run_Simulation(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, User_Command_Structure* User_Command, void* Unknown_Parameter_4)
{
	Is_First_Command_Predicted = User_Command->Predicted;

	(decltype(&Redirected_Run_Simulation)(Original_Run_Simulation_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, User_Command, Unknown_Parameter_4);
}