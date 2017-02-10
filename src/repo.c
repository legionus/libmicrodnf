#include <glib.h>

#include "libmicrodnfP.h"
#include "libmicrodnf-plugin.h"

gboolean dnf_context_repo(dnf_context_t *ctx, const gchar *name, dnf_repo_t **repo, GError **error)
{
	// TODO: lock context ?
	if (!module_is_loaded(ctx, name) &&
	    !load_module(ctx, name, error))
		return FALSE;

	dnf_repo_t *n_repo = g_malloc0(sizeof(dnf_repo_t));
	n_repo->ctx  = ctx;
	n_repo->name = g_strdup(name);

	if (!get_module_function(ctx, name, PluginInitFuncName, (gpointer **)&n_repo->plugin_init, error) ||
	    !get_module_function(ctx, name, PluginFreeFuncName, (gpointer **)&n_repo->plugin_free, error) ||
	    !get_module_function(ctx, name, PluginRepoSetURIFuncName, (gpointer **)&n_repo->plugin_set_uri, error) ||
	    !get_module_function(ctx, name, PluginRepoSetSpeedLimitFuncName, (gpointer **)&n_repo->plugin_set_speed_limit, error))
		goto err;

	n_repo->plugin = g_malloc0(sizeof(dnf_plugin_t));

	if (!n_repo->plugin_init(n_repo))
		goto err;

	*repo = n_repo;

	return TRUE;
err:
	unload_module(ctx, name);
	return FALSE;
}

gboolean dnf_repo_free(dnf_repo_t *repo)
{
	if (repo == NULL)
		return TRUE;

	if (repo->plugin_free != NULL)
		repo->plugin_free(repo);

	unload_module(repo->ctx, repo->name);

	g_free(repo->name);

	return TRUE;
}

gboolean dnf_repo_set_uri(dnf_repo_t *repo, const gchar *uri)
{
	return repo->plugin_set_uri(repo, uri);
}

gboolean dnf_repo_set_speed_limit(dnf_repo_t *repo, const glong limit)
{
	return repo->plugin_set_speed_limit(repo, limit);
}
