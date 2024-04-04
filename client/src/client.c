#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	

	/* ---------------- LOGGING ---------------- 
	HECHO*/

	logger = iniciar_logger();
	
	logger = log_create("tp0.log","MateLavadoTp0",1,LOG_LEVEL_INFO);
	log_info(logger,"Soy un log!");

	
/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	config = config_create("cliente.config");
	valor = config_get_string_value(config, "CLAVE");
	log_info(logger,valor);
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	

	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);


	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}


t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char *linea;
	while (strcmp(linea = readline(">"),"")) {
    	log_info(logger,linea);
	}
	free(linea);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	
	// Leemos y esta vez agregamos las lineas al paquete
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
	t_paquete* paquete;
	paquete = crear_paquete();
	char *linea;
	while (strcmp(linea = readline(">"),"")) {
        agregar_a_paquete(paquete,linea,strlen(linea)+1);
	}
	free(linea);
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
