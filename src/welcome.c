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
#include "solus-installer.h"
#include <stdio.h>
#include <stdlib.h>

/* Function to destroy the window so that the installer quits */
void quit_installer_clicked(GtkWidget *window, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Quit installer clicked.\n");
        }
        gtk_widget_destroy(window);
        exit(EXIT_SUCCESS);
}

/* Function to display changelog for Solus */
void whats_new_clicked(GtkWidget *window, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("What's new clicked.\n");
        }

        /* Declaration/instantiation of the changelog dialog */
        GtkWidget *new_dialog = gtk_dialog_new_with_buttons("What's new?",
                                                            GTK_WINDOW(window),
                                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            "_OK",
                                                            GTK_RESPONSE_ACCEPT,
                                                            NULL);

        /* Declaration/instantiation of the changelog content area and text */
        GtkWidget *new_content_area = gtk_dialog_get_content_area(GTK_DIALOG (new_dialog));
        GtkWidget *changelog_text = gtk_label_new("Solus Release X");

        /* Sets the dialog window size and adds */
        gtk_window_set_default_size(GTK_WINDOW(new_dialog), DIALOG_X, DIALOG_Y);
        gtk_container_add(GTK_CONTAINER(new_content_area), changelog_text);

        /* Connects the dialog button to a function */
        g_signal_connect_swapped(new_dialog, "response", G_CALLBACK(gtk_widget_destroy), new_dialog);

        /* Shows the changelog dialog widget */
        gtk_widget_show_all(new_dialog);
}

/* Function to destroy the window so that the installer quits */
void install_solus_clicked(GtkWidget *notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf("Install Solus clicked.\n");
        }
}
