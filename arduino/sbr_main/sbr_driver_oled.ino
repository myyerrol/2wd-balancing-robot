#ifdef ENABLE_OLED
void initOLED(void) {
    g_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    g_oled.clearDisplay();
    g_oled.setTextSize(2);
    g_oled.setTextColor(WHITE);
    g_oled.setCursor(0, 0);
    g_oled.print("SBR");
    g_oled.display();
}

void showSelfCheckingInfo(void) {
    g_oled.clearDisplay();
    g_oled.setTextSize(1);
    g_oled.setCursor(0, 0);

    // 将Flash程序存储空间中的常量读取到SRAM动态内存中，减少SRAM运行时的资源占用
   for (uint8_t i = 0; i < strlen(g_info_check); i++) {
       // 采用16位短地址寻址模式，最多可以寻址64kB的数据
       uint8_t ch = pgm_read_byte_near(g_info_check + i);
       g_oled.print(ch);
   }
   for (uint8_t i = 0; i < strlen(g_info_temp); i++) {
       uint8_t ch = pgm_read_byte_near(g_info_temp + i);
       g_oled.print(ch);
   }

    g_oled.print((double)g_temp / 340.0 + 31.53);
    g_oled.display();
}
#endif
