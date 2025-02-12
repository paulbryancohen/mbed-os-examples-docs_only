/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "HeapBlockDevice.h"
#include "FlashSimBlockDevice.h"

#define BLOCK_SIZE 512

HeapBlockDevice bd(2048, BLOCK_SIZE); // 2048 bytes with a block size of 512 bytes.
uint8_t block[BLOCK_SIZE] = "Hello World!\n";

int main()
{

    int erase_unit_size = 512;
    HeapBlockDevice heap_bd(4 * erase_unit_size, 1, 4, erase_unit_size);
    FlashSimBlockDevice flash_bd(&heap_bd);

    // This initializes the flash simulator block device (as well as the underlying heap block device).
    int err = flash_bd.init();

    uint8_t buf[16];
    for (int i = 0; i < sizeof(buf); i++) {
        buf[i] = i;
    }

    // This will fail because the erase unit in address 0 has not been erased.
    err = flash_bd.program(buf, 0, sizeof(buf));

    // Erase the erase unit in address 0.
    err = flash_bd.erase(0, erase_unit_size);

    // This will succeed now that the erase unit is erased.
    err = flash_bd.program(buf, 0, sizeof(buf));
}
