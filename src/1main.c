#include "../inc/cub3d.h"

void ft_hook(void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;
    ft_keys_moves(cub);
    ft_draw_map(cub);
    ft_draw_player(cub->mini.canvas, cub->player.y_pix, cub->player.x_pix, 0xffffffff);
	ft_draw_ray(cub);
    //mlx_delete_image(cub->window, cub->window_canvas);
    ft_raycaster(cub);
    //mlx_image_to_window(cub->window, cub->mini.canvas, 0, 0);
    
}

int main(int argc, char **argv)
{
    t_cub3d cub;

    if (argc != 2)
    {
        show_error("Invalid number of arguments\n");
        exit(1);
    }
    if (!validate_scene(argv[1], &cub))
    {
        free_matrix(cub.map.map); // @TODO cub
        exit(1);
    }
    print_scene(&cub);
    printf("scene printed\n");
    cub.window = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
    printf("mlx iniciado\n");
    ft_init_map(&cub);
    printf("mapa inicializado\n");
    ft_init_minimap(&cub);
    printf("minimapa inicializado\n");
    //ft_raycast(&cub);
    mlx_loop_hook(cub.window, &ft_hook, &cub);
    mlx_loop(cub.window);

    mlx_terminate(cub.window);
    
    // Liberar la memoria asignada
    free(cub.map.map);

    return 0;
}
