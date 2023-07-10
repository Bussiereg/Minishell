#include "minishell.h"

int max_length(const char* str1, const char* str2) 
{
    size_t len1;
    size_t len2;

	len1 = ft_strlen(str1);
    len2 = ft_strlen(str2);
    if (len1 >= len2)
        return (len1);
    else
        return (len2);
}

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "pwd", max_length("pwd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "env", max_length("env", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "echo", max_length("echo", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "exit", max_length("exit", cmd)) == EXIT_SUCCESS)
	 	return (EXIT_SUCCESS); 
	return(EXIT_FAILURE);
}

int		execute_builtin(char **cmd_split, t_minishell *mini)
{
	if(ft_strncmp(cmd_split[0], "pwd", max_length("pwd", cmd_split[0])) == EXIT_SUCCESS)
		return (pwd_builtin(mini));
	else if(ft_strncmp(cmd_split[0], "env", max_length("env", cmd_split[0])) == EXIT_SUCCESS)
		return (env_builtin(mini));
	else if(!ft_strncmp(cmd_split[0], "cd", max_length("cd", cmd_split[0])))
		return (cd_builtin(cmd_split[1], mini));
	else if(ft_strncmp(cmd_split[0], "export", max_length("export", cmd_split[0])) == EXIT_SUCCESS)
		return (export_builtin(cmd_split, mini));
	else if(!ft_strncmp(cmd_split[0], "unset", max_length("unset", cmd_split[0])))
		return (unset_builtin(cmd_split, mini));
	 else if(ft_strncmp(cmd_split[0], "echo", max_length("echo", cmd_split[0])) == EXIT_SUCCESS)
	 	return (echo_builtin(cmd_split));
	else if(!ft_strncmp(cmd_split[0], "exit", max_length("exit", cmd_split[0])))
		return (exit_builtin(cmd_split, mini));
	return(EXIT_FAILURE);
}

int	exec(char **cmd, char **envp, t_minishell *mini)
{
    char *path;

	if (is_builtin(cmd[0]) == EXIT_SUCCESS)
	{
		if (execute_builtin(cmd, mini) == EXIT_SUCCESS)
			return(EXIT_SUCCESS);
		return(EXIT_FAILURE);
	}
	else
	{
		path = find_executable(cmd, mini);
		if (!path)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
		}
		else if(execve(path, cmd, envp) == -1)
		{   
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": command not found", 2);
			ft_free(path, NULL, NULL, NULL);
		}
	}
	return(EXIT_FAILURE);
}

int	insert_pipe(char **cmd, char **envp, t_minishell *mini, int index)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			return(EXIT_FAILURE);
		close(fd[1]);
		if (exec(cmd, envp, mini) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	else
	{
		if (is_env_function(cmd[0]) && (index == mini->nb_cmd - 1))
		{
			close(fd[1]);
			close(fd[0]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
	}
	return(EXIT_SUCCESS);
<<<<<<< HEAD
=======
}

int	is_env_function(char *cmd)
{
	if(ft_strncmp(cmd, "cd", max_length("cd", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "export", max_length("export", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else if(ft_strncmp(cmd, "unset", max_length("unset", cmd)) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return(EXIT_FAILURE);
>>>>>>> ec6300a1a0f7f5ae9cc0a7e60a85ab4c3f12784c
}

int    executor(t_minishell *mini, char **envp)
{
	int index;
	pid_t pid;

	index = 0;
	if (is_env_function(mini->cmd_table[mini->nb_cmd - 1][0]) == EXIT_SUCCESS)
	{
		if (input_redirection(*mini) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		while (index < mini->pipe)
		{
			insert_pipe(mini->cmd_table[index], envp, mini, index);
			index++;
		}
		if (output_redirection(*mini) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		if (exec(mini->cmd_table[index], envp, mini) == EXIT_SUCCESS)
<<<<<<< HEAD
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
=======
			return(EXIT_SUCCESS);
		else
			return(EXIT_FAILURE);
>>>>>>> ec6300a1a0f7f5ae9cc0a7e60a85ab4c3f12784c
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_redirection(*mini) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
			while (index < mini->pipe)
			{
				insert_pipe(mini->cmd_table[index], envp, mini, index);
				index++;
			}
			if (output_redirection(*mini) == EXIT_FAILURE)
				exit(EXIT_FAILURE);
			if (exec(mini->cmd_table[index], envp, mini) == EXIT_SUCCESS)
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	return(EXIT_SUCCESS);
}