# SPDX-License-Identifier: GPL-3.0
# Furfetch
#
# CMakelists.txt
#
# COPYRIGHT NOTICE
# Copyright (C) 2024 FurSoft Laboratories and contributors
# This file and software is licenced under the GNU General Public License v3.0. 
# Redistribution of this file and software is permitted under the terms of the 
# GNU General Public License v3.0. 
#
# NO WARRANTY IS PROVIDED WITH THIS SOFTWARE. I AM NOT RELIABLE FOR ANY DAMAGES.
# THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY AND LIABILITY OF ANY KIND.
#
# You should have received a copy of the GNU General Public License v3.0
# along with this program. If you have not please see the following link:
# https://www.gnu.org/licenses/gpl-3.0.html

project(furfetch)

add_compile_options(-fsanitize=address,undefined)
add_executable(furfetch src/help.c src/utils.c src/main.c )
