#pragma once

void* Original_Converge_Angles_Caller_Location;

void __thiscall Redirected_Converge_Angles(void* Animation_State, float Goal, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, float* Current)
{
	__int8 Instant = 0;

	if (Console_Variable_Bruteforce.Integer == 1)
	{
		void* Local_Player = *(void**)607867332;

		if (Animation_State != (void*)(*(unsigned __int32*)((unsigned __int32)Local_Player + 3968) - 148))
		{
			__int32 Entity_Number = 1;

			static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;
		
			__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

			Traverse_Entity_List_Label:
			{
				void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (Entity != Local_Player)
					{
						if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
						{
							Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

							if (Player_Data->Priority != -2)
							{
								if (Player_Data->Animation_State == Animation_State)
								{
									if (Console_Variable_Bruteforce_Memory.Integer == 0)
									{
										Bruteforce_Label:
										{
											Goal = Player_Data->Y + Bruteforce_Angles[Player_Data->Shots_Fired];
										}
									}
									else
									{
										if (Player_Data->Memorized == 0)
										{
											goto Bruteforce_Label;
										}

										Goal = Player_Data->Y + Player_Data->Memorized_Y;
									}

									Instant = 1;
								}
							}
						}
					}
				}

				if (Instant == 0)
				{
					if (Entity_Number != Maximum_Clients)
					{
						Entity_Number += 1;

						goto Traverse_Entity_List_Label;
					}
				}
			}
		}
	}

	if (*(float*)Current != Goal)
	{
		if (Instant == 0)
		{
			(decltype(&Redirected_Converge_Angles)(Original_Converge_Angles_Caller_Location))(Animation_State, Goal, Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Current);
		}
		else
		{
			*(float*)Current = __builtin_remainderf(Goal, 360);
		}

		static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

		*(float*)((unsigned __int32)Animation_State + 52) = Global_Variables->Current_Time;
	}
}