#pragma once

void* Original_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Weapon)
{
	float Accuracy = *(float*)((unsigned __int32)Weapon + 1888);

	(decltype(&Redirected_Item_Post_Frame)(Original_Item_Post_Frame_Caller_Location))(Weapon);

	if (Is_First_Command_Predicted == 1)
	{
		*(float*)((unsigned __int32)Weapon + 1888) = Accuracy;
	}
}