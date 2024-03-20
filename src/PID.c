//MIT License
//
//Copyright (c) 2024 budgettsfrog
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "PID.h"

int pid_init(pid_controller_t *pid, pid_value_t kp, pid_value_t ki, pid_value_t kd, pid_value_t out_min, pid_value_t out_max)
{
    if(!pid)
        return PID_ERR_INVALID_ARGUMENT;

    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->setpoint = 0;
    pid->last_error = 0;
    pid->integral = 0;

    pid->out_min = out_min;
    pid->out_max = out_max;

    return PID_ERR_OK;
}

pid_value_t pid_run(pid_controller_t *pid, pid_value_t input, pid_value_t dt)
{
    if(!pid)
        return 0;

    pid_value_t error = pid->setpoint - input;
    pid->integral += error * dt;
    pid_value_t output = (pid->kp * error) + (pid->ki * pid->integral) + (pid->kd * ((error - pid->last_error) / dt));
    pid->last_error = error;
    return (output < pid->out_min) ? pid->out_min : (output > pid->out_max) ? pid->out_max : output;
}

void pid_set_setpoint(pid_controller_t *pid, pid_value_t setpoint)
{
    if(pid)
        pid->setpoint = setpoint;
}