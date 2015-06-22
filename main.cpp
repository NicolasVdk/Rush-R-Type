/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/20 13:53:32 by kperreau          #+#    #+#             */
/*   Updated: 2015/06/21 23:21:38 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Entity.class.hpp"
#include "includes/Env.class.hpp"
#include "includes/Interface.class.hpp"
#include "includes/Player.class.hpp"
#include "includes/Enemy.class.hpp"
#include "includes/Collision.class.hpp"

#include <iostream>
#include <signal.h>

int			main(int argc, char **argv)
{
	Env				env;
	Interface		*interface = new Interface(&env);
	int				pid;

	pid	= std::system("afplay R-Type.mp3&");
	if (argc == 2 && argv[1][0] == '2')
		interface->start(argv[1]);
	else
		interface->start();
	delete interface;
	kill(pid, SIGTERM);
	return (0);
}
