#ifndef UI_H
#define UI_H

#include "lvgl.h"

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Kenyan Banking Colors
#define COLOR_GREEN       lv_color_hex(0x006600)    // Kenyan green
#define COLOR_BLACK       lv_color_hex(0x000000)    // Kenyan black
#define COLOR_RED         lv_color_hex(0xCC0000)    // Kenyan red
#define COLOR_WHITE       lv_color_white()
#define COLOR_BLUE        lv_color_hex(0x3498db)    // Banking blue
#define COLOR_GOLD        lv_color_hex(0xFFD700)    // Accent gold

// Transaction types
typedef enum {
    TRANS_DEPOSIT,
    TRANS_WITHDRAW,
    TRANS_BALANCE,
    TRANS_TRANSFER,
    TRANS_PAYMENT,
    TRANS_HISTORY
} transaction_type_t;

// UI Structure
typedef struct {
    lv_obj_t *screen;
    
    // Header
    lv_obj_t *header;
    lv_obj_t *bank_logo;
    lv_obj_t *bank_name;
    lv_obj_t *time_label;
    lv_obj_t *teller_label;
    
    // Main display
    lv_obj_t *display_panel;
    lv_obj_t *amount_label;
    lv_obj_t *amount_value;
    lv_obj_t *transaction_label;
    lv_obj_t *customer_label;
    lv_obj_t *status_label;
    
    // Keypad
    lv_obj_t *keypad_container;
    lv_obj_t *keypad_buttons[12];  // 0-9, ., C
    
    // Transaction buttons
    lv_obj_t *trans_buttons[6];
    
    // Footer
    lv_obj_t *footer;
    lv_obj_t *footer_text;
    
} teller_ui_t;

// Function prototypes
void ui_init(void);
void ui_update_time(const char *time_str);
void ui_update_amount(const char *amount);
void ui_update_transaction(const char *trans_name);
void ui_update_customer(const char *customer_name);
void ui_update_status(const char *status, lv_color_t color);
void ui_set_teller_id(const char *teller_id);
void ui_show_message(const char *message, lv_color_t color);

// Global UI instance
extern teller_ui_t ui;

#endif // UI_H