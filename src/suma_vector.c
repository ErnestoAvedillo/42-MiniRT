/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suma_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheel-n <jcheel-n@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:21:33 by eavedill          #+#    #+#             */
/*   Updated: 2023/12/05 12:44:27 by jcheel-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vec3	suma_vector(t_vec3 a, t_vec3 b)
{
	t_vec3	out;

	out.x = a.x + b.x;
	out.y = a.y + b.y;
	out.z = a.z + b.z;
	return (out);
}
