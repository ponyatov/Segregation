#pragma once

__int8 Forbid_Accuracy_Modification;

__int8 __thiscall Redirected_Perform_Prediction(void* Prediction, __int8 Unknown_Parameter, void* Player, __int32 Acknowledged_Command_Number, __int32 Outgoing_Command_Number)
{
	*(__int8*)((unsigned __int32)Prediction + 8) = 1;

	using Compute_First_Command_To_Execute_Type = __int32(__thiscall*)(void* Prediction, __int8 Unknown_Parameter, __int32 Acknowledged_Command_Number, __int32 Outgoing_Command_Number);

	__int32 Current_Command_Number = Compute_First_Command_To_Execute_Type(605206464)(Prediction, 1, Acknowledged_Command_Number, Outgoing_Command_Number);

	__int32 Final_Command_Number = Outgoing_Command_Number + 1;

	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	Predict_Label:
	{
		__int32 Current_Acknowledged_Command_Number = Current_Command_Number + Acknowledged_Command_Number;

		if (Current_Acknowledged_Command_Number != Final_Command_Number)
		{
			if (Current_Command_Number != 90)
			{
				using Run_Simulation_Type = void(__thiscall*)(void* Prediction, __int32 Command_Number, float Current_Time, User_Command_Structure* User_Command, void* Player);

				__int32 Tick_Base = *(__int32*)((unsigned __int32)Player + 3592);

				float Current_Time = Tick_Base * Global_Variables->Interval_Per_Tick;

				using Get_User_Command_Type = User_Command_Structure*(__thiscall*)(void* Unknown_Parameter, __int32 Command_Number);

				User_Command_Structure* User_Command = Get_User_Command_Type(604993792)(*(void**)607769608, Current_Acknowledged_Command_Number);

				if (User_Command->Predicted == 0)
				{
					*(__int8*)((unsigned __int32)Prediction + 9) = 1;
				}
				else
				{
					*(__int8*)((unsigned __int32)Prediction + 9) = 0;

					Forbid_Accuracy_Modification = 1;
				}

				Run_Simulation_Type(605206096)(Prediction, Current_Acknowledged_Command_Number, Current_Time, User_Command, Player);

				Forbid_Accuracy_Modification = 0;

				User_Command->Predicted = 1;

				Global_Variables->Current_Time = Current_Time;

				Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick;

				Tick_Base = (Tick_Base + 1) % 90;

				Uncompressed_View_Offset[Tick_Base] = *(float*)((unsigned __int32)Player + 220);

				float* Velocity = (float*)((unsigned __int32)Player + 224);

				__builtin_memcpy(Uncompressed_Velocity[Tick_Base], Velocity, sizeof(Uncompressed_Velocity[Tick_Base]));

				float* Base_Velocity = (float*)((unsigned __int32)Player + 276);

				__builtin_memcpy(Uncompressed_Base_Velocity[Tick_Base], Base_Velocity, sizeof(Uncompressed_Base_Velocity[Tick_Base]));

				float* Recoil = (float*)((unsigned __int32)Player + 2992);

				__builtin_memcpy(Uncompressed_Recoil[Tick_Base], Recoil, sizeof(Uncompressed_Recoil[Tick_Base]));

				Uncompressed_Stamina[Tick_Base] = *(float*)((unsigned __int32)Player + 4016);
				
				using Store_Results_Type = void(__thiscall*)(void* Prediction, __int32 Number);

				Store_Results_Type(605209056)(Prediction, Current_Command_Number - 1);

				*(__int32*)((unsigned __int32)Prediction + 16) = Current_Command_Number;

				Current_Command_Number += 1;

				goto Predict_Label;
			}
		}

		*(__int32*)((unsigned __int32)Player + 3596) = *(__int32*)((unsigned __int32)Player + 3592);
	}

	*(__int8*)((unsigned __int32)Prediction + 8) = 0;

	return 1;
}