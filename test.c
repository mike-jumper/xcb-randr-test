
#include <stdio.h>

#include <xcb/xcb.h>
#include <xcb/randr.h>

int main() {

    const char display_name[] = ":0";

    /* Connect to X server */
    xcb_connection_t* connection = xcb_connect(display_name, NULL);

    /* Bail on failure */
    if (xcb_connection_has_error(connection)) {
        fprintf(stderr, "Connection failed.\n");
        xcb_disconnect(connection);
        return 1;
    }

    /* Get screen */
    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_t* screen = xcb_setup_roots_iterator(setup).data;

    /* Create dummy window */
    xcb_window_t dummy_id = xcb_generate_id(connection);
    xcb_create_window(connection, 0, dummy_id, screen->root, 0, 0, 1, 1, 0,
            XCB_WINDOW_CLASS_COPY_FROM_PARENT, XCB_COPY_FROM_PARENT, 0, NULL);

    /* Flush pending requests */
    xcb_flush(connection);

    /* Disconnect */
    xcb_disconnect(connection);
    fprintf(stderr, "Success.\n");
    return 0;

}

