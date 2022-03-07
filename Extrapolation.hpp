#pragma once

namespace Extrapolation
{
	void* Player;

	float Velocity[3];

	float Lagged_Movement_Time;

	float Stamina;

	__int32 Ground;

	__int8 Ducking;

	float Origin[3];

	void Initialize(void* Target, float Interval_Per_Tick)
	{
		Player = Target;

		__builtin_memcpy(Velocity, (void*)((unsigned __int32)Player + 224), sizeof(Velocity));

		Lagged_Movement_Time = Interval_Per_Tick * *(float*)((unsigned __int32)Player + 3888);

		Stamina = *(float*)((unsigned __int32)Player + 4016);

		Ducking = (*(__int32*)((unsigned __int32)Player + 692) & 2) == 2;

		Ground = *(__int32*)((unsigned __int32)Player + 456);

		__builtin_memcpy(Origin, (void*)((unsigned __int32)Player + 668), sizeof(Origin));
	}

	void Trace_Ray_Bounding_Box(float* Start, float* End, Trace_Structure* Trace)
	{
		using Trace_Ray_Type = void(__cdecl*)(Ray_Structure* Ray, __int32 Mask, void* Skip, __int32 Group, Trace_Structure* Trace);

		Ray_Structure Ray;

		using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End, float* Minimum, float* Maximum);

		Initialize_Ray_Type(604056560)(&Ray, Start, End, (float*)((unsigned __int32)608155796 + 24 * Ducking), (float*)((unsigned __int32)608155808 + 24 * Ducking));

		Trace_Ray_Type(604317152)(&Ray, 33636363, Player, 8, Trace);
	}

	void Gravity()
	{
		Velocity[2] -= 400 * Lagged_Movement_Time;

		Stamina -= Lagged_Movement_Time * 1000;

		if (Ground == -1)
		{
			Air_Move_Label:
			{
				float Time_Left = Lagged_Movement_Time;

				__int32 Bump_Number = 0;

				Bump_Label:
				{
					float End[3] =
					{
						Origin[0] + Velocity[0] * Time_Left,

						Origin[1] + Velocity[1] * Time_Left,

						Origin[2] + Velocity[2] * Time_Left
					};

					Trace_Structure Trace;

					Trace_Ray_Bounding_Box(Origin, End, &Trace);

					__builtin_memcpy(Origin, Trace.End, sizeof(Trace.End));

					Time_Left -= Time_Left * Trace.Fraction;

					using Clip_Velocity_Type = void(__stdcall*)(float* In, float* Normal, float* Out, float Over_Bounce);

					float Clipped_Velocity[3];

					Clip_Velocity_Type(604802192)(Velocity, Trace.Plane, Clipped_Velocity, 0);

					__builtin_memcpy(Velocity, Clipped_Velocity, sizeof(Clipped_Velocity));

					Bump_Number += 1;

					if (Bump_Number != 2)
					{
						goto Bump_Label;
					}
				}

				Velocity[2] -= 400 * Lagged_Movement_Time;
			}
		}
		else
		{
			Velocity[2] = (Velocity[2] * (float)(Ducking == 0) + 301.99337f) * (100 - Stamina / 1000 * 19) / 100 - 400 * Lagged_Movement_Time;

			goto Air_Move_Label;
		}

		if (Velocity[2] <= 140)
		{
			float End[3] =
			{
				Origin[0],

				Origin[1],

				Origin[2] - 2
			};

			Trace_Structure Trace;

			Trace_Ray_Bounding_Box(Origin, End, &Trace);

			if (Trace.Entity == nullptr)
			{
				Ground = -1;
			}
			else
			{
				Ground = 0;

				Velocity[2] = 0;

				Stamina = 1315.7894f;
			}
		}
		else
		{
			Ground = -1;
		}
	}
}