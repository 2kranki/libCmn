#!/bin/bash
# vi:nu:et:sts=4 ts=4 sw=4

rm ae.db
sqlite3 ae.db <create.sql.txt
sqlite3 ae.db <load_test.sql.txt

