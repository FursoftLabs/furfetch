/* SPDX-License-Identifier: GPL-3.0
 * Furfetch
 *
 * help.c
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
#include "help.h"

void print_help(char *program_name) {
	printf("Usage: %s [OPTION]\n", program_name);
	printf("Fetch system information\n");
	printf("\n");
	printf("Options:\n");
	printf("  -h, --help\t\tDisplay this help message\n");
	printf("  -v, --version\t\tDisplay version information\n");
	printf("\n");
	printf("Copyright (C) 2024 FurSoft Laboratories\n");
	printf("Copyright (C) 2024 0x4248\n");
	printf("GNU General Public License v3.0\n");
}