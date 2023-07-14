//====LIBRERIAS=================================================================
#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

//===============================================================================
#define fila ancho/30
#define columna alto/30
#define alto 1200
#define ancho 720
#define num_enemigos 6

//=====ESTRUCTURAS===============================================================
struct personaje{
	int x;
	int y;		
	int PS;
};
typedef struct personaje jugador;  

struct enemigo{
	int id;
	int x;
	int y;		
	int PS;
	int direccion;
};
typedef struct enemigo zombie;  


//====FUNCIONES==================================================================
void init();
void deinit();
jugador movi(jugador gato_jugador, char mapa[fila][columna]);
zombie movi_zombie_simp(zombie gato_zombie, char mapa[fila][columna]);
void cargar_imagen(jugador gato_jugador);
void limpia();
void dibujar_mapa(char mapa[fila][columna]);
void dibujar_personajes(char mapa[fila][columna], jugador gato_jugador, zombie gato_zombie[]);
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
	zombie gato_zombie[num_enemigos];
	srand(time(NULL));
	
	gato_jugador.x=60;
	gato_jugador.y=500;
	gato_jugador.PS=100;

	for (i = 0; i < num_enemigos; i++){
	    gato_zombie[i].id = i; 
	    gato_zombie[i].x = 600-i*30;
	    gato_zombie[i].y = 60+i*30;
	    gato_zombie[i].PS = 100;
	    if(i < num_enemigos-2)
	    	gato_zombie[i].direccion = 1;
	    else
	    	gato_zombie[i].direccion = 3;
	}
	leer_archivo(mapa,mapa_file);
	cargar_imagen(gato_jugador);
	dibujar_mapa(mapa);

	while (!key[KEY_ESC]) {	
		gato_jugador=movi(gato_jugador, mapa);
		for ( i = 0; i < num_enemigos; i++){
        	gato_zombie[i] = movi_zombie_simp(gato_zombie[i], mapa);
    	}		
    	dibujar_mapa(mapa);
		textprintf_ex(screen, font,100,200, makecol(255, 255, 255), -1, "PS = %d", gato_jugador.PS);
		for (i = 0; i < num_enemigos; i++){
			if (mapa[gato_jugador.y / 30][(gato_jugador.x / 30)+1] == mapa[gato_zombie[i].y / 30][gato_zombie[i].x / 30]){
				gato_jugador.PS -= 20;
				dibujar_personajes(mapa,gato_jugador, gato_zombie);
			}
		}
		
	    blit(buffer,screen,0,0,0,0,alto,ancho);
	    clear_bitmap(buffer);
	  
	    rest(100);
	}
	
	limpia();
	deinit();
	return 0;
}
END_OF_MAIN()

//====FUNCIONES=====================================================================

//=============MOVIMIENTO_Y_COLISION==============================================================================

jugador movi (jugador gato_jugador, char mapa[fila][columna])
{
	
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

zombie movi_zombie_simp(zombie gato_zombie, char mapa[fila][columna]){
	int dir = gato_zombie.direccion;
	int id = gato_zombie.id;
	
	if (dir == 1){		
		if (mapa[gato_zombie.y / 30][(gato_zombie.x + 30) / 30] == ' ')
			gato_zombie.x += 30;
		else{
			if(id<2)
				dir = 0;
			else
				dir = rand() % num_enemigos;
		}
	}
	else if (dir == 0){
		if (mapa[gato_zombie.y / 30][(gato_zombie.x - 30) / 30] == ' ')
			gato_zombie.x -= 30;
		else{
			if(id<2) 
				dir = 1;
			else
				dir = rand() % num_enemigos;
		}

	}
	else if (dir == 3){
		if (mapa[(gato_zombie.y-30) / 30][gato_zombie.x/ 30] == ' ')
			gato_zombie.y -= 30;
		else{
			if(id<2)
				dir = 2;
			else
				dir = rand() % num_enemigos;
		}
	}
	else if (dir == 2){
		if (mapa[(gato_zombie.y+30) / 30][gato_zombie.x/ 30] == ' ')
			gato_zombie.y += 30;
		else{
			if(id<2)
				dir = 3;
			else
				dir = rand() % num_enemigos;
		}
	}
	gato_zombie.direccion = dir;
	return gato_zombie;
}
//=======ARCHIVOS====================================================================================================

void leer_archivo(char mapa[fila][columna], FILE *mapa_file){
	int i, j,aux;
	if ((mapa_file=fopen("mapa1.txt","r"))==NULL){
    	printf("Error al abrir archivo");
	    return;
    }
    else {
    	for(i=0;i<fila;i++){
			for(j=0;j<columna;j++){
				fscanf(mapa_file,"%c",&mapa[i][j]);
			}
			fscanf(mapa_file, "%c", &aux);
		}
	}
	fclose(mapa_file);
}

void cargar_imagen(jugador gato_jugador){
	buffer=create_bitmap(alto,ancho);
	fondo=create_bitmap(alto, ancho);		
	gato = create_bitmap(30,30);
	gato_zombie2 = create_bitmap(30,30);
	pared = create_bitmap(30,30);
	arbol = create_bitmap(30,30);
	arbol2 = create_bitmap(30,30);
	arboles = create_bitmap(30,90);
	vida = create_bitmap(30,90);
	fondo = load_bitmap("media/fondo.bmp",NULL);
	gato = load_bitmap("media/gato.bmp",NULL);
	gato_zombie2 = load_bitmap("media/gato_zombie2.bmp",NULL);
	pared = load_bitmap("media/pared.bmp",NULL);
	arbol = load_bitmap("media/arbol.bmp",NULL);
	arbol2 = load_bitmap("media/arbol2.bmp",NULL);
	arboles = load_bitmap("media/arboleda.bmp",NULL);
	if(gato_jugador.PS==100)
		vida = load_bitmap("media/vida_100.bmp",NULL);
}

void dibujar_mapa(char mapa[fila][columna]){
	int i, j;
	draw_sprite(buffer, fondo, 0, 0);
	draw_sprite(fondo, vida, 30, 30);
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
	}
}

void dibujar_personajes(char mapa[fila][columna], jugador gato_jugador, zombie gato_zombie[]){
	int i, j;
	
	masked_blit(gato, buffer, 0, 0, gato_jugador.x, gato_jugador.y, 30, 30);
	for (i = 0; i < fila; i++){
	    for (j = 0; j < columna; j++){
	        if(mapa[i][j]== 'z')
	        	masked_blit(gato_zombie2, buffer, 0, 0, j*30, i*30, 30, 30);
	    }
	}
}


void limpia(){
	destroy_bitmap(fondo);
	destroy_bitmap(gato);
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

