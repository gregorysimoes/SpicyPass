/*  load.hpp
 *
 *
 *  Copyright (C) 2020 Jfreegman <Jfreegman@gmail.com>
 *
 *  This file is part of SpicyPass.
 *
 *  SpicyPass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SpicyPass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SpicyPass.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LOAD
#define LOAD

#if defined(_WIN32)
    #include <windows.h>
    #include <io.h>
#else
    #include <unistd.h>
    #include <pwd.h>
#endif // _WIN32

#include "spicy.hpp"
#include "crypto.hpp"

#define PASS_STORE_HEADER_SIZE (CRYPTO_HASH_SIZE + CRYPTO_SALT_SIZE + 1)

/*
 * Attempts to validate password, decrypt password store, and load it into `p`.
 *
 * Return 0 on success.
 * Return -1 on file related error.
 * Return -2 if password is invalid.
 * Return -3 on crypto related error.
 * Return -4 on bad file format.
 */
int load_password_store(Pass_Store &p, const unsigned char *password, size_t length);

/*
 * Saves encrypted contents of pass store to disk.
 *
 * This function is atomic: changes will only be made to the pass store file upon success.
 *
 * Return 0 on success.
 * Return -1 if path is invalid.
 * Return -2 if file encryption fails.
 * Return -3 if file save operation fails.
 */
int save_password_store(Pass_Store &p);

/*
 * Return 1 if pass_store file does not exist or is empty.
 * Return 0 if pass_store file exists.
 * Return -1 if invalid path.
 * Return -2 if file cannot be opened.
 */
int first_time_run(void);

/*
 * Adds a header to the beginning of pass store file.
 *
 * This funciton should only be called when the pass store file is empty.
 *
 * Return 0 on success.
 * Return -1 on failure.
 */
int init_pass_hash(const unsigned char *password, size_t length);

/*
 * Initializes `p` with a new encryption key derived from `password`, as well as a
 * new key salt and password hash. Changes are written to file.
 *
 * Return 0 on sucess.
 * Return -1 on crypto related error.
 * Return -2 if `p` fails to update.
 * Return -3 on save failure.
 * Return PASS_STORE_LOCKED if pass store is locked.
 */
int update_crypto(Pass_Store &p, const unsigned char *password, size_t length);

#endif // LOAD
