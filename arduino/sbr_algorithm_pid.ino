void calculateAnglePID(void)
{
    double output_a, output_b;

    if (micros() - g_timer_angle_pid > 10000) {
#ifdef DEBUG_PID_CYCLE
        Serial.print(" A.");
        Serial.print(millis());
#endif
        // Calculate angle.
        double angle_error = g_calc_y_angle - g_angle_setpoint;
        g_angle_integral += angle_error;
        g_angle_output = g_p_angle * angle_error + g_i_angle * g_angle_integral;

        // Calculate turn.
        if (g_robot_state == ROBOT_TURNING) {
            g_turn_integral = 0;
        }
        else {
            g_turn_integral += g_gyro_z;
            g_turn_output = g_p_turn * g_gyro_z + g_i_turn * g_turn_integral;
        }

        output_a = g_angle_output;
        output_b = g_angle_output;


#ifdef ENABLE_MOTOR

#endif
        g_timer_angle_pid = micros();
    }
}

void calculateSpeedPID(void)
{
    if (micros() - g_timer_speed_pid > 50000) {
#ifdef DEBUG_PID_PARAMETER
        Serial.print(" S.");
        Serial.print(millis());
#endif
        double speed_error = (g_count_encoder_a + g_count_encoder_b) * 0.5 -
            g_speed_setpoint;
        g_speed_integral += speed_error;
        g_angle_setpoint = g_p_speed * speed_error + g_i_speed *
            g_speed_integral;

        g_timer_speed_pid = micros();
    }
}
