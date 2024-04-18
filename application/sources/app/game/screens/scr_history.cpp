#include "scr_history.h"
#include "scr_menu.h"

#include "fs_config.h"

/***********************************************************
* VARIABLE AND STRUCT VIEW HISTORY
***********************************************************/
typedef struct
{
    int8_t pointer;
    int8_t page_history;
} fs_table_setting_infor_t;

fs_table_setting_infor_t table_setting_infor;

/***********************************************************
* VIEW - HISTORY
***********************************************************/

static void view_scr_fs_history();

view_dynamic_t dyn_view_history = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_fs_history};

view_screen_t scr_history = {
    &dyn_view_history,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void view_scr_fs_history() {
#define TEXT_X (10)
#define TEXT_Y (10)

    view_render.setTextColor(WHITE);
    view_render.setTextSize(1);
    for (int i = 0; i < FS_NUM_CELL; i++) {
        view_render.setCursor(TEXT_X, TEXT_Y + (i * FS_CELL_Y));
        char temp[18];

        if (i != table_setting_infor.pointer) {
            view_render.drawRoundRect(
                FS_ROUND_RECT_X, FS_ROUND_RECT_Y + (i * FS_CELL_Y),
                FS_ROUND_RECT_WIDTH, FS_ROUND_RECT_HEIGHT, 3, WHITE);
            view_render.setTextColor(WHITE);
        } 
        else {
            view_render.setTextColor(BLACK);
            view_render.fillRoundRect(
                FS_ROUND_RECT_X, FS_ROUND_RECT_Y + (i * FS_CELL_Y),
                FS_ROUND_RECT_WIDTH, FS_ROUND_RECT_HEIGHT, 3, WHITE);
        }
        sprintf(temp, "   SCORE %d : ", (table_setting_infor.page_history * 3) + i + 1);
        view_render.print(temp);
        view_render.print(fs_game_score_history[(table_setting_infor.page_history * 3) + i]);
    }
}

/***********************************************************
* SCREEN HISTORY HANDLE
***********************************************************/

void task_scr_fs_history_handle(ak_msg_t *msg) {
    switch (msg->sig) {
        case AC_DISPLAY_BUTON_MODE_PRESSED: {
            SCREEN_TRAN(task_scr_fs_menu_handler, &scr_menu);
            break;
        }

        case AC_DISPLAY_BUTON_UP_RELEASED: {
            table_setting_infor.pointer--;
            if (table_setting_infor.pointer < 0) {
                table_setting_infor.pointer = 2;
                table_setting_infor.page_history--;
                if (table_setting_infor.page_history < 0)
                    table_setting_infor.page_history = (FS_MAX_HISTORY / 3) - 1;
            }
            break;
        }
        case AC_DISPLAY_BUTON_DOWN_RELEASED: {
            table_setting_infor.pointer++;
            if (table_setting_infor.pointer > 2) {
                table_setting_infor.pointer = 0;
                table_setting_infor.page_history++;
                if (table_setting_infor.page_history > (FS_MAX_HISTORY / 3) - 1)
                    table_setting_infor.page_history = 0;
            }
            break;
        }
        default:
            break;
    }
}
