#include <lib.h>
#include <dirs.h>
#include ROOMS_H

inherit LIB_ROOM;

string GuestRoom();

static void create() {
    room::create();
    SetClimate("indoors");
    SetAmbientLight(30);
    SetShort("RoSE Guest Room");
    SetLong( (:GuestRoom:) );
    SetObviousExits("no exit");
    SetNoModify(1);
}

void init(){
    ::init();
}

string GuestRoom(){
    return read_file("/domains/default/etc/guestroom.txt");
}



