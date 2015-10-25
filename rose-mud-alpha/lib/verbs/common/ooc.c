/*    /verbs/common/ooc.c
 *    like say, but for local room OOC discussion
 *    created by Umbrella Wizard
 */

#include <lib.h>
#include <talk_type.h>
#include "include/ooc.h"

inherit LIB_VERB;

static void create() {
    ::create();
    SetVerb("ooc");
    SetRules("","to LIV STR","STR");
}

mixed can_ooc_to_liv(object ob) {
    if(GUEST_CHECK == "guest") return "You can't do that.";
    else if( !ob ) return 0;
    else return "What is it you are trying to ooc to "+ ob->GetName() + "?";
}

mixed can_ooc_to_liv_str(object targ, string str) {
    if(GUEST_CHECK == "guest") return "You can't do that.";   
    else return this_player()->CanSpeak(targ, TALK_LOCAL_OOC, str, "common");
}

mixed can_ooc(mixed args...) {
    if(GUEST_CHECK == "guest") return "You can't do that."; 
    else return 1;
}

mixed can_ooc_str(string str) {
    if( !str ) return 0;
    else if(GUEST_CHECK == "guest") return "You can't do that.";    
    return this_player()->CanSpeak(0, TALK_LOCAL_OOC, str, "common");
}

mixed do_ooc(mixed args...){
    write("ooc what?");
    return "ooc whut?";
}

mixed do_ooc_to_liv(object ob) { return 1; }

mixed do_ooc_to_liv_str(object targ, string str) {
    return this_player()->eventSpeak(targ, TALK_LOCAL_OOC, str, "common");
}

mixed do_ooc_str(string str) { return do_ooc_to_liv_str(0, str); }

string GetHelp(string str) {
    return ("Syntax: ooc <MESSAGE>\n\n"
            "Sends out a OOC message that everyone in the room can see. "
            "Use this instead say when you need to speak out of character "
            "while roleplaying.\n"
            "See also: say, shout, speak, reply, tell, whisper");
}
