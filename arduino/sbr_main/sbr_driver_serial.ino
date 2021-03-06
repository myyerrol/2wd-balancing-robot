void analyzeSerialData(void) {
    if (g_robot_state & STATE_SERIAL_END) {
        strtok(g_serial_buffer, ",");
        g_joy_x = atof(strtok(NULL, ","));
        g_joy_y = atof(strtok(NULL, ";"));
        switch (g_serial_buffer[1]) {
            case 'J': {
                g_robot_state |= STATE_REMOTE_CONTROL;
                g_speed_setpoint = g_joy_y * 30;
                if ( g_joy_x < -0.2 || g_joy_x > 0.2) {
                    g_robot_state |= STATE_TURNING;
                    if (g_speed_setpoint > 0) {
                        g_turn_output =  g_joy_x * 15;
                    }
                    else {
                        g_turn_output = -g_joy_x * 15;
                    }
                }
                else {
                    g_robot_state &= ~STATE_TURNING;
                    g_turn_output = 0;
                }
                break;
            }
            case 'M': {
                g_robot_state |= STATE_REMOTE_CONTROL;
                g_speed_setpoint = g_joy_x + 20;
                g_speed_setpoint = constrain(g_speed_setpoint, -30, 30);
                if (g_joy_y < -10 || g_joy_y > 10) {
                    g_robot_state |= STATE_TURNING;
                    if (g_speed_setpoint > 0) {
                        g_turn_output =  g_joy_y * 0.3;
                    }
                    else {
                        g_turn_output = -g_joy_y * 0.3;
                    }
                }
                else {
                    g_robot_state &= ~STATE_TURNING;
                    g_turn_output = 0;
                }
                break;
            }
            case 'S': {
                g_speed_setpoint = 0;
                g_turn_output = 0;
                g_robot_state &= ~STATE_TURNING;
                g_robot_state &= ~STATE_REMOTE_CONTROL;
                break;
            }
            default: {
                break;
            }
        }
        g_robot_state &= ~STATE_SERIAL_END;
    }
}

void initSerial(void) {
    Wire.begin();
    Serial.begin(115200);
}

void getSerialData(void) {
    while (Serial.available() > 0) {
<<<<<<< HEAD
        char ch = char(Serial.read());
=======
        char ch = Serial.read();
>>>>>>> 9986ba7eb39c51c01595d9ec6a7024f36a63cda7
        if (ch == ';') {
            g_serial_buffer[g_serial_count] = ch;
            g_serial_count = 0;
            g_robot_state |= STATE_SERIAL_END;
        }
        else {
            g_serial_buffer[g_serial_count] = ch;
            g_serial_count++;
        }
    }
}
