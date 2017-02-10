#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "libmicrodnf.h"

int main(void)
{
	const gchar *plugindir = getenv("LIBMICRODNF_PLUGINDIR");
    int rc = EXIT_SUCCESS;

	GError *error = NULL;

	dnf_context_t *ctx = NULL;

	if (plugindir == NULL) {
		printf("ERR: LIBMICRODNF_PLUGINDIR env required\n");
		return EXIT_FAILURE;
	}

	if (dnf_context(&ctx, &error) == FALSE) {
		fprintf(stderr, "ERR: %s\n", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	dnf_set_plugindir(ctx, plugindir);

	dnf_repo_t *repo = NULL;

	if (dnf_context_repo(ctx, "repo-aptrpm", &repo, &error) == FALSE) {
		fprintf(stderr, "ERR: %s\n", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	gchar *uri = "FOO";
	dnf_repo_set_uri(repo, uri);

	dnf_repo_free(repo);
	dnf_free(ctx);

    return rc;
}
