#include <glib.h>
#include <gmodule.h>

#include "libmicrodnfP.h"

static void module_free(gpointer data)
{
	g_module_close(data);
}

gboolean module_is_loaded(dnf_context_t *ctx, const gchar *name)
{
	return g_datalist_get_data(&ctx->plugins, name) != NULL;
}

gboolean load_module(dnf_context_t *ctx, const gchar *name, GError **error)
{
	GModule *module;
	g_autofree gchar *filename = NULL;

	module = g_datalist_get_data(&ctx->plugins, name);
	if (module) {
		g_set_error(error, DNF_ERROR, DNF_ERROR_PLUGIN_ALREADY_LOADED, "module already loaded: %s", name);
		return FALSE;
	}

	filename = g_module_build_path(ctx->plugindir, name);

	module = g_module_open(filename, G_MODULE_BIND_LAZY);
	if (!module) {
		g_set_error(error, DNF_ERROR, DNF_ERROR_PLUGIN_NOT_FOUND, "%s", g_module_error());
		return FALSE;
	}

	g_datalist_set_data_full(&ctx->plugins, name, module, &module_free);

	return TRUE;
}

gboolean unload_module(dnf_context_t *ctx, const gchar *name)
{
	if (!module_is_loaded(ctx, name))
		return TRUE;

	g_datalist_remove_data(&ctx->plugins, name);

	return TRUE;
}

gboolean get_module_function(dnf_context_t *ctx, const gchar *pluginname, const gchar *funcname, gpointer **func, GError **error)
{
	GModule *module = g_datalist_get_data(&ctx->plugins, pluginname);

	if (!g_module_symbol(module, funcname, (gpointer *)func)) {
		g_set_error(error, DNF_ERROR, DNF_ERROR_PLUGIN_METHOD_MISSING, "%s", g_module_error());
		return FALSE;
	}
	return TRUE;
}
