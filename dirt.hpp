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

	struct trace_t
	{
		__int8 arienost[1234];
	};

	struct Ray_t
	{
		__int8 airesnt[345];
	};

	float* GetPlayerMins()
	{
		if ((*(__int32*)((unsigned __int32)player + 692) & 2) == 0)
		{
			return (float*)0x243FB894;
		}

		return (float*)0x243FB8AC;
	}

	float* GetPlayerMaxs()
	{
		if ((*(__int32*)((unsigned __int32)player + 692) & 2) == 0)
		{
			return (float*)0x243FB8A0;
		}

		return (float*)0x243FB8B8;
	}

	void TracePlayerBBox(float* start, float* end, unsigned int fMask, int collisionGroup, trace_t* pm)
	{
		Ray_t ray;
		using rayinit = void(__thiscall*)(Ray_t* ray, float* start, float* end, float* mins, float* maxs);
		rayinit(0x24012BF0)(&ray, start, end, GetPlayerMins(), GetPlayerMaxs());
		using UTIL_TraceRay = void(__cdecl*)(Ray_t* ray, __int32 Mask, void* handle, __int32 colgroup, trace_t* trace);
		DWORD v8 = *(DWORD*)((unsigned __int32)player + 160);
		int v9; // edx
		void* v10; // ecx
		if (v8 == -1
			|| (v9 = 16 * (v8 & 0xFFF),
				*(DWORD*)(*(char**)0x24392FDC + v9 + 8) != v8 >> 12))
		{
			v10 = 0;
		}
		else
		{
			v10 = *(void**)(*(char**)0x24392FDC + v9 + 4);
		}
		UTIL_TraceRay(0x240525E0)(&ray, fMask, v10, collisionGroup, pm);
	}

	__int32 TryPlayerMove(float* pFirstDest, trace_t* pFirstTrace)
	{
		int			bumpcount, numbumps;
		float		dir[3];
		float		d;
		int			numplanes;
		float		planes[5][3];
		float		primal_velocity[3], original_velocity[3];
		float      new_velocity[3];
		int			i, j;
		trace_t	pm;
		float		end[3];
		float		time_left, allFraction;
		int			blocked;
		numbumps = 4;
		blocked = 0;
		numplanes = 0;

		__builtin_memcpy(original_velocity, velocity, sizeof(velocity));
		__builtin_memcpy(primal_velocity, velocity, sizeof(velocity));

		allFraction = 0;
		time_left = global->Frame_Time;

		__builtin_memset(new_velocity, 0, sizeof(new_velocity));

		for (bumpcount = 0; bumpcount < numbumps; bumpcount++)
		{
			if (__builtin_powf(velocity[0], 2) + __builtin_powf(velocity[1], 2) + __builtin_powf(velocity[2], 2) == 0)
				break;

			end[0] = origin[0] + velocity[0] * time_left;
			end[1] = origin[1] + velocity[1] * time_left;
			end[2] = origin[2] + velocity[2] * time_left;

			if (pFirstDest
				&& *pFirstDest == *end
				&& pFirstDest[1] == *&end[1]
				&& pFirstDest[2] == *&end[2])
			{
				__builtin_memcpy(&pm, pFirstTrace, sizeof(pm));
			}
			else
			{
				TracePlayerBBox(origin, end, 33636363, 8, &pm);
			}

			allFraction += *(float*)((unsigned __int32)&pm + 0x2c);

			if (*(__int8*)((unsigned __int32)&pm + 0x36))
			{
				velocity[0] = 0;
				velocity[1] = 0;
				velocity[2] = 0;
				return 4;
			}

			if (*(float*)((unsigned __int32)&pm + 0x2c) > 0)
			{
				origin[0] = *(float*)((unsigned __int32)&pm + 0xc);
				origin[1] = *(float*)((unsigned __int32)&pm + 0xc+4);
				origin[2] = *(float*)((unsigned __int32)&pm + 0xc+8);
				original_velocity[0] = velocity[0];
				original_velocity[1] = velocity[1];
				original_velocity[2] = velocity[2];
				numplanes = 0;
			}

			if (*(float*)((unsigned __int32)&pm + 0x2c) == 1)
			{
				break;
			}

			if (*(float*)((unsigned __int32)&pm + 0x20) > 0.7)
				blocked |= 1u;
			if (*(float*)((unsigned __int32)&pm + 0x20) == 0.0)
				blocked |= 2u;

			time_left -= time_left * *(float*)((unsigned __int32)&pm + 0x2c);

			if (numplanes >= 5)
			{
				break;
			}

			planes[numplanes][0] = *(float*)((unsigned __int32)&pm + 0x18);
			planes[numplanes][1] = *(float*)((unsigned __int32)&pm + 0x18 + 4);
			planes[numplanes][2] = *(float*)((unsigned __int32)&pm + 0x18 + 8);

			++numplanes;
			using ClipVelocity = __int32(__stdcall*)(float* in, float* normal, float* out, float overbounce);
			if (numplanes == 1 && *(__int32*)((unsigned __int32)player + 456) == -1)
			{
				for (i = 0; i < numplanes; i++)
				{
					if (planes[i][2] > 0.7)
					{
						ClipVelocity(0x240C8C90)(original_velocity, planes[i], new_velocity, 1);
					}
					else
					{
						ClipVelocity(0x240C8C90)(original_velocity, planes[i], new_velocity, 1.0 + *(float*)(*(unsigned __int32*)0x243E9550 + 40) * (1 - *(float*)((unsigned __int32)player + 3936)));
					}
				}

				velocity[0] = new_velocity[0];
				velocity[1] = new_velocity[1];
				velocity[2] = new_velocity[2];
				original_velocity[0] = new_velocity[0];
				original_velocity[1] = new_velocity[1];
				original_velocity[2] = new_velocity[2];
			}
			else
			{
				for (i = 0; i < numplanes; i++)
				{
					ClipVelocity(0x240C8C90)(
						original_velocity,
						planes[i],
						velocity,
						1);

					for (j = 0; j < numplanes; j++)
						if (j != i)
						{
							if (velocity[0] * planes[j][0] + velocity[1] * planes[j][1] + velocity[2] * planes[j][2] < 0)
								break;
						}
					if (j == numplanes)
						break;
				}

				if (i == numplanes)
				{
					if (numplanes != 2)
					{
						velocity[0] = 0;
						velocity[1] = 0;
						velocity[2] = 0;
						break;
					}
					dir[0] = planes[0][1] * planes[1][2] - planes[0][2] * planes[1][1];
					dir[1] = planes[0][2] * planes[1][0] - planes[0][0] * planes[1][2];
					dir[2] = planes[0][0] * planes[1][1] - planes[0][1] * planes[1][0];
					float Magnitude = 1 / (Square_Root(__builtin_powf(dir[0], 2) + __builtin_powf(dir[1], 2) + __builtin_powf(dir[2], 2)) + FLT_EPSILON);
					dir[0] *= Magnitude;
					dir[1] *= Magnitude;
					dir[2] *= Magnitude;
					d = dir[0] * velocity[0] + dir[1] * velocity[1] + dir[2] * velocity[2];
					velocity[0] = dir[0] * d;
					velocity[1] = dir[1] * d;
					velocity[2] = dir[2] * d;
				}

				d = velocity[0] * primal_velocity[0] + velocity[1] * primal_velocity[1] + velocity[2] * primal_velocity[2];
				if (d <= 0)
				{
					velocity[0] = 0;
					velocity[1] = 0;
					velocity[2] = 0;
					break;
				}
			}
		}

		if (allFraction == 0)
		{
			velocity[0] = 0;
			velocity[1] = 0;
			velocity[2] = 0;
		}

		return blocked;
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

				float wishspeed = Magnitude;

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

				float wishspd = wishspeed;

				if (wishspd > 30)
					wishspd = 30;

				currentspeed = velocity[0] * wishdir[0] + velocity[1] * wishdir[1] + velocity[2] * wishdir[2];

				addspeed = wishspd - currentspeed;

				if (addspeed > 0)
				{
					accelspeed = *(float*)((unsigned __int32)player + 3936) * *((float*)global + 4) * wishspeed * accel;

					if (accelspeed > addspeed)
						accelspeed = addspeed;

					for (int i = 0; i < 3; i++)
					{
						velocity[i] += accelspeed * wishdir[i];
					}
				}

				for (int i = 0; i < 3; i++)
				{
					velocity[i] += *(float*)((DWORD)player + 276 + i * 4);
				}

				TryPlayerMove(nullptr, nullptr);

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

				if ((*(__int32*)((unsigned __int32)player + 692) & 2) == 0)
				{
					velocity[2] += Square_Root(91200) * *(float*)&v12;
				}
				else
				{
					velocity[2] = Square_Root(91200) * *(float*)&v12;
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

	void __thiscall debugger(void* x)
	{
		(decltype(&debugger)(org))(x);

		if (grab == 1)
		{
			movegrab[0] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 64);
			movegrab[1] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 68);
			movegrab[2] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 72);

			origingrab[0] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 100);
			origingrab[1] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 104);
			origingrab[2] = *(float*)(*(DWORD*)((unsigned __int32)x + 4) + 108);
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
		Redirection_Manager::Redirect_Function(org, 0, (void*)0x240C97F0, 1, (void*)debugger);
	}
}