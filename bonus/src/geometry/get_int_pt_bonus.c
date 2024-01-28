/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_pt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eavedill <eavedill@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:17:30 by jcheel-n          #+#    #+#             */
/*   Updated: 2024/01/27 16:08:55 by eavedill         ###   ########.fr       */
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
			//out->bumpmap = geom->bumpmap; //no se necesita. está ya en la geometria
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

static t_int_pts	*get_colored_loop(t_vec_pos *vps, t_field *field,
						t_int_pts *vp_int, t_geom *ptr)
{
	t_vec_pos	*out;
	int			i;

	out = get_int_pt(vps, ptr);
	i = -1;
	while (++i < 2)
	{
		if (out && !is_bhd_cam(out[i].pt, vps->pt, field->camera.center.vx))
		{
			vp_int = get_min_vect(vp_int, out, ptr, vps);
			vp_int->pt.v = prod_cte_vector(ptr->sense, vp_int->pt.v);
			vp_int->ref.vz = vp_int->pt.v;
			vp_int->ref.vx = conv_v_unit(prod_vectorial(create_vect(0, 0, 1), \
						vp_int->ref.vz));
			vp_int->ref.vy = conv_v_unit(prod_vectorial(vp_int->ref.vz, \
						vp_int->ref.vx));
		}
		if (ptr->type == PLANE)
			i++;
	}
	if (vp_int->geom && vp_int->geom->bumpmap.is_bumpmap)
		set_pixel_color_bumpmap(vp_int, field);
	free(out);
	return (vp_int);
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
		vp_int = get_colored_loop(vps, field, vp_int, ptr);
		ptr = ptr->next;
	}
	// if (vp_int->geom && vp_int->geom->bumpmap.is_bumpmap)
	// 	set_pixel_color_bumpmap(vp_int, field, vp_int->geom);
	if (vp_int->geom && field->chckbd.is_chckbd && vp_int->geom->is_chckbd == true)
		vp_int->pt.c = set_pixel_color_chckdb(*vp_int, field);
	// else if (vp_int->geom && vp_int->bumpmap.is_bumpmap)
	// 	vp_int->pt.c = set_pixel_color_bumpmap(*vp_int, field, vp_int->geom);
	if (field->chckbd.is_light)
		vp_int->pt.c = set_pixel_color(*vp_int, field, *vps);
}
