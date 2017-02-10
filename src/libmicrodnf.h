#ifndef LIBMICRODNF_H
#define LIBMICRODNF_H

enum librepo_error {
	DNF_ERROR_SUCCESS               = 0,
	DNF_ERROR_ERRNO                 = -1,
	DNF_ERROR_PLUGIN_NOT_FOUND      = -2,
	DNF_ERROR_PLUGIN_NOT_LOADED     = -3,
	DNF_ERROR_PLUGIN_ALREADY_LOADED = -4,
	DNF_ERROR_PLUGIN_UNLOAD         = -5,
	DNF_ERROR_PLUGIN_METHOD_MISSING = -6,
	DNF_ERROR_PLUGIN_INITIALIZATION = -7,
};

#define DNF_ERROR (dnf_error_quark())
GQuark dnf_error_quark(void);

typedef struct _dnf_context dnf_context_t;
typedef struct _dnf_repo    dnf_repo_t;

gboolean dnf_context(dnf_context_t **ctx, GError **error);
gboolean dnf_free(dnf_context_t *ctx);

const gchar *dnf_get_plugindir(dnf_context_t *ctx);
void dnf_set_plugindir(dnf_context_t *ctx, const gchar *plugindir);

gboolean dnf_repo_set_uri(dnf_repo_t *repo, const gchar *uri);
// const gchar *dnf_repo_get_uri(dnf_repo_t *repo);

gboolean dnf_repo_set_speed_limit(dnf_repo_t *repo, const glong limit);
// const glong *dnf_repo_get_speed_limit(dnf_repo_t *repo);

gboolean dnf_context_repo(dnf_context_t *ctx, const gchar *type, dnf_repo_t **repo, GError **error);
gboolean dnf_repo_free(dnf_repo_t *repo);

#endif /* LIBMICRODNF_H */
