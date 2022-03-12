#pragma once

float Shot_Time;

void* Original_Frame_Stage_Notify_Caller_Location;

__int32 lastrecv;

float Absolute(float X)
{
	asm("fabs" : "+t"(X));

	return X;
}

float Uncompressed_Velocity[90][3];

float Uncompressed_Base_Velocity[90][3];

float Uncompressed_Recoil[90][2];

float Uncompressed_Stamina[90];

void __thiscall Redirected_Frame_Stage_Notify(void* Unknown_Parameter, __int32 Stage)
{
	if (Stage == 4)
	{
		if (Console_Variable_Bruteforce.Integer == 1)
		{
			__int32 Entity_Number = 1;

			void* Local_Player = *(void**)607867332;

			static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

			__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

			Traverse_Entity_List_Label:
			{
				void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (Entity == Local_Player)
					{
						if (*(__int8*)((unsigned __int32)Entity + 135) != 0)
						{
							Shot_Time = 0;
						}
					}
					else
					{
						Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

						if (Player_Data->Priority != -2)
						{
							void* Animation_State = *(void**)((unsigned __int32)Entity + 3968);

							if (Console_Variable_Bruteforce_Memory.Integer == 0)
							{
								Bruteforce_Label:
								{
									*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + Bruteforce_Angles[Player_Data->Shots_Fired];
								}
							}
							else
							{
								if (Player_Data->Memorized == 0)
								{
									goto Bruteforce_Label;
								}

								*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + Player_Data->Memorized_Y;
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
	}

	(decltype(&Redirected_Frame_Stage_Notify)(Original_Frame_Stage_Notify_Caller_Location))(Unknown_Parameter, Stage);

	if (Stage == 4)
	{
		void* Local_Player = *(void**)607867332;

		float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

		__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

		if (Absolute(Velocity[0] - Uncompressed_Velocity[Tick_Base][0]) <= 0.5f)
		{
			if (Absolute(Velocity[1] - Uncompressed_Velocity[Tick_Base][1]) <= 0.5f)
			{
				if (Absolute(Velocity[2] - Uncompressed_Velocity[Tick_Base][2]) <= 0.5f)
				{
					__builtin_memcpy((float*)((unsigned __int32)Local_Player + 224), Uncompressed_Velocity[Tick_Base], sizeof(Uncompressed_Velocity[Tick_Base]));
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
					__builtin_memcpy((float*)((unsigned __int32)Local_Player + 276), Uncompressed_Base_Velocity[Tick_Base], sizeof(Uncompressed_Base_Velocity[Tick_Base]));
				}
			}
		}

		float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

		if (Absolute(Recoil[0] - Uncompressed_Recoil[Tick_Base][0]) <= 0.125f)
		{
			if (Absolute(Recoil[1] - Uncompressed_Recoil[Tick_Base][1]) <= 0.125f)
			{
				__builtin_memcpy((float*)((unsigned __int32)Local_Player + 2992), Uncompressed_Recoil[Tick_Base], sizeof(Uncompressed_Recoil[Tick_Base]));
			}
		}

		if (Absolute(*(float*)((unsigned __int32)Local_Player + 4016) - Uncompressed_Stamina[Tick_Base]) <= 0.1f)
		{
			*(float*)((unsigned __int32)Local_Player + 4016) = Uncompressed_Stamina[Tick_Base];
		}
	}
}