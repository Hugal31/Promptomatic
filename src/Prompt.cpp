/*
** init.cpp for promptomatic in /home/laloge_h/projets/Perso/C++/MyPokemon/editor/lib/my_prompt/src
**
** Made by Hugo Laloge
** Login   <laloge_h@epitech.net>
**
** Started on  Tue Jun  9 16:12:38 2015 Hugo Laloge
** Last update Thu Jun 11 19:34:58 2015 Hugo Laloge
*/

#include	<iostream>
#include	<string>
#include	<utility>
#include	"promptomatic.hpp"

promptomatic::Prompt::Prompt(const std::string &prompt_str) :
  _prompt_str(prompt_str), _continue(true)
{
  map_intern_command("exit", prompt_exit, 0, 1, "exit the prompt");
  map_intern_command("help", prompt_help, 0, 0, "display help");
  map_intern_command("clear", prompt_clear, 0, 0, "clear the screen");
}

promptomatic::Prompt::~Prompt()
{

}

promptomatic::command_map	&promptomatic::Prompt::get_command_map()
{
  return (_command_map);
}

promptomatic::intern_command_map	&promptomatic::Prompt::get_intern_command_map()
{
  return (_intern_command_map);
}

void	promptomatic::Prompt::set_prompt(const std::string &prompt_str)
{
  _prompt_str = prompt_str;
}

void	promptomatic::Prompt::map_intern_command(const std::string &key,
						 intern_cmd_handler_func func,
						 const std::string &helptext)
{
  _intern_command_map.insert(std::pair<std::string,
			     promptomatic::InternCommand>(key, promptomatic::InternCommand(func, helptext)));
}

void	promptomatic::Prompt::map_intern_command(const std::string &key,
						 intern_cmd_handler_func func,
						 int arg_min, int arg_max,
						 const std::string &helptext)
{
  _intern_command_map.insert(std::pair<std::string,
			     promptomatic::InternCommand>(key, promptomatic::InternCommand(func, arg_min, arg_max, helptext)));
}

void	promptomatic::Prompt::map_command(const std::string &key,
					  cmd_handler_func func,
					  const std::string &helptext)
{
  _command_map.insert(std::pair<std::string, promptomatic::Command>(key, promptomatic::Command(func, helptext)));
}

void	promptomatic::Prompt::map_command(const std::string &key,
					  cmd_handler_func func,
					  int arg_min, int arg_max,
					  const std::string &helptext)
{
  _command_map.insert(std::pair<std::string,
			     promptomatic::Command>(key, promptomatic::Command(func, arg_min, arg_max, helptext)));
}

void	promptomatic::Prompt::unmap_command(const std::string &key)
{
  _command_map.erase(key);
  _intern_command_map.erase(key);
}

namespace
{
  int	exec_cmd(const promptomatic::Command &cmd,
		 const promptomatic::Arguments &args)
  {
    int	ret(1);

    if (cmd.arg_min >= 0
	and args.argc() <= static_cast<size_t>(cmd.arg_min))
      std::cerr << "No enough arguments" << std::endl;
    else if (cmd.arg_max >= 0
	     and args.argc() - 1 > static_cast<size_t>(cmd.arg_max))
      std::cerr << "Too many arguments" << std::endl;
    else
      ret = cmd.func(args);
    return (ret);
  }

  int	exec_intern_cmd(const promptomatic::InternCommand &cmd,
			const promptomatic::Arguments &args,
			promptomatic::Prompt &prompt)
  {
    int	ret(1);

    if (cmd.arg_min >= 0
	and args.argc() <= static_cast<size_t>(cmd.arg_min))
      std::cerr << "No enough arguments" << std::endl;
    else if (cmd.arg_max >= 0
	     and args.argc() -1 > static_cast<size_t>(cmd.arg_max))
      {
	std::cerr << "arg_max : " << cmd.arg_max << std::endl;
	std::cerr << "Too many arguments" << std::endl;
      }
    else
      ret = cmd.func(args, prompt);
    return (ret);
  }
}

void	promptomatic::Prompt::input_loop()
{
  std::string		line;
  command_map::iterator	cmd;
  intern_command_map::iterator	intern_cmd;

  std::cout << _prompt_str;
  while (_continue && std::getline(std::cin, line))
    {
      promptomatic::Arguments	args(line);
      if (args.argc() >= 1)
	{
	  if ((cmd = _command_map.find(args[0])) != _command_map.end())
	    exec_cmd(cmd->second, args);
	  else if ((intern_cmd = _intern_command_map.find(args[0])) != _intern_command_map.end())
	    exec_intern_cmd(intern_cmd->second, args, *this);
	  else
	    std::cerr << "Unknowned command" << std::endl;
	}
      std::cout << _prompt_str;
    }
  std::cout << "exit" << std::endl;
}

void	promptomatic::Prompt::stop_loop()
{
  _continue = false;
}
