//
// Created by Sylwia Szyda on 07/01/2024.
//

#ifndef PARSER_FAT16_VOLUME_H
#define PARSER_FAT16_VOLUME_H

#include "disk.h"

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct volume_t;
struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector);
int fat_close(struct volume_t* pvolume);

#endif //PARSER_FAT16_VOLUME_H
