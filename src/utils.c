/* SPDX-License-Identifier: GPL-3.0
 * Furfetch
 *
 * utils.c
 *
 * COPYRIGHT NOTICE
 * Copyright (C) 2024 FurSoft Laboratories and contributors
 * This file and software is licenced under the GNU General Public License v3.0. 
 * Redistribution of this file and software is permitted under the terms of the 
 * GNU General Public License v3.0. 
 *
 * NO WARRANTY IS PROVIDED WITH THIS SOFTWARE. I AM NOT RELIABLE FOR ANY DAMAGES.
 * THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY AND LIABILITY OF ANY KIND.
 *
 * You should have received a copy of the GNU General Public License v3.0
 * along with this program. If you have not please see the following link:
 * https://www.gnu.org/licenses/gpl-3.0.html
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h> 
#include <unistd.h>
#include <string.h>

void get_hostname() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    printf("Host: %s\n", hostname);
}

void get_os_info() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    printf("OS: %s\n", buffer.sysname);
    printf("Kernel: %s\n", buffer.release);
}

void get_cpu_info() {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (!cpuinfo) {
        perror("Failed to open /proc/cpuinfo");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), cpuinfo)) {
        if (strncmp(line, "model name", 10) == 0) {
            char *cpu_model = strchr(line, ':') + 2;
            printf("CPU: %s", cpu_model);
            break;
        }
    }

    fclose(cpuinfo);
}

void get_memory_info() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (!meminfo) {
        perror("Failed to open /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    char line[256];
    long total_memory = 0, free_memory = 0;
    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_memory) == 1) {
        }
        if (sscanf(line, "MemAvailable: %ld kB", &free_memory) == 1) {
            break;
        }
    }

    printf("Memory: %.2f GB / %.2f GB\n", (total_memory - free_memory) / (1024.0 * 1024.0), total_memory / (1024.0 * 1024.0));

    fclose(meminfo);
}

void get_uptime() {
    FILE *uptime_file = fopen("/proc/uptime", "r");
    if (!uptime_file) {
        perror("Failed to open /proc/uptime");
        exit(EXIT_FAILURE);
    }

    double uptime_seconds;
    fscanf(uptime_file, "%lf", &uptime_seconds);
    fclose(uptime_file);

    int days = uptime_seconds / (60 * 60 * 24);
    int hours = ((int)uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = ((int)uptime_seconds % (60 * 60)) / 60;

    printf("Uptime: %d days, %d hours, %d minutes\n", days, hours, minutes);
}
