/* Copyright 2015 Michael Rutherford
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

//Imported header files
#include "solus-installer.h"
#include <gtk/gtk.h>
#include <stdlib.h>

//Function prototypes
static void quit_installer_clicked (GtkWidget* window, gpointer user_data);
static void whats_new_clicked (GtkWidget* window, gpointer user_data);
static void install_solus_clicked (GtkWidget* window, gpointer user_data);
//static void install_warning (GtkWidget* window, gpointer user_data);
static void region_entered (GtkWidget* window, gpointer user_data);
static void user_name_entered (GtkWidget* window, gpointer user_data);
static void full_name_entered (GtkWidget* window, gpointer user_data);
static void password_entered (GtkWidget* window, gpointer user_data);
static void password_verification_entered (GtkWidget* window, gpointer user_data);

//Function to destroy the window so that the installer quits
static void quit_installer_clicked (GtkWidget* window, gpointer user_data) {
        printf ("Quit installer clicked.\n");
        gtk_widget_destroy (window);
        exit (EXIT_SUCCESS);
}

//Function to display changelog for Solus
static void whats_new_clicked (GtkWidget* window, gpointer user_data) {
        printf ("What's new clicked.\n");
        gint status;

        //Declaration/instantiation of the changelog dialog
        GtkWidget* new_dialog = gtk_dialog_new_with_buttons ("What's new?",
                                                             GTK_WINDOW (window),
                                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                                             "_OK",
                                                             GTK_RESPONSE_ACCEPT,
                                                             NULL);
        gtk_window_set_default_size (GTK_WINDOW (new_dialog), DIALOG_X, DIALOG_Y);
        //Shows the changelog dialog widget
        status = gtk_dialog_run (GTK_DIALOG (new_dialog));
        if (status == 0) {
                gtk_widget_destroy (new_dialog);
        } else {
                gtk_widget_destroy (new_dialog);
        }
}

//Function to destroy the window so that the installer quits
static void install_solus_clicked (GtkWidget* notebook, gpointer user_data) {
        printf ("Install Solus clicked.\n");
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to handle when the region is entered
static void region_entered (GtkWidget* window, gpointer user_data) {
        printf ("Region entered.\n");
}

//Function to handle when the city is entered
static void city_entered (GtkWidget* notebook, gpointer user_data) {
        printf ("City entered.\n");
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to handle when the username is entered
static void user_name_entered (GtkWidget* window, gpointer user_data) {
        printf ("Username entered.\n");
}

//Function to handle when the full name is entered
static void full_name_entered (GtkWidget* window, gpointer user_data) {
        printf ("Full name entered.\n");
}

//Function to handle when the password is entered
static void password_entered (GtkWidget* window, gpointer user_data) {
        printf ("Password entered.\n");
}

//Function to handle when the password verification is entered
static void password_verification_entered (GtkWidget* notebook, gpointer user_data) {
        printf ("Password verification entered.\n");
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

/*
//Function to display an installation warning
static void install_warning (GtkWidget* window, gpointer user_data) {
        printf ("Install warning displayed.\n");
        gint status;

        //Declaration/instantiation of the changelog dialog
        GtkWidget* new_dialog = gtk_dialog_new_with_buttons ("What's new?",
                                                             GTK_WINDOW (window),
                                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                                             "_OK",
                                                             GTK_RESPONSE_ACCEPT,
                                                             NULL);
        gtk_window_set_default_size (GTK_WINDOW (new_dialog), DIALOG_X, DIALOG_Y);
        //Shows the changelog dialog widget
        status = gtk_dialog_run (GTK_DIALOG (new_dialog));
        if (status == 0) {
                gtk_widget_destroy (new_dialog);
        } else {
                gtk_widget_destroy (new_dialog);
        }
*/

