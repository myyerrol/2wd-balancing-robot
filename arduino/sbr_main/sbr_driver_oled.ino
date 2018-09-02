#ifdef ENABLE_OLED
void initOLED(void)
{
    g_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    g_oled.clearDisplay();
    g_oled.setTextSize(4);
    g_oled.setTextColor(WHITE);
    g_oled.setCursor(30, 20);
    g_oled.print("SBR");
    g_oled.display();
}

void showSelfCheckingInfo(void)
{
    g_oled.clearDisplay();
    g_oled.setTextSize(1);
    g_oled.setCursor(0, 0);

    for (uint8_t i = 0; i < strlen(g_info_check); i++)
    {
        uint8_t byte =  pgm_read_byte_near(g_info_check + i);
        g_oled.print(byte);
    }
    for (uint8_t i = 0; i < strlen(g_info_temp); i++)
    {
        uint8_t byte =  pgm_read_byte_near(g_info_temp + i);
        g_oled.print(byte);
    }

    g_oled.print((double)g_temp / 340.0 + 31.53);
    g_oled.display();
}
#endif
