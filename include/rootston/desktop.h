#ifndef _ROOTSTON_DESKTOP_H
#define _ROOTSTON_DESKTOP_H
#include <time.h>
#include <wayland-server.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_wl_shell.h>
#include <wlr/types/wlr_xdg_shell_v6.h>
#include <wlr/types/wlr_gamma_control.h>
#include "rootston/view.h"
#include "rootston/config.h"

struct roots_output {
	struct roots_desktop *desktop;
	struct wlr_output *wlr_output;
	struct wl_listener frame;
	struct wl_listener resolution;
	struct timespec last_frame;
	struct wl_list link;
};

struct roots_desktop {
	struct wl_list outputs;
	struct timespec last_frame;
	struct roots_server *server;
	struct roots_config *config;

	struct wlr_output_layout *layout;

	struct wlr_compositor *compositor;
	struct wlr_wl_shell *wl_shell;
	struct wlr_xdg_shell_v6 *xdg_shell_v6;
	struct wlr_gamma_control_manager *gamma_control_manager;

	struct wl_listener output_add;
	struct wl_listener output_remove;
	struct wl_listener xdg_shell_v6_surface;
};

struct roots_server;

struct roots_desktop *desktop_create(struct roots_server *server,
		struct roots_config *config);
void desktop_destroy(struct roots_desktop *desktop);

void output_add_notify(struct wl_listener *listener, void *data);
void output_remove_notify(struct wl_listener *listener, void *data);

#endif
