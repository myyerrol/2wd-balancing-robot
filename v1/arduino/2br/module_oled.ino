#ifdef ENABLE_OLED
void initOLED(void) {
    g_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    g_oled.clearDisplay();
    g_oled.setTextSize(2);
    g_oled.setTextColor(WHITE);
    g_oled.setCursor(0, 0);
    g_oled.print("SBR");
    g_oled.display();

    g_oled.drawBitmap((g_oled.width()  - OLED_LOGO_WIDTH ) / 2,
                      (g_oled.height() - OLED_LOGO_HEIGHT) / 2,
                       g_logo_bmp,
                       OLED_LOGO_WIDTH,
                       OLED_LOGO_HEIGHT, 1);
    g_oled.display();
}

void showSelfCheckingInfo(void) {
    g_oled.clearDisplay();
    g_oled.setTextSize(1);
    g_oled.setCursor(0, 0);

    // Read constants from Flash program storage space to SRAM dynamic memory
    // to reduce resource consumption during SRAM runtime.
    for (uint8_t i = 0; i < strlen((char *)g_info_check); i++) {
        // Adopting a 16 bit short address addressing mode, it can address up
        // to 64KB data.
        uint8_t ch = pgm_read_byte_near(g_info_check + i);
        g_oled.print(ch);
    }
    for (uint8_t i = 0; i < strlen((char *)g_info_temp); i++) {
        uint8_t ch = pgm_read_byte_near(g_info_temp + i);
        g_oled.print(ch);
    }

    g_oled.print((double)g_temp / 340.0 + 31.53);
    g_oled.display();
}
#endif
