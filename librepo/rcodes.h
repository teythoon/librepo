/* librepo - A library providing (libcURL like) API to downloading repository
 * Copyright (C) 2012  Tomas Mlcoch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef LR_RETURN_CODES_H
#define LR_RETURN_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Return/Error codes */
typedef enum {
    LRE_OK,                         /*!< everything is ok */
    LRE_BAD_FUNCTION_ARGUMENT,      /*!< bad function argument */

    /* lr_setopt specific */
    LRE_BAD_OPTION_ARGUMENT,        /*!< bad argument of the option */
    LRE_UNKNOWN_OPTION,             /*!< library doesn't know the option */
    LRE_CURL_SETOPT,                /*!< cURL doesn't know the option.
                                         Too old curl version? */
    LRE_ALREADYUSEDRESULT,          /*!< lr_Result object is not clean */
    LRE_INCOMPLETERESULT,           /*!< lr_Result doesn't contain all what
                                         is needed */
    LRE_CURL_DUP,                   /*!< cannot duplicate curl handle */
    LRE_CURL,                       /*!< cURL error. Use the
                                         lr_last_curl_error to get CURLcode */
    LRE_CURLM,                      /*!< cULR multi handle error. Use the
                                         lr_last_mculr_error to get CURLMcode */
    LRE_BAD_STATUS,                 /*!< HTTP or FTP returned status code which
                                         do not represent success
                                         (file doesn't exists, etc.) */
    LRE_NOTLOCAL,                   /*!< URL is not a local address */
    LRE_CANNOT_CREATE_DIR,          /*!< cannot create a directory in output
                                         dir (the directory already exists?) */
    LRE_IO,                         /*!< input output error */
    LRE_ML_BAD,                     /*!< bad mirrorlist/metalink file
                                         (metalink doesn't contain needed file,
                                         mirrorlist doesn't contain urls, ..) */
    LRE_ML_XML,                     /*!< metalink XML parse error */
    LRE_BAD_CHECKSUM,               /*!< bad checksum */
    LRE_REPOMD_XML,                 /*!< repomd XML parse error */
    LRE_NOURL,                      /*!< no usable URL found */
    LRE_CANNOT_CREATE_TMP,          /*!< cannot create tmp directory */
    LRE_UNKNOWN_CHECKSUM,           /*!< unknown type of checksum is need to
                                         calculate to verify one or more file */
    LRE_UNKNOWN_ERROR,              /*!< unknown error - sentinel of
                                         error codes enum */
} lr_Rc; /*!< Return codes */

#ifdef __cplusplus
}
#endif

#endif
