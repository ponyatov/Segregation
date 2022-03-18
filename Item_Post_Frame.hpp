#pragma once

void* Original_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Weapon)
{
	if (__builtin_signbitf(Shot_Time) == 0)
	{
		using Get_Weapon_Data_Type = void* (__thiscall*)(void* Weapon);

		void* Weapon_Data = Get_Weapon_Data_Type(604037872)(Weapon);

		if (*(__int8*)((unsigned __int32)Weapon_Data + 1624) == 1)
		{
			using Get_Primary_Ammo_Capacity_Type = __int32(__thiscall**)(void* Weapon);

			if (*(__int32*)((unsigned __int32)Weapon + 1788) == (*Get_Primary_Ammo_Capacity_Type(*(unsigned __int32*)Weapon + 1000))(Weapon))
			{
				*(float*)((unsigned __int32)Weapon + 1888) = 0.9f;
			}
		}

		float Accuracy = *(float*)((unsigned __int32)Weapon + 1888);

		(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller_Location))(Weapon);

		if (Is_First_Command_Predicted == 1)
		{
			*(float*)((unsigned __int32)Weapon + 1888) = Accuracy;
		}
	}
}