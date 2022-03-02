#include <d3d9.h>

#include "Byte_Manager/Byte_Manager.hpp"

#include <cstdio>

#include "Sounds.hpp"

#include "Structures.hpp"

#include "Console_Variables.hpp"

#include "Draw_Crosshair.hpp"

#define Bits_32

#include "Redirection_Manager/Redirection_Manager.hpp"

#include "Is_Error_Material.hpp"

#include "Interpolate.hpp"

#include "Priority.hpp"

#include "Angles_Y.hpp"

#include "Frame_Stage_Notify.hpp"

#include "Run_Prediction.hpp"

#include <vector>

#include <algorithm>

#include "Weapon_Spread.hpp"

#include "Update_Animation.hpp"

#include "Converge_Angles.hpp"

#include "Copy_User_Command.hpp"

#include "Send_Move.hpp"

#include "Run_Command.hpp"

#include "Item_Post_Frame.hpp"

#pragma comment(lib, "Winmm.lib")

#include "Event_Listener.hpp"

#include "Shutdown.hpp"

__int32 __stdcall DllMain(void* This_Module_Location, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9360), 1, 195);

			AllocConsole();

			SetConsoleTitleW(L"Segregation");

			_wfreopen(L"CONOUT$", L"w", stdout);

			SetConsoleOutputCP(65001);

			HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

			CONSOLE_FONT_INFOEX Console_Font_Information;

			Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

			Console_Font_Information.nFont = 0;

			Console_Font_Information.dwFontSize.X = 0;

			Console_Font_Information.dwFontSize.Y = 12;

			Console_Font_Information.FontFamily = FF_DONTCARE;

			Console_Font_Information.FontWeight = FW_NORMAL;
			
			wcscpy(Console_Font_Information.FaceName, L"Terminal");

			SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

			CONSOLE_CURSOR_INFO Console_Cursor_Information;

			Console_Cursor_Information.bVisible = 0;

			Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

			SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

			SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

			CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

			GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

			COORD Top_Left =
			{
				0,

				0
			};

			DWORD Characters_Written_Count;

			FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

			wprintf(L"[ + ] Remote Thread Dispatch\n");

			unsigned __int8 Apply_View_Effects_Bytes[30] =
			{
				7,

				144,

				144,

				144,

				144,

				144,

				144,

				217,

				31,

				217,

				71,

				4,

				144,

				144,

				144,

				144,

				144,

				144,

				217,

				95,

				4,

				217,

				71,

				8,

				144,

				144,

				144,

				144,

				144,

				144
			};

			Byte_Manager::Copy_Bytes(1, (void*)604082899, sizeof(Apply_View_Effects_Bytes), Apply_View_Effects_Bytes);

			wprintf(L"[ + ] View Effects\n");

			using Create_Console_Variable_Type = void(__thiscall*)(Console_Variable_Structure* Variable, char* Name, char* Value, void* Unknown_Parameter);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Uber_Alles_Scale, (char*)"Uber_Alles_Scale", (char*)"8", nullptr);

			wprintf(L"[ + ] Uber_Alles_Scale %p\n", &Console_Variable_Uber_Alles_Scale);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Uber_Alles_Speed, (char*)"Uber_Alles_Speed", (char*)"192", nullptr);

			wprintf(L"[ + ] Uber_Alles_Speed %p\n", &Console_Variable_Uber_Alles_Speed);

			Redirection_Manager::Redirect_Function(1, (void*)605951488, (void*)Redirected_Draw_Crosshair);

			wprintf(L"[ + ] Crosshair\n");

			Redirection_Manager::Redirect_Function(Original_Is_Error_Material_Caller_Location, 2, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 20432), 1, (void*)Redirected_Is_Error_Material);

			Byte_Manager::Set_Bytes(1, (void*)605809168, 1, 195);

			unsigned __int8 Smoke_Bytes[3] =
			{
				194,

				8,

				0
			};

			Byte_Manager::Copy_Bytes(1, (void*)605610608, sizeof(Smoke_Bytes), Smoke_Bytes);

			wprintf(L"[ + ] Materials\n");

			Redirection_Manager::Redirect_Function(Original_Interpolate_Caller_Location, 0, (void*)604201536, 1, (void*)Redirected_Interpolate);

			wprintf(L"[ + ] Interpolation\n");

			using Create_Console_Command_Type = void(__thiscall*)(Console_Variable_Structure* Variable, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

			Create_Console_Command_Type(606174864)(&Console_Variable_Get_Priorities, (char*)"Get_Priorities", (void*)Get_Priorities, nullptr, nullptr, nullptr);

			wprintf(L"[ + ] Get_Priorities %p\n", &Console_Variable_Get_Priorities);

			using Create_Handled_Console_Variable_Type = void(__thiscall*)(Console_Variable_Structure* Variable, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

			Create_Handled_Console_Variable_Type(539131040)(&Console_Variable_Set_Priority, (char*)"Set_Priority", (char*)"1 0", nullptr, nullptr, (void*)Set_Priority);

			wprintf(L"[ + ] Set_Priority %p\n", &Console_Variable_Set_Priority);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Bruteforce, (char*)"Bruteforce", (char*)"1", nullptr);

			wprintf(L"[ + ] Bruteforce %p\n", &Console_Variable_Bruteforce);

			*(void**)608149676 = (void*)Redirected_Angles_Y;

			Redirection_Manager::Redirect_Function(Original_Frame_Stage_Notify_Caller_Location, 1, (void*)604538592, 1, (void*)Redirected_Frame_Stage_Notify);

			wprintf(L"[ + ] Variable Networking\n");

			Redirection_Manager::Redirect_Function(1, (void*)537158848, (void*)Redirected_Run_Prediction);

			Byte_Manager::Set_Bytes(1, (void*)605209595, 1, 235);

			Byte_Manager::Set_Bytes(1, (void*)537149598, 6, 144);

			wprintf(L"[ + ] Prediction\n");

			Create_Console_Variable_Type(539130656)(&Console_Variable_Extrapolation, (char*)"Extrapolation", (char*)"0", nullptr);

			wprintf(L"[ + ] Extrapolation %p\n", &Console_Variable_Extrapolation);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Extrapolation_Tolerance, (char*)"Extrapolation_Tolerance", (char*)"0", nullptr);

			wprintf(L"[ + ] Extrapolation_Tolerance %p\n", &Console_Variable_Extrapolation_Tolerance);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Extrapolation_Gravity_Tolerance, (char*)"Extrapolation_Gravity_Tolerance", (char*)"0", nullptr);

			wprintf(L"[ + ] Extrapolation_Gravity_Tolerance %p\n", &Console_Variable_Extrapolation_Gravity_Tolerance);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Extrapolation_Force, (char*)"Extrapolation_Force", (char*)"0", nullptr);

			wprintf(L"[ + ] Extrapolation_Force %p\n", &Console_Variable_Extrapolation_Force);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Aim_Height, (char*)"Aim_Height", (char*)"0.85", nullptr);

			wprintf(L"[ + ] Aim_Height %p\n", &Console_Variable_Aim_Height);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Angle_X, (char*)"Angle_X", (char*)"91", nullptr);

			wprintf(L"[ + ] Angle_X %p\n", &Console_Variable_Angle_X);

			Create_Console_Variable_Type(539130656)(&Console_Variable_First_Choked_Angle_Y, (char*)"First_Choked_Angle_Y", (char*)"46", nullptr);

			wprintf(L"[ + ] First_Choked_Angle_Y %p\n", &Console_Variable_First_Choked_Angle_Y);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Second_Choked_Angle_Y, (char*)"Second_Choked_Angle_Y", (char*)"136", nullptr);

			wprintf(L"[ + ] Second_Choked_Angle_Y %p\n", &Console_Variable_Second_Choked_Angle_Y);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Angle_Y, (char*)"Angle_Y", (char*)"-135", nullptr);

			wprintf(L"[ + ] Angle_Y %p\n", &Console_Variable_Angle_Y);

			Byte_Manager::Set_Bytes(1, (void*)605800287, 1, 235);

			Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller_Location, 4,  (void*)605800256, 1, (void*)Redirected_Update_Animation);

			Redirection_Manager::Redirect_Function(Original_Converge_Angles_Caller_Location, 3, (void*)604019936, 1, (void*)Redirected_Converge_Angles);

			wprintf(L"[ + ] Animations\n");

			Redirection_Manager::Redirect_Function(Original_Weapon_Spread_Caller_Location, 1, (void*)605949248, 1, (void*)Redirected_Weapon_Spread);

			wprintf(L"[ + ] Weapon Spread\n");

			Byte_Manager::Set_Bytes(1, (void*)604993824, 3, 144);

			Redirection_Manager::Redirect_Function(Original_Copy_User_Command_Caller_Location, 0, (void*)604850464, 1, (void*)Redirected_Copy_User_Command);

			Redirection_Manager::Redirect_Function(Original_Run_Command_Caller_Location, 0, (void*)605207600, 1, (void*)Redirected_Run_Command);

			Redirection_Manager::Redirect_Function(Original_Item_Post_Frame_Caller_Location, 4, (void*)605953776, 1, (void*)Redirected_Item_Post_Frame);

			wprintf(L"[ + ] Command Processor\n");

			Create_Console_Variable_Type(539130656)(&Console_Variable_Minimum_Choked_Commands, (char*)"Minimum_Choked_Commands", (char*)"2", nullptr);

			wprintf(L"[ + ] Minimum_Choked_Commands %p\n", &Console_Variable_Minimum_Choked_Commands);

			Create_Console_Variable_Type(539130656)(&Console_Variable_Maximum_Choked_Commands, (char*)"Maximum_Choked_Commands", (char*)"21", nullptr);

			wprintf(L"[ + ] Maximum_Choked_Commands %p\n", &Console_Variable_Maximum_Choked_Commands);

			Redirection_Manager::Redirect_Function(1, (void*)537142224, (void*)Redirected_Send_Move);

			wprintf(L"[ + ] Command Networking\n");

			unsigned __int8 Cheat_Flag_Bytes[4] =
			{
				254,

				65,

				44,

				195
			};

			Byte_Manager::Copy_Bytes(1, (void*)538391351, sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

			*(__int8*)542242676 = 1;

			wprintf(L"[ + ] Unlock Variables\n");

			Create_Console_Variable_Type(539130656)(&Console_Variable_Commentator, (char*)"Commentator", (char*)"1", nullptr);

			wprintf(L"[ + ] Commentator %p\n", &Console_Variable_Commentator);

			Event_Listener_Structure* Event_Listener = (Event_Listener_Structure*)malloc(sizeof(void*));

			void* Event_Listener_Table = malloc(sizeof(void*) * 2);

			*(void**)Event_Listener_Table = nullptr;

			*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

			Event_Listener->Table = Event_Listener_Table;

			using Add_Listener_Type = __int8(__thiscall*)(void* Game_Event_Manager, void* Listener, char* Event, __int8 Unknown_Parameter);

			Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_death", 0);

			wprintf(L"[ + ] Events\n");

			Redirection_Manager::Redirect_Function(Original_Shutdown_Caller_Location, 0, (void*)537926128, 1, (void*)Redirected_Shutdown);

			wprintf(L"[ + ] Shutdown\n");
		}
	}

	return 1;
}