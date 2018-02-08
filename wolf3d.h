#ifndef WOLF3D_H
# define WOLF3D_H
# include <SDL2/SDL.h>
# include <stdbool.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 1024
# define mapWidth 24
# define mapHeight 24

typedef struct s_player
{
  double pos_x;
  double pos_y;
  double dir_x;
  double dir_y;
  double plane_x;
  double plane_y;
}              t_player;

typedef struct s_ray
{
  double camera_x;
  double dir_x;
  double dir_y;
  int map_x;
  int map_y;
  double side_dist_x;
  double side_dist_y;
  double delta_dist_x;
  double delta_dist_y;
  bool is_x_side;
  int step_x;
  int step_y;
}              t_ray;

void init_player(t_player *player);
double dist_to_wall(t_ray ray, t_player player);
void draw_line(int line_height);
void get_player_pos(t_player player);
bool put_error(char *str);
bool done(bool quit_if_esc, bool delay);

#endif
