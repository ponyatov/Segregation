#pragma once

void* Original_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Weapon)
{
	static __int8 Shots_Fired;

	if (__builtin_signbitf(Shot_Time) == 0)
	{
		float Previous_Accuracy = *(float*)((unsigned __int32)Weapon + 1888);

		(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller_Location))(Weapon);

		using Get_Weapon_Data_Type = void*(__thiscall*)(void* Weapon);

		void* Weapon_Data = Get_Weapon_Data_Type(604037872)(Weapon);

		if (*(__int8*)((unsigned __int32)Weapon_Data + 1624) == 1)
		{
			if (*(__int8*)((unsigned __int32)Weapon + 1788) == 0)
			{
				*(float*)((unsigned __int32)Weapon + 1888) = 0.9f;
			}
			else
			{
				if (*(__int32*)(*(unsigned __int32*)607867332 + 4024) == 1)
				{
					if (Shots_Fired == 0)
					{
						Shots_Fired = 1;
					}
					else
					{
						*(float*)((unsigned __int32)Weapon + 1888) = Previous_Accuracy;
					}
				}
			}
		}
	}
	else
	{
		if (Shot_Time == -0)
		{
			Shots_Fired = 0;
		}

		Shot_Time *= -1;
	}
}