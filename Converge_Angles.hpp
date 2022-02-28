#pragma once

void* Original_Converge_Angles_Caller_Location;

void __thiscall Redirected_Converge_Angles(void* Animation_State, void* Unknown_Parameter_1, float Rate, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	if (Console_Variable_Bruteforce.Integer == 1)
	{
		__int32 Entity_Number = 0;

		void* Local_Player = *(void**)607867332;

		__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80) - 1;

		Traverse_Player_Data_Label:
		{
			if (Entity_Number != Local_Player_Number)
			{
				Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

				if (Player_Data->Priority != -2)
				{
					if (Player_Data->Animation_State == Animation_State)
					{
						Rate = 0;
					}
				}
			}

			Entity_Number += 1;

			if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
			{
				goto Traverse_Player_Data_Label;
			}
		}
	}

	(decltype(&Redirected_Converge_Angles)(Original_Converge_Angles_Caller_Location))(Animation_State, Unknown_Parameter_1, Rate, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
}