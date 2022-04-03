#pragma once

void Redirected_Send_Move()
{
	struct Move_Message_Structure
	{
		unsigned __int8 Move_Message[69];

		void Construct(__int8* Data)
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

	Move_Message_Structure Move_Message;

	__int8 Data[4000];

	Move_Message.Construct(Data);

	__int32 Choked_Commands = *(__int32*)540627872;

	__int32 Next_Command_Number = *(__int32*)540627868 + Choked_Commands + 1;

	__int32 Commands_Queue = std::clamp(Choked_Commands + 1, 0, 15);

	__int32 Extra_Commands_Queue = Choked_Commands + 1 - Commands_Queue;

	__int32 Backup_Commands = std::clamp(Extra_Commands_Queue, 2, 7);

	*(__int32*)((unsigned __int32)&Move_Message + 16) = Backup_Commands;

	*(__int32*)((unsigned __int32)&Move_Message + 20) = Commands_Queue;

	__int32 To_Command_Number = Next_Command_Number - (Commands_Queue + Backup_Commands) + 1;

	__int32 From_Command_Number = -1;

	Write_Command_Label:
	{
		using Write_Command_Type = __int8(__thiscall*)(void* Client, void* Data, __int32 From, __int32 To, __int8 New);

		static void* Client_Location = *(void**)540494868;

		Write_Command_Type(604533440)(Client_Location, (void*)((unsigned __int32)&Move_Message + 52), From_Command_Number, To_Command_Number, To_Command_Number != Next_Command_Number - Commands_Queue + 1);

		From_Command_Number = To_Command_Number;

		To_Command_Number += 1;

		if (To_Command_Number <= Next_Command_Number)
		{
			goto Write_Command_Label;
		}
	}

	void* Network_Channel = *(void**)540608912;

	if (Extra_Commands_Queue > 0)
	{
		*(__int32*)((unsigned __int32)Network_Channel + 28) -= Extra_Commands_Queue;
	}

	using Send_Network_Message_Type = void(__thiscall*)(void* Network_Channel, void* Message, __int8 Unknown_Parameter);

	Send_Network_Message_Type(537917776)(Network_Channel, &Move_Message, 0);
}