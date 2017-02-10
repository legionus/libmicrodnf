#include <glib.h>

#include "libmicrodnfP.h"

GQuark dnf_error_quark(void)
{
	static GQuark quark = 0;

	if (!quark)
		quark = g_quark_from_static_string(G_LOG_DOMAIN);

	return quark;
}

gboolean dnf_context(dnf_context_t **ctx, __attribute__((unused)) GError **error)
{
	dnf_context_t *n_ctx = g_malloc0(sizeof(dnf_context_t));

	g_datalist_init(&n_ctx->plugins);

	*ctx = n_ctx;

	return TRUE;
}

gboolean dnf_free(dnf_context_t *ctx)
{
	if (ctx == NULL)
		return TRUE;

	if (ctx->plugins)
		g_datalist_clear(&ctx->plugins);

	g_free(ctx->plugindir);
	g_free(ctx);

	return TRUE;
}

void dnf_set_plugindir(dnf_context_t *ctx, const gchar *plugindir)
{
	if (ctx->plugindir)
		g_free(ctx->plugindir);

	ctx->plugindir = g_strdup(plugindir);
}

const gchar *dnf_get_plugindir(dnf_context_t *ctx)
{
	return ctx->plugindir;
}
