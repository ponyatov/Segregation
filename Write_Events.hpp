#pragma once

void* Original_Write_Events_Caller_Location;

void __thiscall Redirected_Write_Events(void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	__builtin_memset(Players_Data, 0, sizeof(Players_Data));

	(decltype(&Redirected_Write_Events)(Original_Write_Events_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2);
}