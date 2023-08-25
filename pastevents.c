#include "headers.h"

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x > y ? y : x)

commandList history[15];
int historyCount = 0;
commandList pasteveexec;
void savePastEventsToFile(commandList *cmdarr, int commandCount)
{
	char path[PATH_MAX];
	mystrcpy(path, home);
	if (path[length(path) - 1] != '/')
		strcat(path, "/");
	strcat(path, "history");
	FILE *file = fopen(path, "wb");
	if (file == NULL)
	{
		fprintf(stderr, "\x1b[31mHistory unavailable\n\x1b[0m");
		return;
	}
	fwrite(&commandCount, sizeof(int), 1, file);
	for (int i = 0; i < commandCount; i++)
	{
		commandList *cmdList = &cmdarr[i];
		fwrite(cmdList, sizeof(commandList), 1, file);
	}
	fclose(file);
}
void readPastEventsFromFile(commandList *cmdarr, int *commandCount)
{
	char path[PATH_MAX];
	mystrcpy(path, home);
	if (path[length(path) - 1] != '/')
		strcat(path, "/");
	strcat(path, "history");
	FILE *file = fopen(path, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "\x1b[31mHistory unavailable\n\x1b[0m");
		return;
	}
	fread(commandCount, sizeof(int), 1, file);
	for (int i = 0; i < *commandCount; i++)
	{
		commandList *cmdList = &cmdarr[i];
		fread(cmdList, sizeof(commandList), 1, file);
	}
	fclose(file);
}
void saveToHistory(commandList new)
{
	if (new.count == 0)
		return;

	bool is_equal = true;
	if (history[0].count == new.count)
	{
		for (int i = 0; i < new.count; ++i)
		{
			if (!is_equal)
				break;
			if (history[0].arr[i].argc == new.arr[i].argc)
			{
				for (int j = 0; j < new.arr[i].argc; ++j)
				{
					if (strcmp(new.arr[i].argv[j], history[0].arr[i].argv[j]) != 0)
					{
						is_equal = false;
						break;
					}
				}
			}
			else
			{
				is_equal = false;
				break;
			}
		}
	}
	else
	{
		is_equal = false;
	}

	if (historyCount != 0 && is_equal)
	{
		return;
	}
	for (int i = 13; i >= 0; --i)
	{
		history[i + 1] = history[i];
	}
	historyCount = MIN(15, historyCount + 1);
	history[0] = new;
	savePastEventsToFile(history, historyCount);
}
void printCommand(command cmd, int last)
{
	for (int i = 0; i < cmd.argc; i++)
	{
		printf("%s ", cmd.argv[i]);
	}
	if (cmd.foreground && !last)
		printf("; ");
	if (!cmd.foreground)
		printf("& ");
}
void printCommandList(commandList cmdL)
{
	for (int i = 0; i < cmdL.count; i++)
	{
		printCommand(cmdL.arr[i], (i == cmdL.count - 1)); // second parameter true only for last element
	}
	printf("\n");
}
void pastevents(command cmd)
{
	if (cmd.argc == 1)
	{
		for (int i = historyCount - 1; i >= 0; i--)
		{
			printCommandList(history[i]);
		}
	}
	if (cmd.argc == 2)
		if ((equal(cmd.argv[1], "purge")))
		{
			{
				FILE *file = fopen("history", "w");
				historyCount = 0;
				savePastEventsToFile(history, historyCount);
			}
		}
		else
		{
			fprintf(stderr, "\x1b[31mpastevents: Invalid arguments\n\x1b[0m");
			return;
		}
	if (cmd.argc == 3)
		if (equal(cmd.argv[1], "execute"))
		{
			int n = myatoi(cmd.argv[2]) - 1;
			if (n == -1 || n >= historyCount)
			{
				fprintf(stderr, "\x1b[31mpastevents: %s is not a valid argument for pastevents execute\n\x1b[0m", cmd.argv[2]);
				return;
			}
			else
			{
				pasteveexec = history[n];
				executeCommand(pasteveexec);
			}
		}
		else
		{
			fprintf(stderr, "\x1b[31mpastevents: Invalid arguments\n\x1b[0m");
			return;
		}
}