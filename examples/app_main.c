/* -----------------------------------------------------------------------------
 * Copyright (c) 2020 Arm Limited (or its affiliates). All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdint.h>

#include "cmsis_os2.h"

#include "netif.h"

static const osThreadAttr_t app_main_attr = {
    .stack_size = 4096U};

void app_initialize(void);

extern int32_t socket_startup(void);
extern int32_t demo(void);

/*-----------------------------------------------------------------------------
 * Application main thread
 *----------------------------------------------------------------------------*/
static void app_main(void *argument)
{
    int32_t status;
    osTimerId_t timer_id;
    printf(" Azure IoT Demo\n");

    status = socket_startup();

    if (status == 0)
    {
        timer_id = osTimerNew(timer_callback, osTimerPeriodic, NULL, NULL);
        osTimerStart(timer_id, 1000U); // start timer with delay 1 seconds
        demo();
    }
}

/*-----------------------------------------------------------------------------
 * Application initialization
 *----------------------------------------------------------------------------*/
void app_initialize(void)
{
    osThreadNew(app_main, NULL, &app_main_attr);
}
