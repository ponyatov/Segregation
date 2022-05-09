#pragma once

Interface_Structure Console_Variable_Commentator;

Interface_Structure Console_Variable_Get_Priorities;

#include "Priority.hpp"

Interface_Structure Console_Variable_Set_Priority;

Interface_Structure Console_Variable_Bruteforce_Memory;

Interface_Structure Console_Variable_Bruteforce_Tolerance;

#include "Bruteforce.hpp"

Interface_Structure Console_Variable_Bruteforce;

Interface_Structure Console_Variable_Minimum_Choked_Commands;

Interface_Structure Console_Variable_Maximum_Choked_Commands;

Interface_Structure Console_Variable_Flow_Synchronization;

Interface_Structure Console_Variable_Flow_Synchronization_Tolerance;

Interface_Structure Console_Variable_Aim_Height;

Interface_Structure Console_Variable_Angle_X;

Interface_Structure Console_Variable_First_Choked_Angle_Y;

Interface_Structure Console_Variable_Second_Choked_Angle_Y;

Interface_Structure Console_Variable_Angle_Y;

Interface_Structure Console_Variable_Uber_Alles_Scale;

Interface_Structure Console_Variable_Uber_Alles_Speed;

void Implement_Extended_Interface()
{
	using Create_Console_Variable_Type = void(__thiscall*)(Interface_Structure* Variable, char* Name, char* Value, void* Unknown_Parameter);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Commentator, (char*)"Commentator", (char*)"1", nullptr);

	wprintf(L"[ + ] Commentator %p\n", &Console_Variable_Commentator);

	using Create_Console_Command_Type = void(__thiscall*)(Interface_Structure* Variable, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

	Create_Console_Command_Type(606174864)(&Console_Variable_Get_Priorities, (char*)"Get_Priorities", (void*)Get_Priorities, nullptr, nullptr, nullptr);

	wprintf(L"[ + ] Get_Priorities %p\n", &Console_Variable_Get_Priorities);

	using Create_Handled_Console_Variable_Type = void(__thiscall*)(Interface_Structure* Variable, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

	Create_Handled_Console_Variable_Type(539131040)(&Console_Variable_Set_Priority, (char*)"Set_Priority", (char*)"1 0", nullptr, nullptr, (void*)Set_Priority);

	wprintf(L"[ + ] Set_Priority %p\n", &Console_Variable_Set_Priority);

	Create_Handled_Console_Variable_Type(539131040)(&Console_Variable_Bruteforce_Memory, (char*)"Bruteforce_Memory", (char*)"1", nullptr, nullptr, (void*)Bruteforce_Reset_Memory);

	wprintf(L"[ + ] Bruteforce_Memory %p\n", &Console_Variable_Bruteforce_Memory);

	Create_Handled_Console_Variable_Type(539131040)(&Console_Variable_Bruteforce_Tolerance, (char*)"Bruteforce_Tolerance", (char*)"0", nullptr, nullptr, (void*)Bruteforce_Reset_Tolerance);

	wprintf(L"[ + ] Bruteforce_Tolerance %p\n", &Console_Variable_Bruteforce_Tolerance);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Bruteforce, (char*)"Bruteforce", (char*)"1", nullptr);

	wprintf(L"[ + ] Bruteforce %p\n", &Console_Variable_Bruteforce);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Minimum_Choked_Commands, (char*)"Minimum_Choked_Commands", (char*)"2", nullptr);

	wprintf(L"[ + ] Minimum_Choked_Commands %p\n", &Console_Variable_Minimum_Choked_Commands);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Maximum_Choked_Commands, (char*)"Maximum_Choked_Commands", (char*)"21", nullptr);

	wprintf(L"[ + ] Maximum_Choked_Commands %p\n", &Console_Variable_Maximum_Choked_Commands);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Flow_Synchronization, (char*)"Flow_Synchronization", (char*)"1", nullptr);

	wprintf(L"[ + ] Flow_Synchronization %p\n", &Console_Variable_Flow_Synchronization);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Flow_Synchronization_Tolerance, (char*)"Flow_Synchronization_Tolerance", (char*)"1", nullptr);

	wprintf(L"[ + ] Flow_Synchronization_Tolerance %p\n", &Console_Variable_Flow_Synchronization_Tolerance);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Aim_Height, (char*)"Aim_Height", (char*)"0.95", nullptr);

	wprintf(L"[ + ] Aim_Height %p\n", &Console_Variable_Aim_Height);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Angle_X, (char*)"Angle_X", (char*)"91", nullptr);

	wprintf(L"[ + ] Angle_X %p\n", &Console_Variable_Angle_X);

	Create_Console_Variable_Type(539130656)(&Console_Variable_First_Choked_Angle_Y, (char*)"First_Choked_Angle_Y", (char*)"46", nullptr);

	wprintf(L"[ + ] First_Choked_Angle_Y %p\n", &Console_Variable_First_Choked_Angle_Y);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Second_Choked_Angle_Y, (char*)"Second_Choked_Angle_Y", (char*)"136", nullptr);

	wprintf(L"[ + ] Second_Choked_Angle_Y %p\n", &Console_Variable_Second_Choked_Angle_Y);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Angle_Y, (char*)"Angle_Y", (char*)"-135", nullptr);

	wprintf(L"[ + ] Angle_Y %p\n", &Console_Variable_Angle_Y);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Uber_Alles_Scale, (char*)"Uber_Alles_Scale", (char*)"8", nullptr);

	wprintf(L"[ + ] Uber_Alles_Scale %p\n", &Console_Variable_Uber_Alles_Scale);

	Create_Console_Variable_Type(539130656)(&Console_Variable_Uber_Alles_Speed, (char*)"Uber_Alles_Speed", (char*)"192", nullptr);

	wprintf(L"[ + ] Uber_Alles_Speed %p\n", &Console_Variable_Uber_Alles_Speed);
}