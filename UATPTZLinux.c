/*
 * UATPTZLinux - Control de cámara PTZ
 * Copyright (C) 2020  Manuel Alcaraz Zambrano
 * Copyright (C) 2020  José Manuel Alcaraz Pelegrina
 *
 * This file is part of UATPTZLinux.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <gtk/gtk.h>
#include <string.h>
#include "data.h"
#include "load_presets.h"


void go_to_scene();

void activate();

void choose_class(GtkFileChooserButton *file_chooser_button, gpointer ptr) {
    presets_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser_button));
    load_presets();
    printf("El aula es %s\n", presets_file);
}

void choose_device(GtkWidget *wid, gpointer ptr) {
    current_device = gtk_combo_box_get_active(GTK_COMBO_BOX (wid));
    selected = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT (wid));
    printf("El device es %d %s \n", current_device, selected);
}


void turn_left(GtkWidget *wid, gpointer ptr) {
    if (panabs < (max_pan - pan_step)) {
        panabs += pan_step;
        go_to_scene();
    }
}

void turn_right(GtkWidget *wid, gpointer ptr) {
    if (panabs > (min_pan + pan_step)) {
        panabs -= pan_step;
        go_to_scene();
    }
}

void turn_up(GtkWidget *wid, gpointer ptr) {
    if (tiltabs < (max_tilt - tilt_step)) {
        tiltabs += tilt_step;
        go_to_scene();
    }
}

void turn_down(GtkWidget *wid, gpointer ptr) {
    if (tiltabs > (min_tilt + tilt_step)) {
        tiltabs -= tilt_step;
        go_to_scene();
    }
}

void increase_zoom(GtkWidget *wid, gpointer ptr) {
    if (zoomabs < max_zoom) {
        zoomabs++;
        go_to_scene();
    }
}

void decrease_zoom(GtkWidget *wid, gpointer ptr) {
    if (zoomabs > min_zoom) {
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
    panabs = escenasval[zona][0];
    tiltabs = escenasval[zona][1];
    zoomabs = escenasval[zona][2];
    go_to_scene();
}

void go_to_screen(GtkWidget *wid, gpointer ptr) {
    zona = 1;
    panabs = escenasval[zona][0];
    tiltabs = escenasval[zona][1];
    zoomabs = escenasval[zona][2];
    go_to_scene();
}

void go_to_teacher_table(GtkWidget *wid, gpointer ptr) {
    zona = 2;
    panabs = escenasval[zona][0];
    tiltabs = escenasval[zona][1];
    zoomabs = escenasval[zona][2];
    go_to_scene();
}

void go_to_general_view(GtkWidget *wid, gpointer ptr) {
    zona = 3;
    panabs = escenasval[zona][0];
    tiltabs = escenasval[zona][1];
    zoomabs = escenasval[zona][2];
    go_to_scene();
}

void go_to_front_view(GtkWidget *wid, gpointer ptr) {
    zona = 4;
    panabs = escenasval[zona][0];
    tiltabs = escenasval[zona][1];
    zoomabs = escenasval[zona][2];
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
