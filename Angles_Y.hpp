#pragma once

void Redirected_Angles_Y(void* Packet, void* Entity, void* Data)
{
	float Y = *(float*)((unsigned __int32)Packet + 4);

	*(float*)Data = Y;

	__int32 Entity_Number = *(__int32*)((unsigned __int32)Entity + 80) - 1;

	Players_Data[Entity_Number].Y = Y;

	void* Animation_State = *(void**)((unsigned __int32)Entity + 3968);

	Players_Data[Entity_Number].Animation_State = (void*)((unsigned __int32)Animation_State - 148);
}