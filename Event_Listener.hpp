#pragma once

void __stdcall Event_Processor(void* Event)
{
	if (Console_Variable_Commentator.Integer == 1)
	{
		void* Local_Player = *(void**)607867332;

		if (Local_Player != nullptr)
		{
			__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);

			using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

			using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

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