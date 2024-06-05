# CUB3D

Para la realización de estre proyecto a priori nos encontramos con tres frentes de trabajo inmediato:

1. Vamos a arrancar una ventana usando la librería gráfica MLX42, que debemos tener en nuestra carpeta de proyecto previamente compilada,para empezar a probar el funcionamiento. 
	* Para ello tenemos que tener instalado **GLFW** que es una biblioteca de código abierto para la creación de ventanas y el manejo de eventos y entrada en OpenGL y Vulkan entre otras APIs de gráficos. Para instalar **GLFW** tendremos que ejecutar en nuestro terminal:
	```bash
	sudo apt-get install lbglfw3-dev
	```
	* No podemos olvidar compilar nuestro proyecto con las flags correspondientes:
	```Makefile
	LIBS = $(LIBMLX)/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
	#$(LIBMLX)/libmlx42.a -> path y archivo de MLX42 a enlazar
	#-Iinclude -> opcion del compilador que añade include al camino de búsqueda de los archivos de cabecera. Por 
	#	ejemplo, si tenemos un archivo de cabecera en include/myheader.h, podemos incluirlo en nuestro código
	#	con #include "myheader.h" en lugar de añadir el path.
	#-lglfw -> le dice al compilador que enlace nuestro programa con la biblioteca GLFW
	#-L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -> añade el path al camino de busqueda de las bibliotecas durante el 	enlace
	```
	* Nos hacemos un main que ejecute una ventana para juguetear con ella, mas adelante iremos añadiendo mas código.
	```C
	void ft_hook(void *mlx)
	{
		(void)mlx;
	}

	int main (void)
	{
		mlx_t	*mlx;

		printf("Hello World\n");
		mlx = mlx_init(1024, 768, "Cub3D", 0);
		mlx_loop_hook(mlx, &ft_hook, &mlx);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		return (0);
	}
	/*Este código creará una ventana con nombre "cub3d"*/
	```
	* Vamos a crear un mapa y añadir un pesrsonaje pero para poder mostrarlo en pantalla tendremos que aprender sobre **raycasting** así que vamos a estudiar un poco sobre eso.


## Raycasting

### Resumen

Es una técnica comunmente utilizada en juegos para renderizar gráficos en 3d. Aunque los gráficos resultantes son en realidad una representación en 2d. El raycasting puede crear una ilusión de profundidad y perspectiva, lo que hace que parezca que estas viendo una escena en 3D. Así es paso a paso como funcionaría el raycasting:
1. **Definir el punto de vista**: Posición desde la que está mirando el personaje.
2. **Definir el campo de visión**: Es el area de la escena que puedes ver desde tu punto de vista. Se repesenta como un ángulo (por ejemplo 60º).
3. **Disparar rayos**: Desde tu punto de vista disparas rayos en varias direcciones dentro de tu campo de visión. Normalmente un rayo por cada columna de píxeles en tu pantalla.
4. **Encontrar el primer objeto que cada rayro golpea**: Necesitamos calcular la distancia desde tu punto de vista hasta el punto donde cada rayo golpea un objeto.
5. **Dibujar la columna de píxeles para cada rayo**: Por cada rayo, dibujas una columna de píxeles en la pantalla. La altura de la pantalla de determina por la distancia hasta el objeto que el rayo golpeó, los objetos mas cercanos tendrán las columnas más altas y los más lejanos más bajas. Esto crea la ilusión de profundidad.
6. **Repetir cada fotograma**: Repites todo el proceso para cada fotograma en el juego. Estop crea la ilusión de movimiento a medida que cambia tu punto de vista.

El raycasting es una técnica comúnmente utilizada en los juegos de computadora para renderizar gráficos en 3D. Aunque los gráficos resultantes son en realidad una representación en 2D, el raycasting puede crear una ilusión de profundidad y perspectiva, lo que hace que parezca que estás viendo una escena en 3D.

Aquí está una descripción paso a paso de cómo funciona el raycasting:

1. **Definir el punto de vista**: Primero, necesitas un punto de vista, que es la posición desde la que estás "mirando" en la escena. En un juego, este sería el punto de vista del jugador. Esto se hace estableciendo las coordenadas(x,y).

2. **Definir el campo de visión**: (FOV- Field Of View angle)Luego, necesitas un campo de visión, que es el área de la escena que puedes ver desde tu punto de vista. Esto se representa a menudo como un ángulo (por ejemplo, 60 grados).

3. **Disparar rayos**: Desde tu punto de vista, "disparas" rayos en varias direcciones dentro de tu campo de visión. Por lo general, disparas un rayo para cada columna de píxeles en tu pantalla. Si nuestra pantalla es de 800x600 píxeles debemos lanzar 800 rayos.
4. **Encontrar el primer objeto que cada rayo golpea**: Cada rayo viaja en línea recta hasta que golpea un objeto en la escena. Necesitas calcular la distancia desde tu punto de vista hasta el punto donde cada rayo golpea un objeto.

5. **Dibujar la columna de píxeles para cada rayo**: Para cada rayo, dibujas una columna de píxeles en la pantalla. La altura de la columna de píxeles se determina por la distancia hasta el objeto que el rayo golpeó (las columnas de píxeles para los objetos más cercanos son más altas que las de los objetos más lejanos). Esto crea la ilusión de profundidad.

6. **Repetir para cada fotograma**: Repites todo el proceso para cada fotograma en tu juego o aplicación. Esto crea la ilusión de movimiento a medida que cambia tu punto de vista.

Es importante tener en cuenta que el raycasting es una simplificación de la renderización en 3D. No tiene en cuenta cosas como la iluminación, las sombras o la reflexión de la luz. Sin embargo, es mucho menos intensivo en términos de recursos de computación que la renderización en 3D completa, lo que lo hace ideal para juegos y aplicaciones que necesitan ser rápidos y eficientes.