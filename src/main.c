/* SPDX-License-Identifier: GPL-3.0
 * Furfetch
 *
 * main.c
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
#include <string.h>
#include "help.h"
#include "utils.h"


void display_ascii_art() {
	printf(" |\\__/,|   (`\\\n");
	printf(" |0 0  |.--.) )\n");
	printf(" ( T   )     /\n");
	printf("(((u_(((/(((_/\n");
}


void print_details() {
	get_hostname();
	get_os_info();
	get_uptime();
	get_cpu_info();
	get_memory_info();
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			print_help(argv[0]);
			return 0;
		}
	}

    printf("\n");
	print_details();
	printf("\n");
    display_ascii_art();

    return 0;
}
