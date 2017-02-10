#include <glib.h>

#include "libmicrodnfP.h"

gboolean dnf_set_plugin_data(dnf_plugin_t *plugin, gpointer *data)
{
	plugin->data = data;
	return TRUE;
}

gpointer dnf_get_plugin_data(dnf_plugin_t *plugin)
{
	return plugin->data;
}
