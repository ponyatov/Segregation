#pragma once

float Shot_Time;

void* Original_Frame_Stage_Notify_Caller_Location;

float Absolute(float X)
{
	asm("fabs" : "+t"(X));

	return X;
}

float Uncompressed_Velocity[90][3];

float Uncompressed_Base_Velocity[90][3];

float Uncompressed_Recoil[90][2];

float Uncompressed_Stamina[90];

void __thiscall Redirected_Frame_Stage_Notify(void* Unknown_Parameter, __int32 Stage)
{
	(decltype(&Redirected_Frame_Stage_Notify)(Original_Frame_Stage_Notify_Caller_Location))(Unknown_Parameter, Stage);

	if (Stage == 4)
	{
		void* Local_Player = *(void**)607867332;

		float* Velocity = (float*)((unsigned __int32)Local_Player + 224);

		__int32 Tick_Base = *(__int32*)((unsigned __int32)Local_Player + 3592) % 90;

		if (Absolute(Velocity[0] - Uncompressed_Velocity[Tick_Base][0]) <= 0.5f)
		{
			if (Absolute(Velocity[1] - Uncompressed_Velocity[Tick_Base][1]) <= 0.5f)
			{
				if (Absolute(Velocity[2] - Uncompressed_Velocity[Tick_Base][2]) <= 0.5f)
				{
					__builtin_memcpy((float*)((unsigned __int32)Local_Player + 224), Uncompressed_Velocity[Tick_Base], sizeof(Uncompressed_Velocity[Tick_Base]));
				}
			}
		}

		float* Base_Velocity = (float*)((unsigned __int32)Local_Player + 276);

		if (Absolute(Base_Velocity[0] - Uncompressed_Base_Velocity[Tick_Base][0]) <= 0.1f)
		{
			if (Absolute(Base_Velocity[1] - Uncompressed_Base_Velocity[Tick_Base][1]) <= 0.1f)
			{
				if (Absolute(Base_Velocity[2] - Uncompressed_Base_Velocity[Tick_Base][2]) <= 0.1f)
				{
					__builtin_memcpy((float*)((unsigned __int32)Local_Player + 276), Uncompressed_Base_Velocity[Tick_Base], sizeof(Uncompressed_Base_Velocity[Tick_Base]));
				}
			}
		}

		float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

		if (Absolute(Recoil[0] - Uncompressed_Recoil[Tick_Base][0]) <= 0.125f)
		{
			if (Absolute(Recoil[1] - Uncompressed_Recoil[Tick_Base][1]) <= 0.125f)
			{
				__builtin_memcpy((float*)((unsigned __int32)Local_Player + 2992), Uncompressed_Recoil[Tick_Base], sizeof(Uncompressed_Recoil[Tick_Base]));
			}
		}

		if (Absolute(*(float*)((unsigned __int32)Local_Player + 4016) - Uncompressed_Stamina[Tick_Base]) <= 0.1f)
		{
			*(float*)((unsigned __int32)Local_Player + 4016) = Uncompressed_Stamina[Tick_Base];
		}
	}
}