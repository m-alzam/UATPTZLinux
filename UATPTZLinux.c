#include <gtk/gtk.h>
#include <string.h>
#include "classes.h"


int maxpan = 606918;
int minpan = -606112;
int maxtilt = 319104;
int mintilt = -105537;
int maxzoom = 996;
int minzoom = 0;
int steppan = 806;
int steptilt = 831;

int aula = 0; // Por defecto pone el SUM 1
int actdevice = 0; //Por defecto pone video0
char *selected = "/dev/video0";
int zona = 0; // Por defecto zona 0 que es la Pizarra

int panabs = 0;
int tiltabs = 0;
int zoomabs = 0;

void go_to_scene();

void activate();

void choose_class(GtkWidget *wid, gpointer ptr) {
    aula = gtk_combo_box_get_active(GTK_COMBO_BOX (wid));
    //char *selected = gtk_combo_box_text_get_active_text ( GTK_COMBO_BOX_TEXT (wid));
    //printf ("The value of the combo is %d %s\n", sel, selected);
    printf("El aula es %d\n", aula);
}

void choose_device(GtkWidget *wid, gpointer ptr) {
    actdevice = gtk_combo_box_get_active(GTK_COMBO_BOX (wid));
    selected = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (wid));
    printf("El device es %d %s \n", actdevice, selected);
}


void turn_left(GtkWidget *wid, gpointer ptr) {
    if (panabs < (maxpan - steppan)) {
        panabs += steppan;
        go_to_scene();
    }
}

void turn_right(GtkWidget *wid, gpointer ptr) {
    if (panabs > (minpan + steppan)) {
        panabs -= steppan;
        go_to_scene();
    }
}

void turn_up(GtkWidget *wid, gpointer ptr) {
    if (tiltabs < (maxtilt - steptilt)) {
        tiltabs += steptilt;
        go_to_scene();
    }
}

void turn_down(GtkWidget *wid, gpointer ptr) {
    if (tiltabs > (mintilt + steptilt)) {
        tiltabs -= steptilt;
        go_to_scene();
    }
}

void increase_zoom(GtkWidget *wid, gpointer ptr) {
    if (zoomabs < maxzoom) {
        zoomabs++;
        go_to_scene();
    }
}

void decrease_zoom(GtkWidget *wid, gpointer ptr) {
    if (zoomabs > minzoom) {
        zoomabs--;
        go_to_scene();
    }
}


void go_to_scene() {

    char comandopan[100];
    char comandotilt[100];
    char comandozoom[100];
    strcpy(comandopan, "v4l2-ctl -d ");
    strcpy(comandotilt, "v4l2-ctl -d ");
    strcpy(comandozoom, "v4l2-ctl -d ");
    strcat(comandopan, selected);
    strcat(comandotilt, selected);
    strcat(comandozoom, selected);
    strcat(comandopan, " -c pan_absolute=");
    strcat(comandotilt, " -c tilt_absolute=");
    strcat(comandozoom, " -c zoom_absolute=");
    char pan[10];
    sprintf(pan, "%d", panabs);
    char tilt[10];
    sprintf(tilt, "%d", tiltabs);
    char zoom[10];
    sprintf(zoom, "%d", zoomabs);
    strcat(comandopan, pan);
    strcat(comandotilt, tilt);
    strcat(comandozoom, zoom);

    printf("%s\n", comandopan);
    system(comandopan);
    printf("%s\n", comandotilt);
    system(comandotilt);
    printf("%s\n", comandozoom);
    system(comandozoom);
}

void reset_scenes() {
    panabs = 0;
    tiltabs = 0;
    zoomabs = 0;
    go_to_scene();
}


void go_to_blackboard(GtkWidget *wid, gpointer ptr) {
    zona = 0;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void go_to_screen(GtkWidget *wid, gpointer ptr) {
    zona = 1;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void go_to_teacher_table(GtkWidget *wid, gpointer ptr) {
    zona = 2;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void go_to_general_view(GtkWidget *wid, gpointer ptr) {
    zona = 3;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void quit(GtkWidget *wid, gpointer window) {
    gtk_window_close(window);
}

void on_menu_item_about(GtkWidget *widget, gpointer dialog) {
    gtk_widget_show(dialog);
}

void activate(GtkApplication *application, gpointer user_data) {
    // Window
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_resource(builder, "/es/sevilinux/uatptzlinux/layout.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    gtk_application_add_window(application, GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Control cámara PTZ");
    gtk_widget_show_all(window);

    // Signals
    gtk_builder_connect_signals(builder, NULL);
}

int main(int argc, char *argv[]) {
    GtkApplication *application;
    int status;

    application = gtk_application_new("es.sevilinux.uatptzlinux", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);

    return status;
}