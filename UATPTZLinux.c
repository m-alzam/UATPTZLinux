#include <gtk-2.0/gtk/gtk.h>
#include <string.h>
#include "aulas.h"



int maxpan=606918;
int minpan=-606112;
int maxtilt=319104;
int mintilt=-105537;
int maxzoom=996;
int minzoom=0;
int steppan=806;
int steptilt=831;

int aula=0; // Por defecto pone el SUM 1
int actdevice=0; //Por defecto pone video0
char *selected="/dev/video0";
int zona=0; // Por defecto zona 0 que es la Pizarra

int panabs=0;
int tiltabs=0;
int zoomabs=0;

void escenas();

void selectAula (GtkWidget *wid, gpointer ptr)
{
	aula = gtk_combo_box_get_active (GTK_COMBO_BOX (wid));
	//char *selected = gtk_combo_box_text_get_active_text ( GTK_COMBO_BOX_TEXT (wid));
	//printf ("The value of the combo is %d %s\n", sel, selected);
	printf("El aula es %d\n", aula);
}

void selectDevice (GtkWidget *wid, gpointer ptr)
{
	actdevice = gtk_combo_box_get_active(GTK_COMBO_BOX (wid));
	selected= gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (wid));
	printf("El device es %d %s \n", actdevice, selected);
}



void panrelp(GtkWidget *wid, gpointer ptr)
{
	if(panabs< (maxpan-steppan))
	{
		panabs+=steppan;
		escenas();
	}

}

void panrelm(GtkWidget *wid, gpointer ptr)
{
       if(panabs> (minpan+steppan))
        {
                panabs-=steppan;
                escenas();
        }

}

void tiltrelp(GtkWidget *wid, gpointer ptr)
{
       if(tiltabs< (maxtilt-steptilt))
        {
                tiltabs+=steptilt;
                escenas();
        }

}

void tiltrelm(GtkWidget *wid, gpointer ptr)
{
       if(tiltabs > (mintilt+steptilt))
        {
                tiltabs-=steptilt;
                escenas();
        }


}

void zoomp(GtkWidget *wid, gpointer ptr)
{
       if(zoomabs< maxzoom)
        {
                zoomabs++;
                escenas();
        }


}

void zoomm(GtkWidget *wid, gpointer ptr)
{
       if(zoomabs> minzoom)
        {
                zoomabs--;
                escenas();
        }


}





void escenas()
{
	
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
	printf("%s\n", comandotilt);
	printf("%s\n", comandozoom);

	system(comandopan);
	system(comandotilt);
	system(comandozoom);
}

void resetescenas()
{
	panabs=0;
	tiltabs=0;
	zoomabs=0;
	escenas();
}


void pizarra(GtkWidget *wid, gpointer ptr)
{
        zona=0;
	panabs=escenasval[aula][zona][0];
	tiltabs=escenasval[aula][zona][1];
	zoomabs=escenasval[aula][zona][2];
        escenas();
}

void pantalla(GtkWidget *wid, gpointer ptr)
{
	zona=1;
        panabs=escenasval[aula][zona][0];
        tiltabs=escenasval[aula][zona][1];
        zoomabs=escenasval[aula][zona][2];
	escenas();
}

void profesor(GtkWidget *wid, gpointer ptr)
{
	zona=2;
        panabs=escenasval[aula][zona][0];
        tiltabs=escenasval[aula][zona][1];
        zoomabs=escenasval[aula][zona][2];
	escenas();
}

void general(GtkWidget *wid, gpointer ptr)
{
	zona=3;
        panabs=escenasval[aula][zona][0];
        tiltabs=escenasval[aula][zona][1];
        zoomabs=escenasval[aula][zona][2];
	escenas();
}



