/* Copyright 2015-2016 Michael Rutherford
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
#include <parted/parted.h>

//Function prototypes
static void quit_installer_clicked (GtkWidget* window, gpointer user_data);
static void whats_new_clicked (GtkWidget* window, gpointer user_data);
static void install_solus_clicked (GtkWidget* notebook, gpointer user_data);
static void find_clicked (GtkWidget* notebook, gpointer user_data);
static void manual_clicked (GtkWidget* notebook, gpointer user_data);
static void region_clicked (char* selected_region, gpointer user_data);
static void full_disk_clicked (GtkWidget* notebook, gpointer user_data);
static void advanced_clicked (GtkWidget* notebook, gpointer user_data);
//static void install_warning (GtkWidget* window, gpointer user_data);

//Declares strings to store timezone and user data
char* region;
char* user_name;
char* full_name;
char* password;
char* verified_password;

//Function to destroy the window so that the installer quits
static void quit_installer_clicked (GtkWidget* window, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Quit installer clicked.\n");
        }
        gtk_widget_destroy (window);
        exit (EXIT_SUCCESS);
}

//Function to display changelog for Solus
static void whats_new_clicked (GtkWidget* window, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("What's new clicked.\n");
        }

        //Declaration/instantiation of the changelog dialog
        GtkWidget* new_dialog = gtk_dialog_new_with_buttons ("What's new?",
                                                             GTK_WINDOW (window),
                                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                                             "_OK",
                                                             GTK_RESPONSE_ACCEPT,
                                                             NULL);

        //Declaration/instantiation of the changelog content area and text
        GtkWidget* new_content_area = gtk_dialog_get_content_area (GTK_DIALOG (new_dialog));
        GtkWidget* changelog_text = gtk_label_new ("Solus Release 1.2");

        //Sets the dialog window size and adds
        gtk_window_set_default_size (GTK_WINDOW (new_dialog), DIALOG_X, DIALOG_Y);
        gtk_container_add (GTK_CONTAINER (new_content_area), changelog_text);

        //Connects the dialog button to a function
        g_signal_connect_swapped (new_dialog, "response", G_CALLBACK (gtk_widget_destroy), new_dialog);

        //Shows the changelog dialog widget
        gtk_widget_show_all (new_dialog);
}

//Function to destroy the window so that the installer quits
static void install_solus_clicked (GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Install Solus clicked.\n");
        }
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to find the user's location automatically
static void find_clicked (GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Find location automatically entered.\n");
        }
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to let the user select their timezone manually
static void manual_clicked (GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Find location manually entered.\n");
        }
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to handle when the region is entered
static void region_clicked (char* selected_region, gpointer user_data)
{
        region = selected_region;
        if (DEBUG_MODE == TRUE) {
                printf ("Region is now %s.\n", region);
        }
}

//Function to handle when the user chooses advanced mode
static void advanced_clicked (GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Advanced mode entered.\n");
        }
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

//Function to handle when the user chooses full disk mode
static void full_disk_clicked (GtkWidget* notebook, gpointer user_data)
{
        if (DEBUG_MODE == TRUE) {
                printf ("Full disk mode entered.\n");
        }
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
        gtk_notebook_next_page (GTK_NOTEBOOK (notebook));
}

/*
//Function to display an installation warning
static void install_warning (GtkWidget* window, gpointer user_data)
{
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
static void activate (GtkApplication* app, gpointer user_data)
{
        //Make dark theme the default theme
        g_object_set (gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);

        //Declaration/instantiation of the window and notebook
        GtkWidget* window = gtk_application_window_new (app);
        GtkWidget* notebook = gtk_notebook_new ();

        //Declaration/instantiation of the button boxes
        GtkWidget* welcome_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* find_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* date_time_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* choose_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* full_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        GtkWidget* advanced_button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);

        //Declaration/instantiation of the tab labels
        GtkWidget* welcome_label = gtk_label_new ("Welcome");
        GtkWidget* find_label = gtk_label_new ("Find");
        GtkWidget* date_time_label = gtk_label_new ("Date/Time");
        GtkWidget* choose_label = gtk_label_new ("Choose");
        GtkWidget* full_label = gtk_label_new ("Full Disk Mode");
        GtkWidget* advanced_label = gtk_label_new ("Advanced Mode");

        //GtkWidget* welcome_title_label = gtk_label_new ("Welcome to Solus Operating System");

        //Declaration/instantiation of the new button and the icon
        GtkWidget* new_button = gtk_button_new_with_label ("What's New In Solus?");
        GtkWidget* new_icon = gtk_image_new_from_file ("data/images/new.png");

        //Declaration/instantiation of the livecd button and the icon
        GtkWidget* livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        GtkWidget* livecd_icon = gtk_image_new_from_file ("data/images/live.png");

        //Declaration/instantiation of the install button and the icon
        GtkWidget* install_button = gtk_button_new_with_label ("Install Solus");
        GtkWidget* install_icon = gtk_image_new_from_file ("data/images/install.png");
        
        //Declaration/instantiation of the find button and the icon
        GtkWidget* find_button = gtk_button_new_with_label ("Find location automatically");
        GtkWidget* find_icon = gtk_image_new_from_file ("data/images/find.png");
        
        //Declaration/instantiation of the find button and the icon
        GtkWidget* manual_button = gtk_button_new_with_label ("Find location manually");
        GtkWidget* manual_icon = gtk_image_new_from_file ("data/images/manual.png");
        
        //Declaration/instantiation of the region button and the icon
        GtkWidget* region_button = gtk_menu_button_new ();
        GtkWidget* region_icon = gtk_image_new_from_file ("data/images/region.png");
        
        //Declaration/instantiation of the region menu
        GtkWidget* region_menu = gtk_menu_new ();

        //Declaration/instantiation of the region menu items
        GtkWidget* region_menu_item_america = gtk_menu_item_new_with_label ("America");
        GtkWidget* region_menu_item_not_america = gtk_menu_item_new_with_label ("Everywhere else");
        
        //Declaration/instantiation of the full disk button
        GtkWidget* full_button = gtk_button_new_with_label ("Full disk mode (Recommended)");

        //Declaration/instantiation of the advanced install button
        GtkWidget* advanced_button = gtk_button_new_with_label ("Advanced mode");

        //Assigns properties to the window
        gtk_window_set_title (GTK_WINDOW (window), "solus-installer");
        gtk_window_set_icon_from_file (GTK_WINDOW (window), "data/images/live.png", NULL);
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), WINDOW_X, WINDOW_Y);
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);

        //Sets the tabs positions and adds pages with labels
        gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
        if (DEBUG_MODE == TRUE) {
                gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), TRUE);
        } else {
                gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), FALSE);
        }
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), welcome_button_box, welcome_label, 0);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), find_button_box, find_label, 1);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), date_time_button_box, date_time_label, 2);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), choose_button_box, choose_label, 3);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), full_button_box, full_label, 4);
        gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), advanced_button_box, advanced_label, 5);

        //Sets button box layouts
        gtk_button_box_set_layout (GTK_BUTTON_BOX (welcome_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (find_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (date_time_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (choose_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (full_button_box), GTK_BUTTONBOX_SPREAD);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (advanced_button_box), GTK_BUTTONBOX_SPREAD);

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
        
        //Assigns an image to the find button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (find_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (find_button), find_icon);
        gtk_button_set_image_position (GTK_BUTTON (find_button), GTK_POS_TOP);
        g_signal_connect_swapped (find_button, "clicked", G_CALLBACK (find_clicked), notebook);

        //Assigns an image to the manual button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (manual_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (manual_button), manual_icon);
        gtk_button_set_image_position (GTK_BUTTON (manual_button), GTK_POS_TOP);
        g_signal_connect_swapped (manual_button, "clicked", G_CALLBACK (manual_clicked), notebook);

        //Assigns an image to the region button and connects a function to the button
        gtk_button_set_always_show_image (GTK_BUTTON (region_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (region_button), region_icon);
        gtk_button_set_image_position (GTK_BUTTON (region_button), GTK_POS_TOP);
        
        //Sets the label on the region button
        gtk_button_set_label (GTK_BUTTON (region_button), "Region");

        //Attaches the region menu items to the region menu
        gtk_menu_attach (GTK_MENU (region_menu), region_menu_item_america, 0, 1, 0, 1);
        gtk_menu_attach (GTK_MENU (region_menu), region_menu_item_not_america, 0, 1, 1, 2);

        //Adds the region menu to the region button and displays the region menu
        gtk_menu_button_set_popup (GTK_MENU_BUTTON (region_button), region_menu);
        gtk_widget_show_all (region_menu);

        //Connects each menu item to a function
        g_signal_connect_swapped (region_menu_item_america, "activate", G_CALLBACK (region_clicked), "America");
        g_signal_connect_swapped (region_menu_item_not_america, "activate", G_CALLBACK (region_clicked), "Somewhere");

        //Connects the partitioning choice buttons to functions
        g_signal_connect_swapped (full_button, "clicked", G_CALLBACK (full_disk_clicked), notebook);
        g_signal_connect_swapped (advanced_button, "clicked", G_CALLBACK (advanced_clicked), notebook);

        //Sets the relief to none on all the buttons
        gtk_button_set_relief (GTK_BUTTON (livecd_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (new_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (install_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (find_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (manual_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (region_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (full_button), GTK_RELIEF_NONE);
        gtk_button_set_relief (GTK_BUTTON (advanced_button), GTK_RELIEF_NONE);

        //Adds buttons to button boxes
        gtk_container_add (GTK_CONTAINER (window), notebook);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), livecd_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), new_button);
        gtk_container_add (GTK_CONTAINER (welcome_button_box), install_button);
        gtk_container_add (GTK_CONTAINER (find_button_box), find_button);
        gtk_container_add (GTK_CONTAINER (find_button_box), manual_button);
        gtk_container_add (GTK_CONTAINER (date_time_button_box), region_button);
        gtk_container_add (GTK_CONTAINER (choose_button_box), full_button);
        gtk_container_add (GTK_CONTAINER (choose_button_box), advanced_button);

        //Displays the window and all the widgets attached to it
        gtk_widget_show_all (window);
}

//Main function
int main (int argc, char **argv)
{
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
