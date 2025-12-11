#include "ui.h"
#include <stdio.h>
#include <string.h>

// Global UI instance
teller_ui_t ui;

// Styles
static lv_style_t style_header;
static lv_style_t style_panel;
static lv_style_t style_button;
static lv_style_t style_button_primary;
static lv_style_t style_label_large;
static lv_style_t style_label_normal;
static lv_style_t style_label_small;

// Keypad button labels
static const char* keypad_labels[] = {
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9",
    ".", "0", "C"
};

// Transaction button labels
static const char* trans_labels[] = {
    "DEPOSIT", "WITHDRAW", "BALANCE",
    "TRANSFER", "PAYMENT", "HISTORY"
};

// Transaction button colors
static const lv_color_t trans_colors[] = {
    lv_color_hex(0x2ecc71),  // Green for deposit
    lv_color_hex(0xe74c3c),  // Red for withdraw
    lv_color_hex(0x3498db),  // Blue for balance
    lv_color_hex(0x9b59b6),  // Purple for transfer
    lv_color_hex(0xf39c12),  // Orange for payment
    lv_color_hex(0x34495e),  // Dark blue for history
};

// Initialize styles
static void init_styles(void) {
    // Header style
    lv_style_init(&style_header);
    lv_style_set_bg_color(&style_header, COLOR_BLACK);
    lv_style_set_bg_opa(&style_header, LV_OPA_100);
    lv_style_set_pad_all(&style_header, 5);
    
    // Panel style
    lv_style_init(&style_panel);
    lv_style_set_bg_color(&style_panel, COLOR_WHITE);
    lv_style_set_bg_opa(&style_panel, LV_OPA_100);
    lv_style_set_radius(&style_panel, 10);
    lv_style_set_shadow_width(&style_panel, 10);
    lv_style_set_shadow_spread(&style_panel, 3);
    lv_style_set_shadow_color(&style_panel, lv_color_hex(0x666666));
    lv_style_set_pad_all(&style_panel, 15);
    
    // Button style
    lv_style_init(&style_button);
    lv_style_set_bg_color(&style_button, COLOR_BLUE);
    lv_style_set_bg_opa(&style_button, LV_OPA_100);
    lv_style_set_radius(&style_button, 8);
    lv_style_set_text_color(&style_button, COLOR_WHITE);
    lv_style_set_shadow_width(&style_button, 5);
    lv_style_set_shadow_spread(&style_button, 2);
    
    // Primary button style
    lv_style_init(&style_button_primary);
    lv_style_set_bg_color(&style_button_primary, COLOR_GREEN);
    lv_style_set_bg_opa(&style_button_primary, LV_OPA_100);
    lv_style_set_radius(&style_button_primary, 8);
    lv_style_set_text_color(&style_button_primary, COLOR_WHITE);
    lv_style_set_shadow_width(&style_button_primary, 5);
    lv_style_set_shadow_spread(&style_button_primary, 2);
    
    // Large label style
    lv_style_init(&style_label_large);
    lv_style_set_text_color(&style_label_large, COLOR_BLACK);
    lv_style_set_text_font(&style_label_large, &lv_font_montserrat_32);
    
    // Normal label style
    lv_style_init(&style_label_normal);
    lv_style_set_text_color(&style_label_normal, COLOR_BLACK);
    lv_style_set_text_font(&style_label_normal, &lv_font_montserrat_20);
    
    // Small label style
    lv_style_init(&style_label_small);
    lv_style_set_text_color(&style_label_small, lv_color_hex(0x666666));
    lv_style_set_text_font(&style_label_small, &lv_font_montserrat_14);
}