void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
//	printf("%i\n", escenas[1][0][0]);
	gtk_init (&argc,&argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Exit");
	g_signal_connect (win, "delete_event", G_CALLBACK(end_program), NULL);
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program), NULL);
	GtkWidget *btnpanrelp = gtk_button_new_with_label ("Pan Relative +");
	g_signal_connect (btnpanrelp, "clicked", G_CALLBACK (panrelp), NULL);
	GtkWidget *btnpanrelm = gtk_button_new_with_label ("Pan Relative -");
        g_signal_connect (btnpanrelm, "clicked", G_CALLBACK (panrelm), NULL);
	GtkWidget *btntilrelp = gtk_button_new_with_label ("Tilt Relative +");
        g_signal_connect (btntilrelp, "clicked", G_CALLBACK (tiltrelp), NULL);
	GtkWidget *btntilrelm = gtk_button_new_with_label ("Tilt Relative -");
        g_signal_connect (btntilrelm, "clicked", G_CALLBACK (tiltrelm), NULL);
	GtkWidget *btnzoomp = gtk_button_new_with_label ("Zoom +");
        g_signal_connect (btnzoomp, "clicked", G_CALLBACK (zoomp), NULL);
	GtkWidget *btnzoomm = gtk_button_new_with_label ("Zoom -");
        g_signal_connect (btnzoomm, "clicked", G_CALLBACK (zoomm), NULL);
	GtkWidget *btnPizarra = gtk_button_new_with_label ("Pizarra");
	g_signal_connect (btnPizarra, "clicked", G_CALLBACK (pizarra), NULL);
	GtkWidget *btnPantalla = gtk_button_new_with_label ("Pantalla");
	g_signal_connect (btnPantalla, "clicked", G_CALLBACK(pantalla), NULL);
	GtkWidget *btnProfe = gtk_button_new_with_label ("Mesa Profesor");
	g_signal_connect (btnProfe, "clicked", G_CALLBACK(profesor), NULL);
	GtkWidget *btnGeneral = gtk_button_new_with_label ("Vista General");
	g_signal_connect (btnGeneral, "clicked", G_CALLBACK(general), NULL); 
	GtkWidget *btnResetEscenas = gtk_button_new_with_label("Reset");
	g_signal_connect (btnResetEscenas, "clicked", G_CALLBACK(resetescenas), NULL);
	GtkWidget *lbl= gtk_label_new ("Control PTZ");
	GtkWidget *lblDevice = gtk_label_new("Device");
	GtkWidget *lblZoom = gtk_label_new ("Zoom");
	GtkWidget *lblScenes = gtk_label_new ("Escenas");
	GtkWidget *lblAulas = gtk_label_new ("Aulas");
	GtkWidget *box= gtk_hbox_new(FALSE, 5);
	GtkWidget *controlbox =gtk_vbox_new(FALSE, 5);
	GtkWidget *controlboxTilt = gtk_hbox_new(FALSE, 5);
	GtkWidget *controlboxZoom = gtk_vbox_new(FALSE, 5);
	GtkWidget *controlboxScenes = gtk_vbox_new(FALSE, 5);
	GtkWidget *controlboxReset = gtk_vbox_new(FALSE, 5);
	GtkWidget *combAulas = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combAulas), "SUM");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combAulas), "AU B11");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combAulas), "SUM 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combAulas), aula);
	g_signal_connect (combAulas, "changed", G_CALLBACK (selectAula), NULL);
	GtkWidget *combDevices = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combDevices), "/dev/video0");
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combDevices), "/dev/video1");
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combDevices), "/dev/video2");
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combDevices), "/dev/video3");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combDevices), actdevice);
	g_signal_connect (combDevices, "changed", G_CALLBACK (selectDevice), NULL);
	gtk_box_pack_start (GTK_BOX (controlboxScenes), lblAulas, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxScenes), combAulas, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxScenes), lblScenes, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxScenes), btnPizarra, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxScenes), btnPantalla, TRUE, TRUE, 0);
        gtk_box_pack_start (GTK_BOX (controlboxScenes), btnProfe, TRUE, TRUE, 0);
        gtk_box_pack_start (GTK_BOX (controlboxScenes), btnGeneral, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxZoom), lblZoom, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxZoom), btnzoomp, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxZoom), btnzoomm, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxTilt), btntilrelm, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxTilt), btntilrelp, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlbox), lbl, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlbox), lblDevice, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlbox), combDevices, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlbox), btnpanrelp, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlbox), controlboxTilt, TRUE, TRUE, 0);
        gtk_box_pack_start (GTK_BOX (controlbox), btnpanrelm, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxReset), btnResetEscenas, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (controlboxReset), btn, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box),controlbox, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), controlboxZoom, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), controlboxScenes, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), controlboxReset, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (win), box);
	//gtk_container_add (GTK_CONTAINER (box), btn);
	//gtk_container_add (GTK_CONTAINER (controlbox),controlboxTilt);
	gtk_widget_show_all (win);
	gtk_main();
	//return 0;
}
