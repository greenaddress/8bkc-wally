#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "8bkc-hal.h"
#include "8bkc-ugui.h"

#include "powerbtn_menu.h"
#include "ugui.h"
#include "esp_system.h"

#include <wally_core.h>
#include <wally_bip39.h>

#define TITLE "Wally"

static uint32_t entropy[10];
static int current_word = 0;

int get_keydown() {
    static int old_buttons = 0xffff;
    int new_buttons = kchal_get_keys();
    int ret = (old_buttons ^ new_buttons) & new_buttons;
    old_buttons = new_buttons;
    return ret;
}

uint16_t centered_text_offset(char *text, uint8_t font_width) {
    size_t text_length = strlen(text) + 1;
    return (KC_SCREEN_W / 2) - ((text_length / 2) * font_width);
}

void draw_title_screen() {
    uint8_t font_width = 6;
    uint8_t font_height = 8;

    kcugui_cls();
    UG_FontSelect(&FONT_6X8);
    UG_SetForecolor(C_LAWN_GREEN);
    UG_PutString(centered_text_offset(TITLE, font_width), 0, TITLE);
    UG_FontSetHSpace(0);
    char *word;
    int word_n = 0;
    char *mnemonic, *original;
    int res;
    res = bip39_mnemonic_from_bytes(NULL, (unsigned char *)entropy, BIP39_ENTROPY_LEN_320, &mnemonic);
    if (res != WALLY_OK) {
        UG_PutString(centered_text_offset("Error", font_width), KC_SCREEN_H / 2, "Error");
        kcugui_flush();
        return;
    }
    original = mnemonic;
    while ((word = strsep(&mnemonic, " "))) {
        if (word_n == current_word) {
            break;
        }
        ++word_n;
    }
    char num[2];
    sprintf(num, "%d", current_word + 1);
    UG_SetForecolor(C_ANTIQUE_WHITE);
    UG_PutString(centered_text_offset(num, font_width), 2 * font_height + 3, num);
    UG_FontSetHSpace(0);
    UG_SetForecolor(C_TOMATO);
    UG_PutString(centered_text_offset(word, font_width), 3 * font_height + 6, word);
    kcugui_flush();
    wally_free_string(original);
}

void do_title_screen() {
    draw_title_screen();
    while (1) {
        int btn = get_keydown();
        if (btn & KC_BTN_POWER) {
            kchal_exit_to_chooser();
        }
        if(btn & KC_BTN_LEFT) {
            if (current_word > 0) {
                --current_word;
                draw_title_screen();
            }
        }
        else if(btn & KC_BTN_RIGHT) {
            if (current_word < 23) {
                ++current_word;
                draw_title_screen();
            }
        }
    }
}

void reset_entropy()
{
    for(int i = 0; i < 10; ++i) {
        entropy[i] = esp_random();
    }
}

void app_main() {
    kchal_init();
    kcugui_init();
    reset_entropy();
    wally_init(0);
    while (1) {
        do_title_screen();
    }
}
