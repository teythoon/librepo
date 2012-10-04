#ifndef LR_TYPES_H
#define LR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef curl_off_t lr_off_t;
typedef struct _lr_Handle *lr_Handle;
typedef struct _lr_Result *lr_Result;

typedef enum {
    LR_CHECK_GPG        = (1<<0),
    LR_CHECK_CHECKSUM   = (1<<1),
} lr_Checks;

typedef enum {
    LR_YUMREPO          = (1<<1),
    LR_SUSEREPO         = (1<<2),   /*!< Not implemented yet */
    LR_DEBREPO          = (1<<3),   /*!< Not implemented yet */
} lr_Repotype;

/* YUM related types */

typedef enum {
/*  LR_YUM_             = (1<<0),  Reserved */
/*  LR_YUM_             = (1<<1),  Reserved */
    LR_YUM_PRI          = (1<<2),
    LR_YUM_FIL          = (1<<3),
    LR_YUM_OTH          = (1<<4),
    LR_YUM_PRI_DB       = (1<<5),
    LR_YUM_FIL_DB       = (1<<6),
    LR_YUM_OTH_DB       = (1<<7),
    LR_YUM_GROUP        = (1<<8),
    LR_YUM_GROUP_GZ     = (1<<9),
    LR_YUM_DELTAINFO    = (1<<10),
    LR_YUM_UPDATEINFO   = (1<<11),

    // Common combinations
    LR_YUM_BASE_XML     = LR_YUM_PRI|LR_YUM_FIL|LR_YUM_OTH,
    LR_YUM_BASE_DB      = LR_YUM_PRI_DB|LR_YUM_FIL_DB|LR_YUM_OTH_DB,
    LR_YUM_BASE_HAWKEY  = LR_YUM_PRI|LR_YUM_FIL|LR_YUM_DELTAINFO,
    LR_YUM_FULL         = LR_YUM_PRI|LR_YUM_FIL|LR_YUM_OTH|
                          LR_YUM_PRI_DB|LR_YUM_FIL_DB|LR_YUM_OTH_DB|
                          LR_YUM_GROUP|LR_YUM_GROUP_GZ|LR_YUM_DELTAINFO|
                          LR_YUM_UPDATEINFO,
} lr_YumRepoFlags;

struct _lr_YumDistroTag {
    char *cpeid;
    char *value;
};
typedef struct _lr_YumDistroTag *lr_YumDistroTag;

struct _lr_YumRepoMdRecord {
    char *location_href;
    char *checksum;
    char *checksum_type;
    char *checksum_open;
    char *checksum_open_type;
    long timestamp;
    long size;
    long size_open;
    int db_version;
};
typedef struct _lr_YumRepoMdRecord *lr_YumRepoMdRecord;

#define LR_NUM_OF_YUM_REPOMD_RECORDS    10  /*!< number of repomd records
                                                 in _lr_YumRepoMd structure */

struct _lr_YumRepoMd {
    char *revision;
    char **repo_tags;
    lr_YumDistroTag *distro_tags;
    char **content_tags;

    int nort; /* number of repo tags */
    int nodt; /* number of distro tags */
    int noct; /* number of content tags */

    lr_YumRepoMdRecord primary;
    lr_YumRepoMdRecord filelists;
    lr_YumRepoMdRecord other;
    lr_YumRepoMdRecord primary_db;
    lr_YumRepoMdRecord filelists_db;
    lr_YumRepoMdRecord other_db;
    lr_YumRepoMdRecord group;
    lr_YumRepoMdRecord group_gz;
    lr_YumRepoMdRecord deltainfo;
    lr_YumRepoMdRecord updateinfo;
};
typedef struct _lr_YumRepoMd *lr_YumRepoMd;

struct _lr_YumRepo {
    char *repomd;
    char *primary;
    char *filelists;
    char *other;
    char *primary_db;
    char *filelists_db;
    char *other_db;
    char *group;
    char *group_gz;
    char *deltainfo;
    char *updateinfo;

    char *url;          /*!< URL from where repo was downloaded */
    char *destdir;      /*!< Local path to the repo */
};
typedef struct _lr_YumRepo *lr_YumRepo;

/* Callbacks */

typedef int (*lr_ProgressCb)(void *clientp,
                              double total_to_download,
                              double now_downloaded);

typedef int (*lr_UpdateCb)(lr_YumRepoMd first, lr_YumRepoMd second);

#ifdef __cplusplus
}
#endif

#endif