#include "../inc/cub3d.h"

void ft_hook(void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;
    ft_keys_moves(cub);
    ft_draw_map(cub);
    ft_draw_player(cub->mini.canvas, cub->player.y_pix, cub->player.x_pix, 0xffffffff);
	ft_draw_ray(cub);
    ft_paint_floor_and_ceiling(cub);
    ft_raycaster(cub);    
}

void uint32_to_rgb(uint32_t color, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *b = (color >> 16) & 0xFF; // Shift right 16 bits and mask out anything not in the lowest 8 bits
    *g = (color >> 8) & 0xFF;  // Shift right 8 bits and mask out anything not in the lowest 8 bits
    *r = color & 0xFF;         // Mask out anything not in the lowest 8 bits
}

// void test_texture_pick_color(void)
// {
//     mlx_texture_t *test;
//     int x;
//     int y;
//     uint8_t r, g, b;
//     uint32_t color;

//     test = malloc(sizeof(mlx_texture_t));
//     test = mlx_load_png("textures/W.png");
//     x = 0; y = 0;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgb(color, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
//     x = 32; y = 32;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgb(color, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
//     x = 15; y = 9;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgb(color, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
// }

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
    mlx_loop_hook(cub.window, &ft_hook, &cub);
    mlx_loop(cub.window);
    mlx_terminate(cub.window);
    // Liberar la memoria asignada
    free(cub.map.map);
    return 0;
}