//Function that is activated by the main function
static void activate (GtkApplication* app, gpointer user_data) {
        //Declaration/instantiation of the window and notebook
        GtkWidget* window = gtk_application_window_new (app);
        GtkWidget* notebook = gtk_notebook_new ();

        //Declaration/instantiation of the button boxes
        GtkWidget* welcome_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* date_time_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* users_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
        GtkWidget* partition_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

        //Declaration/instantiation of the tab labels
        GtkWidget* welcome_label = gtk_label_new ("Welcome");
        GtkWidget* date_time_label = gtk_label_new ("Date/Time");
        GtkWidget* users_label = gtk_label_new ("Users");
        GtkWidget* partition_label = gtk_label_new ("Partioning");

        //Declaration/instantiation of the new button and the icon
        GtkWidget* new_button = gtk_button_new_with_label ("What's New In Solus?");
        GtkWidget* new_icon = gtk_image_new_from_file ("../data/images/new.png");

        //Declaration/instantiation of the livecd button and the icon
        GtkWidget* livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        GtkWidget* livecd_icon = gtk_image_new_from_file ("../data/images/live.png");

        //Declaration/instantiation of the install button and the icon
        GtkWidget* install_button = gtk_button_new_with_label ("Install Solus");
        GtkWidget* install_icon = gtk_image_new_from_file ("../data/images/install.png");

        //Declaration/instantiation of the region button and the icon
        GtkWidget* region_button = gtk_button_new_with_label ("Region");
        GtkWidget* region_icon = gtk_image_new_from_file ("../data/images/region.png");

        //Declaration/instantiation of the city button and the icon
        GtkWidget* city_button = gtk_button_new_with_label ("City");
        //GtkWidget* city_icon = gtk_image_new_from_file ("../data/city.png");

        //Declaration/instantiation of the widgets for the user name
        GtkWidget* user_name_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget* user_name_label = gtk_label_new ("User Name");
        GtkWidget* user_name_entry = gtk_entry_new ();

        //Declaration/instantiation of the widgets for the full name
        GtkWidget* full_name_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget* full_name_label = gtk_label_new ("Full Name");
        GtkWidget* full_name_entry = gtk_entry_new ();

        //Declaration/instantiation of the widgets for the password
        GtkWidget* password_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget* password_label = gtk_label_new ("Password");
        GtkWidget* password_entry = gtk_entry_new ();

        //Declaration/instantiation of the widgets for the password verification
        GtkWidget* verify_password_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
        GtkWidget* verify_password_label = gtk_label_new ("Verify Password");
        GtkWidget* verify_password_entry = gtk_entry_new ();

        //Assigns properties to the window
        gtk_window_set_title (GTK_WINDOW (window), "solus-installer");
        gtk_window_set_icon_from_file (GTK_WINDOW (window), "../data/images/live.png", NULL);
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), WINDOW_X, WINDOW_Y);
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);

        //Sets the tabs positions and adds pages with labels
        gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), welcome_button_box, welcome_label, 0);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), date_time_button_box, date_time_label, 1);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), users_box, users_label, 2);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), partition_button_box, partition_label, 3);

        //Sets button box layouts
        gtk_button_box_set_layout (GTK_BUTTON_BOX (welcome_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (date_time_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (users_box), GTK_BUTTONBOX_SPREAD);

        //Assigns an image to the livecd button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (livecd_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (livecd_button), livecd_icon);
        gtk_button_set_image_position (GTK_BUTTON (livecd_button), GTK_POS_TOP);
        g_signal_connect_swapped (livecd_button, "clicked", G_CALLBACK (quit_installer_clicked), window);

        //Assigns an image to the changelog button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (new_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (new_button), new_icon);
        gtk_button_set_image_position (GTK_BUTTON (new_button), GTK_POS_TOP);
        g_signal_connect_swapped (new_button, "clicked", G_CALLBACK (whats_new_clicked), window);

        //Assigns an image to the install button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (install_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (install_button), install_icon);
        gtk_button_set_image_position (GTK_BUTTON (install_button), GTK_POS_TOP);
        g_signal_connect_swapped (install_button, "clicked", G_CALLBACK (install_solus_clicked), notebook);

        //Assigns an image to the region button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (region_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (region_button), region_icon);
        gtk_button_set_image_position (GTK_BUTTON (region_button), GTK_POS_TOP);
        g_signal_connect (region_button, "clicked", G_CALLBACK (region_entered), window);

        /*
        //Assigns an image to the city button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (city_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (city_button), city_icon);
        gtk_button_set_image_position (GTK_BUTTON (city_button), GTK_POS_TOP);
        */
        g_signal_connect_swapped (city_button, "clicked", G_CALLBACK (city_entered), notebook);

        //Sets user tab label properties
        gtk_label_set_width_chars (GTK_LABEL (user_name_label), ENTRY_WIDTH);
        gtk_label_set_xalign (GTK_LABEL (user_name_label), ALIGN_LEFT);
        gtk_label_set_width_chars (GTK_LABEL (full_name_label), ENTRY_WIDTH);
        gtk_label_set_xalign (GTK_LABEL (full_name_label), ALIGN_LEFT);
        gtk_label_set_width_chars (GTK_LABEL (password_label), ENTRY_WIDTH);
        gtk_label_set_xalign (GTK_LABEL (password_label), ALIGN_LEFT);
        gtk_label_set_width_chars (GTK_LABEL (verify_password_label), ENTRY_WIDTH);
        gtk_label_set_xalign (GTK_LABEL (verify_password_label), ALIGN_LEFT);

        //Removes character visibility from the password entry objects
        gtk_entry_set_visibility (GTK_ENTRY (password_entry), FALSE);
        gtk_entry_set_visibility (GTK_ENTRY (verify_password_entry), FALSE);

        //Connects each entry on the user tab to a function
        g_signal_connect (user_name_entry, "activate", G_CALLBACK (user_name_entered), window);
        g_signal_connect (full_name_entry, "activate", G_CALLBACK (full_name_entered), window);
        g_signal_connect (password_entry, "activate", G_CALLBACK (password_entered), window);
        g_signal_connect_swapped (verify_password_entry, "activate", G_CALLBACK (password_verification_entered), notebook);

        //Adds buttons to button boxes
        gtk_container_add (GTK_CONTAINER (window), notebook);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), livecd_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), new_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), install_button);
        gtk_container_add (GTK_CONTAINER (date_time_button_box), region_button);
        gtk_container_add (GTK_CONTAINER (date_time_button_box), city_button);
        gtk_container_add (GTK_CONTAINER (user_name_box), user_name_label);
        gtk_container_add (GTK_CONTAINER (user_name_box), user_name_entry);
        gtk_container_add (GTK_CONTAINER (users_box), user_name_box);
        gtk_container_add (GTK_CONTAINER (full_name_box), full_name_label);
        gtk_container_add (GTK_CONTAINER (full_name_box), full_name_entry);
        gtk_container_add (GTK_CONTAINER (users_box), full_name_box);
        gtk_container_add (GTK_CONTAINER (password_box), password_label);
        gtk_container_add (GTK_CONTAINER (password_box), password_entry);
        gtk_container_add (GTK_CONTAINER (users_box), password_box);
        gtk_container_add (GTK_CONTAINER (verify_password_box), verify_password_label);
        gtk_container_add (GTK_CONTAINER (verify_password_box), verify_password_entry);
        gtk_container_add (GTK_CONTAINER (users_box), verify_password_box);

        //Displays the window and all the widgets attached to it
        gtk_widget_show_all (window);
}

//Main function
int main (int argc, char **argv) {
        //Declaration of the GtkApplicaton and status
        GtkApplication* app;
        gint status;

        //Instantiation of the GtkApplication and the status
        app = gtk_application_new ("com.solus-project.installer", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);

        //Returns the status of the applicaton
        return status;
}
