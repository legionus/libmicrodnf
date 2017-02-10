#ifndef LIBMICRODNF_PLUGIN_H
#define LIBMICRODNF_PLUGIN_H

#include <glib.h>
#include <libmicrodnf.h>

typedef gboolean (* PluginInitFunc) (dnf_repo_t *repo);
#define PluginInitFuncName "plugin_init"

typedef void (* PluginFreeFunc) (dnf_repo_t *repo);
#define PluginFreeFuncName "plugin_free"

// Repository functions
typedef gboolean (* PluginRepoSetURIFunc) (dnf_repo_t *repo, const gchar *uri);
#define PluginRepoSetURIFuncName "plugin_set_uri"

typedef gboolean (* PluginRepoSetSpeedLimitFunc) (dnf_repo_t *repo, const glong limit);
#define PluginRepoSetSpeedLimitFuncName "plugin_set_speed_limit"

typedef struct _dnf_plugin dnf_plugin_t;

gboolean dnf_set_plugin_data(dnf_plugin_t *plugin, gpointer *data);
gpointer dnf_get_plugin_data(dnf_plugin_t *plugin);

#endif /* LIBMICRODNF_PLUGIN_H */
