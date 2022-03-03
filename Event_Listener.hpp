#pragma once

void __stdcall Event_Processor(void* Event)
{
	void* Local_Player = *(void**)607867332;

	if (Local_Player != nullptr)
	{
		__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);

		using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

		using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Victim_Identifier = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));

		__int32 Killer_Identifier = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"attacker", nullptr));

		if (Local_Player_Number == Victim_Identifier)
		{
			Player_Data_Structure* Player_Data = &Players_Data[Killer_Identifier - 1];

			Player_Data->Memorized = 0;

			if (Console_Variable_Commentator.Integer == 1)
			{
				PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
			}
		}
		else
		{
			if (Local_Player_Number == Killer_Identifier)
			{
				unsigned __int32 Weapon_Index = *(unsigned __int32*)((unsigned __int32)Local_Player + 2872);

				void* Weapon = *(void**)((unsigned __int32)607973860 + (((Weapon_Index & 4095) - 4097) << 4));

				if (Weapon != nullptr)
				{
					Player_Data_Structure* Player_Data = &Players_Data[Victim_Identifier - 1];

					Player_Data->Memorized = 1;

					using Get_Primary_Ammo_Capacity_Type = __int32(__thiscall**)(void* Weapon);

					Player_Data->Memorized_Shots = (*Get_Primary_Ammo_Capacity_Type(*(unsigned __int32*)Weapon + 1000))(Weapon);

					constexpr float Angles[5] =
					{
						0,

						-45,

						45,

						-90,

						90
					};

					Player_Data->Memorized_Y = Angles[(Player_Data->Shots_Fired - 1) % 5];
				}

				if (Console_Variable_Commentator.Integer == 1)
				{
					PlaySoundW((wchar_t*)Sounds_Exclamation, nullptr, SND_ASYNC | SND_MEMORY);
				}
			}
		}
	}
}