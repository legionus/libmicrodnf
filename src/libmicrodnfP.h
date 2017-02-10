#ifndef LIBMICRODNF_INIT_P_H
#define LIBMICRODNF_INIT_P_H

#include <glib.h>

#include <libmicrodnf.h>
#include <libmicrodnf-plugin.h>

struct _dnf_context {
	gchar *plugindir;
	GData *plugins;
};

struct _dnf_plugin {
	gpointer *data;
};

struct _dnf_repo {
	dnf_context_t *ctx;
	gchar *name;

	PluginInitFunc              plugin_init;
	PluginFreeFunc              plugin_free;
	PluginRepoSetURIFunc        plugin_set_uri;
	PluginRepoSetSpeedLimitFunc plugin_set_speed_limit;

	dnf_plugin_t *plugin;
};

gboolean module_is_loaded(dnf_context_t *ctx, const gchar *name);
gboolean load_module(dnf_context_t *ctx, const gchar *name, GError **error);
gboolean unload_module(dnf_context_t *ctx, const gchar *name);
gboolean get_module_function(dnf_context_t *ctx, const gchar *pluginname, const gchar *funcname, gpointer **func, GError **error);

#endif /* LIBMICRODNF_INIT_P_H */
