#pragma once

namespace dirt
{
	void* player;

	float velocity[3];

	float movegrab[3];

	float origin[3];

	void* org;

	__int8 grab;

	Global_Variables_Structure* global;

	void give(void* playerr, Global_Variables_Structure* nariosetnr)
	{
		player = playerr;

		__builtin_memcpy(velocity, (void*)((unsigned __int32)player + 224), sizeof(velocity));

		__builtin_memcpy(origin, (void*)((unsigned __int32)player + 668), sizeof(origin));

		global = nariosetnr;

		grab = 1;
	}

	void process()
	{
		*((float*)global + 3) = (double)*(int*)((unsigned __int32)player + 3592) * *((float*)global + 7);
		*((DWORD*)global + 4) = *((DWORD*)global + 7);

		*((float*)global + 4) = *(float*)((unsigned __int32)player + 3888) * *((float*)global + 4);

		float v2 = 1;
		velocity[2] = velocity[2]
			- v2 * *(float*)(*(unsigned __int32*)0x243E90D0 + 40) * *((float*)global + 4) * 0.5;
		velocity[2] = *((float*)global + 4) * *(float*)((DWORD)player + 284)
			+ velocity[2];

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

			grab = 0;
		}
	}

	void finalize()
	{
		if (grab == 0)
		{
			wprintf(L"%f %f %f\n",
				Absolute(velocity[0] - movegrab[0]),
				Absolute(velocity[0] - movegrab[0]),
				Absolute(velocity[0] - movegrab[0]));
		}
	}

	void attach_Debbbuger()
	{
		Redirection_Manager::Redirect_Function(org, 3, (void*)0x240CACF0, 1, (void*)debugger);
	}
}