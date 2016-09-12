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

/* Function to handle when the user chooses advanced mode */
void advanced_clicked(GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Advanced mode entered.\n");
        }
}

/* Function to handle when the user chooses full disk mode */
void full_disk_clicked(GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Full disk mode entered.\n");
        }
}
