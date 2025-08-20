#!/usr/bin/bash

rm -f aup_files_payloads/*
./aup_extract.py aup_files --verbose --extract aup_files_payloads &>aup_extract.log
