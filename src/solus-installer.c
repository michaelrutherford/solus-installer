#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data) {
        GtkWidget *window;
        GtkWidget *livecd_button;
        GtkWidget *button_box;
        window = gtk_application_window_new (app);
        gtk_window_set_title (GTK_WINDOW (window), "Solus Installer");
        gtk_window_set_resizable (GTK_WINDOW (window), TRUE);
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add (GTK_CONTAINER (window), button_box);
        livecd_button = gtk_button_new_with_label ("Keep Using LiveCD");
        gtk_container_add (GTK_CONTAINER (button_box), livecd_button);
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
