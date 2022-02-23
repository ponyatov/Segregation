#pragma once

void* Original_Is_Missing_Texture_Caller_Location;

__int8 __thiscall Redirected_Is_Missing_Texture(void* Texture)
{
	__int8 Is_Missing_Texture = (decltype(&Redirected_Is_Missing_Texture)(Original_Is_Missing_Texture_Caller_Location))(Texture);

	if (Is_Missing_Texture == 0)
	{
		static void* Get_Group_Location = (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 18224);

		using Get_Group_Type = char*(__thiscall*)(void* Texture);

		char* Group = Get_Group_Type(Get_Group_Location)(Texture);

		using Color_Modulate_Type = void(__thiscall**)(void* Material, float Red, float Green, float Blue);

		if (*(unsigned __int16*)Group == 'oW')
		{
			using Alpha_Modulate_Type = void(__thiscall**)(void* Material, float Alpha);

			(*Alpha_Modulate_Type(*(unsigned __int32*)Texture + 116))(Texture, 0.25f);

			(*Color_Modulate_Type(*(unsigned __int32*)Texture + 120))(Texture, 1, 0.5f, 0.5f);
		}
		else
		{
			if (*(unsigned __int16*)Group == 'kS')
			{
				(*Color_Modulate_Type(*(unsigned __int32*)Texture + 120))(Texture, 0, 0, 0);
			}
		}
	}

	return Is_Missing_Texture;
}