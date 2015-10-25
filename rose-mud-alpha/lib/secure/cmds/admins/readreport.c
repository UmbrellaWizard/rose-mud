//	/secure/cmds/admins/readreport.c
//      For Remnants of Storied Encounters MUD
//	Displays reports made with the report command.
//	written by Umbrella Wizard

#include <lib.h>
#include <daemons.h>

inherit LIB_GET_IDLE;
inherit LIB_CLEAN_TIME;

static private string report_list = "/log/reports/reportlist";

void cmd(string all) 
{
    int pos;
    string *unread_lines = ({}), *read_lines = ({});
    string read = "", output = "", unread = "", tag = "<" + convert_name(this_player()->GetKeyName()) + ">\n";
    string file = read_file(report_list);
    if(!file_exists(report_list) || (file_exists(report_list) && read_file(report_list) == ""))
    {
        message("help", "\n%^BOLD%^%^GREEN%^No troublemakers to report!%^RESET%^\n", this_player());
        return;
    }
    if((pos = strsrch(file, tag)) != -1)
    {
        read = first(file, pos);
        unread = last(file, strlen(file) - strlen(tag) - pos);
        file = read + unread;
        if(unread != "")
        {
             output += "\n";
             unread_lines = explode(unread, "\n");
             foreach(string unread_line in unread_lines)
             {
                  if(regexp(unread_line, "<*>") != 1) output += unread_line + "\n";
             }
        }
        if(all != "-all") message("help", "\n%^YELLOW%^Player Reports:%^RESET%^" + output, this_player());
    }
    else 
    {
         read_lines = explode(file, "\n");
         output += "\n";
         foreach(string read_line in read_lines)
         {
              if(regexp(read_line, "<*>") != 1) output += read_line + "\n";
         }
         output = truncate(output, 1);
         message("help", "\n%^YELLOW%^Player Reports:%^RESET%^" + file = output, this_player());
    }    
    if(output == "" && file != "" && all != "-all")
    {
        message("help", "%^BOLD%^%^GREEN%^No one has misbehaved since you last checked.%^RESET%^\n", this_player());
        return;
    }
    if(all == "-all") message("help", "\n%^YELLOW%^Player Reports:%^RESET%^" + file, this_player());
    else
    {
        write_file(report_list, file + tag, 1);
    }

    return;
}

string GetHelp()
{
    return ("Syntax: readreport -all\n\n"
            "Returns the list of player reported troublemakers. "
             "If -all is specified, returns reports from the beginning "
             "of the log. Otherwise it only shows what's been added since "
             "you last called the command. ");
}
