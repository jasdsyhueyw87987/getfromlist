sudo apt-get install libwebkit2gtk-4.0-dev
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "WebKitGTK Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));
    
    // Load a URL
    webkit_web_view_load_uri(web_view, "https://acas.edu.bd");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
