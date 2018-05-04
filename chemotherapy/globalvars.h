#pragma once

#include "chemo.h"

namespace source_sdk 
{
	struct global_vars 
	{
		float real_time;
		int32_t frame_count;
		float absolute_frame_time;
		float absolute_frame_start_time;
		float cur_time;
		float frame_time;
		int32_t max_clients;
		int32_t tick_count;
		float interval_per_tick;
		float interpolation_amount;
		int32_t sim_ticks_this_frame;
		int32_t network_protocol;
		void *save_data;
		bool client;
		int32_t timestamp_networking_base;
		int32_t timestamp_randomize_window;
	};
};
extern source_sdk::global_vars *global_vars;