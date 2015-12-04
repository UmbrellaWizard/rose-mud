#include <lib.h>
#include <daemons.h>
#include <commands.h>
#include <message_class.h>

inherit LIB_DAEMON;
inherit LIB_GET_IDLE;
inherit LIB_CLEAN_TIME;
inherit LIB_VALID_DATE;

string gfile;
static private mapping forwarded_chans = (["pub" : "public"]);
static private string *chanvalues = ({}); 
static private int count;

varargs string *Prettify(string *arr, string chan){
    string *ret = ({});
    string colorchan = "", remotechan, tagcolor;
    chan = CHAT_D->GetLocalChannel(chan);
    remotechan = CHAT_D->GetRemoteChannel(chan);

    if(!chan || !(tagcolor = CHAT_D->GetTag(chan))){
        if(!(colorchan = CHAT_D->GetTag(remotechan))){
            colorchan = "%^B_BLACK%^YELLOW%^<"+chan+">%^RESET%^";
        }
    }   
    else colorchan += tagcolor + "<" + capitalize(chan) + ">%^RESET%^";
    foreach(string line in arr){
        line = replace_string(line, "<"+ chan +">", colorchan, 1);
        //mess = replace_string(line, "<"+ remotechan +">", colorchan, 1);
        ret += ({ line });
    }
    return ret;
}

mixed cmd(string args) {
    string *talks, *ret = ({});
    int i, lines;
    string second_arg = "", third_arg = "";
    string log_contents, location, start_date, end_date;
    gfile = "";

    if(!args){ 
        this_player()->eventPrint("Syntax: <hist [channel | say]>");
        return 1;
    }

    this_player()->eventPrint("Retrieving history...\n");

    if(!strsrch(args, "tell")){
        load_object(CMD_TELL)->cmd("hist");
        return 1;
    }

    if(!LOG_REMOTE_CHANS && 
            member_array(args, CHAT_D->GetRemoteChannels(1)) != -1){
        ret = CHAT_D->cmdLast(args);
        if(sizeof(ret)) return ret;
    }

    if(!LOG_LOCAL_CHANS && 
            member_array(args, CHAT_D->GetRemoteChannels()) == -1){
        ret = CHAT_D->cmdLast(args);
        if(sizeof(ret)) return ret;
    }
    
    i = sscanf(args,"%s %s %s", gfile, second_arg, third_arg);
    if(i == 1)
    {
        sscanf(args,"%s %s", gfile, second_arg);
        if(strsrch(second_arg, "/") == -1) 
        {    
             lines = to_int(second_arg); 
             i = 2;
	     if(lines == 0) return "Invalid input. Second argument must either be a positive integer value, or a date following the YYYY/MM/DD format.";
        }
        else
        {
             start_date = second_arg;
             end_date=first(clean_time(this_player()->GetProperty("timezone")), 10);
             i = 3;
        }
        
    }
    else if(second_arg != "" && third_arg != "")
    {
        start_date = second_arg;
        end_date = third_arg;
    }
    else
    {
        lines = 20;
        gfile = args;
    }

    //Fix to enable hist on channel forwarder verbs.
    chanvalues = values(forwarded_chans);
    count = 0;
    foreach(mixed foo in keys(forwarded_chans))
    {
        count++;
        if(gfile == foo)
        {
            gfile = chanvalues[count-1];
        }
    }
    talks = this_player()->GetTalkHistTypes();
    if(talks && member_array(gfile, talks) != -1){
        string room = "/log/room" + base_name(environment(this_player()));
        string ret2 = "Your "+gfile+" history: \n\n";
        int year = 0, month = 0, day = 0;

        if(gfile == "ooc" || gfile == "say")
        {
             room = "/log/room" + base_name(environment(this_player()));
             if(!file_exists(room + "/" + gfile )) return "Backlog for " + gfile + " is empty!";
             else room = room + "/" + gfile;
        }
	else ret2 += implode(this_player()->GetTalkHistory(gfile),"\n");
        if(i > 2)
        {
            i = sscanf(start_date, "%d/%d/%d", year, month, day);
            if(year == 0 || month == 0 || day == 0) return "Invalid input. Second argument must either be an integer value, or a date following the YYYY/MM/DD format.";
            if(valid_date(year, month, day) == 1)
            {
                year = month = day = 0;
                if(get_idle(0, start_date) < 0) return "Looking for a time paradox? (Check your dates)";
                else
                {   
                    i = sscanf(end_date, "%d/%d/%d", year, month, day);
                    if(year == 0 || month == 0|| day == 0) return "Invalid input. Third argument is not a date following the YYYY/MM/DD format.";
                    if(valid_date(year, month, day) == 1)
                    {
                        if(get_idle(0, end_date) < 0 || get_idle(0, end_date) > get_idle(0, start_date)) return "Looking for a time paradox? (Check your dates)";
                        else
                        {
                            string *loglines = explode(read_file(room), "\"\n");
                            lines = sizeof(loglines);
                            foreach(string logline in loglines)
                            {
                                if(get_idle(0, start_date) >= get_idle(0, first(logline,10)) && get_idle(0, end_date) <= get_idle(0, first(logline,10))) ret2+= logline + "\n";
                            }
                        }
                    }
		    else return end_date + " is not a valid date!";
                }
            }
            else return start_date + " is not a valid date, nevermind what you put after it!";
        }
        else ret2+= read_file(room);
        print_long_string(this_player(), ret2); 
        return 1;
    }
    if(!CHAT_D->CanListen(this_player(), gfile)){
        return "You do not have privileges to: "+gfile;
    }
    if(!CHAT_D->GetListening(this_player(), gfile)){
        return "You are not listening to channel: "+gfile;
    }
    if(gfile == "admin"){
        location = "/secure/log/admin";
    }
    else {
        location = DIR_CHANNEL_LOGS +"/"+ gfile;
    }
    if( !(log_contents = read_file(location)) ){
        return CHAT_D->cmdLast(gfile);
    }
    if(lines > 100 && !creatorp(this_player())) lines = 100;
    if(sizeof(ret = (Prettify(explode(log_contents,"\n"), gfile))) < lines){
        string *archive_array;
        archive_array = (get_dir(DIR_CHANNEL_LOGS +"/archive/") || ({}) );
        archive_array = filter(archive_array, (: !strsrch($1,gfile) :) );
        archive_array = sort_array(archive_array, -1);
        foreach(string element in archive_array){
            string junk1, tmp;
            if(sizeof(ret) >= lines) break;
            if(sscanf(element,"%s%*d.%*d.%*d-%*d.%*d", junk1) != 6) continue;
            if(truncate(junk1,1) != gfile) continue;
            tmp = read_file(DIR_CHANNEL_LOGS +"/archive/"+element);
            if(!tmp) continue;
            ret = Prettify(explode(tmp,"\n"), gfile)+ret;
        }
    }
    ret = ret[<lines..];
    this_player()->eventPage(ret, "system");
    return 1;
}

string GetHelp(){
    string ret = "Syntax: hist <CHANNEL> [number] | [start date] [end date]\n"
        "        hist [ say | whisper | tell | yell | shout ]\n\n"
        "Gives you the backscroll of the specified communication. "
        "[number] only works with global channels and specifies the number of "
        "backscroll lines to display. Default is 20. For local channels, only the "
        "backscroll between [start date] and [end date], if specified, will be "
        "displayed. If not specified, [end date] is the current date. Dates must "
        "be given in YYYY/MM/DD format.\n";
    if(!LOG_REMOTE_CHANS){
        ret += "Note that remote channel logging is not enabled on "
            "this mud, so hist for intermud channels will not work.";
    }
    return ret;
}
