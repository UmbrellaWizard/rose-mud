//	/cmds/player/report.c
//      For Remnants of Storied Encounters MUD
//	Used to report abusive/problematic players.
//	written by Umbrella Wizard


#include <lib.h>
inherit LIB_BOARD;
inherit LIB_CAP_STRING;
inherit LIB_CLEAN_TIME;

void cmd(string args)
{
    string player_name;
    if(!args || args == "") 
    {
         message("error", "You can't make a report without specifying who to report.", this_player());
         return;
    }
    if(!user_exists(convert_name(args))) 
    {
         message("error", "Namazu bothering you? " + cap_string(args) + " does not exist.", this_player());
         return;
    } 
    message("system", "What did " + cap_string(args) + " do?\n", this_player());
    cmd_post(args);
    return;
}

string GetHelp(){
    return ("Syntax: report [playername]\n\nUse this command to report abusive or "
            "unacceptable behavior by [playername]. You will be asked to provide "
            "details of what happened. If the behavior happened in a public room, "
            "please specify the room and date that the offending incident occured. "
            "An admin wil be notified and will investigate the report as soon as "
            "time allows. ");
}
