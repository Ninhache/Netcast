#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mimetype.h"
#include "utils.h"

static struct mimetype_t {
    char *extension;
    char *mime;
} mimetypes[] = {
    // Default MIME type
    // Text MIME types
    { "css",   "text/css" },
    { "csv",   "text/csv" },
    { "htc",   "text/x-component" },
    { "htm",   "text/html" },
    { "html",  "text/html" },
    { "shtm",  "text/html" },
    { "shtml", "text/html" },
    { "stm",   "text/html" },
    { "txt",   "text/plain" },
    { "vcf",   "text/vcard" },
    { "vcard", "text/vcard" },

    // Image MIME types
    { "gif",   "image/gif" },
    { "ico",   "image/x-icon" },
    { "jpg",   "image/jpeg" },
    { "jpeg",  "image/jpeg" },
    { "png",   "image/png" },
    { "svg",   "image/svg+xml" },
    { "tif",   "image/tiff" },

    // Audio MIME types
    { "aac",   "audio/x-aac" },
    { "aif",   "audio/x-aiff" },
    { "mp3",   "audio/mpeg" },
    { "wav",   "audio/x-wav" },
    { "wma",   "audio/x-ms-wma" },

    // Video MIME types
    { "avi",   "video/x-msvideo" },
    { "flv",   "video/x-flv" },
    { "mov",   "video/quicktime" },
    { "mp4",   "video/mp4" },
    { "mpg",   "video/mpeg" },
    { "mpeg",  "video/mpeg" },
    { "wmv",   "video/x-ms-wmv" },

    // Application MIME types
    { "doc",   "application/msword" },
    { "gz",    "application/x-gzip" },
    { "gzip",  "application/x-gzip" },
    { "js",    "application/javascript" },
    { "json",  "application/json" },
    { "ogg",   "application/ogg" },
    { "pdf",   "application/pdf" },
    { "ppt",   "application/vnd.ms-powerpoint" },
    { "rar",   "application/x-rar-compressed" },
    { "rtf",   "application/rtf" },
    { "tar",   "application/x-tar" },
    { "tgz",   "application/x-gzip" },
    { "xht",   "application/xhtml+xml" },
    { "xhtml", "application/xhtml+xml" },
    { "xls",   "application/vnd.ms-excel" },
    { "xml",   "application/xml" },
    { "zip",   "application/zip" },
    { NULL,    "application/octet-stream" } // Default mime

};

char* mimetype(char *file_path) {
    return ext_mimetype(file_extension(file_path));
}

char* ext_mimetype(char *ext) {
    char *ext_l = strlower(ext);

    int i = 0;
    for (i = 0; mimetypes[i].extension != NULL ; ++i) {
        if (strcmp(ext_l, mimetypes[i].extension) == 0) {
            return mimetypes[i].mime;
        }
    }

    free(ext_l);

    return "application/octet-stream";
}