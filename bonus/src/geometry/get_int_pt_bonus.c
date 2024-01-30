/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_pt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:17:30 by jcheel-n          #+#    #+#             */
/*   Updated: 2024/01/30 11:10:05 by eavedill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt_bonus.h"

static bool	is_bhd_cam(t_vec3 pint, t_vec3 pi, t_vec3 vx)
{
	t_vec3	temp;
	double	aux;

	temp = conv_v_unit(resta_vector(pint, pi));
	aux = prod_escalar(vx, temp);
	if (aux > 0)
		return (false);
	return (true);
}

static t_int_pts	*get_min_vect(t_int_pts *cur, t_vec_pos *new,
						t_geom *geom, t_vec_pos *pixl)
{
	t_int_pts	*out;
	double		long_cur;
	int			i;

	out = cur;
	if (!new)
		return (out);
	long_cur = modulo_vector(resta_vector(cur->pt.pt, pixl->pt));
	i = -1;
	while (++i < 2)
	{
		if (modulo_vector(resta_vector(new[i].pt, pixl->pt)) < long_cur)
		{
			out->pt = new[i];
			out->pt.c = geom->color;
			out->geom = geom;
		}
	}
	return (out);
}

t_vec_pos	*get_int_pt(t_vec_pos *vps, t_geom *geo)
{
	t_vec_pos	*out;

	if (geo->type == SPHERE)
		out = int_vect_esfera(*vps, geo);
	else if (geo->type == CYLINDER)
		out = int_vect_cilind(*vps, geo);
	else if (geo->type == PLANE)
		out = int_vect_plano(*vps, geo->vp);
	else if (geo->type == CONUS)
		out = int_vect_cono(*vps, geo);
	else if (geo->type == TRIANGLE)
		out = int_vect_triang(*vps, geo);
	else
		out = NULL;
	return (out);
}

static void	create_ref(t_vec_pos *vps, t_int_pts *vp_int, t_vec_pos *out, \
			t_geom *ptr)
{
	double	ax;

	vp_int = get_min_vect(vp_int, out, ptr, vps);
	vp_int->ref.vz = vp_int->pt.v;
	ax = round(prod_escalar(vp_int->pt.v, create_vect(0, 0, 1)) * 1E5) / 1E5;
	if (ax == 1 || ax == -1)
	{
		if (vp_int->ref.vz.z == 0)
		{
			vp_int->ref.vz = create_vect(0, 0, 1);
			vp_int->ref.vy = create_vect(0, 1, 0);
		}
		if (vp_int->ref.vz.z > 0)
			vp_int->ref.vy = create_vect(0, 1, 0);
		else
			vp_int->ref.vy = create_vect(0, -1, 0);
		vp_int->ref.vx = create_vect(1, 0, 0);
	}
	else
	{
		vp_int->ref.vx = conv_v_unit(prod_vectorial(\
							create_vect(0, 0, 1), vp_int->ref.vz));
		vp_int->ref.vy = conv_v_unit(\
							prod_vectorial(vp_int->ref.vz, vp_int->ref.vx));
	}
}
/*
to print in case of error.
//	vp_int->pt.v = prod_cte_vector(ptr->sense, vp_int->pt.v);
//	ft_print_vec3("Valor de vp.pt", vp_int->pt.pt);
//	ft_print_vec3("Valor de vp.v", vp_int->pt.v);
//	printf("valores de aux %f -- %f\n", ax[1], ax[0]);ax[0] == 0 ||
//		ft_print_vec3("Valor de vp.vz ", vp_int->ref.vz);
//		ft_print_vec3("Valor de vp.vx ", vp_int->ref.vx);
//		ft_print_vec3("Valor de vp.vy ", vp_int->ref.vy);
*/

static void get_colored_loop(t_vec_pos *vps, t_field *field, \
								t_int_pts *vp_int, t_geom *ptr)
{
	t_vec_pos	*out;
	int			i;

	out = get_int_pt(vps, ptr);
	i = -1;
	while (out && ++i < 2)
	{
		if (!is_bhd_cam(out[i].pt, vps->pt, field->camera.center.vx))
			create_ref(vps, vp_int, out, ptr);
		if (ptr->type == PLANE)
			i++;
	}
	if (vp_int->geom && vp_int->geom->bumpmap.is_bumpmap)
		set_pixel_color_bumpmap(vp_int, field);
	free(out);
}

/// @brief Gives the color of the closest surface to the pixel.
/// @param pixel
/// @param field
void	get_colored_int_pt(int pixel, t_field *field)
{
	t_geom		*ptr;
	t_int_pts	*vp_int;
	t_vec_pos	*vps;

	ptr = field->geom;
	vps = &field->camera.field_vp[pixel];
	vp_int = &field->camera.int_vp[pixel];
	vp_int->pt = init_vp(vps->c);
	vp_int->geom = NULL;
	while (ptr)
	{
		get_colored_loop(vps, field, vp_int, ptr);
		ptr = ptr->next;
	}
	if (vp_int->geom && field->chckbd.is_chckbd && vp_int->geom->is_chckbd == true)
		vp_int->pt.c = set_pixel_color_chckdb(*vp_int, field);
	if (field->chckbd.is_light)
		vp_int->pt.c = set_pixel_color(*vp_int, field, *vps);
}
