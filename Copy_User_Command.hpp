#pragma once

__int32 Shot_Tick;

float Arc_Tangent_2(float X, float Y)
{
	asm("fpatan" : "+t"(X) : "u"(Y));

	return X;
}

float Square_Root(float X)
{
	asm("fsqrt" : "+t"(X));

	return X;
}

void Sine_Cosine(float& Sine, float& Cosine, float Value)
{
	asm("fsincos" : "=u"(Sine), "=t"(Cosine) : "1"(Value));
}

void* Original_Copy_User_Command_Caller_Location;

void __thiscall Redirected_Copy_User_Command(void* Unknown_Parameter, User_Command_Structure* User_Command)
{
	Redirected_Run_Prediction();

	Shot_Tick = -1;

	void* Local_Player = *(void**)607867332;

	float Local_Player_Previous_Origin[3] =
	{
		*(float*)((unsigned __int32)Local_Player + 668),

		*(float*)((unsigned __int32)Local_Player + 672),

		*(float*)((unsigned __int32)Local_Player + 676),
	};

	using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Local_Player, User_Command_Structure* User_Command, void* Move_Helper);

	static void* Prediction = *(void**)540494880;

	Run_Command_Type(605207600)(Prediction, Local_Player, User_Command, (void*)607735532);

	*(__int32*)((unsigned __int32)Local_Player + 3592) -= 1;

	float Move_Angles[3] =
	{
		User_Command->View_Angles[0],

		User_Command->View_Angles[1],

		User_Command->View_Angles[2]
	};

	static float Previous_Move_Angle_Y = Move_Angles[1];

	if ((User_Command->Buttons_State & 2) == 2)
	{
		User_Command->Move[0] = 0;

		if (*(__int32*)((unsigned __int32)Local_Player + 456) != -1)
		{
			User_Command->Buttons_State &= ~2;
		}

		float Difference = __builtin_remainderf(User_Command->View_Angles[1] - Previous_Move_Angle_Y, 360);

		Previous_Move_Angle_Y = User_Command->View_Angles[1];

		float* Velocity = (float*)((unsigned __int32)Local_Player + 236);

		if (Absolute(Difference) < Arc_Tangent_2(Square_Root(__builtin_powf(Velocity[0], 2) + __builtin_powf(Velocity[1], 2)), 30) * 180 / 3.1415927f)
		{
			float Strafe_Angle = __builtin_remainderf(User_Command->View_Angles[1] - Arc_Tangent_2(Velocity[0], Velocity[1]) * 180 / 3.1415927f, 360);

			if (__builtin_signbitf(Strafe_Angle) == 0)
			{
				User_Command->Move[1] = -400;
			}
			else
			{
				User_Command->Move[1] = 400;
			}

			Move_Angles[1] -= Strafe_Angle;
		}
		else
		{
			if (__builtin_signbitf(Difference) == 0)
			{
				User_Command->Move[1] = -400;
			}
			else
			{
				User_Command->Move[1] = 400;
			}
		}
	}
	else
	{
		Previous_Move_Angle_Y = User_Command->View_Angles[1];
	}

	__int32 Choked_Commands_Count = *(__int32*)540627872;

	__int8 Send_Packet;

	__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

	__int8 Predicted_Send_Packet;

	float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 668);

	if (Choked_Commands_Count < Console_Variable_Minimum_Choked_Commands.Integer)
	{
		Send_Packet = 0;

		if (Predicted_Choked_Commands_Count == Console_Variable_Minimum_Choked_Commands.Integer)
		{
			if (Predicted_Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
			{
				goto Predict_Adaptive_Send_Packet_Label;
			}
			else
			{
				Predicted_Send_Packet = 1;
			}
		}
		else
		{
			Predicted_Send_Packet = -1;
		}
	}
	else
	{
		static float Previous_Networked_Origin[3];

		if (Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
		{
			float Difference[3] =
			{
				Previous_Networked_Origin[0] - Local_Player_Previous_Origin[0],

				Previous_Networked_Origin[1] - Local_Player_Previous_Origin[1],

				Previous_Networked_Origin[2] - Local_Player_Previous_Origin[2]
			};

			if (__builtin_powf(Difference[0], 2) + __builtin_powf(Difference[1], 2) + __builtin_powf(Difference[2], 2) <= 4096)
			{
				Send_Packet = 0;
			}
			else
			{
				Previous_Networked_Origin[0] = *(float*)((unsigned __int32)Local_Player + 668);

				Previous_Networked_Origin[1] = *(float*)((unsigned __int32)Local_Player + 672);

				Previous_Networked_Origin[2] = *(float*)((unsigned __int32)Local_Player + 676);

				Send_Packet = 1;
			}

			Predict_Adaptive_Send_Packet_Label:
			{
				if (Predicted_Choked_Commands_Count == Console_Variable_Maximum_Choked_Commands.Integer)
				{
					Predicted_Send_Packet = 1;
				}
				else
				{
					Difference[0] = Previous_Networked_Origin[0] - Local_Player_Origin[0];

					Difference[1] = Previous_Networked_Origin[1] - Local_Player_Origin[1];

					Difference[2] = Previous_Networked_Origin[2] - Local_Player_Origin[2];

					if (__builtin_powf(Difference[0], 2) + __builtin_powf(Difference[1], 2) + __builtin_powf(Difference[2], 2) <= 4096)
					{
						Predicted_Send_Packet = -1;
					}
					else
					{
						Predicted_Send_Packet = 1;
					}
				}
			}
		}
		else
		{
			Previous_Networked_Origin[0] = *(float*)((unsigned __int32)Local_Player + 668);

			Previous_Networked_Origin[1] = *(float*)((unsigned __int32)Local_Player + 672);

			Previous_Networked_Origin[2] = *(float*)((unsigned __int32)Local_Player + 676);

			Send_Packet = 1;

			Predicted_Send_Packet = -1;
		}
	}

	__int32 Entity_Number = 1;

	__int32 Team_Number = *(__int32*)((unsigned __int32)Local_Player + 144);

	struct Target_Structure
	{
		__int8 Priority;

		float Distance;

		void* Target;
	};

	static std::vector<Target_Structure> Distance_Sorted_Target_List;

	Distance_Sorted_Target_List.clear();

	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

	Traverse_Entity_List_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

		if (Player_Data->Priority != -1)
		{
			void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

			if (Entity != nullptr)
			{
				if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
				{
					if (*(__int32*)((unsigned __int32)Entity + 144) != Team_Number)
					{
						if (*(__int8*)((unsigned __int32)Entity + 320) == 0)
						{
							Target_Structure Target;

							Target.Priority = Player_Data->Priority;

							float* Entity_Origin = (float*)((unsigned __int32)Entity + 668);

							Target.Distance = Square_Root(__builtin_powf(Local_Player_Origin[0] - Entity_Origin[0], 2) + __builtin_powf(Local_Player_Origin[1] - Entity_Origin[1], 2) + __builtin_powf(Local_Player_Origin[2] - Entity_Origin[2], 2));

							Target.Target = Entity;

							Distance_Sorted_Target_List.push_back(Target);
						}
					}
				}
			}
		}
		
		if (Entity_Number != Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}

	auto Compare = [](Target_Structure X, Target_Structure Y) -> __int8
	{
		if (X.Priority > Y.Priority)
		{
			return 1;
		}

		return X.Distance < Y.Distance;
	};

	std::sort(Distance_Sorted_Target_List.begin(), Distance_Sorted_Target_List.end(), Compare);

	size_t Target_Number = 0;

	void* Optimal_Target;

	float Extrapolation_Time;

	using Eye_Position = void(__thiscall*)(void* Player, float* Eye_Position);

	float Local_Player_Eye_Position[3];

	Eye_Position(604058320)(Local_Player, Local_Player_Eye_Position);

	float Aim_Angles[2];

	Traverse_Distance_Sorted_Target_List_Label:
	{
		if (Target_Number != Distance_Sorted_Target_List.size())
		{
			using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

			Optimal_Target = Distance_Sorted_Target_List.at(Target_Number).Target;

			void* Renderable = (void*)((unsigned __int32)Optimal_Target + 4);

			float Bones[128][3][4];

			if (Setup_Bones_Type(604209888)(Renderable, Bones, 128, 524032, Global_Variables->Current_Time) == 1)
			{
				void* Model = *(void**)((unsigned __int32)Renderable + 88);

				if (Model != nullptr)
				{
					using Get_Studio_Model_Type = void* (__thiscall*)(void* Model_Cache, void* Model);

					static void* Get_Studio_Model_Location = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 46416);

					static void* Model_Cache = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 125464);

					void* Studio_Model = Get_Studio_Model_Type((unsigned __int32)Get_Studio_Model_Location)(Model_Cache, *(void**)((unsigned __int32)Model + 144));

					if (Studio_Model != nullptr)
					{
						struct Trace_Structure
						{
							__int8 Additional_Bytes_1[12];

							float End[3];

							__int8 Additional_Bytes_2[52];

							void* Entity;

							__int8 Additional_Bytes_3[4];
						};

						Trace_Structure Trace;

						auto Trace_Ray = [&](float* Start, float* End, Trace_Structure* Trace, __int8 Investigation) -> __int8
						{
							struct Ray_Structure
							{
								__int8 Additional_Bytes[50];
							};

							struct Trace_Filter_Structure
							{
								void* Trace_Filter;

								void* Skip;

								__int8 Additional_Bytes[4];

								__int32 Collision_Group;
							};

							using Trace_Ray_Type = void(__thiscall*)(void* Engine_Trace, Ray_Structure* Ray, __int32 Mask, Trace_Filter_Structure* Trace_Filter, Trace_Structure* Trace);

							Ray_Structure Ray;

							using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

							Initialize_Ray_Type(537380224)(&Ray, Start, End);

							Trace_Filter_Structure Trace_Filter;

							Trace_Filter.Trace_Filter = (void*)607282712;

							Trace_Filter.Skip = Local_Player;

							Trace_Filter.Collision_Group = 0;

							Trace_Ray_Type(537565888)((void*)540446304, &Ray, 1174421515, &Trace_Filter, Trace);

							if (Investigation == 0)
							{
								if (Trace->Entity == nullptr)
								{
									return 1;
								}

								if (Trace->Entity == Optimal_Target)
								{
									return 1;
								}
							}

							return 0;
						};

						void* Hitbox_Set = (void*)((unsigned __int32)Studio_Model + *(__int32*)((unsigned __int32)Studio_Model + 176));

						float* Bounding_Box_Minimum = (float*)((unsigned __int32)Hitbox_Set + 836);

						float* Bounding_Box_Maximum = (float*)((unsigned __int32)Hitbox_Set + 848);

						float Hitbox_Minimum[3] =
						{
							Bounding_Box_Minimum[0] * Bones[14][0][0] + Bounding_Box_Minimum[1] * Bones[14][0][1] + Bounding_Box_Minimum[2] * Bones[14][0][2] + Bones[14][0][3],

							Bounding_Box_Minimum[0] * Bones[14][1][0] + Bounding_Box_Minimum[1] * Bones[14][1][1] + Bounding_Box_Minimum[2] * Bones[14][1][2] + Bones[14][1][3],

							Bounding_Box_Minimum[0] * Bones[14][2][0] + Bounding_Box_Minimum[1] * Bones[14][2][1] + Bounding_Box_Minimum[2] * Bones[14][2][2] + Bones[14][2][3]
						};

						float Hitbox_Maximum[3] =
						{
							Bounding_Box_Maximum[0] * Bones[14][0][0] + Bounding_Box_Maximum[1] * Bones[14][0][1] + Bounding_Box_Maximum[2] * Bones[14][0][2] + Bones[14][0][3],

							Bounding_Box_Maximum[0] * Bones[14][1][0] + Bounding_Box_Maximum[1] * Bones[14][1][1] + Bounding_Box_Maximum[2] * Bones[14][1][2] + Bones[14][1][3],

							Bounding_Box_Maximum[0] * Bones[14][2][0] + Bounding_Box_Maximum[1] * Bones[14][2][1] + Bounding_Box_Maximum[2] * Bones[14][2][2] + Bones[14][2][3]
						};

						float Optimal_Target_Origin[3] =
						{
							(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2,

							(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2,

							Hitbox_Maximum[2] + (Hitbox_Maximum[2] - Hitbox_Minimum[2]) * (Console_Variable_Aim_Height.Floating_Point - 1)
						};

						if (Console_Variable_Extrapolation.Integer == 0)
						{
							Extrapolation_Time = 0;
						}
						else
						{
							__int32 Optimal_Target_Index = *(__int32*)((unsigned __int32)Optimal_Target + 80) - 1;

							__int32 Current_Player_History_Number = 0;

							float High_Simulation_Time = 0;

							__int32 High_Player_History_Number;

							Traverse_Player_History_Find_High_Label:
							{
								float Current_Simulation_Time = Players_History[Optimal_Target_Index][Current_Player_History_Number].Simulation_Time;

								if (High_Simulation_Time < Current_Simulation_Time)
								{
									High_Simulation_Time = Current_Simulation_Time;

									High_Player_History_Number = Current_Player_History_Number;
								}

								Current_Player_History_Number += 1;

								if (Current_Player_History_Number != sizeof(Players_History[0]) / sizeof(Player_History_Structure))
								{
									goto Traverse_Player_History_Find_High_Label;
								}
							}
							
							if ((__int32)((Global_Variables->Current_Time - High_Simulation_Time) / Global_Variables->Interval_Per_Tick + 0.5f) == 1)
							{
								Extrapolation_Time = 0;

								goto Bypass_Extrapolation_Force_Label;
							}
							else
							{
								float Mid_Simulation_Time = High_Simulation_Time;

								__int32 Mid_Player_History_Number;

								Traverse_Player_History_Find_Mid_Label:
								{
									float Current_Simulation_Time = High_Simulation_Time - Players_History[Optimal_Target_Index][Current_Player_History_Number].Simulation_Time;

									if (Current_Simulation_Time != 0)
									{
										if (Mid_Simulation_Time > Current_Simulation_Time)
										{
											Mid_Simulation_Time = Current_Simulation_Time;

											Mid_Player_History_Number = Current_Player_History_Number;
										}
									}

									if (Current_Player_History_Number != 0)
									{
										Current_Player_History_Number -= 1;

										goto Traverse_Player_History_Find_Mid_Label;
									}

									Mid_Simulation_Time = High_Simulation_Time - Mid_Simulation_Time;
								}

								Extrapolation_Time = High_Simulation_Time - Mid_Simulation_Time;

								if (Extrapolation_Time != 0)
								{
									float Low_Simulation_Time = Mid_Simulation_Time;

									__int32 Low_Player_History_Number;

									Traverse_Player_History_Find_Low_Label:
									{
										float Current_Simulation_Time = Mid_Simulation_Time - Players_History[Optimal_Target_Index][Current_Player_History_Number].Simulation_Time;

										if (Current_Simulation_Time > 0)
										{
											if (Low_Simulation_Time > Current_Simulation_Time)
											{
												Low_Simulation_Time = Current_Simulation_Time;

												Low_Player_History_Number = Current_Player_History_Number;
											}
										}

										Current_Player_History_Number += 1;

										if (Current_Player_History_Number != sizeof(Players_History[0]) / sizeof(Player_History_Structure))
										{
											goto Traverse_Player_History_Find_Low_Label;
										}
									}

									if (Mid_Simulation_Time == Low_Simulation_Time)
									{
										Extrapolation_Time = 0;
									}
									else
									{
										Player_History_Structure* Mid_Player_History = &Players_History[Optimal_Target_Index][Mid_Player_History_Number];

										Player_History_Structure* Low_Player_History = &Players_History[Optimal_Target_Index][Low_Player_History_Number];

										float Mid_Low_Origin_Difference[3] =
										{
											Mid_Player_History->Origin[0] - Low_Player_History->Origin[0],

											Mid_Player_History->Origin[1] - Low_Player_History->Origin[1],

											Mid_Player_History->Origin[2] - Low_Player_History->Origin[2]
										};

										__int32 Origin_Difference_Number = 0;

										float High_Mid_Origin_Difference_Acceleration[3];

										Player_History_Structure* High_Player_History = &Players_History[Optimal_Target_Index][High_Player_History_Number];

										float High_Mid_Origin_Difference[3] =
										{
											High_Player_History->Origin[0] - Mid_Player_History->Origin[0],

											High_Player_History->Origin[1] - Mid_Player_History->Origin[1],

											High_Player_History->Origin[2] - Mid_Player_History->Origin[2]
										};

										float Accelerated_High_Mid_Origin_Difference[3];

										Accelerate_High_Mid_Origin_Difference_Label:
										{
											float Mid_Low_Difference = Mid_Low_Origin_Difference[Origin_Difference_Number];

											if (Mid_Low_Difference != 0)
											{
												High_Mid_Origin_Difference_Acceleration[Origin_Difference_Number] = High_Mid_Origin_Difference[Origin_Difference_Number] / Mid_Low_Difference;
											}
											else
											{
												High_Mid_Origin_Difference_Acceleration[Origin_Difference_Number] = 0;
											}

											Accelerated_High_Mid_Origin_Difference[Origin_Difference_Number] = High_Mid_Origin_Difference[Origin_Difference_Number] * High_Mid_Origin_Difference_Acceleration[Origin_Difference_Number];

											Origin_Difference_Number += 1;

											if (Origin_Difference_Number != 3)
											{
												goto Accelerate_High_Mid_Origin_Difference_Label;
											}
										}

										if (Absolute(__builtin_ceilf(High_Mid_Origin_Difference_Acceleration[0]) - High_Mid_Origin_Difference_Acceleration[0]) <= Console_Variable_Extrapolation_Tolerance.Floating_Point)
										{
											if (Absolute(__builtin_ceilf(High_Mid_Origin_Difference_Acceleration[1]) - High_Mid_Origin_Difference_Acceleration[1]) <= Console_Variable_Extrapolation_Tolerance.Floating_Point)
											{
												if (Absolute(__builtin_ceilf(High_Mid_Origin_Difference_Acceleration[2]) - High_Mid_Origin_Difference_Acceleration[2]) <= Console_Variable_Extrapolation_Gravity_Tolerance.Floating_Point)
												{
													float Previous_Optimal_Target_Origin[3] =
													{
														Optimal_Target_Origin[0],

														Optimal_Target_Origin[1],

														Optimal_Target_Origin[2]
													};

													float Extrapolated_Optimal_Target_Origin[3]
													{
														Optimal_Target_Origin[0] + Accelerated_High_Mid_Origin_Difference[0],

														Optimal_Target_Origin[1] + Accelerated_High_Mid_Origin_Difference[1],

														Optimal_Target_Origin[2] + Accelerated_High_Mid_Origin_Difference[2],
													};

													Trace_Ray(Optimal_Target_Origin, Extrapolated_Optimal_Target_Origin, &Trace, 1);

													Optimal_Target_Origin[0] = Trace.End[0];

													Optimal_Target_Origin[1] = Trace.End[1];

													Optimal_Target_Origin[2] = Trace.End[2];

													if (Trace_Ray(Local_Player_Eye_Position, Optimal_Target_Origin, &Trace, 0) == 0)
													{
														Extrapolation_Time = 0;

														Optimal_Target_Origin[0] = Previous_Optimal_Target_Origin[0];

														Optimal_Target_Origin[1] = Previous_Optimal_Target_Origin[1];

														Optimal_Target_Origin[2] = Previous_Optimal_Target_Origin[2];
													}
													else
													{
														goto Set_Aim_Angles_Label;
													}
												}
												else
												{
													Extrapolation_Time = 0;
												}
											}
											else
											{
												Extrapolation_Time = 0;
											}
										}
										else
										{
											Extrapolation_Time = 0;
										}
									}
								}
							}
						}
						
						if (Console_Variable_Extrapolation.Integer * Console_Variable_Extrapolation_Force.Integer == 0)
						{
							Bypass_Extrapolation_Force_Label:
							{
								if (Trace_Ray(Local_Player_Eye_Position, Optimal_Target_Origin, &Trace, 0) == 1)
								{
									Set_Aim_Angles_Label:
									{
										float Origin_Difference[3] =
										{
											Optimal_Target_Origin[0] - Local_Player_Eye_Position[0],

											Optimal_Target_Origin[1] - Local_Player_Eye_Position[1],

											Optimal_Target_Origin[2] - Local_Player_Eye_Position[2],
										};

										Aim_Angles[0] = Arc_Tangent_2(Square_Root(__builtin_powf(Origin_Difference[0], 2) + __builtin_powf(Origin_Difference[1], 2)), -Origin_Difference[2]) * 180 / 3.1415927f;

										Aim_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f;

										User_Command->Buttons_State |= 1;
									}
								}
								else
								{
									Optimal_Target = nullptr;

									Target_Number += 1;

									goto Traverse_Distance_Sorted_Target_List_Label;
								}
							}
						}
						else
						{
							Optimal_Target = nullptr;

							Target_Number += 1;

							goto Traverse_Distance_Sorted_Target_List_Label;
						}
					}
					else
					{
						Optimal_Target = nullptr;

						Target_Number += 1;

						goto Traverse_Distance_Sorted_Target_List_Label;
					}
				}
				else
				{
					Optimal_Target = nullptr;

					Target_Number += 1;

					goto Traverse_Distance_Sorted_Target_List_Label;
				}
			}
			else
			{
				Optimal_Target = nullptr;

				Target_Number += 1;

				goto Traverse_Distance_Sorted_Target_List_Label;
			}
		}
		else
		{
			Optimal_Target = nullptr;
		}
	}

	__int8 In_Attack;

	if ((User_Command->Buttons_State & 1) == 1)
	{
		if ((User_Command->Buttons_State & 2048) == 0)
		{
			if (Send_Packet == 0)
			{
				if (Predicted_Send_Packet == 1)
				{
					float Delta_Time;

					__int32 Target_Tick_Number;
					
					if (Optimal_Target == nullptr)
					{
						Delta_Time = 0;
					}
					else
					{
						using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Flow_Type);

						void* Network_Channel = *(void**)540608912;

						float Total_Latency = Get_Latency_Type(537919008)(Network_Channel, 0) + Get_Latency_Type(537919008)(Network_Channel, 1);

						float Interpolation_Ratio = *(float*)607906336;

						float Minimum_Interpolation_Ratio = *(float*)542242312;

						float Maximum_Interpolation_Ratio = *(float*)542242072;

						if (Interpolation_Ratio < Minimum_Interpolation_Ratio)
						{
							Interpolation_Ratio = Minimum_Interpolation_Ratio;
						}
						else
						{
							if (Interpolation_Ratio > Maximum_Interpolation_Ratio)
							{
								Interpolation_Ratio = Maximum_Interpolation_Ratio;
							}
						}

						__int32 Update_Rate = *(__int32*)540495212;

						__int32 Maximum_Update_Rate = *(__int32*)542221412;

						__int32 Minimum_Update_Rate = *(__int32*)542221268;

						if (Update_Rate < Minimum_Update_Rate)
						{
							Update_Rate = Minimum_Update_Rate;
						}
						else
						{
							if (Update_Rate > Maximum_Update_Rate)
							{
								Update_Rate = Maximum_Update_Rate;
							}
						}

						float Interpolation_Time = Interpolation_Ratio / Update_Rate;

						float Interpolation = *(float*)541928632;

						if (Interpolation_Time < Interpolation)
						{
							Interpolation_Time = Interpolation;
						}

						float Corrected_Interpolation_Time = std::clamp(Total_Latency + Interpolation_Time, 0.f, 1.f);

						Target_Tick_Number = (*(float*)((unsigned __int32)Optimal_Target + 104) + Interpolation_Time + Extrapolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;
						
						__int32 Tick_Number_Difference = Global_Variables->Tick_Number + 1 + Total_Latency / Global_Variables->Interval_Per_Tick + 0.5f - Target_Tick_Number;

						if (Tick_Number_Difference * -1 <= 7)
						{
							Delta_Time = Absolute(Corrected_Interpolation_Time - Tick_Number_Difference * Global_Variables->Interval_Per_Tick);
						}
						else
						{
							Delta_Time = FLT_MAX;
						}
					}
					
					if (Delta_Time <= 0.2f)
					{
						if (*(float*)((unsigned __int32)Local_Player + 2544) <= Global_Variables->Current_Time)
						{
							unsigned __int32 Weapon_Index = *(unsigned __int32*)((unsigned __int32)Local_Player + 2872);

							void* Weapon = *(void**)((unsigned __int32)607973860 + (((Weapon_Index & 4095) - 4097) << 4));

							if (Weapon != nullptr)
							{
								if (*(__int8*)((unsigned __int32)Weapon + 1732) == 0)
								{
									if (*(__int32*)((unsigned __int32)Weapon + 1788) <= 0)
									{
										In_Attack = 0;
									}
									else
									{
										if (*(float*)((unsigned __int32)Weapon + 1720) <= Global_Variables->Current_Time)
										{
											Shot_Tick = *(__int32*)((unsigned __int32)Local_Player + 3592);

											In_Attack = 1;

											if (Optimal_Target != nullptr)
											{
												User_Command->Tick_Number = Target_Tick_Number;

												User_Command->View_Angles[0] = Aim_Angles[0];

												User_Command->View_Angles[1] = Aim_Angles[1];
												
												__int32 Optimal_Target_Index = *(__int32*)((unsigned __int32)Optimal_Target + 80) - 1;

												Player_Data_Structure* Player_Data = &Players_Data[Optimal_Target_Index];

												if (Player_Data->Memorized == 0)
												{
													Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % 5;
												}
												else
												{
													Player_Data->Memorized_Shots -= 1;

													Player_Data->Memorized = Player_Data->Memorized_Shots > 0;
												}
											}

											float Sine_X;

											float Cosine_X;

											Sine_Cosine(Sine_X, Cosine_X, User_Command->View_Angles[0] * 3.1415927f / 180);

											float Sine_Y;

											float Cosine_Y;

											Sine_Cosine(Sine_Y, Cosine_Y, User_Command->View_Angles[1] * 3.1415927f / 180);

											constexpr __int32 Random_Seed = 32;

											User_Command->Random_Seed = Random_Seed;

											User_Command->Command_Number = -2076434770;

											using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

											static void* Random_Seed_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11856);

											Random_Seed_Type((unsigned __int32)Random_Seed_Location)((Random_Seed & 255) + 1);

											using Random_Float_Type = float(__cdecl*)(float Min, float Max);

											static void* Random_Float_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11872);

											float Random_X = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

											float Random_Y = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

											using Primary_Attack_Type = void(__thiscall**)(void* Weapon);

											Weapon_Spread = -1;

											(*Primary_Attack_Type(*(unsigned __int32*)Weapon + 856))(Weapon);

											float Direction[3] =
											{
												Cosine_X * Cosine_Y + Random_X * Weapon_Spread * Sine_Y + Random_Y * Weapon_Spread * (Sine_X * Cosine_Y),

												Cosine_X * Sine_Y + Random_X * Weapon_Spread * -Cosine_Y + Random_Y * Weapon_Spread * (Sine_X * Sine_Y),

												-Sine_X + Random_Y * Weapon_Spread * Cosine_X
											};

											Weapon_Spread = 0;

											float Magnitude = 1 / (Square_Root(__builtin_powf(Direction[0], 2) + __builtin_powf(Direction[1], 2) + __builtin_powf(Direction[2], 2)) + FLT_EPSILON);

											Direction[0] *= Magnitude;

											Direction[1] *= Magnitude;

											Direction[2] *= Magnitude;

											float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

											User_Command->View_Angles[0] = Arc_Tangent_2(Square_Root(__builtin_powf(Direction[0], 2) + __builtin_powf(Direction[1], 2)), -Direction[2]) * 180 / 3.1415927f - Recoil[0] * 2;

											User_Command->View_Angles[1] = Arc_Tangent_2(Direction[0], Direction[1]) * 180 / 3.1415927f - Recoil[1] * 2;
										}
										else
										{
											In_Attack = 0;
										}
									}
								}
								else
								{
									In_Attack = 0;
								}
							}
							else
							{
								In_Attack = 0;
							}
						}
						else
						{
							In_Attack = 0;
						}
					}
					else
					{
						In_Attack = 0;
					}
				}
				else
				{
					In_Attack = 0;
				}
			}
			else
			{
				In_Attack = 0;
			}
		}
		else
		{
			In_Attack = 0;
		}
	}
	else
	{
		In_Attack = 0;
	}

	if (In_Attack == 0)
	{
		User_Command->Buttons_State &= ~1;

		if (Distance_Sorted_Target_List.size() != 0)
		{
			User_Command->View_Angles[0] = Console_Variable_Angle_X.Floating_Point;

			Update_Animation_Angle[0] = User_Command->View_Angles[0];

			float* Optimal_Target_Origin = (float*)((unsigned __int32)Distance_Sorted_Target_List.at(0).Target + 668);

			float Origin_Difference[2] =
			{
				Optimal_Target_Origin[0] - Local_Player_Origin[0],

				Optimal_Target_Origin[1] - Local_Player_Origin[1]
			};

			if (Send_Packet == 0)
			{
				if ((User_Command->Command_Number % 2) == 0)
				{
					User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_First_Choked_Angle_Y.Floating_Point;
				}
				else
				{
					User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Second_Choked_Angle_Y.Floating_Point;
				}
			}
			else
			{
				User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Angle_Y.Floating_Point;		

				Update_Animation_Angle[1] = User_Command->View_Angles[1];
			}
		}
		else
		{
			Update_Animation_Angle[0] = User_Command->View_Angles[0];

			Update_Animation_Angle[1] = User_Command->View_Angles[1];
		}
	}

	*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 24) = Send_Packet;

	auto Angle_Vectors = [](float* Angles, float* Forward, float* Right) -> void
	{
		float Sine_X;

		float Cosine_X;

		Sine_Cosine(Sine_X, Cosine_X, Angles[0] * 3.1415927f / 180);

		float Sine_Y;

		float Cosine_Y;

		Sine_Cosine(Sine_Y, Cosine_Y, Angles[1] * 3.1415927f / 180);

		Forward[0] = Cosine_X * Cosine_Y;

		Forward[1] = Cosine_X * Sine_Y;

		Right[0] = Sine_Y;

		Right[1] = -Cosine_Y;
	};

	float Desired_Move_Forward[2];

	float Desired_Move_Right[2];

	Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right);

	float Magnitude = 1 / (Square_Root(__builtin_powf(Desired_Move_Forward[0], 2) + __builtin_powf(Desired_Move_Forward[1], 2)) + FLT_EPSILON);

	Desired_Move_Forward[0] *= Magnitude;

	Desired_Move_Forward[1] *= Magnitude;

	Magnitude = 1 / (Square_Root(__builtin_powf(Desired_Move_Right[0], 2) + __builtin_powf(Desired_Move_Right[1], 2)) + FLT_EPSILON);

	Desired_Move_Right[0] *= Magnitude;

	Desired_Move_Right[1] *= Magnitude;

	float Desired_Move[2] =
	{
		Desired_Move_Forward[0] * User_Command->Move[0] + Desired_Move_Right[0] * User_Command->Move[1],

		Desired_Move_Forward[1] * User_Command->Move[0] + Desired_Move_Right[1] * User_Command->Move[1]
	};

	float Move_Forward[2];

	float Move_Right[2];

	Angle_Vectors(User_Command->View_Angles, Move_Forward, Move_Right);

	Magnitude = 1 / (Square_Root(__builtin_powf(Move_Forward[0], 2) + __builtin_powf(Move_Forward[1], 2)) + FLT_EPSILON);

	Move_Forward[0] *= Magnitude;

	Move_Forward[1] *= Magnitude;

	Magnitude = 1 / (Square_Root(__builtin_powf(Move_Right[0], 2) + __builtin_powf(Move_Right[1], 2)) + FLT_EPSILON);

	Move_Right[0] *= Magnitude;

	Move_Right[1] *= Magnitude;

	float Divider = (Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1]);

	User_Command->Move[0] = (Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider;

	User_Command->Move[1] = (Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider;

	(decltype(&Redirected_Copy_User_Command)(Original_Copy_User_Command_Caller_Location))(Unknown_Parameter, User_Command);
}