// Create header
static void create_header(void) {
    // Header bar (Kenyan black)
    ui.header = lv_obj_create(ui.screen);
    lv_obj_set_size(ui.header, SCREEN_WIDTH, 50);
    lv_obj_add_style(ui.header, &style_header, 0);
    lv_obj_set_style_border_width(ui.header, 0, 0);
    lv_obj_align(ui.header, LV_ALIGN_TOP_MID, 0, 0);
    
    // Bank logo/name with Kenyan flag
    ui.bank_name = lv_label_create(ui.header);
    lv_label_set_text(ui.bank_name, "🇰🇪 KCB Teller");
    lv_obj_set_style_text_color(ui.bank_name, COLOR_WHITE, 0);
    lv_obj_set_style_text_font(ui.bank_name, &lv_font_montserrat_20, 0);
    lv_obj_align(ui.bank_name, LV_ALIGN_LEFT_MID, 10, 0);
    
    // Time display
    ui.time_label = lv_label_create(ui.header);
    lv_label_set_text(ui.time_label, "14:30");
    lv_obj_set_style_text_color(ui.time_label, COLOR_WHITE, 0);
    lv_obj_align(ui.time_label, LV_ALIGN_CENTER, 0, 0);
    
    // Teller ID
    ui.teller_label = lv_label_create(ui.header);
    lv_label_set_text(ui.teller_label, "Teller: #001");
    lv_obj_set_style_text_color(ui.teller_label, COLOR_WHITE, 0);
    lv_obj_align(ui.teller_label, LV_ALIGN_RIGHT_MID, -10, 0);
}

// Create main display panel
static void create_display_panel(void) {
    // Main display panel
    ui.display_panel = lv_obj_create(ui.screen);
    lv_obj_set_size(ui.display_panel, SCREEN_WIDTH - 20, 80);
    lv_obj_add_style(ui.display_panel, &style_panel, 0);
    lv_obj_align(ui.display_panel, LV_ALIGN_TOP_MID, 0, 60);
    
    // Amount label
    ui.amount_label = lv_label_create(ui.display_panel);
    lv_label_set_text(ui.amount_label, "AMOUNT:");
    lv_obj_add_style(ui.amount_label, &style_label_small, 0);
    lv_obj_align(ui.amount_label, LV_ALIGN_TOP_LEFT, 0, 0);
    
    // Amount value (large display)
    ui.amount_value = lv_label_create(ui.display_panel);
    lv_label_set_text(ui.amount_value, "0.00");
    lv_obj_add_style(ui.amount_value, &style_label_large, 0);
    lv_obj_align(ui.amount_value, LV_ALIGN_TOP_MID, 0, 15);
    
    // Transaction type
    ui.transaction_label = lv_label_create(ui.display_panel);
    lv_label_set_text(ui.transaction_label, "Transaction: DEPOSIT");
    lv_obj_add_style(ui.transaction_label, &style_label_small, 0);
    lv_obj_align(ui.transaction_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    
    // Customer name
    ui.customer_label = lv_label_create(ui.display_panel);
    lv_label_set_text(ui.customer_label, "Customer: John Mwangi");
    lv_obj_add_style(ui.customer_label, &style_label_small, 0);
    lv_obj_align(ui.customer_label, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
}

// Create keypad
static void create_keypad(void) {
    ui.keypad_container = lv_obj_create(ui.screen);
    lv_obj_set_size(ui.keypad_container, 140, 160);
    lv_obj_set_style_bg_opa(ui.keypad_container, LV_OPA_0, 0);
    lv_obj_set_style_border_width(ui.keypad_container, 0, 0);
    lv_obj_align(ui.keypad_container, LV_ALIGN_LEFT_MID, 10, 20);
    
    // Create 4x3 keypad grid
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            int index = row * 3 + col;
            if (index >= 12) break;
            
            ui.keypad_buttons[index] = lv_btn_create(ui.keypad_container);
            lv_obj_set_size(ui.keypad_buttons[index], 40, 35);
            lv_obj_set_pos(ui.keypad_buttons[index], col * 45, row * 40);
            lv_obj_add_style(ui.keypad_buttons[index], &style_button, 0);
            
            // Style Clear button differently
            if (strcmp(keypad_labels[index], "C") == 0) {
                lv_obj_set_style_bg_color(ui.keypad_buttons[index], COLOR_RED, 0);
            }
            
            lv_obj_t *label = lv_label_create(ui.keypad_buttons[index]);
            lv_label_set_text(label, keypad_labels[index]);
            lv_obj_center(label);
        }
    }
}

