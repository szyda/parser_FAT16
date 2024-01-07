//
// Created by Sylwia Szyda on 07/01/2024.
//

#include "disk.h"
#include <stdint.h>
#include <stdlib.h>

struct disk_t* disk_open_from_file(const char* volume_file_name) {
    if (volume_file_name == NULL) {
        errno = EFAULT;
        return NULL;
    }

    FILE *file = fopen(volume_file_name, "rb");
    if (file == NULL) {
        errno = ENOENT;
        return NULL;
    }

    struct disk_t *disk_image = malloc(sizeof(struct disk_t));
    if (disk_image == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    disk_image->file = file;

    return disk_image;
}


int disk_read(struct disk_t* pdisk, int32_t first_sector, void* buffer, int32_t sectors_to_read) {
    if (pdisk == NULL || pdisk->file == NULL || first_sector < 0 || buffer == NULL || sectors_to_read < 1) {
        errno = EFAULT;
        return -1;
    }

    size_t valid_size = sectors_to_read * SECTOR_SIZE;

    fseek(pdisk->file, first_sector * SECTOR_SIZE, SEEK_SET);

    if (fread(buffer, 1, sectors_to_read * SECTOR_SIZE, pdisk->file) != valid_size) {
        errno = ERANGE;
        return  -1;
    }

    return sectors_to_read;
}

int disk_close(struct disk_t* pdisk) {
    if (pdisk == NULL | pdisk->file == NULL) {
        errno = EFAULT;
        return -1;
    }

    fclose(pdisk->file);
    free(pdisk);

    return 0;
}
