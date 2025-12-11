#include "screens/ui.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Demo customer data
static const char* demo_customers[] = {
    "John Mwangi",
    "Sarah Odhiambo", 
    "Michael Kamau",
    "Grace Wanjiku",
    "David Ochieng",
    "Mercy Achieng"
};

// Demo transactions
static const char* demo_transactions[] = {
    "DEPOSIT", "WITHDRAW", "BALANCE", "TRANSFER", "PAYMENT"
};

// Current amount buffer
static char amount_buffer[20] = "0.00";
static int current_customer = 0;
static int current_transaction = 0;
static int demo_counter = 0;

// Get current time
static void get_time_string(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, size, "%02d:%02d", t->tm_hour, t->tm_min);
}

// Keypad callback simulator
static void simulate_keypad_input(void) {
    // Simulate random number input
    if (demo_counter % 3 == 0) {
        char digit = '0' + (rand() % 10);
        
        if (strcmp(amount_buffer, "0.00") == 0) {
            amount_buffer[0] = digit;
            amount_buffer[1] = '\0';
        } else {
            strcat(amount_buffer, &digit);
        }
        
        ui_update_amount(amount_buffer);
    }
}

// Demo transaction simulation
static void simulate_transaction(void) {
    // Cycle through customers
    current_customer = (current_customer + 1) % 6;
    ui_update_customer(demo_customers[current_customer]);
    
    // Cycle through transactions
    current_transaction = (current_transaction + 1) % 5;
    ui_update_transaction(demo_transactions[current_transaction]);
    
    // Update status
    const char* statuses[] = {
        "🟢 Transaction approved",
        "🟡 Processing...",
        "🔴 Insufficient funds",
        "🟢 Cash dispensed",
        "🟡 Verifying..."
    };
    lv_color_t colors[] = {
        lv_color_hex(0x2ecc71),  // Green
        lv_color_hex(0xf39c12),  // Orange
        lv_color_hex(0xe74c3c),  // Red
        lv_color_hex(0x2ecc71),  // Green
        lv_color_hex(0xf39c12)   // Orange
    };
    
    int status_idx = rand() % 5;
    ui_update_status(statuses[status_idx], colors[status_idx]);
    
    // Show random message
    if (demo_counter % 7 == 0) {
        const char* messages[] = {
            "Please insert cash",
            "Enter PIN to proceed",
            "Take your receipt",
            "Transaction complete",
            "Thank you for banking with us"
        };
        ui_show_message(messages[rand() % 5], lv_color_hex(0x3498db));
    }
}

// Timer callback for updates
static void demo_timer_cb(lv_timer_t* timer) {
    char time_str[10];
    
    // Update time
    get_time_string(time_str, sizeof(time_str));
    ui_update_time(time_str);
    
    // Simulate keypad input
    simulate_keypad_input();
    
    // Simulate transaction every 5 seconds
    if (demo_counter++ >= 5) {
        simulate_transaction();
        demo_counter = 0;
        
        // Reset amount occasionally
        if (rand() % 3 == 0) {
            strcpy(amount_buffer, "0.00");
            ui_update_amount(amount_buffer);
        }
    }
}

// Main application
void app_main(void) {
    // Initialize LVGL
    lv_init();
    
    // Initialize display (platform specific)
    // display_init();
    
    // Initialize UI
    ui_init();
    
    // Set initial values
    ui_set_teller_id("#001");
    ui_update_customer("John Mwangi");
    ui_update_transaction("DEPOSIT");
    ui_update_amount("0.00");
    ui_update_status("🟢 Ready for transaction", lv_color_hex(0x2ecc71));
    
    // Create demo timer
    lv_timer_create(demo_timer_cb, 1000, NULL);
    
    // Main loop
    while (1) {
        lv_timer_handler();
        // Platform delay
        // lv_tick_inc(5);
        // delay_ms(5);
    }
}

// Simple main for compilation
int main(void) {
    app_main();
    return 0;
}