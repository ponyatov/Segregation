#pragma once

void* Original_Shutdown_Caller_Location;

void __thiscall Redirected_Shutdown(void* Unknown_Parameter, char* Reason)
{
	(decltype(&Redirected_Shutdown)(Original_Shutdown_Caller_Location))(Unknown_Parameter, (char*)"Segregation");

	__builtin_memset(Players_Data, 0, sizeof(Players_Data));

	__builtin_memset(Players_History, 0, sizeof(Players_History));
}