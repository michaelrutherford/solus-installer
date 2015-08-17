#include <gtk/gtk.h>
#include <stdlib.h>

static void quit_installer (GtkWidget* window, gpointer user_data) {
        gtk_widget_destroy (window);
        exit (0);
}

static void install_warning (GtkWidget* window, gpointer user_data) {
        GtkWidget *warning_dialog;
        GtkWidget *warning_text;

        warning_dialog = gtk_message_dialog_new (GTK_WINDOW (window), 
                                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_WARNING,
                                                 GTK_BUTTONS_OK,
                                                 "Installing Solus will erase the contents of the disk.");
        gtk_window_set_title (GTK_WINDOW (warning_dialog), "Warning");
        g_signal_connect_swapped (warning_dialog, "response", G_CALLBACK (gtk_widget_destroy), warning_dialog);

        gtk_widget_show_all (warning_dialog);
}

static void change_log (GtkWidget* window, gpointer user_data) {
        GtkWidget *new_dialog;

        new_dialog = gtk_message_dialog_new (GTK_WINDOW (window), 
                                             GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_MESSAGE_WARNING,
                                             GTK_BUTTONS_OK,
                                             "Everyone likes new things, right? "
                                             "Well we’ve been getting a lot of software updated lately, " 
                                             "but realised we hadn’t really told everyone.. "
                                             "Well, far be it from me to miss an opportunity to brag a lil’.\n\n"
                                             "- Linux Kernel 4.1.4\n"
                                             "- Firefox 39.0.3\n"
                                             "- LibreOffice 5.0.0.5\n\n"
                                             "We’ve also made a few security updates lately:\n"
                                             "- WebKitGTK+ updated to 2.8.5 – addressing multiple security concerns\n"
                                             "- libxml2 – patched CVE-2015-1819\n"
                                             "- libidn updated to 1.32 – addressing multiple concerns in older versions\n"
                                             "- kernel – addressed CVE-2015-5697\n\n"
                                             "Some obligatory mentions for other packages we also have:\n"
                                             "- rust 1.2.0\n"
                                             "- Atom 1.0.5\n"
                                             "- Telegram 0.8.48\n");
        gtk_window_set_title (GTK_WINDOW (new_dialog), "What's New?");
        g_signal_connect_swapped (new_dialog, "response", G_CALLBACK (gtk_widget_destroy), new_dialog);

        gtk_widget_show_all (new_dialog);
}

static void activate (GtkApplication* app, gpointer user_data) {
        GtkWidget *window;
        GtkWidget *new_button;
        GtkWidget *new_icon;
        GtkWidget *livecd_button;
        GtkWidget *livecd_icon;
        GtkWidget *install_icon;
        GtkWidget *install_button;
        GtkWidget *button_box;

        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "Solus Installer");
        gtk_window_set_icon_from_file (GTK_WINDOW (window), "live.png", NULL);
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), 1250, 500);
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);

        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (button_box), GTK_BUTTONBOX_SPREAD);

        livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        livecd_icon = gtk_image_new_from_file ("live.png");
        gtk_button_set_always_show_image (GTK_BUTTON (livecd_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (livecd_button), livecd_icon);
        g_signal_connect_swapped (livecd_button, "clicked", G_CALLBACK (quit_installer), window);
        
        new_button = gtk_button_new_with_label ("What's New In Solus?");
        new_icon = gtk_image_new_from_file ("new.png");
        gtk_button_set_always_show_image (GTK_BUTTON (new_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (new_button), new_icon);
        g_signal_connect_swapped (new_button, "clicked", G_CALLBACK (change_log), window);

        install_button = gtk_button_new_with_label ("Install Solus");
        install_icon = gtk_image_new_from_file ("install.png");
        gtk_button_set_always_show_image (GTK_BUTTON (install_button), TRUE);
        gtk_button_set_image (GTK_BUTTON (install_button), install_icon);
        g_signal_connect_swapped (install_button, "clicked", G_CALLBACK (install_warning), window);

        gtk_container_add (GTK_CONTAINER (window), button_box);
        gtk_container_add (GTK_CONTAINER (button_box), livecd_button);
        gtk_container_add (GTK_CONTAINER (button_box), new_button);
        gtk_container_add (GTK_CONTAINER (button_box), install_button);

        gtk_widget_show_all (window);
}

int main (int argc, char **argv) {
        GtkApplication *app;
        int status;
        app = gtk_application_new ("com.solus-project.installer", G_APPLICATION_FLAGS_NONE);
        g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        status = g_application_run (G_APPLICATION (app), argc, argv);
        g_object_unref (app);
        return status;
}
