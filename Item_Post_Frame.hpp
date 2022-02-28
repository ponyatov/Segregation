#pragma once

void* Original_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Weapon)
{
	(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller_Location))(Weapon);

	using Get_Weapon_Data_Type = void*(__thiscall*)(void* Weapon);

	void* Weapon_Data = Get_Weapon_Data_Type(604037872)(Weapon);

	if (*(__int8*)((unsigned __int32)Weapon_Data + 1624) == 1)
	{
		void* Local_Player = *(void**)607867332;

		static float Accuracy;

		if (*(__int32*)((unsigned __int32)Local_Player + 3592) == Shot_Tick)
		{
			Accuracy = *(float*)((unsigned __int32)Weapon + 1888);

			Shot_Tick = 0;
		}

		using Get_Primary_Ammo_Capacity_Type = __int32(__thiscall**)(void* Weapon);

		if (*(__int32*)((unsigned __int32)Weapon + 1788) == (*Get_Primary_Ammo_Capacity_Type(*(unsigned __int32*)Weapon + 1000))(Weapon))
		{
			*(float*)((unsigned __int32)Weapon + 1888) = 0.9f;
		}
		else
		{
			*(float*)((unsigned __int32)Weapon + 1888) = Accuracy;
		}
	}
}