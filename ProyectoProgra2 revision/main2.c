#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//===============================================================================
#define alto 1200
#define ancho 720
#define fila 40
#define columna 24

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
void dibujar_mapa(char mapa[fila][columna]);
void leer_archivo(char mapa[fila][columna], FILE *mapa_file);
void dibujar_personajes(char mapa[fila][columna], jugador gato_jugador);
void limpia();
jugador movi(jugador gato_jugador, char mapa[fila][columna]);

//====BITMAPs=====================================================================
BITMAP *buffer;
BITMAP *fondo;
BITMAP *gato;
BITMAP *pared;
BITMAP *arbol;
BITMAP *arbol2;


int main() {
	init();
	
	jugador gato_jugador;
	char mapa[fila][columna];
	
	FILE* mapa_file;
	gato_jugador.x=60;
	gato_jugador.y=500;
	gato_jugador.PS=100;
	
	leer_archivo(mapa,mapa_file);


	while (!key[KEY_ESC]) {
		gato_jugador=movi(gato_jugador, mapa);
	//	allegro_message("Después de llamar a movi");
		cargar_imagen();
		cargar_imagen(gato_jugador);
	
	
	
		dibujar_mapa(mapa);
		dibujar_personajes(mapa, gato_jugador);
		
		blit(buffer,screen,0,0,0,0,alto,ancho);
	    clear_bitmap(buffer);
	    
	    
	}

	limpia();
	deinit();
	return 0;
}
END_OF_MAIN()

//=============MOVIMIENTO_Y_COLISION==============================================================================

jugador movi (jugador gato_jugador, char mapa[fila][columna]){
    if (key[KEY_W]) {
        if (mapa[(gato_jugador.y-30)/30][gato_jugador.x/30] != 'x') 
			gato_jugador.y -=30;	
    }
    if (key[KEY_S]) {
        if (mapa[(gato_jugador.y+30)/30][gato_jugador.x/30] != 'x' ) 
			gato_jugador.y +=30;	
    }
    if (key[KEY_A]){
        if (mapa[gato_jugador.y/30][(gato_jugador.x-30)/30] != 'x' ){
			gato_jugador.x -=30;
			
			gato = load_bitmap("media/gato2.bmp",NULL);
		}			
    }
    if (key[KEY_D]) {
        if (mapa[gato_jugador.y/30][(gato_jugador.x+30)/30] != 'x' ) {
			gato_jugador.x +=30;
		
			gato = load_bitmap("media/gato.bmp",NULL);
		}
    }
	return gato_jugador;
}

//=======ARCHIVOS====================================================================================================

void leer_archivo(char mapa[fila][columna], FILE *mapa_file){
	int i, j,aux;
	
	if ((mapa_file=fopen("mapa1.txt","r"))==NULL){
    	allegro_message("Error al abrir el archivo mapa1.txt");
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
	gato = create_bitmap(30,30);	
	pared = create_bitmap(30,30);
	arbol = create_bitmap(30,30);
	arbol2 = create_bitmap(30,30);	
	//==========================================================================
	fondo = load_bitmap("media/fondo.bmp",NULL);
	gato = load_bitmap("media/gato.bmp",NULL);
	pared = load_bitmap("media/pared.bmp",NULL);
	arbol = load_bitmap("media/arbol.bmp",NULL);
	arbol2 = load_bitmap("media/arbol2.bmp",NULL);

}

void dibujar_mapa(char mapa[fila][columna]){
	int i,j;	
	
	draw_sprite(buffer, fondo, 0, 0);

	for (i = 0; i < columna; i++){
	    for (j = 0; j < fila; j++){
	        if (mapa[i][j] == 'x')
	            draw_sprite(buffer, pared, j * 30, i * 30);
	            /*
	        if (mapa[i][j] == 'a')
	            masked_blit(arbol, buffer, 0, 0, j * 30, i * 30, 30, 30);
	        if (mapa[i][j] == 'A')
	            masked_blit(arbol2, buffer, 0, 0, j * 30, i * 30, 30, 30);
	            */
	    }
	}
}

void dibujar_personajes(char mapa[fila][columna], jugador gato_jugador){
    masked_blit(gato, buffer, 0, 0, gato_jugador.x, gato_jugador.y, 30, 30);
}
void limpia(){
	destroy_bitmap(fondo);
	destroy_bitmap(gato);
	destroy_bitmap(pared);

}

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, alto, ancho, 0, 0);
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


