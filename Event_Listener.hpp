#pragma once

void __stdcall Event_Processor(void* Event)
{
	using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

	if (Get_Integer_Type(537579136)(Event, (char*)"timelimit", nullptr) != 0)
	{
		__builtin_memset(Players_Data, 0, sizeof(Players_Data));

		__builtin_memset(Players_History, 0, sizeof(Players_History));
	}
	else
	{
		if (Console_Variable_Commentator.Integer == 1)
		{
			void* Local_Player = *(void**)607867332;

			if (Local_Player != nullptr)
			{
				__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);

				using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

				__int32 Victim_Identifier = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));

				if (Local_Player_Number == Victim_Identifier)
				{
					PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
				}
				else
				{
					__int32 Killer_Identifier = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"attacker", nullptr));

					if (Local_Player_Number == Killer_Identifier)
					{
						PlaySoundW((wchar_t*)Sounds_Exclamation, nullptr, SND_ASYNC | SND_MEMORY);
					}
				}
			}
		}
	}
}