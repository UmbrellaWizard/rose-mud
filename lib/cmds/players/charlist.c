//	/cmds/player/charlist.c
//      For Remnants of Storied Encounters MUD
//	displays the character list.
//	written by Umbrella Wizard

#include <dirs.h>

inherit LIB_GET_IDLE;

static string charlist = DIR_SAVE + "/charlist.o";
static string pendlist = DIR_SAVE + "/pending.o";

void cmd()
{
    string *charnames = ({}), *pendingchars = ({});
    string seen_times, online, last_seen, name = "";
    object ob;
    int windows = 1, pc98header = 0, ocheader = 0, pos = 0, this_year, idle;

    if(!file_exists(charlist))
    {
        message("error", "A hungry hungry ghost must be on the loose, because the information you're looking for has vanished!\n"
                + "(" + charlist + " is missing or corrupt. Please contact an admin.)\n", this_player()); 
        return;
    }

    charnames = explode(read_file(charlist), "\n");
    seen_times = read_file("/log/reports/lastseen");

    if(file_exists(pendlist))
    {
        pendingchars = explode(read_file(pendlist), "\n");
    }

    message("help", "%^BOLD%^%^BLUE%^" + sprintf("%-25s%-13s%-10s", "Name", "Status", "Connection") + "%^RESET%^", this_player());
    foreach(string charname in charnames)
    {
        pos = strsrch(seen_times, charname);
        idle = -1;
        online = "";
        name = convert_name(charname);

        if(pos != -1)
	{    
            last_seen = last(first(seen_times, pos + strlen(charname) + 11), 11);
            idle = get_idle(pos, last_seen);
	}  
        if(name == "pc98") 
        {
            ocheader = -1;
            windows = 0; 
        }     
        else if(name == "oc") 
        {
            ocheader = 0;
            pc98header = -1;
        }
        if(member_array(charname, pendingchars) != -1)
        {
            message("help", "%^YELLOW%^" + sprintf("%-25s%-13s%-30s", charname, "Pending", " " + online) + "%^RESET%^", this_player());
        }
        else if(windows == 1)
        {
            if(user_exists(name))
            {
                if(idle == 1) online = "Last Activity " + idle + " day ago";
                else if (idle != -1) online = "Last Activity " + idle + " days ago";
                if(ob = find_player(name))
                {
                     if(interactive(ob)) online = "Online";
                }
                message("help", "%^BOLD%^%^GREEN%^" + sprintf("%-25s%-13s%-30s", charname, "Approved", " " + online) + "%^RESET%^", this_player());
            }
            else message("help", sprintf("%-25s%-13s%-30s", charname, "Open", " " + online), this_player());
        } 
        else 
        {
            if(user_exists(name))
            {
	        if(ocheader == 0) 
                {
                   ocheader = 1;
                   message("help", "%^BOLD%^%^BLUE%^\nOriginal Characters%^RESET%^", this_player());
                }
                if(pc98header == 0) 
                {
                   pc98header = 1;
                   message("help", "%^BOLD%^%^BLUE%^\nPC-98%^RESET%^", this_player());
                }
		else
		{
                    if(idle == 1) online = "Last Activity " + idle + " day ago";
                    else if (idle != -1) online = "Last Activity " + idle + " days ago";
                    if(ob = find_player(name))
                    {
                         if(interactive(ob)) online = "Online";
                    }
                }
                if(ob = find_player(name))
                {
                   if(interactive(ob)) online = "Online";
                }
                else if(idle == 1) online = "Last Activity " + idle + " day ago";
                else if(idle != -1) online = "Last Activity " + idle + " days ago";     
                message("help", "%^BOLD%^%^GREEN%^" + sprintf("%-25s%-13s%-30s", charname, "Approved", " " + online) + "%^RESET%^", this_player());
            }
        } 
    }
    return;
}

string GetHelp(){
    return ("Syntax: charlist\n\nThis command displays the character list.");
}