// Create transaction buttons
static void create_transaction_buttons(void) {
    lv_obj_t *trans_container = lv_obj_create(ui.screen);
    lv_obj_set_size(trans_container, 150, 160);
    lv_obj_set_style_bg_opa(trans_container, LV_OPA_0, 0);
    lv_obj_set_style_border_width(trans_container, 0, 0);
    lv_obj_align(trans_container, LV_ALIGN_RIGHT_MID, -10, 20);
    
    // Create 2x3 grid of transaction buttons
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            int index = row * 3 + col;
            if (index >= 6) break;
            
            ui.trans_buttons[index] = lv_btn_create(trans_container);
            lv_obj_set_size(ui.trans_buttons[index], 140, 35);
            lv_obj_set_pos(ui.trans_buttons[index], 0, row * 40);
            lv_obj_set_style_bg_color(ui.trans_buttons[index], trans_colors[index], 0);
            lv_obj_set_style_radius(ui.trans_buttons[index], 8, 0);
            
            lv_obj_t *label = lv_label_create(ui.trans_buttons[index]);
            lv_label_set_text(label, trans_labels[index]);
            lv_obj_set_style_text_color(label, COLOR_WHITE, 0);
            lv_obj_center(label);
        }
    }
}

// Create status bar
static void create_status_bar(void) {
    ui.status_label = lv_label_create(ui.screen);
    lv_label_set_text(ui.status_label, "🟢 Ready for transaction");
    lv_obj_set_style_text_color(ui.status_label, COLOR_GREEN, 0);
    lv_obj_align(ui.status_label, LV_ALIGN_TOP_MID, 0, 150);
}

// Create footer
static void create_footer(void) {
    ui.footer = lv_obj_create(ui.screen);
    lv_obj_set_size(ui.footer, SCREEN_WIDTH, 30);
    lv_obj_set_style_bg_color(ui.footer, COLOR_RED, 0);
    lv_obj_set_style_border_width(ui.footer, 0, 0);
    lv_obj_align(ui.footer, LV_ALIGN_BOTTOM_MID, 0, 0);
    
    ui.footer_text = lv_label_create(ui.footer);
    lv_label_set_text(ui.footer_text, "🇰🇪 Kenya Commercial Bank • Secure Banking System");
    lv_obj_set_style_text_color(ui.footer_text, COLOR_WHITE, 0);
    lv_obj_set_style_text_font(ui.footer_text, &lv_font_montserrat_12, 0);
    lv_obj_center(ui.footer_text);
}

// Public: Initialize UI
void ui_init(void) {
    // Create main screen with Kenyan green background
    ui.screen = lv_obj_create(NULL);
    lv_obj_set_size(ui.screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_bg_color(ui.screen, COLOR_GREEN, 0);
    
    // Initialize styles
    init_styles();
    
    // Create all UI sections
    create_header();
    create_display_panel();
    create_keypad();
    create_transaction_buttons();
    create_status_bar();
    create_footer();
    
    // Load the screen
    lv_scr_load(ui.screen);
}

// Public: Update time display
void ui_update_time(const char *time_str) {
    lv_label_set_text(ui.time_label, time_str);
}

// Public: Update amount display
void ui_update_amount(const char *amount) {
    lv_label_set_text(ui.amount_value, amount);
}

// Public: Update transaction type
void ui_update_transaction(const char *trans_name) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Transaction: %s", trans_name);
    lv_label_set_text(ui.transaction_label, buffer);
}

// Public: Update customer name
void ui_update_customer(const char *customer_name) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Customer: %s", customer_name);
    lv_label_set_text(ui.customer_label, buffer);
}

// Public: Update status
void ui_update_status(const char *status, lv_color_t color) {
    lv_label_set_text(ui.status_label, status);
    lv_obj_set_style_text_color(ui.status_label, color, 0);
}

// Public: Set teller ID
void ui_set_teller_id(const char *teller_id) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Teller: %s", teller_id);
    lv_label_set_text(ui.teller_label, buffer);
}

// Public: Show temporary message
void ui_show_message(const char *message, lv_color_t color) {
    lv_obj_t *msg_box = lv_obj_create(ui.screen);
    lv_obj_set_size(msg_box, 280, 60);
    lv_obj_set_style_bg_color(msg_box, color, 0);
    lv_obj_set_style_bg_opa(msg_box, LV_OPA_90, 0);
    lv_obj_set_style_radius(msg_box, 10, 0);
    lv_obj_align(msg_box, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_t *msg_label = lv_label_create(msg_box);
    lv_label_set_text(msg_label, message);
    lv_obj_set_style_text_color(msg_label, COLOR_WHITE, 0);
    lv_obj_center(msg_label);
    
    // Auto-remove after 2 seconds
    lv_timer_t *timer = lv_timer_create([](lv_timer_t *t) {
        lv_obj_t *obj = (lv_obj_t *)t->user_data;
        lv_obj_del(obj);
        lv_timer_del(t);
    }, 2000, msg_box);
}