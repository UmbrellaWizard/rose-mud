Remnants of Storied Encounters Quick Setup and Important Information

For Windows: (Pending updated batch file and instructions)

You must install and setup the dead souls mudlib first! ( http://dead-souls.net/ds-inst-faq.html ). After making an admin character, make a copy of the ds folder to c:\dsbackup as a backup to save yourself from headaches later. Once this is done, run "windows-update.bat" and follow the onscreen prompt.

For Linux:

Make sure you are in a terminal. Download and extract the latest Dead Souls mudlib to your directory of choice (http://lpmuds.net/files/deadsouls/ds3.8.6.zip most current as of writing).  Run './linux-install' in the base extracted RoSE directory. Follow all prompts to finish installation and start the server.

New commands:
/cmds/charprofile.c - Syntax: charprofile <charactername> If called without <charactername>, displays your character's profile information if it exists under /profiles. Calling with <charactername> it will display <charactername>'s profile information, if it exists. Profile information is only created for imported characters.

/include/talk_type.h
- Updated header enabling new ooc verb to function

/lib/player.c
- Changed default channels new characters are assigned to. "gossip" became "public".

/lib/talk.c
- Added ooc verb handling to the list of 'talk' verbs

/lib/std/room.c
- Added ooc verb handling to cooperate with talk.c

/news/creationno
- Contains the news message to display when character creation is disabled with ENABLE_CREATION = 0

/profiles - Stores profile infomration for imported characters.

/secure/cfg/read.c
- Added 'ASSIST' permissions on /secure/pending
- Added 'all' permissions on /profile

New races:
/secure/cfg/races/tsuchigumo *
/secure/cfg/races/youkai *
/secure/cfg/races/yukionna *
/secure/cfg/races/guest **

* Placeholders for now, these are simply renamed copies of /secure/cfg/races/human
** Not truly a race. This is used to restrict guest accounts. Guests cannot move, are invisible to other players, cannot be targeted, and can only speak in the public channel.

/secure/daemon/chat.c
- Added "public" to the list of valid public channels. 

/secure/include/news.h
/secure/include/lib.h
/secure/include/dirs.h
-References to new files made.

/secure/lib/connect.c
- Character import from file:
When logging in, connect.c now checks if the account logging in is an admin. If it is, and files exist in the /pending folder, it attempts to read them and plug the data into the correct character generation functions and displays success or failure messages. Once finished, the admin is logged into the world as usual.
- If a race extracted from an app does not exist, or is unplayable, /secure/cfg/races is searched for a matching race template file. If one is found, an attempt will be made to import it automatically.
- Drop in replacement for the default connect.c. All original functionality should be intact and added features can be disabled by changing constants.
- ENABLE_CREATION and ENABLE_IMPORT enable or disable the normal character creation and new character importing functions respectively. DEFAULT_PASS is used to set the default password for imported characters.

/secure/lib/include/connect.h
- Updated header for connect.c

/secure/cmds/players/hist.h
- Added code to enable pub shortcut to function with hist. Aliases make this pointless, but it's left as is for educational purposes.

/secure/pending - This is where connect.c looks at upon login for characters to import. Four sample templates are included here. These should be stored as plaintext, Unix friendly files using the following template:

Name: Name here
Race: Race here
Gender: Gender here
Ability: Character ability here. *
Personality: Personality here. *
Description: Description here. *
History: History here. *
OC: No **

* These are purely used for profile infomration called by the charprofile command.
** Unused currently.

/secure/save/players/g/guest.o
-Edited guest save file included for debugging purposes. Ideally, the guest race should take care of setting the correct parameters upon login.

New verbs:
/verbs/common/pub.c This simply forwards 'pub' to 'public' as a shortcut. Aliases make this pointless, but it's left as is for educational purposes.
/verbs/common/ooc.c This enables an ooc 'channel' for rooms. Works just like say, but should be used to keep ooc discussion seperated from the ic roleplay it pertains to.
