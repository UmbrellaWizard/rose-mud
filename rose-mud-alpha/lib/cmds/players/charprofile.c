//	/cmds/player/charprofile.c
//      For Remnants of Storied Encounters MUD
//	command to view MUD specific character profile information.
//	written by Umbrella Wizard

#include <dirs.h>

void cmd(string args)
{
    string *foo = ({}), *sort = allocate(7);
    string profile = "";
    if(!args) 
    {
        foo = explode(base_name(this_player()), "/");
        profile = DIR_PROFILES + "/" + foo[4][0..0] + "/" + foo[4];
        if(!(file_exists(profile)))
        {
            message("error", "You have no profile information!\n", this_player());
            return;
        }
    }
    else
    {
        profile = DIR_PROFILES + "/" + convert_name(args)[0..0] + "/" + convert_name(args);
        if(!(file_exists(profile)))
        {
            message("error", "No profile found for " + args + "\n", this_player());
            return;
        }
        if(read_file(profile) == "") message("error", "Error reading " + args + "'s profile\n", this_player());
    }
    foo = explode(read_file(profile), "\n");
    foreach(string elem in foo)
    {
	if(strsrch(elem, "Name: ") != -1) sort[0] = elem;
	if(strsrch(elem, "Race: ") != -1) sort[1] = elem;
	if(strsrch(elem, "Gender: ") != -1) sort[2] = elem;
	if(strsrch(elem, "Ability: ") != -1) sort[3] = elem;
	if(strsrch(elem, "Personality: ") != -1) sort[4] = elem;
	if(strsrch(elem, "Description: ") != -1) sort[5] = elem;
	if(strsrch(elem, "History: ") != -1) sort[6] = elem;
    }
    profile = "";
    foreach(string elem in sort) profile += (elem + "\n");
    message("help", profile, this_player());
    return;
}

string GetHelp(){
    return ("Syntax: charprofile <charactername>\n\nThis command displays profile"
            " information for <charactername> if found. If <charactername> is not"
            " given, any profile information for the player calling this command"
            " will be displayed.");
}
