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

/*
 * escenasval[i][] corresponde a Pizarra (i=0), Pantalla (i=1), Profesor (i=2),  Vista General (i=3) y Vista Frontal (i=4)
 * escenasval[][j] corresponde a Pan (Absolute) (j=0), Tilt (Absolute) (j=1) y Zoom, Absolute (j=2)
 */

int escenasval[5][3];

char *presets_file = "";

int max_pan = 606918;
int min_pan = -606112;
int max_tilt = 319104;
int min_tilt = -105537;
int max_zoom = 996;
int min_zoom = 0;
int pan_step = 1612;
int tilt_step = 1662;

int current_device = 0; // /dev/video0
char *selected = "/dev/video0";
int zona = 0; // Por defecto zona 0 que es la Pizarra

int panabs = 0;
int tiltabs = 0;
int zoomabs = 0;
