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
#include <stdarg.h>

#define BLUE "\033[0;34m"
#define RESET "\033[0m"

char* get_logo(){
    return
" |\\__/,|   (`\\\n"
" |0 0  |.--.) )\n"
" ( T   )     /\n"
"(((u_(((/(((_/\n";
}
                            

int get_logo_line_cout(const char *logo) {
    int count = 0;
    for (int i = 0; logo[i] != '\0'; i++) {
        if (logo[i] == '\n') {
            count++;
        }
    }
    return count;
}


int get_longest_line_in_logo(const char *logo) {
    int longest_line = 0;
    int current_line = 0;
    for (int i = 0; logo[i] != '\0'; i++) {
        if (logo[i] == '\n') {
            if (current_line > longest_line) {
                longest_line = current_line;
            }
            current_line = 0;
        } else {
            current_line++;
        }
    }
    return longest_line;
}

char get_logo_line(const char *logo, int current_line, int max_len){
    if (current_line >= get_logo_line_cout(logo)) {
        for (int i = 0; i < max_len; i++) {
            printf(" ");
        }
        return 0;
    }

    char line[256];

    int i = 0;
    int j = 0;
    while (logo[i] != '\0') {
        if (logo[i] == '\n') {
            line[j] = '\0';
            if (current_line == 0) {
                break;
            }
            current_line--;
            j = 0;
        } else {
            line[j] = logo[i];
            j++;
        }
        i++;
    }

    int line_len = strlen(line);
    int diff = max_len - line_len;

    for (int i = 0; i < diff; i++) {
        line[line_len + i] = ' ';
    }

    line[line_len + diff] = '\0';
    printf("%s", line);
}

int current_line = 0;

int show_detail(const char *name, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int tabs = 2 - strlen(name) / 8;
    const char *logo = get_logo();
    int max_len = get_longest_line_in_logo(logo);
    max_len++;
    get_logo_line(logo, current_line, max_len);
    printf(BLUE);
    printf("%s:", name);
    printf(RESET);
    for (int i = 0; i < tabs; i++) {
        printf("\t");
    }


    int ret = vprintf(format, args);
    va_end(args);
    current_line++;
    return ret;
}

FILE *open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

void get_hostname() {
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));
    show_detail("Hostname", "%s\n", hostname);
}

void get_os_info() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    show_detail("OS", "%s\n", buffer.sysname);
    show_detail("Kernel Version", "%s\n", buffer.release);
    show_detail("OS Version", "%s\n", buffer.version);
}



void get_cpu_info() {
    FILE *cpuinfo = open_file("/proc/cpuinfo", "r");

    char line[256];
    while (fgets(line, sizeof(line), cpuinfo)) {
        if (strncmp(line, "model name", 10) == 0) {
            char *cpu_model = strchr(line, ':') + 2;
            show_detail("CPU Model", "%s", cpu_model);
            break;
        }
    }

    fclose(cpuinfo);
}

void get_memory_info() {
    FILE *meminfo = open_file("/proc/meminfo", "r");

    char line[256];
    long total_memory = 0, free_memory = 0;
    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_memory) == 1) {
        }
        if (sscanf(line, "MemAvailable: %ld kB", &free_memory) == 1) {
            break;
        }
    }

    show_detail("Memory", "%.2f GB / %.2f GB\n", (total_memory - free_memory) / (1024.0 * 1024.0), total_memory / (1024.0 * 1024.0));
    fclose(meminfo);
}

void get_uptime() {
    FILE *uptime_file = open_file("/proc/uptime", "r");

    double uptime_seconds;
    fscanf(uptime_file, "%lf", &uptime_seconds);
    fclose(uptime_file);

    int days = uptime_seconds / (60 * 60 * 24);
    int hours = ((int)uptime_seconds % (60 * 60 * 24)) / (60 * 60);
    int minutes = ((int)uptime_seconds % (60 * 60)) / 60;

    show_detail("Uptime", "%d days, %d hours, %d minutes\n", days, hours, minutes);
}
