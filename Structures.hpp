#pragma once

struct Console_Variable_Structure
{
	__int8 Additional_Bytes_1[32];

	char* String;

	__int8 Additional_Bytes_2[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_3[24];
};

struct Global_Variables_Structure
{
	__int8 Additional_Bytes_1[8];

	float Absolute_Frame_Time;

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct Player_Data_Structure
{
	__int8 Priority;

	float Y;

	__int8 Shots_Fired;
};

struct Player_History_Structure
{
	__int32 Tick_Base;

	float Simulation_Time;

	float Origin[3];
};

struct User_Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float View_Angles[3];

	float Move[3];

	__int32 Buttons_State;

	__int8 Additional_Bytes_2[9];

	__int32 Random_Seed;
};

struct Move_Message_Structure
{
	unsigned __int8 Move_Message[69];

	void Construct(unsigned __int8* Data)
	{
		*(void**)this = (void*)539887964;

		*(__int8*)((unsigned __int32)this + 4) = 0;

		*(__int8*)((unsigned __int32)this + 8) = 0;

		*(__int32*)((unsigned __int32)this + 28) = 0;

		*(__int32*)((unsigned __int32)this + 32) = 0;

		*(__int32*)((unsigned __int32)this + 36) = -1;

		*(__int32*)((unsigned __int32)this + 40) = 0;

		*(__int8*)((unsigned __int32)this + 44) = 0;

		*(__int8*)((unsigned __int32)this + 45) = 1;

		*(__int32*)((unsigned __int32)this + 48) = 0;

		*(void**)((unsigned __int32)this + 52) = Data;

		*(__int32*)((unsigned __int32)this + 56) = 4000;

		*(__int32*)((unsigned __int32)this + 60) = 32000;

		*(__int32*)((unsigned __int32)this + 64) = 0;

		*(__int8*)((unsigned __int32)this + 68) = 0;
	}
};

struct Event_Listener_Structure
{
	void* Table;
};