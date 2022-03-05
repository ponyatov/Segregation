#pragma once

void Bruteforce_Memory_Reset()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		if (Player_Data->Memorized != 0)
		{
			Player_Data->Memorized = 0;

			Player_Data->Shots_Fired = (Player_Data->Shots_Fired - 1) % 5;
		}

		Entity_Number += 1;

		if (Entity_Number != 64)
		{
			goto Traverse_Players_Data_Label;
		}
	}
}