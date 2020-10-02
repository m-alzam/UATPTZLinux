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

#include <json-c/json.h>
#include <string.h>

void load_presets() {
    FILE *fp;
    char buffer[1024];
    struct json_object *preset_json, *escena, *namezonaaula, *absolute_pan, *absolute_tilt, *absolute_zoom;
    size_t n_escenas;

    const char *zonaaula;
    int zone = 0;

    fp = fopen(presets_file, "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    preset_json = json_tokener_parse(buffer);

    n_escenas = json_object_array_length(preset_json);

    for (int i = 0; i < n_escenas; i++) {
        escena = json_object_array_get_idx(preset_json, i);
        json_object_object_get_ex(escena, "Name", &namezonaaula);
        zonaaula = json_object_get_string(namezonaaula);

        if (strcmp(zonaaula, "Pizarra verde") == 0) {
            zone = 0;
        } else if (strcmp(zonaaula, "Pantalla") == 0) {
            zone = 1;
        } else if (strcmp(zonaaula, "Profesor") == 0) {
            zone = 2;
        } else if (strcmp(zonaaula, "General") == 0) {
            zone = 3;
        } else if (strcmp(zonaaula, "Frontal") == 0) {
            zone = 4;
        }

        json_object_object_get_ex(escena, "Tilt", &absolute_tilt);
        escenasval[zone][1] = json_object_get_int(absolute_tilt);
        json_object_object_get_ex(escena, "Pan", &absolute_pan);
        escenasval[zone][0] = json_object_get_int(absolute_pan);
        json_object_object_get_ex(escena, "Zoom", &absolute_zoom);
        escenasval[zone][2] = json_object_get_int(absolute_zoom);
    }
}


