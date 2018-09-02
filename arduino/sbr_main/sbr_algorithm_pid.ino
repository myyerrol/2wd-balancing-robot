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
        if (g_robot_state & STATE_TURNING) {
            g_turn_integral = 0;
        }
        else {
            g_turn_integral += g_gyro_z;
            g_turn_output = g_p_turn * g_gyro_z + g_i_turn * g_turn_integral;
        }

        output_a = g_angle_output;
        output_b = g_angle_output;

        output_a = constrain(output_a, -255, 255);
        output_b = constrain(output_b, -255, 255);

#ifdef ENABLE_MOTOR
        if (output_a > 0) {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
        }
        else {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
        }

        if (output_b > 0) {
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else {
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }

        setMotorSpeed(MOTOR_A, output_a);
        setMotorSpeed(MOTOR_B, output_b);
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
