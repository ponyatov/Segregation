#pragma once

void Redirected_Angles_Y(void* Packet, void* Entity, void* Data)
{
	float Y = *(float*)((unsigned __int32)Packet + 4);

	*(float*)Data = Y;

	Players_Data[*(__int32*)((unsigned __int32)Entity + 80) - 1].Y = Y;
}