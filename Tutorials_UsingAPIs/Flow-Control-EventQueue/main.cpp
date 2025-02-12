/*
 * Copyright (c) 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

void flip(DigitalOut &led)
{
    led = !led;
}

int main()
{
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);

    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call_every(1000, flip, led1);
    queue.call_every(500, flip, led2);

    // events are executed by the dispatch method
    queue.dispatch_forever();
}
