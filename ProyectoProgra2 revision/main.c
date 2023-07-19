//====LIBRERIAS=================================================================
#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

//===============================================================================
#define alto 1200
#define ancho 720
#define fila (alto/30)
#define columna (ancho/30)
#define num_enemigos 5  

//=====ESTRUCTURAS===============================================================
struct personaje{
	int x;
	int y;		
	int PS;
};
typedef struct personaje jugador;  

//====FUNCIONES==================================================================
void init();
void deinit();

void cargar_imagen();
void limpia();
void dibujar_mapa(char mapa[fila][columna]);
void leer_archivo(char mapa[fila][columna], FILE *mapa_file);

//====BITMAPs=====================================================================
BITMAP *buffer;
BITMAP *fondo;
BITMAP *gato;
BITMAP *pared;
BITMAP *arbol;
BITMAP *arbol2;
BITMAP *arboles;
BITMAP *vida;
BITMAP *gato_zombie2;


//===MAIN=========================================================================
int main(){
	init();

	int i,j;
	int dir=0;
	char mapa[fila][columna];
	FILE* mapa_file;
		
	jugador gato_jugador;
	srand(time(NULL));
	
	gato_jugador.x=60;
	gato_jugador.y=500;
	gato_jugador.PS=100;
	
	leer_archivo(mapa,mapa_file);

		cargar_imagen();
		dibujar_mapa(mapa);
				
	while (!key[KEY_ESC]) {	
	

	    blit(buffer,screen,0,0,0,0,alto,ancho);
	    clear_bitmap(buffer);
	  
	    rest(100);
	}
	
	//limpia();
	deinit();
	return 0;
}
END_OF_MAIN()

//=======ARCHIVOS====================================================================================================

void leer_archivo(char mapa[fila][columna], FILE *mapa_file){
	int i, j,aux;
	
	if ((mapa_file=fopen("mapa1.txt","r"))==NULL){
    	printf("Error al abrir archivo");
	    return;
    }
    else {
    	for(i=0;i<fila;i++)
			for(j=0;j<columna;j++){
				fscanf(mapa_file,"%c",&mapa[i][j]);
			}
			fscanf(mapa_file, "%c", &aux);
	}
	fclose(mapa_file);
}

void cargar_imagen(){
	
	buffer=create_bitmap(alto,ancho);
	fondo=create_bitmap(alto, ancho);		
//	gato = create_bitmap(30,30);

	//pared = create_bitmap(30,30);
//	arbol = create_bitmap(30,30);
	//arbol2 = create_bitmap(30,30);
//	vida = create_bitmap(30,90);
//==========================================================================
	fondo = load_bitmap("media/fondo.bmp",NULL);
//	gato = load_bitmap("media/gato.bmp",NULL);
//	gato_zombie2 = load_bitmap("media/gato_zombie2.bmp",NULL);
//	pared = load_bitmap("media/pared.bmp",NULL);
//	arbol = load_bitmap("media/arbol.bmp",NULL);
//	arbol2 = load_bitmap("media/arbol2.bmp",NULL);
//	vida = load_bitmap("media/vida_100.bmp",NULL);
}

void dibujar_mapa(char mapa[fila][columna]){
	int i, j;
	
	draw_sprite(buffer, fondo, 0, 0);
	draw_sprite(fondo, vida, 30, 30);
/*	
	for (i = 0; i < fila; i++){
	    for (j = 0; j < columna; j++){
	        if (mapa[i][j] == 'x')
	            draw_sprite(buffer, pared, j * 30, i * 30);
	        if (mapa[i][j] == 'a')
	            masked_blit(arbol, buffer, 0, 0, j * 60, i * 60, 60, 60);
	        if (mapa[i][j] == 'A')
	            masked_blit(arbol2, buffer, 0, 0, j * 30, i * 30, 30, 30);
	        if (mapa[i][j] == 'B')
	            masked_blit(arboles, buffer, 0, 0, j * 30, i * 30, 30, 30);
	    }
	}*/
}

void limpia(){
	destroy_bitmap(fondo);
	destroy_bitmap(gato);
	destroy_bitmap(gato_zombie2);
	destroy_bitmap(pared);
	destroy_bitmap(vida);
}

//======FUNCIONES DE ALLEGRO=================================================
void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) 
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, alto, 660, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	install_mouse();
}
void deinit() {
	clear_keybuf();
}

