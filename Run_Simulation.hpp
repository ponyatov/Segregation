#pragma once

__int8 Is_First_Command_Predicted;

void* Original_Run_Simulation_Caller_Location;

void __thiscall Redirected_Run_Simulation(void* Prediction, __int32 Command_Number, float Current_Time, User_Command_Structure* User_Command, void* Player)
{
	Is_First_Command_Predicted = User_Command->Predicted;

	(decltype(&Redirected_Run_Simulation)(Original_Run_Simulation_Caller_Location))(Prediction, Command_Number, Current_Time, User_Command, Player);
}