#include "../inc/cub3d.h"

void ft_init_data(t_game *cub)
{
    ft_printf("Inicializando datos\n");

    // Asignar memoria para el array del mapa
    cub->map.map = malloc(5 * sizeof(char *));
    if (!cub->map.map)
    {
        ft_printf("Falló la asignación de memoria\n");
        exit(1);
    }
    
    // Inicializar el mapa
    cub->map.map[0] = "11111111111";
    cub->map.map[1] = "10000000001";
    cub->map.map[2] = "10000111001";
    cub->map.map[3] = "100N0000001";
    cub->map.map[4] = "11111111111";
    // cub->player = malloc(sizeof(t_player));
    
    cub->player.y = 3.0 * PIX;
    cub->player.x = 3.0 * PIX;

    cub->map.rows = 5;
    cub->map.cols = 11; // Cambié 12 a 11 ya que los strings del mapa tienen longitud 11
    cub->map.w_px = cub->map.cols * PIX;
    cub->map.h_px = cub->map.rows * PIX;
    cub->ins_floor = 0;
    cub->ins_wall = 0;
    print_player_position(cub);
}



void ft_hook(void *param)
{
    t_game *cub;

    cub = (t_game *)param;
    ft_keys_moves(cub);
    ft_draw_map(cub);
    //ft_draw_player(cub->mini, ((cub->player.y * PIX)/4) + 24, ((cub->player.x * PIX)/4) + 24, 0xffffff00);
}

int main(void)
{
    t_game cub;
    
    ft_init_data(&cub);

    cub.mlx = mlx_init(cub.map.w_px, cub.map.h_px, "cub3d", 0);
    if (!cub.mlx)
    {
        ft_printf("Falló la inicialización de MLX\n");
        exit(1);
    }

    ft_init_map2d(&cub);
    ft_init_minimap(&cub);
    mlx_loop_hook(cub.mlx, &ft_hook, &cub);
    mlx_loop(cub.mlx);

    mlx_terminate(cub.mlx);
    
    // Liberar la memoria asignada
    free(cub.map.map);

    return 0;
}