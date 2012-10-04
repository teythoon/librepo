#define _XOPEN_SOURCE 600
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>

#include "librepo.h"
#include "util.h"
#include "repomd.h"
#include "yum.h"

int
lr_repoutil_yum_check_repo(const char *path)
{
    int rc;
    lr_Handle h;
    lr_Result result;

    h = lr_handle_init();
    result = lr_result_init();
    if (!h)
        return LRE_UNKNOWN_ERROR;

    if ((rc = lr_setopt(h, LRO_REPOTYPE, LR_YUMREPO)) != LRE_OK)
        return rc;

    if ((rc = lr_setopt(h, LRO_URL, path)) != LRE_OK)
        return rc;

    if ((rc = lr_setopt(h, LRO_CHECKSUM, 1)) != LRE_OK)
        return rc;

    if ((rc = lr_setopt(h, LRO_LOCAL, 1)) != LRE_OK)
        return rc;

    rc = lr_perform(h, result);

    lr_result_free(result);
    lr_handle_free(h);
    return rc;
}

int
lr_repoutil_yum_parse_repomd(const char *path, lr_YumRepoMd repomd)
{
    int fd, rc;
    struct stat st;

    if (stat(path, &st) != 0)
        return LRE_IO;

    if (st.st_mode & S_IFDIR) {
        char *path2 = lr_pathconcat(path, "repodata/repomd.xml", NULL);
        fd = open(path2, O_RDONLY);
        lr_free(path2);
    } else
        fd = open(path, O_RDONLY);

    if (fd < 0)
        return LRE_IO;

    rc = lr_yum_repomd_parse_file(repomd, fd);
    close(fd);
    return rc;
}
