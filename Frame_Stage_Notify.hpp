#pragma once

void* Original_Frame_Stage_Notify_Caller_Location;

float Uncompressed_Recoil[90][2];

void __thiscall Redirected_Frame_Stage_Notify(void* Unknown_Parameter, __int32 Stage)
{
	if (Stage == 2)
	{
		if (Console_Variable_Bruteforce.Integer == 1)
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
						Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

						if (Player_Data->Priority != -2)
						{
							void* Animation_State = *(void**)((unsigned __int32)Entity + 3968);

							if (Player_Data->Shots_Fired == 0)
							{
								*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y;

								*(float*)((unsigned __int32)Animation_State - 116) = Player_Data->Y;
							}
							else
							{
								if (Player_Data->Shots_Fired == 1)
								{
									*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y - 45;

									*(float*)((unsigned __int32)Animation_State - 116) = Player_Data->Y - 45;
								}
								else
								{
									if (Player_Data->Shots_Fired == 2)
									{
										*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + 45;

										*(float*)((unsigned __int32)Animation_State - 116) = Player_Data->Y + 45;
									}
									else
									{
										if (Player_Data->Shots_Fired == 3)
										{
											*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y - 90;

											*(float*)((unsigned __int32)Animation_State - 116) = Player_Data->Y - 90;
										}
										else
										{
											if (Player_Data->Shots_Fired == 4)
											{
												*(float*)((unsigned __int32)Animation_State - 112) = Player_Data->Y + 90;

												*(float*)((unsigned __int32)Animation_State - 116) = Player_Data->Y + 90;
											}
										}
									}
								}
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

		float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

		__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

		if (__builtin_fabsf(Recoil[0] - Uncompressed_Recoil[Tick_Base][0]) <= 0.125f)
		{
			if (__builtin_fabsf(Recoil[1] - Uncompressed_Recoil[Tick_Base][1]) <= 0.125f)
			{
				*(float*)((unsigned __int32)Local_Player + 2992) = Uncompressed_Recoil[Tick_Base][0];

				*(float*)((unsigned __int32)Local_Player + 2996) = Uncompressed_Recoil[Tick_Base][1];
			}
		}
	}
}