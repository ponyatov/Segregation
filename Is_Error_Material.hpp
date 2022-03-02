#pragma once

void* Original_Is_Error_Material_Caller_Location;

__int8 __thiscall Redirected_Is_Error_Material(void* Material)
{
	__int8 Is_Error_Material = (decltype(&Redirected_Is_Error_Material)(Original_Is_Error_Material_Caller_Location))(Material);

	if (Is_Error_Material == 0)
	{
		static void* Get_Group_Location = (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 18224);

		using Get_Group_Type = char*(__thiscall*)(void* Material);

		char* Group = Get_Group_Type(Get_Group_Location)(Material);

		using Color_Modulate_Type = void(__thiscall**)(void* Material, float Red, float Green, float Blue);

		if (*(unsigned __int16*)Group == 'oW')
		{
			using Alpha_Modulate_Type = void(__thiscall**)(void* Material, float Alpha);

			(*Alpha_Modulate_Type(*(unsigned __int32*)Material + 116))(Material, 0.25f);

			(*Color_Modulate_Type(*(unsigned __int32*)Material + 120))(Material, 1, 0.5f, 0.5f);
		}
		else
		{
			if (*(unsigned __int16*)Group == 'kS')
			{
				(*Color_Modulate_Type(*(unsigned __int32*)Material + 120))(Material, 0, 0, 0);
			}
		}
	}

	return Is_Error_Material;
}