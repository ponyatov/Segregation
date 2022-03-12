#pragma once

void* Original_Converge_Angles_Caller_Location;

void __thiscall Redirected_Converge_Angles(void* Animation_State, void* Unknown_Parameter_1, float Rate, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
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
						Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

						if (Player_Data->Priority != -2)
						{
							if (Player_Data->Animation_State == Animation_State)
							{
								Rate = 0;
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

	(decltype(&Redirected_Converge_Angles)(Original_Converge_Angles_Caller_Location))(Animation_State, Unknown_Parameter_1, Rate, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}