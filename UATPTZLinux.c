#include <gtk/gtk.h>
#include <string.h>
#include "aulas.h"


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


void panrelp(GtkWidget *wid, gpointer ptr) {
    if (panabs < (maxpan - steppan)) {
        panabs += steppan;
        go_to_scene();
    }
}

void panrelm(GtkWidget *wid, gpointer ptr) {
    if (panabs > (minpan + steppan)) {
        panabs -= steppan;
        go_to_scene();
    }
}

void tiltrelp(GtkWidget *wid, gpointer ptr) {
    if (tiltabs < (maxtilt - steptilt)) {
        tiltabs += steptilt;
        go_to_scene();
    }
}

void tiltrelm(GtkWidget *wid, gpointer ptr) {
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

void resetescenas() {
    panabs = 0;
    tiltabs = 0;
    zoomabs = 0;
    go_to_scene();
}


void pizarra(GtkWidget *wid, gpointer ptr) {
    zona = 0;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void pantalla(GtkWidget *wid, gpointer ptr) {
    zona = 1;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void profesor(GtkWidget *wid, gpointer ptr) {
    zona = 2;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void general(GtkWidget *wid, gpointer ptr) {
    zona = 3;
    panabs = escenasval[aula][zona][0];
    tiltabs = escenasval[aula][zona][1];
    zoomabs = escenasval[aula][zona][2];
    go_to_scene();
}

void activate(GtkApplication *application, gpointer user_data) {
    // Window
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../layout.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    gtk_application_add_window(application, GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "Control cámara PTZ");
    gtk_widget_show_all(window);

    // Signals

    // Exit Button
    GtkWidget *exit_button = GTK_WIDGET(gtk_builder_get_object(builder, "exit_button"));
    g_signal_connect(exit_button, "clicked", G_CALLBACK(gtk_window_close), NULL);

    // Reset Scenes Button
    GtkWidget *reset_scenes = GTK_WIDGET(gtk_builder_get_object(builder, "reset_button"));
    g_signal_connect(reset_scenes, "clicked", G_CALLBACK(resetescenas), NULL);

    // Pan Relative + Button
    GtkWidget *pan_rel_incr_button = GTK_WIDGET(gtk_builder_get_object(builder, "pan_rel_incr_button"));
    g_signal_connect(pan_rel_incr_button, "clicked", G_CALLBACK(panrelp), NULL);

    // Pan Relative - Button
    GtkWidget *pan_rel_decr_button = GTK_WIDGET(gtk_builder_get_object(builder, "pan_rel_decr_button"));
    g_signal_connect(pan_rel_decr_button, "clicked", G_CALLBACK(panrelm), NULL);

    // Tilt Relative + Button
    GtkWidget *tilt_rel_incr_button = GTK_WIDGET(gtk_builder_get_object(builder, "tilt_rel_incr_button"));
    g_signal_connect(tilt_rel_incr_button, "clicked", G_CALLBACK(tiltrelp), NULL);

    // Tilt Relative - Button
    GtkWidget *tilt_rel_decr_button = GTK_WIDGET(gtk_builder_get_object(builder, "tilt_rel_decr_button"));
    g_signal_connect(tilt_rel_decr_button, "clicked", G_CALLBACK(tiltrelm), NULL);

    // Zoom + Button
    GtkWidget *zoom_incr_button = GTK_WIDGET(gtk_builder_get_object(builder, "zoom_incr_button"));
    g_signal_connect(zoom_incr_button, "clicked", G_CALLBACK(increase_zoom), NULL);

    // Zoom + Button
    GtkWidget *zoom_decr_button = GTK_WIDGET(gtk_builder_get_object(builder, "zoom_decr_button"));
    g_signal_connect(zoom_decr_button, "clicked", G_CALLBACK(decrease_zoom), NULL);

    // Blackboard Button
    GtkWidget *blackboard_button = GTK_WIDGET(gtk_builder_get_object(builder, "blackboard_button"));
    g_signal_connect(blackboard_button, "clicked", G_CALLBACK(pizarra), NULL);

    // Screen Button
    GtkWidget *screen_button = GTK_WIDGET(gtk_builder_get_object(builder, "screen_button"));
    g_signal_connect(screen_button, "clicked", G_CALLBACK(pantalla), NULL);

    // Teacher's Table Button
    GtkWidget *teacher_table_button = GTK_WIDGET(gtk_builder_get_object(builder, "teacher_table_button"));
    g_signal_connect(teacher_table_button, "clicked", G_CALLBACK(profesor), NULL);

    // General View Button
    GtkWidget *general_view_button = GTK_WIDGET(gtk_builder_get_object(builder, "general_view_button"));
    g_signal_connect(general_view_button, "clicked", G_CALLBACK(general), NULL);

    // Change Device Combo Box
    GtkWidget *device_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "device_chooser"));
    g_signal_connect (device_chooser, "changed", G_CALLBACK(choose_device), NULL);

    // Change Class Combo Box
    GtkWidget *class_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "class_chooser"));
    g_signal_connect (class_chooser, "changed", G_CALLBACK(choose_class), NULL);
}

int main(int argc, char *argv[]) {
    GtkApplication *application;
    int status;

    application = gtk_application_new("es.sevilinux.controlptz", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);

    return status;
}