#include <stdio.h>
#include <glib.h>
#include <gmodule.h>

#include "libmicrodnf.h"
#include "libmicrodnf-plugin.h"

G_MODULE_EXPORT gboolean plugin_init(__attribute__((unused)) dnf_repo_t *repo)
{
	g_warning("plugin_init: call!!!");
	return TRUE;
}

G_MODULE_EXPORT void plugin_free(__attribute__((unused)) dnf_repo_t *repo)
{
	g_warning("plugin_free: call!!!");
	return;
}

G_MODULE_EXPORT gboolean plugin_set_uri(__attribute__((unused)) dnf_repo_t *repo, const gchar *uri)
{
	g_warning("plugin_set_uri: call!!! uri=%s", uri);
	return TRUE;
}

G_MODULE_EXPORT gboolean plugin_set_speed_limit(__attribute__((unused)) dnf_repo_t *repo, __attribute__((unused)) const glong limit)
{
	g_warning("plugin_set_speed_limit: call!!!");
	return TRUE;
}
