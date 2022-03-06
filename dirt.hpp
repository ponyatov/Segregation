#pragma once

namespace dirt
{
	void* player;

	float velocity[3];

	float movegrab[3];

	float origingrab[3];

	float origin[3];

	void* org;

	__int8 grab;

	User_Command_Structure* ucmd;

	Global_Variables_Structure* global;

	void give(void* playerr, Global_Variables_Structure* nariosetnr, User_Command_Structure* aioresntoarsnita)
	{
		player = playerr;
		__builtin_memcpy(velocity, (void*)((unsigned __int32)player + 224), sizeof(velocity));

		__builtin_memcpy(origin, (void*)((unsigned __int32)player + 668), sizeof(origin));

		ucmd = aioresntoarsnita;

		global = nariosetnr;

		grab = 1;
	}

	void CheckVelocity()
	{
		int i; // esi
		float* v3; // ecx

		for (i = 0; i < 3; ++i)
		{
			if ((*(DWORD*)((DWORD)velocity + 4 * i) & 0x7F800000) == 0x7F800000)
			{
				*(DWORD*)((DWORD)velocity + 4 * i) = 0;
			}
			if ((*(DWORD*)((DWORD)origin+ 4 * i) & 0x7F800000) == 2139095040)
			{
				*(DWORD*)((DWORD)origin+ 4 * i) = 0;
			}
			v3 = (float*)((DWORD)velocity + 4 * i);

			if (*v3 <= *(float*)(*(unsigned __int32*)0x243E9598 + 40))
			{
				if (-*(float*)(*(unsigned __int32*)0x243E9598 + 40) > *v3)
				{
					*(float*)((DWORD)velocity + 4 * i) = -*(float*)(*(unsigned __int32*)0x243E9598 + 40);
				}
			}
			else
			{
				*(DWORD*)((DWORD)velocity + 4 * i) = *(DWORD*)(*(unsigned __int32*)0x243E9598 + 40);
			}
		}
	}

