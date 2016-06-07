/*
 * Copyright 2015-2016 Michael Rutherford
 *
 * This file is part of solus-installer.
 *
 * solus-installer is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * solus-installer is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with solus-installer. If not, see http://www.gnu.org/licenses/.
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include "solus-installer.h"

/* Function to find the user's location automatically */
void find_clicked(GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Find location automatically entered.\n");
        }
}

/* Function to let the user select their timezone manually */
void manual_clicked(GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Find location manually entered.\n");
        }
}

/* Function to handle when the region is entered */
void region_clicked(char* selected_region, gpointer user_data)
{
        extern char* region;
        region = selected_region;
        if (DEBUG_MODE == TRUE) {
                printf("Region is now %s.\n", region);
        }
}
