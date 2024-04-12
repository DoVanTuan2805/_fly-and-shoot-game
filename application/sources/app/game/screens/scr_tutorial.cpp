#include "app.h"
#include "task_list.h"
#include "screen_manager.h"

#include "scr_tutorial.h"
#include "scr_bitmap.h"
#include "scr_menu.h"
static void view_scr_tutorial();

view_dynamic_t dyn_view_tutorial = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_tutorial
};
view_screen_t scr_tutorial = {
    &dyn_view_tutorial,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};
void view_scr_tutorial()
{
    #define QR_X    (34)
    #define QR_Y    (2)
    view_render.drawBitmap(QR_X, QR_Y, QR_tutorial, QR_TUTORIAL_WIDTH, QR_TUTORIAL_HEIGHT, WHITE);
}
void task_scr_tutorial_handle(ak_msg_t *msg) {
    switch (msg->sig) {
        case AC_DISPLAY_BUTON_MODE_PRESSED:
            SCREEN_TRAN(task_scr_menu_handler, &scr_menu);
            break;

        case AC_DISPLAY_BUTON_UP_RELEASED:
            SCREEN_TRAN(task_scr_menu_handler, &scr_menu);
            break;

        case AC_DISPLAY_BUTON_DOWN_RELEASED:
            SCREEN_TRAN(task_scr_menu_handler, &scr_menu);
            break;
        default:
            break;
    }
}