	void process()
	{
		*((float*)global + 3) = *(int*)((unsigned __int32)player + 3592) * *((float*)global + 7);
		*((DWORD*)global + 4) = *((DWORD*)global + 7);

		*((float*)global + 4) = *(float*)((unsigned __int32)player + 3888) * *((float*)global + 4);

		float stamina = *(float*)((unsigned __int32)player + 4016);

		if (stamina > 0.0)
		{
			stamina = stamina - *((float*)global + 4) * 1000.0;
			if (stamina < 0.0)
				stamina = 0.0;
		}

		float v2 = 1;
		velocity[2] -= (v2 * *(float*)(*(unsigned __int32*)0x243E90D0 + 40) * 0.5 * global->Frame_Time);
		velocity[2] += *(float*)((DWORD)player + 284) * global->Frame_Time;

		*(float*)((DWORD)player + 284) = 0;

		CheckVelocity();

		if (*(__int32*)((unsigned __int32)player + 456) == -1)
		{
			airmove:
			{
				using AngleVectors = void(__cdecl*)(float* x, float* y, float* z, float* w);

				float f[3], r[3];

				AngleVectors(0x2424B270)(ucmd->View_Angles, f, r, nullptr);

				float fmove = ucmd->Move[0], smove = ucmd->Move[1];
				
				fmove = std::clamp(fmove, (ucmd->Buttons_State & 131072) == 131072 ? -100.f : -250.f, (ucmd->Buttons_State & 131072) == 131072 ? 100.f : 250.f);
				smove = std::clamp(smove, (ucmd->Buttons_State & 131072) == 131072 ? -100.f : -250.f, (ucmd->Buttons_State & 131072) == 131072 ? 100.f : 250.f);

				f[2] = 0;
				r[2] = 0;

				float Magnitude = 1 / (Square_Root(__builtin_powf(f[0], 2) + __builtin_powf(f[1], 2)) + FLT_EPSILON);
				f[0] *= Magnitude;
				f[1] *= Magnitude;
				Magnitude = 1 / (Square_Root(__builtin_powf(r[0], 2) + __builtin_powf(r[1], 2)) + FLT_EPSILON);
				r[0] *= Magnitude;
				r[1] *= Magnitude;

				float wishvel[3];

				for (int i = 0; i < 2; i++)
					wishvel[i] = f[i] * fmove + r[i] * smove;
				wishvel[2] = 0;

				float wishdir[3] = {wishvel[0],wishvel[1],wishvel[2]};

				Magnitude = Square_Root(__builtin_powf(wishdir[0], 2) + __builtin_powf(wishdir[1], 2));

				wishdir[0] *= 1 / (Magnitude + FLT_EPSILON);
				wishdir[1] *= 1 / (Magnitude + FLT_EPSILON);

				float wishspeed = Magnitude; //instruction set inaccuracy

				float m_flMaxSpeed = *(float*)(*(unsigned __int32*)0x243E9598 + 40);

				if (wishspeed != 0 && (wishspeed > m_flMaxSpeed))
				{
					wishvel[0] *= m_flMaxSpeed / wishspeed;
					wishvel[1] *= m_flMaxSpeed / wishspeed;
					wishvel[2] *= m_flMaxSpeed / wishspeed;
					wishspeed = m_flMaxSpeed;
				}

				float accel = *(float*)(*(unsigned __int32*)0x243E9358 + 40);

				float addspeed, accelspeed, currentspeed;

				if (wishspeed > 30)
					wishspeed = 30;

				currentspeed = velocity[0] * wishdir[0] + velocity[1] * wishdir[1] + velocity[2] * wishdir[2];

				addspeed = wishspeed - currentspeed;

				if (addspeed <= 0)
					return;

				accelspeed = accel * wishspeed * global->Frame_Time;

				if (accelspeed > addspeed)
					accelspeed = addspeed;

				for (int i = 0; i < 3; i++)
				{
					velocity[i] += accelspeed * wishdir[i];

					velocity[i] += *(float*)((DWORD)player + 276 + i * 4);
				}

				//PlayerMove

				for (int i = 0; i < 3; i++)
				{
					velocity[i] -= *(float*)((DWORD)player + 276 + i * 4);
				}
			}
		}
		else
		{
			if ((ucmd->Buttons_State & 2) == 2)
			{
				int v12 = 0x3F800000;

				if ((*(__int32*)((unsigned __int32)player + 692) & 2) == 2)
				{
					velocity[2] = Square_Root(91200) * *(float*)&v12;
				}
				else
				{
					velocity[2] += Square_Root(91200) * *(float*)&v12;
				}

				if (stamina > 0)
				{
					velocity[2] *= (100.0 - stamina * 0.001 * 19.0) * 0.01;
				}

				stamina = 1315.789473684211;

				velocity[2] -= (v2 * *(float*)(*(unsigned __int32*)0x243E90D0 + 40) * global->Frame_Time * 0.5);

				CheckVelocity();

				goto airmove;
			}
		}

		grab = 1;
	}

	void __thiscall debugger(void* x, float* y, float z, float w)
	{
		(decltype(&debugger)(org))(x, y, z, w);

		if (grab == 1)
		{
			movegrab[0] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 64);
			movegrab[1] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 68);
			movegrab[2] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 72);

			origingrab[0] = *(float*)(*(DWORD*)((unsigned __int32)x + 8) + 668);
			origingrab[1] = *(float*)(*(DWORD*)((unsigned __int32)x + 8) + 672);
			origingrab[2] = *(float*)(*(DWORD*)((unsigned __int32)x + 8) + 676);

			grab = 0;
		}
	}

	void finalize()
	{
		if (grab == 0)
		{
			wprintf(L"%f %f %f ^ %f %f %f\n",
				Absolute(velocity[0] - movegrab[0]),
				Absolute(velocity[1] - movegrab[1]),
				Absolute(velocity[2] - movegrab[2]),
				Absolute(origingrab[0] - origin[0]),
				Absolute(origingrab[1] - origin[1]),
				Absolute(origingrab[2] - origin[2]));
		}
	}

	void attach_Debbbuger()
	{
		Redirection_Manager::Redirect_Function(org, 2, (void*)0x240C96F0, 1, (void*)debugger);
	}
}