#include "../includes/wolf3d.h"

void	define_sprites_1(t_env *env)
{
	int i;

	i = 12;
	env->spr[0] = define_sprite(2, 4, 0);
	env->spr[1] = define_sprite(2, 5, 0);
	env->spr[2] = define_sprite(2, 6, 0);
	env->spr[3] = define_sprite(5, 6, 1);
	env->spr[4] = define_sprite(5, 4, 1);
	env->spr[5] = define_sprite(5, 5, TWO_P);
	env->spr[6] = define_sprite(9.5, 2, TEN_P);
	env->spr[7] = define_sprite(9.5, 7.5, TEN_P);
	env->spr[8] = define_sprite(13.5, 2, TEN_P);
	env->spr[9] = define_sprite(13.5, 7.5, TEN_P);
	env->spr[10] = define_sprite(18, 4, 1);
	env->spr[11] = define_sprite(18, 6, 1);
	env->spr[12] = define_sprite(18, 5, 4);
	while (++i < SPRITES)
		env->spr[i] = define_sprite(0, 0, 0);
}

void	define_sprites_2(t_env *env)
{
	env->spr[0] = define_sprite(1.5, 8.5, 1);
	env->spr[1] = define_sprite(1.5, 1.5, 1);
	env->spr[2] = define_sprite(1.5, 13.5, 1);
	env->spr[3] = define_sprite(1.5, 22.5, 1);
	env->spr[4] = define_sprite(1.5, 30.5, 1);
	env->spr[5] = define_sprite(1.5, 55.5, 1);
	env->spr[6] = define_sprite(9.5, 31.5, 1);
	env->spr[7] = define_sprite(9.5, 47.5, 1);
	env->spr[8] = define_sprite(17.5, 9.5, 1);
	env->spr[9] = define_sprite(17.5, 14.5, 1);
	env->spr[10] = define_sprite(17.5, 23.5, 1);
	env->spr[11] = define_sprite(17.5, 47.5, 1);
	env->spr[12] = define_sprite(10.5, 46.5, 1);
	env->spr[13] = define_sprite(16.5, 10.5, 1);
	env->spr[14] = define_sprite(16.5, 13.5, 1);
	env->spr[15] = define_sprite(16.5, 24.5, 1);
	env->spr[16] = define_sprite(16.5, 46.5, 1);
	env->spr[17] = define_sprite(24.5, 1.5, 1);
	env->spr[18] = define_sprite(24.5, 55.5, 1);
	env->spr[19] = define_sprite(25.5, 14.5, 1);
	env->spr[20] = define_sprite(25.5, 23.5, 1);
	env->spr[21] = define_sprite(25.5, 31.5, 1);
	env->spr[22] = define_sprite(25.5, 40.5, 1);
	env->spr[23] = define_sprite(26.5, 1.5, 1);
	define_sprites_2_1(env);
}

void	define_sprites_2_1(t_env *env)
{
	env->spr[24] = define_sprite(26.5, 13.5, 1);
	env->spr[25] = define_sprite(26.5, 24.5, 1);
	env->spr[26] = define_sprite(26.5, 30.5, 1);
	env->spr[27] = define_sprite(40.5, 1.5, 1);
	env->spr[28] = define_sprite(40.5, 13.5, 1);
	env->spr[29] = define_sprite(40.5, 15.5, 1);
	env->spr[30] = define_sprite(40.5, 22.5, 1);
	env->spr[31] = define_sprite(40.5, 24.5, 1);
	env->spr[32] = define_sprite(40.5, 30.5, 1);
	env->spr[33] = define_sprite(40.5, 32.5, 1);
	env->spr[34] = define_sprite(40.5, 55.5, 1);
	env->spr[35] = define_sprite(34.5, 55.5, 1);
	env->spr[36] = define_sprite(3.5, 8.5, 0);
	env->spr[37] = define_sprite(7.5, 3.5, 0);
	env->spr[38] = define_sprite(21.5, 13.5, 0);
	env->spr[39] = define_sprite(10.5, 11.5, 0);
	env->spr[40] = define_sprite(25.5, 3.5, 0);
	env->spr[41] = define_sprite(28.5, 11.5, 0);
	env->spr[42] = define_sprite(33.5, 14.5, 0);
	env->spr[43] = define_sprite(9.5, 25.5, 0);
	env->spr[44] = define_sprite(10.5, 35, 0);
	env->spr[45] = define_sprite(35, 6, 0);
	env->spr[46] = define_sprite(40, 28, 0);
	env->spr[47] = define_sprite(29, 45, 0);
	define_sprites_2_2(env);
}

void	define_sprites_2_2(t_env *env)
{
	env->spr[48] = define_sprite(7, 42, 0);
	env->spr[49] = define_sprite(13, 55, 0);
	env->spr[50] = define_sprite(27.5, 55.5, TEN_P);
	env->spr[51] = define_sprite(28.5, 55.5, TEN_P);
	env->spr[52] = define_sprite(29.5, 55.5, TEN_P);
	env->spr[53] = define_sprite(30.5, 55.5, TEN_P);
	env->spr[54] = define_sprite(31.5, 55.5, TWO_P);
	env->spr[55] = define_sprite(5.5, 5.5, TWO_P);
	env->spr[56] = define_sprite(15.5, 10.5, TWO_P);
	env->spr[57] = define_sprite(15.5, 25.5, TWO_P);
	env->spr[58] = define_sprite(3.5, 35.5, TWO_P);
	env->spr[59] = define_sprite(25.5, 39.5, TWO_P);
	env->spr[60] = define_sprite(38.5, 2.5, TWO_P);
	env->spr[61] = define_sprite(40.5, 17.5, TWO_P);
	env->spr[62] = define_sprite(31.5, 21.5, TWO_P);
	env->spr[63] = define_sprite(29.5, 55.5, TWO_P);
	env->spr[64] = define_sprite(31.5, 50.5, TWO_P);
	env->spr[65] = define_sprite(37.5, 55.5, 4);
}