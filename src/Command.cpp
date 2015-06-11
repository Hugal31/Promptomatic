/*
** Command.cpp for promptomatic in /home/laloge_h/rendu/MyPokemon/editor/lib/promptomatic/src
**
** Made by Hugo Laloge
** Login   <laloge_h@epitech.net>
**
** Started on  Wed Jun 10 10:20:36 2015 Hugo Laloge
** Last update Thu Jun 11 19:34:02 2015 Hugo Laloge
*/

#include	"command.hpp"

promptomatic::Command::Command(cmd_handler_func _func,
			       const std::string &_desc) :
  func(_func),  desc(_desc),
  arg_min(-1), arg_max(-1)
{

}

promptomatic::Command::Command(cmd_handler_func _func,
		      int _arg_min, int _arg_max,
		      const std::string &_desc) :
  func(_func), desc(_desc),
  arg_min(_arg_min), arg_max(_arg_max < 0 ? _arg_min : _arg_max)
{

}

promptomatic::Command::~Command()
{

}

promptomatic::InternCommand::InternCommand(intern_cmd_handler_func _func,
					   const std::string &_desc) :
  func(_func), desc(_desc),
  arg_min(-1), arg_max(-1)
{

}

promptomatic::InternCommand::InternCommand(intern_cmd_handler_func _func,
					   int _arg_min, int _arg_max,
					   const std::string &_desc) :
  func(_func), desc(_desc),
  arg_min(_arg_min), arg_max(_arg_max < 0 ? _arg_min : _arg_max)
{

}

promptomatic::InternCommand::~InternCommand()
{

}
