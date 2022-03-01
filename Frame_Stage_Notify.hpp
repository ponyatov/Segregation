#pragma once

Player_History_Structure Players_History[64][90];

void* Original_Frame_Stage_Notify_Caller_Location;

float Absolute(float X)
{
	asm("fabs" : "+t"(X));

	return X;
}

float Uncompressed_Velocity[90][3];

float Uncompressed_Base_Velocity[90][3];

float Uncompressed_Recoil[90][2];

float Uncompressed_Fall_Velocity[90];

float Uncompressed_Stamina[90];

void __thiscall Redirected_Frame_Stage_Notify(void* Unknown_Parameter, __int32 Stage)
{
	if (Stage == 2)
	{
		__int32 Entity_Number = 1;

		static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

		__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

		Traverse_Entity_List_Label:
		{
			void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

			if (Entity != nullptr)
			{
				void* Local_Player = *(void**)607867332;

				if (Entity != Local_Player)
				{
					__int32 Normalized_Entity_Number = Entity_Number - 1;

					if (Console_Variable_Bruteforce.Integer == 1)
					{
						Player_Data_Structure* Player_Data = &Players_Data[Normalized_Entity_Number];

						if (Player_Data->Priority != -2)
						{
							void* Animation_State = *(void**)((unsigned __int32)Entity + 3968);

							if (Player_Data->Shots_Fired == 0)
							{
								*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y;
							}
							else
							{
								if (Player_Data->Shots_Fired == 1)
								{
									*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y - 45;
								}
								else
								{
									if (Player_Data->Shots_Fired == 2)
									{
										*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + 45;
									}
									else
									{
										if (Player_Data->Shots_Fired == 3)
										{
											*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y - 90;
										}
										else
										{
											if (Player_Data->Shots_Fired == 4)
											{
												*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + 90;
											}
										}
									}
								}
							}
						}
					}

					if (Local_Player != nullptr)
					{
						__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592);

						if (Tick_Base == Global_Variables->Tick_Number)
						{
							Player_History_Structure* Player_History = &Players_History[Normalized_Entity_Number][Tick_Base % 90];

							float Simulation_Time = *(float*)((unsigned __int32)Entity + 104);

							Player_History->Simulation_Time = Simulation_Time;

							float* Origin = (float*)((unsigned __int32)Entity + 668);

							Player_History->Origin[0] = Origin[0];

							Player_History->Origin[1] = Origin[1];

							Player_History->Origin[2] = Origin[2];
						}
					}
				}
			}

			if (Entity_Number != Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}
	}

	(decltype(&Redirected_Frame_Stage_Notify)(Original_Frame_Stage_Notify_Caller_Location))(Unknown_Parameter, Stage);

	if (Stage == 4)
	{
		void* Local_Player = *(void**)607867332;

		float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

		__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

		constexpr __int8 Clean_Server = 0;

		if (Clean_Server == 0)
		{
			if (Absolute(Velocity[0] - Uncompressed_Velocity[Tick_Base][0]) <= 0.5f)
			{
				if (Absolute(Velocity[1] - Uncompressed_Velocity[Tick_Base][1]) <= 0.5f)
				{
					if (Absolute(Velocity[2] - Uncompressed_Velocity[Tick_Base][2]) <= 0.5f)
					{
						*(float*)((unsigned __int32)Local_Player + 224) = Uncompressed_Velocity[Tick_Base][0];

						*(float*)((unsigned __int32)Local_Player + 228) = Uncompressed_Velocity[Tick_Base][1];

						*(float*)((unsigned __int32)Local_Player + 232) = Uncompressed_Velocity[Tick_Base][2];
					}
				}
			}
		}
		else
		{
			constexpr float Proportional_Maximum_Velocity = 3500 / 3;

			if (Absolute(Velocity[0] - Uncompressed_Velocity[Tick_Base][0]) <= Proportional_Maximum_Velocity)
			{
				if (Absolute(Velocity[1] - Uncompressed_Velocity[Tick_Base][1]) <= Proportional_Maximum_Velocity)
				{
					if (Absolute(Velocity[2] - Uncompressed_Velocity[Tick_Base][2]) <= Proportional_Maximum_Velocity)
					{
						*(float*)((unsigned __int32)Local_Player + 224) = Uncompressed_Velocity[Tick_Base][0];

						*(float*)((unsigned __int32)Local_Player + 228) = Uncompressed_Velocity[Tick_Base][1];

						*(float*)((unsigned __int32)Local_Player + 232) = Uncompressed_Velocity[Tick_Base][2];
					}
				}
			}
		}

		float* Base_Velocity = (float*)((unsigned __int32)Local_Player + 276);

		if (Absolute(Base_Velocity[0] - Uncompressed_Base_Velocity[Tick_Base][0]) <= 0.1f)
		{
			if (Absolute(Base_Velocity[1] - Uncompressed_Base_Velocity[Tick_Base][1]) <= 0.1f)
			{
				if (Absolute(Base_Velocity[2] - Uncompressed_Base_Velocity[Tick_Base][2]) <= 0.1f)
				{
					*(float*)((unsigned __int32)Local_Player + 276) = Uncompressed_Base_Velocity[Tick_Base][0];

					*(float*)((unsigned __int32)Local_Player + 280) = Uncompressed_Base_Velocity[Tick_Base][1];

					*(float*)((unsigned __int32)Local_Player + 284) = Uncompressed_Base_Velocity[Tick_Base][2];
				}
			}
		}

		float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

		if (Absolute(Recoil[0] - Uncompressed_Recoil[Tick_Base][0]) <= 0.125f)
		{
			if (Absolute(Recoil[1] - Uncompressed_Recoil[Tick_Base][1]) <= 0.125f)
			{
				*(float*)((unsigned __int32)Local_Player + 2992) = Uncompressed_Recoil[Tick_Base][0];

				*(float*)((unsigned __int32)Local_Player + 2996) = Uncompressed_Recoil[Tick_Base][1];
			}
		}

		if (Absolute(*(float*)((unsigned __int32)Local_Player + 2972) - Uncompressed_Fall_Velocity[Tick_Base]) <= 0.5f)
		{
			*(float*)((unsigned __int32)Local_Player + 2972) = Uncompressed_Fall_Velocity[Tick_Base];
		}

		if (Absolute(*(float*)((unsigned __int32)Local_Player + 4016) - Uncompressed_Stamina[Tick_Base]) <= 0.1f)
		{
			*(float*)((unsigned __int32)Local_Player + 4016) = Uncompressed_Stamina[Tick_Base];
		}
	}
}