#include<json-c/json.h>
#include<string.h>

char *presets_file="";

void presets_load() {
	FILE *fp;
	char buffer[1024];
	struct json_object *preset_json;
	struct json_object *escena;
	struct json_object *namezonaaula;
	struct json_object *panabs;
	struct json_object *tiltabs;
	struct json_object *zoomabs;
	size_t n_escenas;

	char *zonaaula;
	int zona=0;

	fp = fopen(presets_file,"r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	preset_json = json_tokener_parse(buffer);

	n_escenas = json_object_array_length(preset_json);
	//printf("Found %lu friends\n",n_escenas);

	for(int i=0;i<n_escenas;i++) {
		escena = json_object_array_get_idx(preset_json, i);
		json_object_object_get_ex(escena, "Name", &namezonaaula);
		zonaaula=json_object_get_string(namezonaaula);

		if (strcmp(zonaaula,"Pizarra verde")==0){
			zona=0;
		}
		else if (strcmp(zonaaula,"Pantalla")==0){
			zona=1;
		}
		else if (strcmp(zonaaula,"Profesor")==0){
			zona=2;
		}else if (strcmp(zonaaula,"General")==0){
			zona=3;
		}
		else if (strcmp(zonaaula,"Frontal")==0){
			zona=4;
		}
		json_object_object_get_ex(escena, "Tilt", &tiltabs);
		escenasval[zona][1]=json_object_get_int(tiltabs);
		json_object_object_get_ex(escena, "Pan", &panabs);
		escenasval[zona][0]=json_object_get_int(panabs);
		json_object_object_get_ex(escena,"Zoom", &zoomabs);
		escenasval[zona][2]=json_object_get_int(zoomabs);
		//printf("zonaula = %s, zona= %d \n", zonaaula, zona);
		//printf("Pan = %d \n", escenasval[zona][0]);
		//printf("Tilt = %d \n", escenasval[zona][1]);
		//printf("Zoom = %d \n", escenasval[zona][2]);
		//printf("%lu. %s\n",i+1,json_object_get_string(name));
	}
}


