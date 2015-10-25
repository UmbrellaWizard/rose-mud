//	/secure/cmds/admins/idlereport.c
//      For Remnants of Storied Encounters MUD
//	handles idle checking. 
//	written by Umbrella Wizard

#include <lib.h>
#include <daemons.h>

inherit LIB_GET_IDLE;
//inherit LIB_DAEMON;

static int idlelimit =14;

void cmd(string charname) 
{
    string seen_times, last_seen, today, first_name, last_name;
    string *idle_list_names = ({});
    int pos, idle_days = -1, i;
    object ob;

    today = timestamp();
    seen_times = upper_case(read_file("/log/reports/lastseen"));

    if(!charname) 
    {
        idle_list_names = explode(seen_times, "\n");

        message("help", "Due for a strike:\n", this_player());
        foreach(string idle_list_name in idle_list_names)
        {
	     last_seen = first(last(idle_list_name, 22),10);
             idle_days = get_idle(0, last_seen);
             if(idle_days > idlelimit) 
             {
                pos = 1;
                //Get character name from lastseen log
                charname = truncate(idle_list_name, 20);
                //Display character names that have been idle for over idlelimit.
                message("help", charname + "'s last activity was " + idle_days + " days ago!", this_player());
             }
        }
        if(pos == 0) message("help", "No one!", this_player());
        return;
    }
    i = sscanf(charname, "%s %s", first_name, last_name);
    if(i == 2)
    {
        charname = capitalize(lower_case(first_name)) + " " + capitalize(lower_case(last_name)) ;
    }
    if(ob = find_player(convert_name(charname)))
    {
        if(interactive(ob))
        {
            message("help", charname + " is online right now.", this_player());
            return; 
        }
    }
    else if((pos = strsrch(seen_times, upper_case(charname))) != -1)
    {     
        last_seen = last(first(seen_times, pos + strlen(charname) + 11), 11);
        idle_days = get_idle(pos, last_seen);
    }
    if(idle_days == -1)
    {
        message("help", charname + " has never been seen!", this_player());
        return;
    }
    if(idle_days == 1) message("help", charname + " was last seen: " + idle_days + " day ago", this_player());
    else message("help", charname + " was last seen: " + idle_days + " days ago", this_player());
    return;
}

string GetHelp()
{
    return ("Syntax: idlereport <charactername>\n\n"
            "Returns how many days ago <charactername> was last seen. "
            "If <charactername> is not given, returns a list of "
            "characters idle for more than " + idlelimit + " days.");
}
