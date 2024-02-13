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

#ifndef PID_H_
#define PID_H_

// Protect against C++ compilers
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "PID_fixed_point.h"

#define PID_ERR_OK 0
#define PID_ERR_INVALID_ARGUMENT -1

typedef struct {
    // PID coefficients
    pid_value_t kp;
    pid_value_t ki;
    pid_value_t kd;

    // PID state
    pid_value_t setpoint;
    pid_value_t last_error;
    pid_accum_t integral;

    // Output limits
    pid_value_t out_min;
    pid_value_t out_max;
} pid_controller_t;

/**
 * @brief Initialize a PID controller
 * @param pid Pointer to the PID controller
 * @param kp Proportional gain
 * @param ki Integral gain
 * @param kd Derivative gain
 * @param out_min Minimum output value
 * @param out_max Maximum output value
 * @return 0 if successful, negative error code otherwise
 */
int pid_init(pid_controller_t *pid, pid_value_t kp, pid_value_t ki, pid_value_t kd, pid_value_t out_min, pid_value_t out_max);

/**
 * @brief Run the PID controller
 * @param pid Pointer to the PID controller
 * @param input Current input value
 * @param dt Time since last update
 * @return Output value
 */
pid_value_t pid_run(pid_controller_t *pid, pid_value_t input, pid_value_t dt);

/** @brief Update the set point for a PID instance
 * @param pid Pointer to the PID controller
 * @param setpoint New set point
 */
void pid_set_setpoint(pid_controller_t *pid, pid_value_t setpoint);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PID_H_ */