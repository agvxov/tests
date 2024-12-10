// @BAKE gcc -o finalize_reprepare finalize_reprepare.c -lsqlite3

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DB_NAME "test.db"
#define ITERATIONS 10000

void handle_error(int rc, sqlite3 *db) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
}

void finalize_reprepare_performance() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "INSERT INTO test (value) VALUES (?);";

    rc = sqlite3_open(DB_NAME, &db);
    handle_error(rc, db);

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);", NULL, NULL, NULL);
    handle_error(rc, db);

    for (int i = 0; i < ITERATIONS; i++) {
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        handle_error(rc, db);

        rc = sqlite3_bind_text(stmt, 1, "test", -1, SQLITE_STATIC);
        handle_error(rc, db);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) handle_error(rc, db);

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
}

int main() {
    finalize_reprepare_performance();
    return 0;
}
