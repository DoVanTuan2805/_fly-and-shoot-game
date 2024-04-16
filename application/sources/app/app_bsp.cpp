#include "button.h"

#include "sys_dbg.h"

#include "app.h"
#include "app_bsp.h"
#include "app_dbg.h"
#include "app_if.h"

#include "task_list.h"
#include "task_list_if.h"

#include "buzzer.h"

#include "screen_infor.h"

#include "prc_missile.h"
#include "buzzer_def.h" 
button_t btn_mode;
button_t btn_up;
button_t btn_down;


void btn_mode_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
            // APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_PRESSED\n");
            APP_DBG("SCREEN NOW : %d\n",state_game );
            if (state_game == GAME_OFF) {
                task_post_pure_msg(AC_TASK_DISPLAY_ID			, AC_DISPLAY_BUTON_MODE_PRESSED);
            } else if (state_game == GAME_ON) {
                task_post_pure_msg(AC_TASK_MISSLE_ID, SIG_MISSLE_PUSH);
            } else if (state_game == GAME_OVER) {		
                task_post_pure_msg(AC_TASK_DISPLAY_GAME_OVER_ID	, SIG_DISPLAY_GAME_OVER_MODE_PRESSED);
            }
        } break;

        case BUTTON_SW_STATE_LONG_PRESSED: {
            // APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
			if (state_game == GAME_OFF) {
				task_post_pure_msg(AC_TASK_DISPLAY_ID			, AC_DISPLAY_BUTON_MODE_LONG_PRESSED);
			}
        } break;

        case BUTTON_SW_STATE_RELEASED: {
            // APP_DBG("[btn_mode_callback] BUTTON_SW_STATE_RELEASED\n");
            if (state_game == GAME_OFF) {
                task_post_pure_msg(AC_TASK_DISPLAY_ID			, AC_DISPLAY_BUTON_MODE_RELEASED);
            }
        } break;

        default:
            break;
	}
}

void btn_up_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		//APP_DBG("[btn_up_callback] BUTTON_SW_STATE_PRESSED\n");
		if(state_game == GAME_OFF)
		{
			task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_UP_PRESSED);
		}
		else if(state_game == GAME_ON)
		{
			task_post_pure_msg(AC_TASK_PLANE_ID, SIG_PLANE_UP);
		}
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		//APP_DBG("[btn_up_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		//APP_DBG("[btn_up_callback] BUTTON_SW_STATE_RELEASED\n");
		if(state_game == GAME_OFF)
		{
			task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_UP_RELEASED);
		}
	}
		break;

	default:
		break;
	}
}

void btn_down_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		//APP_DBG("[btn_down_callback] BUTTON_SW_STATE_PRESSED\n");
		if(state_game == GAME_OFF)
		{
			task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_DOWN_PRESSED);
		}
		else if(state_game == GAME_OVER) {
			task_post_pure_msg(AC_TASK_DISPLAY_GAME_OVER_ID, SIG_DISPLAY_GAME_OVER_DOWN_PRESSED);
		}

	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		//APP_DBG("[btn_down_callback] BUTTON_SW_STATE_LONG_PRESSED\n");
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		//APP_DBG("[btn_down_callback] BUTTON_SW_STATE_RELEASED\n");
		if(state_game == GAME_OFF)
		{
			task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_DOWN_RELEASED);
		}
	}
		break;

	default:
		break;
	}
}
