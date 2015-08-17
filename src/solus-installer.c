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
                                                 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                 GTK_MESSAGE_QUESTION,
                                                 GTK_BUTTONS_OK_CANCEL,
                                                 "Installing Solus will override the contents of the disk.");
        g_signal_connect_swapped (warning_dialog, "response", G_CALLBACK (gtk_widget_destroy), warning_dialog);

        gtk_widget_show_all (warning_dialog);
}

static void activate (GtkApplication* app, gpointer user_data) {
        GtkWidget *window;
        GtkWidget *livecd_button;
        GtkWidget *install_button;
        GtkWidget *button_box;

        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "Solus Installer");
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);

        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add (GTK_CONTAINER (window), button_box);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (button_box), GTK_BUTTONBOX_SPREAD);

        livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        g_signal_connect_swapped (livecd_button, "clicked", G_CALLBACK (quit_installer), window);

        install_button = gtk_button_new_with_label ("Install Solus");
        g_signal_connect_swapped (install_button, "clicked", G_CALLBACK (install_warning), window);

        gtk_container_add (GTK_CONTAINER (button_box), livecd_button);
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
