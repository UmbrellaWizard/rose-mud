/*    /verbs/common/pub.c
 *    forwards pub to public
 *    created by Umbrella Wizard
 */

#include <lib.h>
#include <daemons.h>

inherit LIB_VERB;

static void create() {
    verb::create();
    SetVerb("pub");
    SetRules("", "STR");
    SetHelp("See: help public.");
}

mixed can_pub()
{
    return CHAT_D->cmdChannel("public", "");
}

mixed can_pub_str() 
{
    if(this_player()->GetGaggedType("public")) return "Try 'help commands' for a list of some commands.";
    return 1;
}

mixed do_pub()
{
    return 1;
}

mixed do_pub_str(string str) 
{ 
    return CHAT_D->cmdChannel("public", str); 
}
