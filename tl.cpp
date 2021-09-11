#include <iostream>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <vector>

struct extensionEntry
{
	std::string extensionName;
	// i don't expect it but there's a chance someone has more than 4 bilion files so eh
	unsigned long long count;
};

char *getExtension(char *name)
{
	// i assume that file names aren't longer than 2^31 characters
	long index = 0;

	long i = 0;
	while (name[i] != 0)
	{
		if (name[i] == '.')
		{
			// possible extension part found
			index = i;
		}
		i++;
	}
	// if no extension found
	if (index == 0)
	{
		return 0;
	}
	// return 0 if the string only consists of a '.'
	if (name[index + 1] == 0)
	{
		return 0;
	}

	// return position of extension
	return name + index + 1;
}

void addExtension(std::vector<extensionEntry> &list, std::string extension)
{
	// check if exists
	for (unsigned long long i = 0; i < list.size(); i++)
	{
		if (list[i].extensionName == extension)
		{
			list[i].count++;
			return;
		}
	}

	list.insert(list.end(), {extension, 1});
}

int main(int argc, char **argv)
{

	// check arguments
	if (argc < 3)
	{
		std::cout << "error, arguments provided are wrong, use the command like this:\ntl {OPTIONS} {PATH}\nwhere OPTIONS are all needed single letter options and PATH is the path"
				<< "\npossible options include: << "
				<< "\n\tn - run normally, shows the types"
				<<" \n\tc - shows count of the types aswell\n";
		return -1;
	}

	bool showCount;

	long iterator = 0;
	while (argv[1][iterator] != 0)
	{
		if (argv[1][iterator] == 'c')
		{
			showCount = true;
		}
		iterator++;
	}



	// create extension table
	std::vector<extensionEntry> extensionList;
	extensionList.clear();

	DIR *directory;
	struct dirent *entry;





	// check if directory can be opened
	if ((directory = opendir(argv[2])) != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
		{
			// print name of files in the directory
			char *x = getExtension(entry->d_name);
			if (x != 0)
			{
				addExtension(extensionList, std::string(x));
			}
		}
		// close the directory
		closedir(directory);

		if (showCount)
		{
			for (unsigned long long i = 0; i < extensionList.size(); i++)
			{
				std::cout << extensionList[i].extensionName << "\n"
						  << extensionList[i].count << "\n\n";
			}
		}
		else
		{
			for (unsigned long long i = 0; i < extensionList.size(); i++)
			{
				std::cout << extensionList[i].extensionName << "\n\n";
			}
		}
	}

	else
	{
		std::cout << "error: directory could not be opened";
		return -2;
	}
}