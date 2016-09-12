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

#ifndef welcome_h
#define welcome_h

#include <gtk/gtk.h>

/* Welcome function prototypes */
void quit_installer_clicked(GtkWidget *window, gpointer user_data);
void whats_new_clicked(GtkWidget *window, gpointer user_data);
void install_solus_clicked(GtkWidget *notebook, gpointer user_data);

#endif
