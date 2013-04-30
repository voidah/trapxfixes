#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <X11/cursorfont.h>

#define TMPFILE "/tmp/cursor_hidden"

typedef void (*my_XFixesHideCursor)(Display *, Window);
typedef void (*my_XFixesShowCursor)(Display *, Window);

void XFixesHideCursor(Display *dpy, Window win)
{
    my_XFixesHideCursor original = (my_XFixesHideCursor)dlsym (RTLD_NEXT, "XFixesHideCursor");

    FILE* f = fopen(TMPFILE, "w");
    fclose(f);

    //std::cout << "Cursor is hidden" << std::endl;

    original(dpy, win);
}

void XFixesShowCursor(Display *dpy, Window win)
{
    my_XFixesShowCursor original = (my_XFixesShowCursor)dlsym (RTLD_NEXT, "XFixesShowCursor");

    //std::cout << "Cursor is visible" << std::endl;

    unlink(TMPFILE);
    original(dpy, win);
}

